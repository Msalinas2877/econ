#include "cbase.h"
#include "econ_item.h"
//=========================================================================
//|	Create() actually looks through all the Shared Object types, but i only
//| want to implement the inventory, hence why i will only support CEconitem
//=========================================================================
GCSDK::CSharedObject* GCSDK::CSharedObject::Create( SharedObjectType Type )
{
	if ( Type == SO_TYPE_ITEM )
		return new CEconItem;
	return NULL;
}

bool GCSDK::CSharedObject::BIsKeyEqual( CSharedObject * const pSO )
{
	return false;
}

bool GCSDK::CSharedObject::BShouldDeleteByCache()
{
	return true;
}

SharedObjectType GCSDK::CSharedObject::GetType() const
{
	return SO_TYPE_INVALID;
}
