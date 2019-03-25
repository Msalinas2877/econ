#include "cbase.h"
#include "econ_item_inventory.h"
#include "econ_item.h"
#include "tf_gc_manager.h"

void IInventoryUpdateListener::SOCreated( const CSteamID & SteamID, GCSDK::CSharedObject const * SO, GCSDK::ESOCacheEvent SOCacheEvent )
{
	InventoryUpdated( NULL );
}

void IInventoryUpdateListener::PreSOUpdate( const CSteamID & SteamID, GCSDK::ESOCacheEvent SOCacheEvent )
{
	//Do nothing
}

void IInventoryUpdateListener::SOUpdated( const CSteamID & SteamID, GCSDK::CSharedObject const * SO, GCSDK::ESOCacheEvent SOCacheEvent )
{
	//Do nothing
}

void IInventoryUpdateListener::PostSOUpdate( const CSteamID & SteamID, GCSDK::ESOCacheEvent SOCacheEvent )
{
	InventoryUpdated( NULL );
}

void IInventoryUpdateListener::SODestroyed( const CSteamID & SteamID, GCSDK::ESOCacheEvent SOCacheEvent )
{
	InventoryUpdated( NULL );
}

void IInventoryUpdateListener::SOCacheSubscribed( const CSteamID & SteamID, GCSDK::ESOCacheEvent SOCacheEvent )
{
	InventoryUpdated( NULL );
}

void IInventoryUpdateListener::SOCacheUnsubscribed( const CSteamID & SteamID, GCSDK::ESOCacheEvent SOCacheEvent )
{
	InventoryUpdated( NULL );
}

bool CInventoryManager::Init()
{
	ItemSystem()->Init();
	return true;
}

void CInventoryManager::PostInit()
{
	ItemSystem()->PostInit();
}

void CInventoryManager::PreInitGC()
{
}

void CInventoryManager::PostInitGC()
{
}

void CInventoryManager::Shutdown()
{

}

void CInventoryManager::LevelInitPreEntity()
{
}

void CInventoryManager::LevelShutdownPostEntity()
{
}

void CInventoryManager::GetInventoryForAccount( uint iAccountID )
{
}

void CInventoryManager::AddBaseItemCriteria()
{
}

void CInventoryManager::GetBackpackPositionFromBackend( uint iAccountID )
{
}

void CInventoryManager::SteamRequestInventory( CPlayerInventory * pInventory, CSteamID SteamID, IInventoryUpdateListener * pListener )
{
	pInventory->RequestInventory( SteamID );
	if ( pListener )
		pInventory->AddListener( pListener );
}

void CInventoryManager::GameServerSteamAPIActivated()
{
}

void CPlayerInventory::SOCreated( const CSteamID & SteamID, GCSDK::CSharedObject const * pSO, GCSDK::ESOCacheEvent SOCacheEvent )
{
	AddEconItem( (CEconItem*)pSO, true, true, true );
	SendInventoryUpdateEvent();

}

void CPlayerInventory::PreSOUpdate( const CSteamID & SteamID, GCSDK::ESOCacheEvent SOCacheEvent )
{
	//Do nothing.
}

void CPlayerInventory::SOUpdated( const CSteamID & SteamID, GCSDK::CSharedObject const * pSO, GCSDK::ESOCacheEvent SOCacheEvent )
{
}

void CPlayerInventory::PostSOUpdate( const CSteamID & SteamID, GCSDK::ESOCacheEvent SOCacheEvent )
{
	//Do nothing.
}

void CPlayerInventory::SODestroyed( const CSteamID & SteamID, GCSDK::ESOCacheEvent SOCacheEvent )
{
}

void CPlayerInventory::SOCacheSubscribed( const CSteamID & SteamID, GCSDK::ESOCacheEvent SOCacheEvent )
{

}

void CPlayerInventory::SOCacheUnsubscribed( const CSteamID & SteamID, GCSDK::ESOCacheEvent SOCacheEvent )
{
}

void CPlayerInventory::SOClear()
{
}

void CPlayerInventory::RequestInventory( CSteamID SteamID )
{
	if ( m_SteamID != SteamID )
		SOClear();

	m_SteamID = SteamID;
	GCManager()->AddSOCacheListener( SteamID, this );
}

void CPlayerInventory::AddListener( GCSDK::ISharedObjectListener * pListener )
{
	GCManager()->AddSOCacheListener( m_SteamID, pListener );
}

bool CPlayerInventory::AddEconItem( CEconItem * pEconItem, bool a, bool b, bool c )
{
	CEconItemView EconItemView;
	if ( FilloutItemFromEconItem( &EconItemView, pEconItem ) )
	{
		m_Items.Insert( &EconItemView );
		ItemHasBeenUpdated( &EconItemView, a, b );
		return true;
	}
	return false;
}

bool CPlayerInventory::FilloutItemFromEconItem( CEconItemView * pEconItemView, CEconItem * pEconItem )
{
	return false;
}

void CPlayerInventory::ItemHasBeenUpdated( CEconItemView * pEconItemView, bool a, bool b )
{
}

void CPlayerInventory::SendInventoryUpdateEvent()
{
#ifdef CLIENT_DLL

#endif
}
