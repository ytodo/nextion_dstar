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
#ifndef __NEXTION_H__
#define __NEXTION_H__

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
#define LOGDIR      "/var/log/"
#define DUMPFILE    "/tmp/tcpdump.dstar"
#define BAUDRATE	9600
#define LISTSIZE	256
#define CHARSIZE	30
#define SLEEPCOUNT  200                 // コマンド実行待ちカウント
#define TXHANG      2                   // ラストパケット検出後のハングタイム（秒）
#define TXDELAY     0                   // 実際の送信開始に対する表示開始の遅れ（秒）

/* 日付表示関連 */
time_t  timer;
struct  tm *timeptr;
time_t  jstimer;
struct  tm *jstimeptr;

/* Variables */
extern  char    status[CHARSIZE];       // ログファイルからの状況取得用
extern  char    status2[CHARSIZE];      // 〃（主にラストハード）
extern  char    linkref[CHARSIZE];      // 接続先リフレクタ
extern  char    station[CHARSIZE];      // ノード用コールサイン
extern  char    ifname[CHARSIZE];       // 通信用LAN インターフェース名
extern  char    ipaddress[CHARSIZE];    // eth0 のIP アドレス
extern  char    localport[CHARSIZE];    // ゲートウェイとの通信ポート
extern  char    modemtype[CHARSIZE];    // モデムアダプタの種類
extern  char    cputemp[CHARSIZE];      // CPU の温度
extern  char    dstarlogpath[CHARSIZE]; // D-STAR Repeater ログのフルパス
extern  char    chklink[CHARSIZE];      // ループ内の多重処理禁止用
extern  char    chklink2[CHARSIZE];     // ループ内の多重処理禁止用
extern  char    chkstat[256];           // ループ内の多重処理禁止用
extern  char    chkstat2[256];          // ループ内の多重処理禁止用
extern  char    chkstat3[256];          // ループ内の多重処理禁止用
extern  int     cnt_temp;               // 温度測定間隔調整用カウンタ
extern  int     net_flag;               // ネット側ストリームon/off状態
extern  int     rf_flag;                // RF 側ストリームon/off状態

/* Functions */
int	    openport(char *devicename, long baudrate);
int     getconfig(void);
int     dispcmdinfo(void);
int	    disploginfo(void);
int     dispstreaminfo(void);
void	recvdata(char *touchcmd);
void	sendcmd(char *cmd);
void    reflesh_idle();

#endif // __NEXTION_H__
