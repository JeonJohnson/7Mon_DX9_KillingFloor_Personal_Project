#pragma once

#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

#include "Engine_Include.h"

class SoundManager
{
	Declare_Singleton(SoundManager)

public:
	SoundManager();
	virtual ~SoundManager();

public:
	void Initialize(int _iChannelCount = 8);
	void Release();
public:
	void Play_Sound(TCHAR* _pSoundKey, _sound_channel _eID);
	void Overlap_Play(TCHAR* _pSoundKey, _sound_channel _eID);
	void PlayBGM(TCHAR* _pSoundKey);
	void StopSound(_sound_channel _eID);
	void StopAll();

private:
	void LoadSoundFile();

private:
	// 사운드 리소스 정보를 갖는 객체 
	map<TCHAR*, FMOD_SOUND*> m_mapSound;
	// FMOD_CHANNEL : 재생하고 있는 사운드를 관리할 객체 
	
	FMOD_CHANNEL* m_pChannelArr[8]; //동적할당이나 STL로 바꿔주기
	// 사운드 ,채널 객체 및 장치를 관리하는 객체 
	FMOD_SYSTEM* m_pSystem = nullptr;
};

#endif//_SOUND_MANAGER_H_