#ifndef ECON_WEARABLE_H
#define ECON_WEARABLE_H

#define MAX_WEARABLES_SENT_FROM_SERVER 0

#ifdef CLIENT_DLL
#define CEconWearable C_EconWearable
#endif

struct wearableanimplayback_t
{
	int iStub;
};

class CEconWearable : public CBaseAnimating
{
public:
	DECLARE_CLASS( CEconWearable, CBaseAnimating );
	DECLARE_NETWORKCLASS();

	void Equip( CBaseEntity* entity ) {};
	void UnEquip( CBaseEntity* entity ) {};
	void PlayAnimForPlaybackEvent( wearableanimplayback_t anim ) {};
};
#endif