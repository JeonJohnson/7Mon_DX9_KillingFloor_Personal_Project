#pragma once

#ifndef _ENGINE_KEY_DEFINE_H_
#define _ENGINE_KEY_DEFINE_H_

#pragma region Old
//#define KEY_LBUTTON	0x00000001 //DEC 1
//#define KEY_RBUTTON	0x00000002 //DEC 2
//
//////Special////
//#define KEY_ENTER	0x00000004
//#define KEY_SPACE	0x00000008
//#define KEY_LSHIFT  0x00000010
//#define KEY_ESC		0x00000020
//
//////ARROW////
//#define KEY_LEFT	0x00000040
//#define KEY_RIGHT	0x00000080
//#define KEY_UP		0x00000100	
//#define KEY_DOWN    0x00000200
//
//////Keys////
//#define KEY_W		0x00000400
//#define KEY_A		0x00000800
//#define KEY_S		0x00001000
//#define KEY_D		0x00002000
//
//#define KEY_Q		0x00004000
//#define KEY_E		0x00008000
//
//#define KEY_F1		0x00010000
//#define KEY_F2		0x00020000
//#define KEY_F3		0x00040000
#pragma endregion

#pragma region DinputDefine
//키보드 배열 순서대로 좌->우 left->Right
//Upper F~ / 1열
#define	KEY_STATE_ESC		DIK_ESCAPE
#define	KEY_STATE_F1		DIK_F1
#define	KEY_STATE_F2		DIK_F2
#define	KEY_STATE_F3		DIK_F3
#define	KEY_STATE_F4		DIK_F4
#define	KEY_STATE_F5		DIK_F5
#define	KEY_STATE_F6		DIK_F6
#define	KEY_STATE_F7		DIK_F7
#define	KEY_STATE_F8		DIK_F8
#define	KEY_STATE_F9		DIK_F9
#define	KEY_STATE_F10		DIK_F10
#define	KEY_STATE_F11		DIK_F11
#define	KEY_STATE_F12		DIK_F12

//nums / 2열 
#define	KEY_STATE_1			DIK_1
#define	KEY_STATE_2			DIK_2
#define	KEY_STATE_3			DIK_3
#define	KEY_STATE_4			DIK_4
#define	KEY_STATE_5			DIK_5
#define	KEY_STATE_6			DIK_6
#define	KEY_STATE_7			DIK_7
#define	KEY_STATE_8			DIK_8
#define	KEY_STATE_9			DIK_9
#define	KEY_STATE_0			DIK_0
#define	KEY_STATE_Minus		DIK_MINUS
#define	KEY_STATE_Equals	DIK_EQUALS
#define	KEY_STATE_BackSpace	DIK_BACK

//QWERTY / 3열
#define	KEY_STATE_TAB		DIK_TAB
#define	KEY_STATE_Q			DIK_Q
#define	KEY_STATE_W			DIK_W
#define	KEY_STATE_E			DIK_E
#define	KEY_STATE_R			DIK_R
#define	KEY_STATE_T			DIK_T
#define	KEY_STATE_Y			DIK_Y
#define	KEY_STATE_U			DIK_U
#define	KEY_STATE_I			DIK_I
#define	KEY_STATE_O			DIK_O
#define	KEY_STATE_P			DIK_P
//#define	KEY_STATE_			DIK_LBRACKET
//#define	KEY_STATE_			DIK_RBRACKET
//#define	KEY_STATE_			DIK_BACKSLASH

//ASDF /4열
#define	KEY_STATE_Caps		DIK_CAPITAL
#define	KEY_STATE_A			DIK_A
#define	KEY_STATE_S			DIK_S
#define	KEY_STATE_D			DIK_D
#define	KEY_STATE_F			DIK_F
#define	KEY_STATE_G			DIK_G
#define	KEY_STATE_H			DIK_H
#define	KEY_STATE_J			DIK_J
#define	KEY_STATE_K			DIK_K
#define	KEY_STATE_L			DIK_L
//#define	KEY_STATE_			DIK_SEMICOLON
//#define	KEY_STATE_			DIK_APOSTROPHE
//#define	KEY_STATE_			DIK_GRAVE
#define	KEY_STATE_ENTER		DIK_RETURN

//ZXCV / 5열
#define	KEY_STATE_Lshift	DIK_LSHIFT
#define	KEY_STATE_Z			DIK_Z
#define	KEY_STATE_X			DIK_X
#define	KEY_STATE_C			DIK_C
#define	KEY_STATE_V			DIK_V
#define	KEY_STATE_B			DIK_B
#define	KEY_STATE_N			DIK_N
#define	KEY_STATE_M			DIK_M
#define	KEY_STATE_Comma		DIK_COMMA
//#define	KEY_STATE_			DIK_PERIOD
//#define	KEY_STATE_			DIK_SLASH
#define	KEY_STATE_RShift	DIK_RSHIFT

//Downer / 6열
#define	KEY_STATE_LCtrl		DIK_LCONTROL
#define	KEY_STATE_LWindows	DIK_LWIN
#define	KEY_STATE_LAlt		DIK_LMENU
#define	KEY_STATE_Space		DIK_SPACE
#define	KEY_STATE_RAlt		DIK_RMENU
#define	KEY_STATE_RWindows	DIK_RWIN
#define	KEY_STATE_RCtrl		DIK_RCONTROL

//2X3 Function
#define	KEY_STATE_Insert	DIK_INSERT
#define	KEY_STATE_Home		DIK_HOME
#define	KEY_STATE_PageUp	DIK_PRIOR
#define	KEY_STATE_PageDown	DIK_NEXT
#define	KEY_STATE_Delete	DIK_DELETE
#define	KEY_STATE_End		DIK_END

//Arrows
#define	KEY_STATE_Up		DIK_UP
#define	KEY_STATE_Left		DIK_LEFT
#define	KEY_STATE_Right		DIK_RIGHT
#define	KEY_STATE_Down		DIK_DOWN


#pragma region NumPad(TenKey)
//#define	KEY_STATE_			DIK_MULTIPLY
//#define	KEY_STATE_			DIK_NUMLOCK
//#define	KEY_STATE_			DIK_SCROLL
//#define	KEY_STATE_			DIK_NUMPAD7
//#define	KEY_STATE_			DIK_NUMPAD8
//#define	KEY_STATE_			DIK_NUMPAD9
//#define	KEY_STATE_			DIK_SUBTRACT
//#define	KEY_STATE_			DIK_NUMPAD4
//#define	KEY_STATE_			DIK_NUMPAD5
//#define	KEY_STATE_			DIK_NUMPAD6
//#define	KEY_STATE_			DIK_ADD
//#define	KEY_STATE_			DIK_NUMPAD1
//#define	KEY_STATE_			DIK_NUMPAD2
//#define	KEY_STATE_			DIK_NUMPAD3
//#define	KEY_STATE_			DIK_NUMPAD0
//#define	KEY_STATE_			DIK_DECIMAL
//#define	KEY_STATE_			DIK_NUMPADENTER
//#define	KEY_STATE_			DIK_NUMPADCOMMA
//#define	KEY_STATE_			DIK_DIVIDE
//#define	KEY_STATE_			DIK_SYSRQ
#pragma endregion
#pragma endregion



#endif //_ENGINE_KEY_DEFINE_H_
