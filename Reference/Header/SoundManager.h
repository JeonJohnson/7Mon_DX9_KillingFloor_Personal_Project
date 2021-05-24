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
	void Play_Loop(TCHAR* _pSoundKey, _sound_channel _eID);
	void PlayBGM(TCHAR* _pSoundKey);
	void StopSound(_sound_channel _eID);
	void StopAll();

	void Set_Volume_CH(_sound_channel _eID, float _fVolume);

private:
	void LoadSoundFile();

private:
	// ���� ���ҽ� ������ ���� ��ü 
	map<TCHAR*, FMOD_SOUND*> m_mapSound;
	// FMOD_CHANNEL : ����ϰ� �ִ� ���带 ������ ��ü 
	
	FMOD_CHANNEL* m_pChannelArr[32]; //�����Ҵ��̳� STL�� �ٲ��ֱ�
	//�ȵ�. ����ü ���� ������ �ȵǼ� �׳� ä�� ���� ����� ���� ���� ����;


	// ���� ,ä�� ��ü �� ��ġ�� �����ϴ� ��ü 
	FMOD_SYSTEM* m_pSystem = nullptr;
};

#endif//_SOUND_MANAGER_H_