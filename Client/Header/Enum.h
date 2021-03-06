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
	Weapon_Special,
	Weapon_Priority_End

}WEAPON_PRIORITY;

typedef enum eWeaponType
{
	Weapon_Rifle,
	Weapon_Shotgun,
	Weapon_Sniper,
	Weapon_Pistol,
	Weapon_Knife,
	Weapon_Injector,
	Weapon_Bomb,
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
	CHURCH_RIGHT,
	CHURCH_LEFT,
	POLICE_RIGHT,
	POLICE_LEFT,
	ZED_GEN_END

}ZED_LOCATE;

typedef enum eStageState
{
	STAGE_SHOP,
	STAGE_1,
	STAGE_2,
	STAGE_BOSS,
	STAGE_ENDING,

	STAGE_END

}STAGE_NAME;


typedef enum eSoundChannel
{
	SoundCH_BGM,
	SoundCH_UI,
	SoundCH_FX0,
	SoundCH_FX1,
	SoundCH_FX2,

	SoundCH_PLAYER_FIRE,
	SoundCH_PLAYER_Reload,
	SoundCH_PLAYER_WALK,
	SoundCH_PLAYER_HIT,

	SoundCH_Clot_IDLE, //idle == walk
	SoundCH_Clot_ATT,
	SoundCH_Clot_HIT,
	SoundCH_Clot_Death,

	SoundCH_GoreFast_Idle,
	SoundCH_GoreFast_Run,
	SoundCH_GoreFast_Att,
	SoundCH_GoreFast_Hit,
	SoundCH_GoreFast_Death,

	SoundCH_Scrake_Init,
	SoundCH_Scrake_Idle,
	SoundCH_Scrake_Run,
	SoundCH_Scrake_Att,
	SoundCH_Scrake_Hit,
	SoundCH_Scrake_Death,
	
	

	SoundCH_END


}SOUND_CHANNEL;


#endif //_ENUM_H_