#include "cbase.h"
#include "econ_item_schema.h"
#include "econ_item_system.h"
#include "filesystem.h"
#include "keyvalues.h"

#define SchemaError(error)	\
		CUtlString mystring;	\
		mystring.Format(error);	\
		errorbuffer->AddToTail(mystring);	\
		mystring.Purge();	\
		return false;	\

#define SchemaErrorFormat(error, etc)	\
		CUtlString mystring;	\
		mystring.Format(error, etc);	\
		errorbuffer->AddToTail(mystring);	\
		mystring.Purge();	\
		return false;	\

void MergeDefinitionPrefab( KeyValues* kv1, KeyValues* kv2 )
{
	const char* prefabvalues = kv2->GetString( "prefab", NULL);
	if ( prefabvalues )
	{
		CUtlVector<char*, CUtlMemory<char*> > prefabs;
		Q_SplitString( prefabvalues, " ", prefabs );
		for ( int i = 0; i < prefabs.Count(); ++i )
		{
			KeyValues* pPrefabKv = GetItemSchema()->FindDefitionPrefab( prefabs[i] );
			if ( pPrefabKv )
				return MergeDefinitionPrefab( kv1, pPrefabKv );
		}
	}
	kv1->RecursiveMergeKeyValues( kv2 );
}

bool CEconItemDefinition::BInitFromKV( KeyValues* kv, CUtlVector< CUtlString >* errorbuffer )
{
	m_pKeyValues = new KeyValues( kv->GetName() );
	MergeDefinitionPrefab( m_pKeyValues, kv );
	m_bEnabled = m_pKeyValues->GetBool( "enabled" );
	m_szName = m_pKeyValues->GetString( "name" );
	m_uIndex = V_atoi( m_pKeyValues->GetName() );
	m_szItemClass = m_pKeyValues->GetString( "item_class" );
	m_szItemName = m_pKeyValues->GetString( "item_name" );
	m_szItemTypeName = m_pKeyValues->GetString( "item_type_name" );
//	const char* m_szItemDescription;
	m_bBaseItem = m_pKeyValues->GetBool( "baseitem" );
	m_szModelPlayer = m_pKeyValues->GetString( "model_player" );
	m_szModelWorld = m_pKeyValues->GetString( "model_world" );
	m_bAttachToHands = m_pKeyValues->GetBool( "attach_to_hands" );
	m_bAttachToHandsVmOnly = m_pKeyValues->GetBool( "attach_to_hands_vm_only" );
	m_bFlipViewmodel = m_pKeyValues->GetBool( "flip_viewmodel" );
	m_bActAsWearable = m_pKeyValues->GetBool( "act_as_wearable" );
	m_bActAsWeapon = m_pKeyValues->GetBool( "act_as_weapon" );
	return true;
}

bool CEconItemAttributeDefinition::BInitFromKV( KeyValues * kv, CUtlVector<CUtlString>* errorbuffer )
{
	m_pKeyValues = kv->MakeCopy();
	const char* name = m_pKeyValues->GetName();
	m_uIndex = V_atoi( name );
	m_szName = m_pKeyValues->GetString( "name", "(unnamed)" );
	m_iHidden = m_pKeyValues->GetInt( "hidden" );
	m_iForceOuputDescription = m_pKeyValues->GetInt( "force_output_description" );
	m_iStoredAsInteger = m_pKeyValues->GetInt( "hidden" );
	return true;
}

bool CEconItemSchema::BInit( const char* file, const char* path, CUtlVector< CUtlString >* errorbuffer )
{
	//The signature verification should go here but i
	//don´t really see the point of it on a mod

	CUtlBuffer buffer(0, 0, CUtlBuffer::READ_ONLY | CUtlBuffer::TEXT_BUFFER);
	if ( g_pFullFileSystem->ReadFile( file, path, buffer ) )
	{
		BInitTextBuffer( buffer, errorbuffer );
		return true;
	}
	return false;
}

CEconItemDefinition* CEconItemSchema::GetItemDefinition( int index )
{
	int i = m_ItemsDefs.Find( index );
	return m_ItemsDefs.Element( i );
}

KeyValues* CEconItemSchema::FindDefitionPrefab( const char* name )
{
	int i = m_Prefabs.Find( name );
	return m_Prefabs.Element(i);
}

bool CEconItemSchema::BInitTextBuffer( CUtlBuffer &buffer, CUtlVector< CUtlString >*  errorbuffer )
{
	m_pSchemaKV = new KeyValues( "CEconItemSchema" );
	if ( m_pSchemaKV->LoadFromBuffer("scripts/items/items_game.txt", buffer) )
	{
		if ( BInitSchema( m_pSchemaKV, errorbuffer ) )
		{
			return BPostSchemaInit(errorbuffer);
		}
	}
	return false;
}

#define ParseSchemaSectionWithoutError(name, function)	\
		KeyValues* key##name = schema->FindKey(#name);	\
		if( key##name )	\
		{	\
			function(key##name, errorbuffer);	\
		}	\
		else	\
		{	\
			return false;	\
		}	\

#define ParseSchemaSection(name, function)	\
		KeyValues* key##name = schema->FindKey(#name);	\
		if( key##name )	\
		{	\
			function(key##name, errorbuffer);	\
		}	\
		else	\
		{	\
			SchemaError("Required key \""###name##"\" missing. \n")	\
		}	\
	
bool CEconItemSchema::BInitSchema( KeyValues* schema, CUtlVector< CUtlString >*  errorbuffer )
{
	ParseSchemaSectionWithoutError( prefabs, BInitPrefabs );
	ParseSchemaSection( attributes, BInitAttributes );
	ParseSchemaSection( items, BInitItems );
	return true;
}

bool CEconItemSchema::BPostSchemaInit( CUtlVector< CUtlString >*  errorbuffer )
{
	return true;
}

bool CEconItemSchema::BInitPrefabs( KeyValues* prefabs, CUtlVector< CUtlString >*  errorbuffer )
{
	FOR_EACH_TRUE_SUBKEY( prefabs, prefab )
	{	
		const char* name = prefab->GetName();
		if  ( m_Prefabs.Find( name ) > -1 )
		{
			SchemaErrorFormat( "Duplicate prefab name (%s). \n", name );
		}
		m_Prefabs.Insert( name, prefab );
	}
	return true;
}

bool CEconItemSchema::BInitAttributes( KeyValues* attributes, CUtlVector< CUtlString >* errorbuffer )
{
	FOR_EACH_TRUE_SUBKEY( attributes, attribute )
	{
		const char* name = attribute->GetName();
		int uIndex = V_atoi( name );
		if  ( m_Attributes.Find( uIndex ) != m_Attributes.InvalidIndex() )
		{
			SchemaErrorFormat( "Duplicate attribute definition index (%d). \n", uIndex );
		}
		if ( uIndex < 0 )
		{
			SchemaErrorFormat( "Attribute definition index %d must be greater than or equal to zero", uIndex );
		}
		m_Attributes.Insert( uIndex );
		if ( m_Attributes[uIndex]->BInitFromKV( attribute, errorbuffer ) )
			return NULL;
	}
	return true;
}

bool CEconItemSchema::BInitItems( KeyValues* items, CUtlVector< CUtlString >* errorbuffer )
{
	FOR_EACH_TRUE_SUBKEY( items, item )
	{
		const char* name = item->GetName();
		if ( Q_stricmp( name, "default") != 0 )
		{
			int uIndex = V_atoi( name );
			if ( m_ItemsDefs.Find( uIndex ) != m_ItemsDefs.InvalidIndex() )
			{
				SchemaErrorFormat( "Duplicate item definition (%d)", uIndex );
			}
			if ( uIndex < 0 )
			{
				SchemaErrorFormat( "Item definition index %d must be greater than or equal to zero", uIndex );
			}
			CEconItemDefinition* pItemdef = CreateEconItemDefinition();
			m_ItemsDefs.Insert( uIndex, pItemdef );
			if ( !pItemdef->BInitFromKV( item, errorbuffer ) )
				return false;
			
			if (pItemdef->m_bBaseItem)
			{
				m_BaseItemsDefs.Insert( uIndex, pItemdef );
			}
		}
		else
		{
			if ( m_pDefaultItemDef != nullptr )
			{
				SchemaError("Duplicate 'default' item definition.")
			}
			CEconItemDefinition* pItemdef = CreateEconItemDefinition();
			m_pDefaultItemDef = pItemdef;
			pItemdef->BInitFromKV( item, errorbuffer );
		}
	}
	return true;
}

bool CEconItemSchema::BInitGameInfo( KeyValues* game_info, CUtlVector< CUtlString >*  errorbuffer )
{
	return true;
}