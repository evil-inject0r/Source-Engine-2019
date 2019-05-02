//========= Copyright � 1996-2006, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $Header: $
// $NoKeywords: $
//=============================================================================//

#include "BaseVSShader.h"
#include "cpp_shader_constant_register_map.h"

#include "bik_ps30.inc"
#include "bik_vs30.inc"

BEGIN_VS_SHADER( Bik, "Help for Bik" )
	BEGIN_SHADER_PARAMS
		SHADER_PARAM( YTEXTURE, SHADER_PARAM_TYPE_TEXTURE, "shadertest/BaseTexture", "Y Bink Texture" )
		SHADER_PARAM( ATEXTURE, SHADER_PARAM_TYPE_TEXTURE, "shadertest/BaseTexture", "A Bink Texture" )
		SHADER_PARAM( CRTEXTURE, SHADER_PARAM_TYPE_TEXTURE, "shadertest/BaseTexture", "Cr Bink Texture" )
		SHADER_PARAM( CBTEXTURE, SHADER_PARAM_TYPE_TEXTURE, "shadertest/BaseTexture", "Cb Bink Texture" )
	END_SHADER_PARAMS

	SHADER_INIT_PARAMS()
	{
	}

	SHADER_FALLBACK
	{
		if ( g_pHardwareConfig->GetDXSupportLevel() < 90 )
		{
			return "bik_dx81";
		}
		return 0;
	}

	SHADER_INIT
	{
		if ( params[YTEXTURE]->IsDefined() )
		{
			LoadTexture( YTEXTURE );
		}
		if ( params[ATEXTURE]->IsDefined() )
		{
			LoadTexture( ATEXTURE );
		}
		if ( params[CRTEXTURE]->IsDefined() )
		{
			LoadTexture( CRTEXTURE );
		}
		if ( params[CBTEXTURE]->IsDefined() )
		{
			LoadTexture( CBTEXTURE );
		}
	}

	SHADER_DRAW
	{
		SHADOW_STATE
		{
			pShaderShadow->EnableTexture( SHADER_SAMPLER0, true );
			pShaderShadow->EnableTexture( SHADER_SAMPLER1, true );
			pShaderShadow->EnableTexture( SHADER_SAMPLER2, true );
			pShaderShadow->EnableTexture( SHADER_SAMPLER3, true );

			unsigned int flags = VERTEX_POSITION;
			int numTexCoords = 1;
			pShaderShadow->VertexShaderVertexFormat( flags, numTexCoords, 0, 0 );

			DECLARE_STATIC_VERTEX_SHADER( bik_vs30 );
			SET_STATIC_VERTEX_SHADER( bik_vs30 );

			DECLARE_STATIC_PIXEL_SHADER( bik_ps30 );
			SET_STATIC_PIXEL_SHADER( bik_ps30 );

			pShaderShadow->EnableSRGBWrite( false );

			EnableAlphaBlending( SHADER_BLEND_SRC_ALPHA, SHADER_BLEND_ONE_MINUS_SRC_ALPHA );
		}
		DYNAMIC_STATE
		{
			BindTexture( SHADER_SAMPLER0, YTEXTURE, FRAME );
			BindTexture( SHADER_SAMPLER1, CRTEXTURE, FRAME );
			BindTexture( SHADER_SAMPLER2, CBTEXTURE, FRAME );
			BindTexture( SHADER_SAMPLER3, ATEXTURE, FRAME );

			// We need the view matrix
			LoadViewMatrixIntoVertexShaderConstant( VERTEX_SHADER_VIEWMODEL );

			MaterialFogMode_t fogType = pShaderAPI->GetSceneFogMode();
			int fogIndex = ( fogType == MATERIAL_FOG_LINEAR_BELOW_FOG_Z ) ? 1 : 0;

			DECLARE_DYNAMIC_VERTEX_SHADER( bik_vs30 );
			SET_DYNAMIC_VERTEX_SHADER_COMBO( DOWATERFOG,  fogIndex );
			SET_DYNAMIC_VERTEX_SHADER( bik_vs30 );

			pShaderAPI->SetPixelShaderFogParams( PSREG_FOG_PARAMS );		

			float vEyePos_SpecExponent[4];
			pShaderAPI->GetWorldSpaceCameraPosition( vEyePos_SpecExponent );
			vEyePos_SpecExponent[3] = 0.0f;
			pShaderAPI->SetPixelShaderConstant( PSREG_EYEPOS_SPEC_EXPONENT, vEyePos_SpecExponent, 1 );

			DECLARE_DYNAMIC_PIXEL_SHADER( bik_ps30 );
			SET_DYNAMIC_PIXEL_SHADER_COMBO( PIXELFOGTYPE, pShaderAPI->GetPixelFogCombo() );
			SET_DYNAMIC_PIXEL_SHADER( bik_ps30 );
		}
		Draw( );
	}
END_SHADER
