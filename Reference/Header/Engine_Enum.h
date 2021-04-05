#pragma once

#ifndef _ENGINE_ENUM_H_
#define _ENGINE_ENUM_H_

//enum eRenderLayer 
//{
//	RenderLayer_Priority,
//	RenderLayer_NonAlpha,
//	RenderLayer_Alpha,
//	RenderLayer_UI,
//	RenderLayer_End
//};

typedef enum eVIBuffer_Kind
{
	VIBuffer_Color,
	VIBuffer_Textrue,
	VIBuffer_End
}VIBUFFER_KIND;

typedef enum eTexture_Kind
{
	Texture_Image,
	Texture_DDS,
	Texture_Kind_End


}TEXTURE_KIND;


#endif //_ENGINE_ENUM_H_