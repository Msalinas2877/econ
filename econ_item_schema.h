#ifndef ECON_ITEM_SCHEMA_H
#define ECON_ITEM_SCHEMA_H
#ifdef _WIN32
#pragma once
#endif
#include "tier1/utldict.h"
#include "tier1/utlbuffer.h"
#include "tier1/utlrbtree.h"
#include "tier1/utlmap.h"

class CEconItemDefinition
{
public:
	virtual bool BInitFromKV( KeyValues* kv, CUtlVector< CUtlString >* errorbuffer );
	virtual bool BInitItemMappings( CUtlVector< CUtlString >* errorbuffer ) { return true; }
	KeyValues* const GetKeyValues() { return m_pKeyValues; }
private:
	KeyValues* m_pKeyValues;
public:
	bool	m_bEnabled;
	const char* m_szName;
	unsigned int m_uIndex;
	const char* m_szItemClass;
	const char* m_szItemName;
	const char* m_szItemTypeName;
	const char* m_szItemDescription;
	bool m_bBaseItem;
	const char* m_szModelPlayer;
	const char* m_szModelWorld;
	bool m_bAttachToHands;//152
	bool m_bAttachToHandsVmOnly;//153
	bool m_bFlipViewmodel;//154
	bool m_bActAsWearable;//154
	bool m_bActAsWeapon;//156
};

class CEconItemAttributeDefinition
{
public:
	virtual bool BInitFromKV( KeyValues* kv, CUtlVector< CUtlString >* errorbuffer );
private:
	KeyValues* m_pKeyValues;
public:
	unsigned int m_uIndex;
	const char* m_szName;
	int m_iHidden;
	int m_iForceOuputDescription;
	int m_iStoredAsInteger;
	bool m_bIsSetBonus;
	bool m_bCanAffectMarketName;
	bool m_bCanAffectRecipeComponentName;
	int m_iIsUserGenerated;
	int m_iEffectType;
	int m_iDescriptionFormat;
	const char* m_szDescriptionString;
	const char* m_szArmoryDesc;
	const char* m_szAttributeClass;
	bool m_bInstanceData;
};

class CEconItemSchema{
public:
	CEconItemSchema() { SetDefLessFunc( m_ItemsDefs ); SetDefLessFunc( m_BaseItemsDefs ); SetDefLessFunc( m_Prefabs ); }
	virtual bool BInit( const char* file, const char* path, CUtlVector< CUtlString >*  errorbuffer );
	virtual KeyValues* FindDefitionPrefab( const char* name );
	virtual CEconItemDefinition* GetItemDefinition( int index );
	const CUtlMap<int, CEconItemDefinition*, int> &GetBaseItemDefinitions()  { return m_BaseItemsDefs; }
private:
	virtual bool BInitTextBuffer( CUtlBuffer &buffer, CUtlVector< CUtlString >*  errorbuffer );
	virtual bool BInitSchema( KeyValues* pschema, CUtlVector< CUtlString >*  errorbuffer );
	virtual bool BPostSchemaInit( CUtlVector< CUtlString >*  errorbuffer );
	virtual bool BInitPrefabs( KeyValues* prefabs, CUtlVector< CUtlString >* errorbuffer );
	virtual bool BInitAttributes( KeyValues* attributes, CUtlVector< CUtlString >* errorbuffer );
	virtual bool BInitItems( KeyValues* items, CUtlVector< CUtlString >* errorbuffer );
	virtual bool BInitGameInfo( KeyValues* game_info, CUtlVector< CUtlString >* errorbuffer );
	virtual CEconItemDefinition* CreateEconItemDefinition() { return new CEconItemDefinition; }

	CEconItemDefinition* m_pDefaultItemDef = nullptr;

	KeyValues* m_pSchemaKV;
	CUtlMap<const char*, KeyValues*, int> m_Prefabs;
	CUtlMap<int, CEconItemDefinition*, int> m_BaseItemsDefs;
	CUtlMap<int, CEconItemAttributeDefinition*, int> m_Attributes;
	CUtlMap<int, CEconItemDefinition*, int> m_ItemsDefs;
};

#endif // ECON_ITEM_SCHEMA_H