
/*
 *  Copyright (C) 2018-2019 by Yosh Todo JE3HCZ
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


#include "nextion.h"


int main(int argc, char *argv[])
{
	int	    fd;
	int	    i;
	int	    flag;
	char	command[32] 	= {'\0'};
	char	statpre[32] 	= {'\0'};
	char	rptcallpre[32] 	= {'\0'};
	char	usercmd[32]	    = {'\0'};
	char	concallpre[8]	= {'\0'};
    char    tmpstr[32]      = {'\0'};
    char    fname[128]      = {'\0'};

    /* 日付入りログファイル名の作成 */
    timer = time(NULL);
    timeptr = gmtime(&timer);
    strftime(fname, sizeof(fname), "dstarrepeaterd-%Y-%m-%d.log", timeptr);
    sprintf(dstarlogpath, "%s%s", LOGDIR, fname);

	/* GPIO シリアルポートのオープン*/
	fd = openport(SERIALPORT, BAUDRATE);

    /* 環境設定ファイルの読み取り */
    getconfig();

	/* メインスクリーンの初期設定 */
	sendcmd("dim=50");
	sendcmd("page MAIN");

    sprintf(command, "station.txt=\"%s\"", station);
    sendcmd(command);
    sendcmd("t0.txt=station.txt");

    sendcmd("status.txt=\"Node Idle\"");
  	sendcmd("t1.txt=status.txt");

    sprintf(command, "ipaddr.txt=\"%s\"", ipaddress);
    sendcmd(command);
    sendcmd("t3.txt=ipaddr.txt");

    sprintf(command, "va2.txt=\"%s\"", modemtype);
    sendcmd(command);
    sendcmd("t30.txt=va2.txt");


	/* 送・受信ループ */
	while (1) {

		/*
		 * 受信処理
		 */

		/* タッチパネルのデータを読み込む */
		recvdata(usercmd);

        /* タッチデータが選択されている場合、前回と同じかチェック（同じならパス） */
		if ((strlen(usercmd) > 3) && (strncmp(usercmd, concallpre, 8) != 0))  {

			/* 現在の返り値を保存 */
			strncpy(concallpre, usercmd, 8);

			/* コマンドをスイッチに振り分ける */
			if (strncmp(usercmd, "restart", 7) == 0) flag = 1;
			if (strncmp(usercmd, "reboot",  6) == 0) flag = 2;
			if (strncmp(usercmd, "shutdown",8) == 0) flag = 3;

			switch (flag) {
			case 1:
                sendcmd("page MAIN");
				system("systemctl restart dstarrepeater.service");
                system("systemctl restart nextion.service");
				break;

			case 2:
				sendcmd("page MAIN");
				system("sudo shutdown -r now");
				break;

			case 3:
				sendcmd("page MAIN");
				system("sudo shutdown -h now");
				break;

			default:
				break;
			}
		}

		/*
		 * 送信処理
		 */

		/* ステータス・ラストハードの読み取り */
        getstatus();

        /* CPU 温度の表示*/
        sprintf(command, "temp.txt=\"%s\"", cputemp);
        sendcmd(command);
        sendcmd("t20.txt=temp.txt");

        /* CPU 温度による表示色変更 */
        strcpy(tmpstr, cputemp);
        tmpstr[strlen(tmpstr) - 4] = '\0';
        int temp = atoi(tmpstr);
        if (temp < 45) {
            sendcmd("t20.pco=2016");
            sendcmd("t20.bco=25356");
        }
        if (temp >= 45 && temp < 50) {
            sendcmd("t20.pco=65504");
            sendcmd("t20.bco=25356");
        }
        if (temp >= 50 && temp < 55) {
            sendcmd("t20.pco=64520");
            sendcmd("t20.bco=25356");
        }
        if (temp >= 55) {
            sendcmd("t20.pco=65504");
            sendcmd("t20.bco=63488");
        }

        sprintf(command, "t2.txt=\"%s\"", status);
        sendcmd(command);

		/* ステータス・ラストハードの表示 */
//		if ((strncmp(status, "", 1) != 0) && (strncmp(status, statpre, 24) != 0)) {
//			strcpy(statpre, status);
//			sendcmd("dim=50");

            /* STATUS1 => STATUS2 */
//			sendcmd("MAIN.stat2.txt=MAIN.stat1.txt");

            /* 取得ステイタス=> STATUS1 */
//			sprintf(command, "MAIN.stat1.txt=\"%s\"", status);
//			sendcmd(command);
//			sendcmd("t2.txt=MAIN.stat1.txt");
//			sendcmd("t3.txt=MAIN.stat2.txt");
//		}

//	usleep(1*1000000); //Sleep:msec/sleep:sec
	}

	/* GPIO シリアルポートのクローズ*/
	close(fd);
	return (EXIT_SUCCESS);
}

