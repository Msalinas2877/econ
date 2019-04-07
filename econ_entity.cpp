#include "cbase.h"
#include "econ_entity.h"

#ifdef CLIENT_DLL
void FormatViewModelAttachment( Vector &vOrigin, bool bInverse );
#endif

IMPLEMENT_NETWORKCLASS_ALIASED( EconEntity, DT_EconEntity );

BEGIN_NETWORK_TABLE( CEconEntity, DT_EconEntity )
#ifdef CLIENT_DLL
	RecvPropDataTable( RECVINFO_DT( m_AttributeManager ), 0, &REFERENCE_RECV_TABLE( DT_AttributeContainer ) )
#else
	SendPropDataTable( SENDINFO_DT( m_AttributeManager ), &REFERENCE_SEND_TABLE( DT_AttributeContainer ) )
#endif
END_NETWORK_TABLE();

#ifdef CLIENT_DLL
void CEconEntity::UpdateAttachmentModels()
{
	if ( m_AttributeManager.m_Item.GetStaticData() && ( m_AttributeManager.m_Item.GetStaticData()->m_bAttachToHands || m_AttributeManager.m_Item.GetStaticData()->m_bAttachToHandsVmOnly ) )
	{
		if ( AttachmentModelsShouldBeVisible() )
		{
			if ( m_pAttachment != NULL )
			{
				m_pAttachment->m_nSkin = GetSkin();
				m_pAttachment->RemoveEffects(EF_NODRAW);
			}
			else
			{
				CBaseViewModel *pVM = C_BasePlayer::GetLocalPlayer()->GetViewModel();
	
				C_ViewmodelAttachmentModel *pAttachment = new C_ViewmodelAttachmentModel;
				pAttachment->SetOwnerEntity( this );
				if ( pAttachment->InitializeAsClientEntity( m_AttributeManager.m_Item.GetPlayerDisplayModel(), RENDER_GROUP_VIEW_MODEL_OPAQUE ) == false )
				{
					pAttachment->Remove();
					return;
				}
				m_pAttachment = pAttachment;
				m_pAttachment->SetParent( pVM );
				m_pAttachment->SetLocalOrigin( vec3_origin );
				m_pAttachment->UpdateVisibility();
			}
		}
		else
		{
			if ( m_pAttachment != NULL )
			{
				m_pAttachment->AddEffects(EF_NODRAW);
			}
		}
	}
};

void CEconEntity::Release()
{
	if ( m_pAttachment )
	{
		m_pAttachment->Release();
	}
	BaseClass::Release();
};

void CEconEntity::OnDataChanged( DataUpdateType_t updateType )
{
	BaseClass::OnDataChanged( updateType );
	return UpdateAttachmentModels();
};


bool C_ViewmodelAttachmentModel::InitializeAsClientEntity( const char *pszModelName, RenderGroup_t renderGroup )
{
	if ( BaseClass::InitializeAsClientEntity( pszModelName, renderGroup ) )
	{
		AddEffects( EF_BONEMERGE );
		AddEffects( EF_BONEMERGE_FASTCULL );
		AddEffects( EF_NODRAW );
		return true;
	}
	return false;
}

int C_ViewmodelAttachmentModel::InternalDrawModel( int flags )
{
	CMatRenderContextPtr pRenderContext( materials );
	if ( ((CBaseViewModel *)GetOwnerEntity())->ShouldFlipViewModel() )
		pRenderContext->CullMode( MATERIAL_CULLMODE_CW );

	int ret = BaseClass::InternalDrawModel( flags );

	pRenderContext->CullMode( MATERIAL_CULLMODE_CCW );

	return ret;
}

bool C_ViewmodelAttachmentModel::OnPostInternalDrawModel( ClientModelRenderInfo_t *pInfo )
{
	return BaseClass::OnPostInternalDrawModel( pInfo );
}

void C_ViewmodelAttachmentModel::StandardBlendingRules( CStudioHdr *pStudioHdr, Vector pos[], QuaternionAligned q[], float currentTime, int boneMask )
{
	BaseClass::StandardBlendingRules( pStudioHdr, pos, q, currentTime, boneMask );
}

void C_ViewmodelAttachmentModel::FormatViewModelAttachment( int nAttachment, matrix3x4_t &attachmentToWorld )
{
	Vector vecOrigin;
	MatrixPosition( attachmentToWorld, vecOrigin );
	::FormatViewModelAttachment( vecOrigin, false );
	PositionMatrix( vecOrigin, attachmentToWorld );
}

int C_ViewmodelAttachmentModel::GetSkin( void )
{
	return BaseClass::GetSkin();
}
#endif