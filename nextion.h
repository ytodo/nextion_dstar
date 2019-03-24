/*
 *  Copyright (C) 2018 by Yosh Todo JE3HCZ
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *  本プログラムはD-STAR Network の一部の機能を実現するための物で、
 *  アマチュア無線の技術習得とその本来の用途以外では使用しないでください。
 *
 */

/**************************************************
 * D-STAR Repeater Nextion display for dmonitor   *
 *      main.h version 00.01                      *
 *      2018.11.01 - 2019.01.02                   *
 *                                                *
 *  Multi_Forwardが搭載されているリピータリストを *
 *  取得して「接続可能リピータ」としてdmonitor用  *
 *  ディスプレイに表示。タッチパネルから接続する　*
 *                                                *
 **************************************************/
#ifndef __DMONITOR_H__
#define __DMONITOR_H__

/* Header Files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <time.h>

/* Macros */
#define SERIALPORT  "/dev/ttyAMA0"
#define CONFFILE    "/etc/dstarrepeater"
#define LOGPATH     "/var/log/"
#define BAUDRATE	9600
#define LISTSIZE	256
#define CHARSIZE	30
#define SLEEPTIME   300000 /* micro sec (default 0.3秒=300000) */

/* 日付表示関連 */
time_t  timer;
struct  tm *timeptr;
extern  char    tmstr[256];

/* Variables */
extern	char    status[CHARSIZE];
extern	char	rptcall[CHARSIZE];
extern  char    station[CHARSIZE];
extern  char    ipaddress[CHARSIZE];
extern  char    modemtype[CHARSIZE];
extern  char    cputemp[CHARSIZE];
extern  int     cnt_temp;

/* Functions */
int	    getstatus();
int     getconfig();
int	    openport(char *devicename, long baudrate);
void	recvdata(char *rptcon);
void	sendcmd(char *cmd);

#endif // __DMONITOR_H__

