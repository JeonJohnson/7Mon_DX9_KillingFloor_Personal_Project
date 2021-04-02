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
	void Initailize(_object_Tag _maxCount);
	void Update();
	void LateUpdate();
	void ReadyRender();
	void Release();

public: /* functions */
	void ReleaseScene();
	
	void Merge_Gameobjects();
	void Delete_DeadGameObjects();

public: /* Get */

public: /* Set */
	void	Insert_GameObject(GameObject* _gameObject);
	
private:
	list<GameObject*>					m_newGameObjectList;
	vector<list<GameObject*>>			m_vecGameObjectList;
	//map ����ϱ� �� tag�� �������ֱ� ������ ����;
	//������ tag�� enum���� int���ε� vector�� ������
	
	//new GameObjList�� ������ ���� ���� �� �� ���� ���� �����ӿ� �Ѱ��ٲ��ϱ�
	//�߰��� ����� �󸶾ȵ�� list���ٱ�..?

	//Tag���� ���� �ٸ��� ����������ؼ� map�� ���Ұ� ������
	//map�� []�����ؼ� �����ϴ°� �Ǽ��ϸ� �� ���󰡱��ѵ�... �����
	//�ؿ������� ������ ��������Ʈ
	//�� ���Խ�[key] �� ���� �ִ��� ������ Ȯ���� ���� ������ [key]������ ���� ���ٰ� �Ͻ�.
};

#endif //_GAMEOBJECT_MANAGER_H_