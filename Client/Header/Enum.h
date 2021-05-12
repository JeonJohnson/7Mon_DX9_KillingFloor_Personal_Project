#pragma once

#ifndef _ENUM_H_
#define _ENUM_H_

typedef enum eRenderLayer
{
	RENDER_LAYER_Priority,
	RENDER_LAYER_NonAlpha,
	RENDER_LAYER_Alpha,
	RENDER_LAYER_Sprite,
	RENDER_LAYER_Text,
	RENDER_LAYER_Line,
	RENDER_LAYER_End

}RENDER_LAYER;

typedef enum eGameObjectTag
{
	OBJECT_TAG_DEFAULT,
	OBJECT_TAG_TERRAIN,
	OBJECT_TAG_MAINCAM,
	OBJECT_TAG_PLAYER,
	OJBECT_TAG_UI,
	OBJECT_TAG_NAVIPOINT,
	OBJECT_TAG_END

}OBJECT_TAG;

typedef enum eCollisionTag
{

}COLLISION_TAG;


typedef enum eWeaponType
{
	Weapon_Primary,
	Weapon_Secondary,
	Weapon_Melee,
	Weapon_End

}WEAPON_TYPE;

#endif //_ENUM_H_