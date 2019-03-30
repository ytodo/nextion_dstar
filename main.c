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


#include    "nextion.h"
#define     WAITTIME 50000  // microsec

int main(int argc, char *argv[])
{
    int	    fd;
    int	    i;
    int	    flag;
    char	command[32] 	= {'\0'};
    char	usercmd[32]     = {'\0'};
    char    tmpstr[32]      = {'\0'};

	/* GPIO シリアルポートのオープン*/
	fd = openport(SERIALPORT, BAUDRATE);

    /* 環境設定ファイルの読み取り */
    getconfig();

	/* メインスクリーンの初期設定 */
	sendcmd("dim=50");
	sendcmd("page IDLE");

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

    	/* コマンドをスイッチに振り分ける */
		if (strncmp(usercmd, "restart", 7) == 0) flag = 1;
		if (strncmp(usercmd, "reboot",  6) == 0) flag = 2;
		if (strncmp(usercmd, "shutdown",8) == 0) flag = 3;

		switch (flag) {
			case 1:
                sendcmd("page IDLE");
				system("systemctl restart dstarrepeater.service");
                system("systemctl restart nextion.service");
				break;

			case 2:
				sendcmd("page IDLE");
				system("sudo shutdown -r now");
				break;

			case 3:
				sendcmd("page IDLE");
				system("sudo shutdown -h now");
				break;

			default:
				break;
		}

		/*
		 * 送信処理
		 */

        /* CPU 温度の表示 */
        dispcputemp();

		/* ステータス・ラストハードの読み取り */
        displinkinfo();

	}

	/* GPIO シリアルポートのクローズ*/
	close(fd);
	return (EXIT_SUCCESS);
}


