#ifndef ATTRIBUTE_MANAGER_H
#define ATTRIBUTE_MANAGER_H
#ifdef _WIN32
#pragma once
#endif

// CAttribute_String is defined on protobufs
// if you have protobufs included please define PBAttributeString and change the include path
#ifdef PBAttributeString
#include "generated_proto/tf_gcmessages.pb.h"
#else
class CAttribute_String;
#warning You need protobuf messages to use CAttribute_String
#endif

#define CALL_ATTRIB_HOOK_INT( value, attribute ) \
	value = CAttributeManager::AttribHookValue<int>( value, #attribute, (const CBaseEntity*)this );

#define CALL_ATTRIB_HOOK_FLOAT( value, attribute ) \
	value = CAttributeManager::AttribHookValue<float>( value, #attribute, (const CBaseEntity*)this );

#define CALL_ATTRIB_HOOK_STRING( value, attribute ) \
	value = CAttributeManager::AttribHookValue<CAttribute_String>( value, #attribute, (const CBaseEntity*)this );

#define CALL_ATTRIB_HOOK_INT_ON_OTHER( entity, value, attribute ) \
	value = CAttributeManager::AttribHookValue<int>( value, #attribute, (const CBaseEntity*)entity );

#define CALL_ATTRIB_HOOK_FLOAT_ON_OTHER( entity, value, attribute ) \
	value = CAttributeManager::AttribHookValue<float>( value, #attribute, (const CBaseEntity*)entity );

#define CALL_ATTRIB_HOOK_STRING_ON_OTHER( value, attribute ) \
	value = CAttributeManager::AttribHookValue<CAttribute_String>( value, #attribute, (const CBaseEntity*)entity );

#ifdef CLIENT_DLL
EXTERN_RECV_TABLE( DT_AttributeManager )
#else
EXTERN_SEND_TABLE( DT_AttributeManager )
#endif

class CAttributeManager
{
public:
	DECLARE_CLASS_NOBASE( CAttributeManager );
	DECLARE_EMBEDDED_NETWORKVAR();

	template <typename T>
	static T AttribHookValue( T value, const char* pszAttribute, const CBaseEntity *pEntity, CUtlVector<CBaseEntity*> *pEntities = NULL, bool bUnknown = true )
	{
		return value;
	}

	void StopProvidingTo( CBaseEntity* pEntity );

	CNetworkVarEmbedded( CEconItemView, m_Item );
};

class CAttributeContainer : public CAttributeManager
{

};

class CAttributeList
{

};

#endif // ATTRIBUTE_MANAGER_H