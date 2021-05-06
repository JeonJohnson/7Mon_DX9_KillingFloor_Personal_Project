#pragma once

#ifndef _DEFINE_H_
#define _DEFINE_H_

#define WINCX 1280
#define WINCY 720

#define WINCX_DEBUG 425
#define WINCY_DEBUG	WINCY

#define MsgBox(title, message) MessageBox(0, message, title, MB_OK)

#define EngineFunction			Engine_Mother::Get_Instance()
#define DEBUG_LOG(script)		Engine_Mother::Get_Instance()->DebugLog(script)

#define fTime Engine_Mother::Get_Instance()->Get_fDeltaTime()
#define dTime Engine_Mother::Get_Instance()->Get_dDeltaTime()

#define ON	true
#define OFF	false

#define KeyUp(KeyValue) Engine_Mother::Get_Instance()->GetKeyUp(KeyValue)
#define KeyDown(KeyValue) Engine_Mother::Get_Instance()->GetKeyDown(KeyValue)
#define KeyPress(KeyValue) Engine_Mother::Get_Instance()->GetKeyPress(KeyValue)
#define MouseUp(MouseValue) Engine_Mother::Get_Instance()->GetMouseUp(MouseValue)
#define MouseDown(MouseValue) Engine_Mother::Get_Instance()->GetMouseDown(MouseValue)
#define MousePress(MouseValue) Engine_Mother::Get_Instance()->GetMousePress(MouseValue)
#define MouseMove(Mouse)		Engine_Mother::Get_Instance()->GetMouseMove(Mouse)

#pragma region Functions
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
#pragma endregion



#endif //_DEFINE_H_


