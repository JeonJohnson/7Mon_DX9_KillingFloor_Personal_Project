#pragma once

#ifndef _GAMEOBJECT_MANAGER_H_
#define _GAMEOBJECT_MANAGER_H_

#include "Engine_Include.h"	

#include "GameObject.h"

class GameObjectManager
{
	Declare_Singleton(GameObjectManager)

private:
	GameObjectManager();
	~GameObjectManager();
	
public:
	void Initailize();
	void Update();
	void LateUpdate();
	void ReadyRender();
	void Release();

public: /* functions */
	void ReleaseScene();

public: /* Get */

public: /* Set */
	void	Insert_GameObject(GameObject* _gameObject);

private:
	//vector<GameObject*>				m_vecNewGameObjectList;
	//map<int, GameObject*>			m_mapGameObjectList;
	//map<int, list<GameObject*>>	m_vecGameObjectList;
	
	//new GameObjList�� ������ ���� ���� �� �� ���� ���� �����ӿ� �Ѱ��ٲ��ϱ�
	//�߰��� ����� �󸶾ȵ�� list���ְ�

	//Tag���� ���� �ٸ��� ����������ؼ� map�� ���Ұ� ������
	//map�� []�����ؼ� ����, ���� �ϴ°� �Ǽ��ϸ� �� ���󰡱��ѵ�... �����
	//�ؿ������� ������ ��������Ʈ
	//�� ���Խ�[key] �� ���� �ִ��� ������ Ȯ���� ���� ������ [key]������ ���� ���ٰ� �Ͻ�.
};

#endif