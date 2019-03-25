#ifndef ECON_ITEM_H
#define ECON_ITEM_H
#ifdef _WIN32
#pragma once
#endif

struct wearableanimplayback_t
{
	int iStub;
};

class CAttributeList
{
public:
//	DECLARE_PREDICTABLE();
	DECLARE_CLASS_NOBASE( CAttributeList );
	DECLARE_EMBEDDED_NETWORKVAR();
};

// To Do: Add more types
enum SharedObjectType
{
	SO_TYPE_INVALID,
	SO_TYPE_ITEM,		//CEconItem
	SO_TYPE_PLAYERINFO,	//CTFPlayerInfo
	SO_TYPE_CLAIMCODE,	//CEconClaimCode
};

namespace GCSDK 
{
	class CSharedObject
	{
	public:
		static CSharedObject* Create( SharedObjectType Type );
		bool BIsKeyEqual( CSharedObject* const pSO );
		bool BShouldDeleteByCache();
		SharedObjectType GetType() const;
	};
	typedef int ESOCacheEvent;

	//According to IDA, this has 7 pure virtual functions
	class ISharedObjectListener
	{
	public:
		virtual void SOCreated( const CSteamID &SteamID, CSharedObject const* SO, ESOCacheEvent SOCacheEvent ) = 0;
		virtual void PreSOUpdate( const CSteamID &SteamID, ESOCacheEvent SOCacheEvent ) = 0;
		virtual void SOUpdated( const CSteamID &SteamID, CSharedObject const* SO, ESOCacheEvent SOCacheEvent ) = 0;
		virtual void PostSOUpdate( const CSteamID &SteamID, ESOCacheEvent SOCacheEvent ) = 0;
		virtual void SODestroyed( const CSteamID &SteamID, ESOCacheEvent SOCacheEvent ) = 0;
		virtual void SOCacheSubscribed( const CSteamID &SteamID, ESOCacheEvent SOCacheEvent ) = 0;
		virtual void SOCacheUnsubscribed( const CSteamID &SteamID, ESOCacheEvent SOCacheEvent ) = 0;
	};
};

class CEconItem : public GCSDK::CSharedObject
{
public:
	SharedObjectType GetType() const { return SO_TYPE_ITEM; }
};
#endif