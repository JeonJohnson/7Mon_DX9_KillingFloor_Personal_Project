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

typedef enum eUi_Kind
{
	UI_SPRITE,
	UI_TEXT,
	UI_COMPONENT,
	UI_END

}UI_KIND;

typedef enum eNaviPoint
{
	POINT_A,
	POINT_B,
	POINT_C,
	POINT_NAME_END

}Point_Name;

typedef enum eLineDirection
{
	LINE_LEFT,
	LINE_RIGHT,
	LINE_DIR_END

}Line_Dir;

typedef enum eNaviCell_Adjacency
{
	//선분에서 오른쪽기준
	//		  A
	//	2	/   \  0
	//	   C-----B
	//        1
	CELL_AB,
	CELL_BC,
	CELL_CA,
	CELL_ADJACENCY_END

}Cell_Adjacency;

typedef enum eNaviCell_Option
{
	CELL_MOVE,
	CELL_STOP,
	CELL_OPTION_END

}Cell_Option;





#endif //_ENGINE_ENUM_H_