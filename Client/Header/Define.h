#pragma once

#ifndef _DEFINE_H_
#define _DEFINE_H_

#define WINCX 1280
#define WINCY 720

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


#endif