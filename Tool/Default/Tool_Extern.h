#pragma once
#ifndef _EXTERN_OBJECT_TOOL_H_
#define _EXTERN_OBJECT_TOOL_H_

#include "MainFrm.h"
#include "ToolView.h"
#include "Spec_FormView.h"
#include "ObjectTool_Dialog.h"
#include "NaviMeshTool_Dialog.h"
#include "ColliderTool_Dialog.h"

//extern	HWND				g_hWnd_ObjectTool;

extern	CMainFrame*			g_pMainFrame;

extern	CToolView*			g_pDefaultView;
extern	Spec_FormView*		g_pSpec_FormView;

extern ObjectTool_Dialog*		g_pObjectTool_Dialog;
extern NaviMeshTool_Dialog*		g_pNaviMeshTool_Dialog;
extern ColliderTool_Dialog*		g_pColliderTool_Dialog;

#endif // _EXTERN_OBJECT_TOOL_H_