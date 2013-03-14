/* ***************************************************************************
 * LCUI_Work.h -- LCUI's other work
 * 
 * Copyright (C) 2013 by
 * Liu Chao
 * 
 * This file is part of the LCUI project, and may only be used, modified, and
 * distributed under the terms of the GPLv2.
 * 
 * (GPLv2 is abbreviation of GNU General Public License Version 2)
 * 
 * By continuing to use, modify, or distribute this file you indicate that you
 * have read the license and understand and accept it fully.
 *  
 * The LCUI project is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GPL v2 for more details.
 * 
 * You should have received a copy of the GPLv2 along with this file. It is 
 * usually in the LICENSE.TXT file, If not, see <http://www.gnu.org/licenses/>.
 * ****************************************************************************/
 
/* ****************************************************************************
 * LCUI_Work.h -- LCUI 的其它工作
 *
 * 版权所有 (C) 2013 归属于
 * 刘超
 * 
 * 这个文件是LCUI项目的一部分，并且只可以根据GPLv2许可协议来使用、更改和发布。
 *
 * (GPLv2 是 GNU通用公共许可证第二版 的英文缩写)
 * 
 * 继续使用、修改或发布本文件，表明您已经阅读并完全理解和接受这个许可协议。
 * 
 * LCUI 项目是基于使用目的而加以散布的，但不负任何担保责任，甚至没有适销性或特
 * 定用途的隐含担保，详情请参照GPLv2许可协议。
 *
 * 您应已收到附随于本文件的GPLv2许可协议的副本，它通常在LICENSE.TXT文件中，如果
 * 没有，请查看：<http://www.gnu.org/licenses/>. 
 * ****************************************************************************/

#ifndef __LCUI_WORK_H__
#define __LCUI_WORK_H__

#define RELATIVE_POS	1 /* 相对坐标 */
#define NORMAL_POS	0 /*普通坐标 */

LCUI_BEGIN_HEADER

typedef enum {
	EVENT_DRAG,	/* 部件的拖动事件 */
	EVENT_CLICKED,	/* 部件的点击事件 */
	EVENT_MOVE,	/* 部件的移动事件 */
	EVENT_RESIZE,	/* 部件尺寸改变 */
	EVENT_REDRAW,	/* 部件重绘 */
	EVENT_KEYBOARD,	/* 按键事件 */
	EVENT_FOCUSIN,	/* 得到焦点 */
	EVENT_FOCUSOUT	/* 失去焦点 */
} WidgetEventType; 

typedef struct {
	uchar_t type;
	LCUI_Size old_size;
	LCUI_Size new_size;
} LCUI_WidgetResizeEvent;

typedef struct {
	uchar_t type;
	LCUI_Pos new_pos;	/* 部件的新全局坐标 */
	LCUI_Pos cursor_pos;	/* 鼠标游标的坐标 */
	LCUI_BOOL first_click;	/* 标志，是否为首次点击 */ 
	LCUI_BOOL end_click;	/* 标志，是否已经结束拖动 */
} LCUI_WidgetDragEvent; 

typedef struct {
	uchar_t type;
	LCUI_BOOL focus;
} LCUI_WidgetFocusEvent;

typedef LCUI_KeyboardEvent LCUI_WidgetKeyboardEvent;

typedef union {
	unsigned char type;
	LCUI_WidgetDragEvent drag;
	LCUI_WidgetKeyboardEvent key;
	LCUI_WidgetFocusEvent focus;
	LCUI_WidgetResizeEvent resize;
} LCUI_WidgetEvent;


LCUI_EXPORT(void) NULL_Func();
/* 功能：空函数，不做任何操作 */ 

LCUI_EXPORT(void) FuncQueue_Init(LCUI_Queue *queue);
/* 功能：初始化函数指针队列 */ 

/*----------------------------- 部件事件 -------------------------------------*/
/* 将回调函数与部件的指定事件进行关联 */
LCUI_EXPORT(int)
Widget_Event_Connect(	LCUI_Widget *widget, WidgetEventType event_id, 
			void (*func)(LCUI_Widget*, LCUI_WidgetEvent*) );

/* 处理与部件事件关联的回调函数 */
LCUI_EXPORT(int)
Widget_DispatchEvent( LCUI_Widget *widget, LCUI_WidgetEvent *event );

/* 初始化部件模块 */
LCUI_EXPORT(void)
LCUIModule_Widget_Init( void );

/* 停用部件模块 */
LCUI_EXPORT(void)
LCUIModule_Widget_End( void );
/*-------------------------------- END ---------------------------------------*/

/*--------------------------- Focus Proc ------------------------------*/
LCUI_EXPORT(LCUI_BOOL)
Set_Focus( LCUI_Widget *widget );
/* 
 * 功能：为部件设置焦点
 * 说明：上个获得焦点的部件会得到EVENT_FOCUSOUT事件，而当前获得焦点的部件会得到
 * EVENT_FOCUSIN事件。
 * */ 

/* 设定部件是否能够获取焦点 */
LCUI_EXPORT(void)
Widget_SetFocus( LCUI_Widget *widget, LCUI_BOOL flag );

/* 获取指定部件内的已获得焦点的子部件 */
LCUI_EXPORT(LCUI_Widget*)
Get_FocusWidget( LCUI_Widget *widget );

LCUI_EXPORT(LCUI_BOOL)
Cancel_Focus( LCUI_Widget *widget );
/* 
 * 功能：取消指定部件的焦点
 * 说明：该部件会得到EVENT_FOCUSOUT事件，并且，会将焦点转移至其它部件
 * */ 

LCUI_EXPORT(LCUI_BOOL)
Reset_Focus( LCUI_Widget* widget );
/* 复位指定部件内的子部件的焦点 */ 

/*------------------------- End Focus Proc ----------------------------*/

LCUI_END_HEADER

#endif

