//===== Copyright � 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $Header: $
// $NoKeywords: $
//===========================================================================//

#include "BaseVSShader.h"

#include "unlitgeneric_vs30.inc"
#include "unlitgeneric_ps30.inc"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

BEGIN_VS_SHADER_FLAGS( DebugNormalMap, "Help for DebugNormalMap", SHADER_NOT_EDITABLE )
			  
	BEGIN_SHADER_PARAMS
		SHADER_PARAM( BUMPMAP, SHADER_PARAM_TYPE_TEXTURE, "shadertest/WorldDiffuseBumpMap_bump", "bump map" )
		SHADER_PARAM( BUMPFRAME, SHADER_PARAM_TYPE_INTEGER, "0", "frame number for $bumpmap" )
		SHADER_PARAM( BUMPTRANSFORM, SHADER_PARAM_TYPE_MATRIX, "center .5 .5 scale 1 1 rotate 0 translate 0 0", "$bumpmap texcoord transform" )
	END_SHADER_PARAMS

	SHADER_INIT_PARAMS()
	{
		SET_FLAGS2( MATERIAL_VAR2_SUPPORTS_HW_SKINNING );
	}

	SHADER_INIT
	{
	}

	SHADER_FALLBACK
	{
		if( g_pHardwareConfig->GetDXSupportLevel() < 80 )
		{
//			Assert( 0 );
			return "Wireframe";
		}
		return 0;
	}

	SHADER_DRAW
	{
		SHADOW_STATE
		{
			pShaderShadow->EnableTexture( SHADER_SAMPLER0, true );

			// Set stream format (note that this shader supports compression)
			unsigned int flags = VERTEX_POSITION | VERTEX_FORMAT_COMPRESSED;
			int nTexCoordCount = 1;
			int userDataSize = 0;
			pShaderShadow->VertexShaderVertexFormat( flags, nTexCoordCount, NULL, userDataSize );

			if( g_pHardwareConfig->GetDXSupportLevel() >= 90 )
			{
				DECLARE_STATIC_VERTEX_SHADER( unlitgeneric_vs30 );
				SET_STATIC_VERTEX_SHADER( unlitgeneric_vs30 );

				DECLARE_STATIC_PIXEL_SHADER( unlitgeneric_ps30 );
				SET_STATIC_PIXEL_SHADER( unlitgeneric_ps30 );
			}
		}
		DYNAMIC_STATE
		{
			if ( params[BUMPMAP]->IsTexture() )
			{
				BindTexture( SHADER_SAMPLER0, BUMPMAP, BUMPFRAME );
			}
			else
			{
				pShaderAPI->BindStandardTexture( SHADER_SAMPLER0, TEXTURE_NORMALMAP_FLAT );
			}
			SetVertexShaderTextureTransform( VERTEX_SHADER_SHADER_SPECIFIC_CONST_0, BUMPTRANSFORM );

			if( g_pHardwareConfig->GetDXSupportLevel() >= 90 )
			{
				BOOL bShaderConstants[1] = { false };
				pShaderAPI->SetBooleanVertexShaderConstant( VERTEX_SHADER_SHADER_SPECIFIC_BOOL_CONST_0, bShaderConstants, 1 );

				DECLARE_DYNAMIC_VERTEX_SHADER( unlitgeneric_vs30 );
				SET_DYNAMIC_VERTEX_SHADER_COMBO( DOWATERFOG, pShaderAPI->GetSceneFogMode() == MATERIAL_FOG_LINEAR_BELOW_FOG_Z );
				SET_DYNAMIC_VERTEX_SHADER_COMBO( SKINNING, pShaderAPI->GetCurrentNumBones() > 0 );
				SET_DYNAMIC_VERTEX_SHADER_COMBO( COMPRESSED_VERTS, (int)vertexCompression );
				SET_DYNAMIC_VERTEX_SHADER( unlitgeneric_vs30 );

				DECLARE_DYNAMIC_PIXEL_SHADER( unlitgeneric_ps30 );
				SET_DYNAMIC_PIXEL_SHADER( unlitgeneric_ps30 );
			}
		}
		Draw();
	}
END_SHADER

