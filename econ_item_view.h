#ifndef ECON_ITEM_VIEW_H
#define ECON_ITEM_VIEW_H

#include "econ_item_system.h"

#ifdef CLIENT_DLL
EXTERN_RECV_TABLE( DT_ScriptCreatedItem )
#else
EXTERN_SEND_TABLE( DT_ScriptCreatedItem )
#endif

class CEconItemView
{
public:
	DECLARE_CLASS_NOBASE( CEconItemView );
	DECLARE_EMBEDDED_NETWORKVAR();
	CEconItemView& operator=(const CEconItemView *itemcopy) { m_iItemDefinitionIndex = itemcopy->m_iItemDefinitionIndex; m_iItemDefinitionIndex = itemcopy->m_iAccountID; return *this; }
	void Init( int definitionindex, int minlevel = 0, int maxlevel = 0, uint32 accountid = 0 );

	const char* GetPlayerDisplayModel() const { return GetStaticData()->m_szModelPlayer; }
	const char* GetWorldDisplayModel() const { return GetStaticData()->m_szModelWorld; }

	CEconItemDefinition* GetStaticData() const { return GetItemSchema()->GetItemDefinition( m_iItemDefinitionIndex ); }

	virtual CEconItemDefinition* GetItemDefinition() { return GetStaticData(); }
	virtual int GetID()	{ return m_iItemDefinitionIndex; }
	virtual uint32 GetAccountID()	{ return m_iAccountID; }
private:
	CNetworkVar( uint, m_iItemDefinitionIndex );
	CNetworkVar( int, m_iEntityQuality );
	CNetworkVar( int, m_iEntityLevel );
	CNetworkVar( uint, m_iItemIDHigh );
	CNetworkVar( uint, m_iItemIDLow );
	CNetworkVar( uint32, m_iAccountID );
	CNetworkVar( bool, m_bInitialized );
	CNetworkVar( bool, m_bOnlyIterateItemViewAttributes );
};
#endif