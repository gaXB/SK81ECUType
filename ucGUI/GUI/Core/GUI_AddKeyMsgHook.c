/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              ?C/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : GUI_SetKeyMsgHook.c
Purpose     : Implementation of GUI_SetKeyMsgHook
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Protected.h"
#include "GUIDebug.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_SetKeyMsgHook
*/
GUI_KEY_MSG_HOOK* GUI_SetKeyMsgHook(GUI_KEY_MSG_HOOK* pHook) {
  GUI_KEY_MSG_HOOK* r;
  r = GUI_pfKeyMsgHook;
  GUI_pfKeyMsgHook = pHook;
  return r;
}

/*************************** End of file ****************************/
