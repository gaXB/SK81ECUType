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
File        : LISTVIEW_SetTextColor.c
Purpose     : Implementation of LISTVIEW_SetTextColor
---------------------------END-OF-HEADER------------------------------
*/

#include "LISTVIEW_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Public routines
*
**********************************************************************
*/
/*********************************************************************
*
*       LISTVIEW_SetTextColor
*/
void LISTVIEW_SetTextColor(LISTVIEW_Handle hObj, unsigned int Index, GUI_COLOR Color) {
  if (hObj) {
    LISTVIEW_Obj* pObj;
    if (Index < GUI_COUNTOF(pObj->Props.aTextColor)) {
      WM_LOCK();
      pObj = LISTVIEW_H2P(hObj);
      if (Color != pObj->Props.aTextColor[Index]) {
        pObj->Props.aTextColor[Index] = Color;
        LISTVIEW__InvalidateInsideArea(hObj, pObj);
      }
      WM_UNLOCK();
    }
  }
}

#else                            /* Avoid problems with empty object modules */
  void LISTVIEW_SetTextColor_C(void);
  void LISTVIEW_SetTextColor_C(void) {}
#endif
