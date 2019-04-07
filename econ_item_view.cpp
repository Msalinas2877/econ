#include "cbase.h"
#include "econ_item_view.h"
#include "econ_item_schema.h"
#include "steam/steam_api.h"

BEGIN_NETWORK_TABLE_NOBASE( CEconItemView, DT_ScriptCreatedItem )
#ifdef CLIENT_DLL
	RecvPropInt( RECVINFO( m_iItemDefinitionIndex ) ),
	RecvPropInt( RECVINFO( m_iEntityQuality ) ),
	RecvPropInt( RECVINFO( m_iEntityLevel ) ),
	RecvPropInt( RECVINFO( m_iItemIDHigh ) ),
	RecvPropInt( RECVINFO( m_iItemIDLow ) ),
	RecvPropBool( RECVINFO( m_bInitialized ) ),
	RecvPropBool( RECVINFO( m_bOnlyIterateItemViewAttributes ) )
	
#else
	SendPropInt( SENDINFO( m_iItemDefinitionIndex ) ),
	SendPropInt( SENDINFO( m_iEntityQuality ) ),
	SendPropInt( SENDINFO( m_iEntityLevel ) ),
	SendPropInt( SENDINFO( m_iItemIDHigh ) ),
	SendPropInt( SENDINFO( m_iItemIDLow ) ),
	SendPropBool( SENDINFO( m_bInitialized ) ),
	SendPropBool( SENDINFO( m_bOnlyIterateItemViewAttributes ) )
#endif
END_NETWORK_TABLE()

CEconItemView::CEconItemView()
{
	m_iItemDefinitionIndex = -1;
}

void CEconItemView::Init( int definitionindex, int minlevel, int maxlevel, uint32 accountid )
{
	m_iItemDefinitionIndex = definitionindex;
	m_iAccountID = accountid;
	GetItemSchema()->GetItemDefinition( definitionindex );
};