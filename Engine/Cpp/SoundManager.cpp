#include "..\Header\SoundManager.h"

Implement_Singleton(SoundManager)

SoundManager::SoundManager()
{
}


SoundManager::~SoundManager()
{
	Release();
}

void SoundManager::Initialize(int _iChannelCount)
{
	FMOD_System_Create(&m_pSystem);

	FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, NULL);

	LoadSoundFile();

}

void SoundManager::Release()
{
	for (auto& Mypair : m_mapSound)
	{
		delete[] Mypair.first;
		FMOD_Sound_Release(Mypair.second);
	}
	m_mapSound.clear();
	FMOD_System_Release(m_pSystem);
	FMOD_System_Close(m_pSystem);
}

void SoundManager::Play_Sound(TCHAR * _pSoundKey, _sound_channel _eID)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), [&](auto& iter)
	{
		return !lstrcmp(_pSoundKey, iter.first);
	});

	if (iter == m_mapSound.end())
		return;

	FMOD_BOOL bPlay = FALSE;

	if (FMOD_Channel_IsPlaying(m_pChannelArr[_eID], &bPlay))
	{
		FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter->second, FALSE, &m_pChannelArr[_eID]);
	}
	//FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter->second, FALSE, &m_pChannelArr[eID]);

	//FMOD_Channel_SetVolume(m_pChannelArr[SOUNDCHANNEL::BGM], 0.5f);

	//FMOD_Channel_SetVolume(m_pChannelArr[SOUNDCHANNEL::HERO_ATT], 0.8f);
	//FMOD_Channel_SetVolume(m_pChannelArr[SOUNDCHANNEL::HERO_HIT], 0.7f);
	//FMOD_Channel_SetVolume(m_pChannelArr[SOUNDCHANNEL::MONSTER_ATT], 0.7f);
	//FMOD_Channel_SetVolume(m_pChannelArr[SOUNDCHANNEL::MONSTER_HIT], 0.7f);
	//FMOD_Channel_SetVolume(m_pChannelArr[SOUNDCHANNEL::NARRATION], 0.4f);

	FMOD_System_Update(m_pSystem);
}

void SoundManager::Overlap_Play(TCHAR * _pSoundKey, _sound_channel _eID)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), [&](auto& iter)
	{
		return !lstrcmp(_pSoundKey, iter.first);
	});

	if (iter == m_mapSound.end())
		return;

	//FMOD_BOOL bPlay = FALSE;

	//FMOD_Channel_SetVolume(m_pChannelArr[SOUNDCHANNEL::HERO_ATT], 0.8f);
	//FMOD_Channel_SetVolume(m_pChannelArr[SOUNDCHANNEL::HERO_HIT], 0.7f);
	//FMOD_Channel_SetVolume(m_pChannelArr[SOUNDCHANNEL::MONSTER_ATT], 0.7f);
	//FMOD_Channel_SetVolume(m_pChannelArr[SOUNDCHANNEL::MONSTER_HIT], 0.7f);
	//FMOD_Channel_SetVolume(m_pChannelArr[SOUNDCHANNEL::NARRATION], 0.4f);

	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter->second, FALSE, &m_pChannelArr[_eID]);
	FMOD_System_Update(m_pSystem);
}

void SoundManager::PlayBGM(TCHAR * _pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), [&](auto& iter)
	{
		return !lstrcmp(_pSoundKey, iter.first);
	});

	if (iter == m_mapSound.end())
		return;

	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter->second, FALSE, &m_pChannelArr[0]);
	FMOD_Channel_SetMode(m_pChannelArr[0], FMOD_LOOP_NORMAL);

	//FMOD_Channel_SetVolume(m_pChannelArr[0], 0.5f);

	FMOD_System_Update(m_pSystem);
}

void SoundManager::StopSound(_sound_channel _eID)
{
	FMOD_Channel_Stop(m_pChannelArr[_eID]);
}

void SoundManager::StopAll()
{
	for (int i = 0; i < 8; ++i)
	{		
		FMOD_Channel_Stop(m_pChannelArr[i]);	
	}
}

void SoundManager::LoadSoundFile()
{
	_finddata_t fd;

	intptr_t handle = _findfirst("../../Resource/Sound/*.*", &fd);

	if (handle == 0)
		return;

	int iResult = 0;

	char szCurPath[128] = "../../Resource/Sound/";
	char szFullPath[128] = "";

	while (iResult != -1)
	{
		strcpy_s(szFullPath, szCurPath);
		strcat_s(szFullPath, fd.name);
		FMOD_SOUND* pSound = nullptr;

		FMOD_RESULT eRes = FMOD_System_CreateSound(m_pSystem, szFullPath, FMOD_HARDWARE, 0, &pSound);

		if (eRes == FMOD_OK)
		{
			size_t iLength = strlen(fd.name) + 1;

			TCHAR* pSoundKey = new TCHAR[iLength];
			ZeroMemory(pSoundKey, sizeof(TCHAR) * iLength);
			MultiByteToWideChar(CP_ACP, 0, fd.name, (int)iLength, pSoundKey, (int)iLength);

			m_mapSound.emplace(pSoundKey, pSound);
		}
		iResult = _findnext(handle, &fd);
	}
	FMOD_System_Update(m_pSystem);
	_findclose(handle);
}
