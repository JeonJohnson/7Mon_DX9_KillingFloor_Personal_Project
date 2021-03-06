#pragma once

#ifndef _TOOL_DEFINE_H_
#define _TOOL_DEFINE_H_

#define EngineFunction Engine_Mother::Get_Instance()

#define dTime Engine_Mother::Get_Instance()->Get_fDeltaTime()

#define ruSure(Script) AfxMessageBox(Script, MB_YESNO | MB_ICONQUESTION)
//IDYES, IDNO
#define Notice(Script2) AfxMessageBox(Script2, MB_OK| MB_ICONASTERISK)

#define KeyUp(KeyValue) Engine_Mother::Get_Instance()->GetKeyUp(KeyValue)
#define KeyDown(KeyValue) Engine_Mother::Get_Instance()->GetKeyDown(KeyValue)
#define KeyPress(KeyValue) Engine_Mother::Get_Instance()->GetKeyPress(KeyValue)
#define MouseUp(MouseValue) Engine_Mother::Get_Instance()->GetMouseUp(MouseValue)
#define MouseDown(MouseValue) Engine_Mother::Get_Instance()->GetMouseDown(MouseValue)
#define MousePress(MouseValue) Engine_Mother::Get_Instance()->GetMousePress(MouseValue)
#define MouseMove(Mouse)		Engine_Mother::Get_Instance()->GetMouseMove(Mouse)

#endif //_TOOL_DEFINE_H_