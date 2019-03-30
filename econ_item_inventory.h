#ifndef ECON_ITEM_INVENTORY_H
#define ECON_ITEM_INVENTORY_H
#ifdef _WIN32
#pragma once
#endif
#include "igamesystem.h"
#include "steam/steamclientpublic.h"
#include "econ_item.h"
#include "econ_item_view.h"
#include "UtlSortVector.h"

class CPlayerInventory : public GCSDK::ISharedObjectListener
{
public:
	virtual void SOCreated( const CSteamID &SteamID, GCSDK::CSharedObject const* pSO, GCSDK::ESOCacheEvent SOCacheEvent );
	virtual void PreSOUpdate( const CSteamID &SteamID, GCSDK::ESOCacheEvent SOCacheEvent );
	virtual void SOUpdated( const CSteamID &SteamID, GCSDK::CSharedObject const* pSO, GCSDK::ESOCacheEvent SOCacheEvent );
	virtual void PostSOUpdate( const CSteamID &SteamID, GCSDK::ESOCacheEvent SOCacheEvent );
	virtual void SODestroyed( const CSteamID &SteamID, GCSDK::ESOCacheEvent SOCacheEvent );
	virtual void SOCacheSubscribed( const CSteamID &SteamID, GCSDK::ESOCacheEvent SOCacheEvent );
	virtual void SOCacheUnsubscribed( const CSteamID &SteamID, GCSDK::ESOCacheEvent SOCacheEvent );
	virtual void SOClear();
	virtual void RequestInventory( CSteamID SteamID );
	virtual void AddListener( GCSDK::ISharedObjectListener* pListener );
	virtual bool AddEconItem( CEconItem* pEconItem, bool a, bool b, bool c );
	virtual bool FilloutItemFromEconItem( CEconItemView* pEconItemView, CEconItem* pEconItem );
	virtual void ItemHasBeenUpdated( CEconItemView* pEconItemView, bool a, bool b );
	virtual void SendInventoryUpdateEvent();

private:
	CSteamID m_SteamID;
	CUtlSortVector<CEconItemView *> m_Items;
};

//This seems to containt one extra virtual pure function
//which is overriden by CTFPlayer::InventoryUpdated(CPlayerInventory *)
class IInventoryUpdateListener : public GCSDK::ISharedObjectListener
{
	virtual void SOCreated( const CSteamID &SteamID, GCSDK::CSharedObject const* pSO, GCSDK::ESOCacheEvent SOCacheEvent );
	virtual void PreSOUpdate( const CSteamID &SteamID, GCSDK::ESOCacheEvent SOCacheEvent );
	virtual void SOUpdated( const CSteamID &SteamID, GCSDK::CSharedObject const* pSO, GCSDK::ESOCacheEvent SOCacheEvent );
	virtual void PostSOUpdate( const CSteamID &SteamID, GCSDK::ESOCacheEvent SOCacheEvent );
	virtual void SODestroyed( const CSteamID &SteamID, GCSDK::ESOCacheEvent SOCacheEvent );
	virtual void SOCacheSubscribed( const CSteamID &SteamID, GCSDK::ESOCacheEvent SOCacheEvent );
	virtual void SOCacheUnsubscribed( const CSteamID &SteamID, GCSDK::ESOCacheEvent SOCacheEvent );

	virtual void InventoryUpdated( CPlayerInventory* pInventory ) = 0;
};

class CInventoryManager : public CAutoGameSystemPerFrame
{
public:
	virtual bool Init();
	virtual void PostInit();
	void PreInitGC();
	void PostInitGC();
	virtual void Shutdown();
	virtual void LevelInitPreEntity();
	virtual void LevelShutdownPostEntity();
	virtual void GetInventoryForAccount( uint iAccountID ); //Not sure about the parametter
	virtual void AddBaseItemCriteria();
	virtual void GetBackpackPositionFromBackend( uint iAccountID ); //whats this for?
	void SteamRequestInventory( CPlayerInventory* pInventory, CSteamID SteamID, IInventoryUpdateListener* pListener );
	void GameServerSteamAPIActivated();
};

#endif