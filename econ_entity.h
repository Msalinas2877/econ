#ifndef ECON_ENTITY_H
#define ECON_ENTITY_H

#ifdef _WIN32
#pragma once
#endif

#include "econ_item.h"
#include "econ_item_system.h"
#include "econ_item_view.h"

#ifdef CLIENT_DLL
#define CEconEntity C_EconEntity
class C_ViewmodelAttachmentModel;
#endif

class CEconEntity : public CBaseAnimating
{
public:
	DECLARE_CLASS( CEconEntity, CBaseAnimating );
	DECLARE_NETWORKCLASS();

#ifdef CLIENT_DLL
	virtual void Release();
	virtual bool AttachmentModelsShouldBeVisible() { return true; }
	virtual void UpdateAttachmentModels();
#endif
	int TranslateViewmodelHandActivity( int iActivity ) { return TranslateViewmodelHandActivityInternal( iActivity ); }
	virtual int TranslateViewmodelHandActivityInternal( int iActivity ) { return iActivity; }
	virtual void PlayAnimForPlaybackEvent( wearableanimplayback_t iPlayback ) {};
#ifdef CLIENT_DLL
	virtual void			OnDataChanged( DataUpdateType_t updateType );
	virtual bool WantsToOverrideViewmodelAttachments()	{ return false; }
	virtual bool	OnFireEvent( C_BaseViewModel *pViewModel, const Vector& origin, const QAngle& angles, int event, const char *options ) { return false; }
private:
	CHandle<C_ViewmodelAttachmentModel> m_pAttachment;
#endif
public: 
	CEconItemView m_Item;
};
#endif