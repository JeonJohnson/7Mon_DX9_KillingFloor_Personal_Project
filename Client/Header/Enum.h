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
	OBJECT_TAG_WEAPON,
	OBJECT_TAG_PLAYER,
	OBJECT_TAG_BULLET,
	OBJECT_TAG_ZED,
	OBJECT_TAG_UI,
	OBJECT_TAG_NAVIPOINT,
	OBJECT_TAG_END

}OBJECT_TAG;

typedef enum eCollisionTag
{

}COLLISION_TAG;


typedef enum eWeaponPriority
{
	Weapon_Primary,
	Weapon_Secondary,
	Weapon_Melee,
	Weapon_Priority_End

}WEAPON_PRIORITY;

typedef enum eWeaponType
{
	Weapon_Rifle,
	Weapon_Shotgun,
	Weapon_Sniper,
	Weapon_Pistol,
	Weapon_Knife,
	Weapon_Type_End

}WEAPON_TYPE;

typedef	enum eZedType
{
	ZED_Clot,
	ZED_GoreFast,
	ZED_Scrake,
	ZED_Patriarch,
	ZED_TYPE_END

}ZED_TYPE;

typedef enum eZedGenLocate
{
	CHURCH,
	POLICE,
	HOTEL_LEFT,
	HOTEL_RIGHT,
	ZED_GEN_END
}ZED_LOCATE;


#endif //_ENUM_H_