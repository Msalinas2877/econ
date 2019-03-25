#include "cbase.h"
#include "econ_item_system.h"

CEconItemSytem* ItemSystem()
{
	static CEconItemSytem *pSystem;
	if ( !pSystem )
	{
		pSystem = new CEconItemSytem();
#ifdef TF_EP
		pSystem->m_pItemSchema = new CTFItemSchema(); 
#else
		pSystem->m_pItemSchema = new CEconItemSchema(); 
#endif
	}
	return pSystem;
}

CEconItemSchema* GetItemSchema()
{
	return ItemSystem()->GetItemSchema();
}

void CEconItemSytem::Init()
{
	if ( m_bParsed )
		return;

	ParseItemSchemaFile( "scripts/items/items_game.txt" );
	m_bParsed = true;
}

void CEconItemSytem::ParseItemSchemaFile( const char* file )
{
	CUtlVector< CUtlString > errorbuffer;
	if ( !m_pItemSchema->BInit( file, "GAME", &errorbuffer ) && errorbuffer.Count() > 0 )
	{
		for (int i = 0; errorbuffer.Count() > i; i++)
		{
			Error( "%s\n", errorbuffer.Element(i).Get() );
		}
	}
	errorbuffer.Purge();
}