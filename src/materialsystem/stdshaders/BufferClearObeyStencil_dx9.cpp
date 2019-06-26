//========= Copyright � 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: Clears color/depth, but obeys stencil while doing so
//
//=============================================================================//

#include "BaseVSShader.h"

#include "bufferclearobeystencil_vs30.inc"
#include "bufferclearobeystencil_ps30.inc"


// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

DEFINE_FALLBACK_SHADER( BufferClearObeyStencil, BufferClearObeyStencil_DX9 )

BEGIN_VS_SHADER_FLAGS( BufferClearObeyStencil_DX9, "", SHADER_NOT_EDITABLE )

	BEGIN_SHADER_PARAMS
		SHADER_PARAM( CLEARCOLOR, SHADER_PARAM_TYPE_INTEGER, "1", "activates clearing of color" )
		SHADER_PARAM( CLEARDEPTH, SHADER_PARAM_TYPE_INTEGER, "1", "activates clearing of depth" )
	END_SHADER_PARAMS

	SHADER_INIT_PARAMS()
	{
	}

	SHADER_FALLBACK
	{
		return 0;
	}

	SHADER_INIT
	{
	}

	SHADER_DRAW
	{
		bool bEnableColorWrites = params[CLEARCOLOR]->GetIntValue() != 0;

		SHADOW_STATE
		{
			pShaderShadow->DepthFunc( SHADER_DEPTHFUNC_ALWAYS );
			bool bEnableDepthWrites = params[CLEARDEPTH]->GetIntValue() != 0;
			pShaderShadow->EnableDepthWrites( bEnableDepthWrites );

			pShaderShadow->EnableColorWrites( bEnableColorWrites );
			pShaderShadow->EnableAlphaWrites( bEnableColorWrites );

			pShaderShadow->VertexShaderVertexFormat( VERTEX_POSITION|VERTEX_COLOR, 1, NULL, 0 );

			DECLARE_STATIC_VERTEX_SHADER( bufferclearobeystencil_vs30 );
			SET_STATIC_VERTEX_SHADER_COMBO( USESCOLOR, bEnableColorWrites );
			SET_STATIC_VERTEX_SHADER( bufferclearobeystencil_vs30 );

			//avoid setting a pixel shader when only doing depth/stencil operations, as recommended by PIX
			if( bEnableColorWrites )
			{
				DECLARE_STATIC_PIXEL_SHADER( bufferclearobeystencil_ps30 );
				SET_STATIC_PIXEL_SHADER( bufferclearobeystencil_ps30 );
			}
		}

		DYNAMIC_STATE
		{
			DECLARE_DYNAMIC_VERTEX_SHADER( bufferclearobeystencil_vs30 );
			SET_DYNAMIC_VERTEX_SHADER( bufferclearobeystencil_vs30 );

			//avoid setting a pixel shader when only doing depth/stencil operations, as recommended by PIX
			if( bEnableColorWrites )
			{
				DECLARE_DYNAMIC_PIXEL_SHADER( bufferclearobeystencil_ps30 );
				SET_DYNAMIC_PIXEL_SHADER( bufferclearobeystencil_ps30 );
			}
		}

		Draw( );
	}

END_SHADER
