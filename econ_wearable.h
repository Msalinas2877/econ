#ifndef ECON_WEARABLE_H
#define ECON_WEARABLE_H

#ifdef CLIENT_DLL
#define CEconWearable C_EconWearable
#endif

class CEconWearable : public CBaseAnimating
{
public:
	DECLARE_CLASS( CEconWearable, CBaseAnimating );
	DECLARE_NETWORKCLASS();
};
#endif