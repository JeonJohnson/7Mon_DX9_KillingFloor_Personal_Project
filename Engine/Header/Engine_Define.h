#pragma once

#ifndef _ENGINE_DEFINE_H_
#define _ENGINE_DEFINE_H_

#define MsgBox(title, script) MessageBox(0, script, title, MB_OK)

#ifdef DLL_EXPORT
#define DLL_STATE _declspec(dllexport)
#else
#define DLL_STATE _declspec(dllimport)
#endif //DLL_EXPORT

#define Engine_fTime TimeManager::Get_Instance()->Get_fTime()


#define	Declare_Singleton(Class)				\
private:										\
	static	Class*	m_Instance;					\
public:											\
	static	Class*	Get_Instance();				\
	static	void	Destroy_Instance();


#define Implement_Singleton(Class)				\
Class*	Class::m_Instance = nullptr;			\
Class*	Class::Get_Instance()					\
{												\
	if(!m_Instance)								\
	{											\
		m_Instance = new Class();				\
	}											\
	return m_Instance;							\
}												\
void	Class::Destroy_Instance()				\
{												\
	if(m_Instance)								\
	{											\
		delete m_Instance;						\
		m_Instance = nullptr;					\
	}											\
}

#define Safe_Delete(Class)						\
if(Class)										\
{ delete Class; Class = nullptr; }

#define Safe_Delete_Arr(Class)					\
if(Class)										\
{ delete[]Class; Class= nullptr; }

#define Safe_Release(Class)						\
if(Class)										\
{ Class->Release(); Class = nullptr; }




#endif //_ENGINE_DEFINE_H_
