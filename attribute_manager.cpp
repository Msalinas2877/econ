#include "cbase.h"
#include "attribute_manager.h"

BEGIN_NETWORK_TABLE_NOBASE( CAttributeManager, DT_AttributeManager )
END_NETWORK_TABLE();

BEGIN_NETWORK_TABLE_NOBASE( CAttributeContainer, DT_AttributeContainer )
#ifdef CLIENT_DLL
RecvPropDataTable( RECVINFO_DT( m_Item ), 0, &REFERENCE_RECV_TABLE( DT_ScriptCreatedItem ) )
#else
SendPropDataTable( SENDINFO_DT( m_Item ), &REFERENCE_SEND_TABLE( DT_ScriptCreatedItem ) )
#endif
END_NETWORK_TABLE();

void CAttributeManager::StopProvidingTo( CBaseEntity * pEntity )
{
}
