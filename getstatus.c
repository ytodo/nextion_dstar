/********************************************************
 * dmonitor のログファイルよりラストハード及び
 * 状況を取得し変数status に入れる
 ********************************************************/

#include "nextion.h"
#define SLEEPTIME   300000  /* micro sec (default 0.3秒=300000) */

int getstatus(void)
{
	FILE	*fp;
    char    cmdline[512];
	char	line[512] 	= {'\0'};
	char	*tmpstr;

    /*
     * CPU 温度の標準出力を取得
     */
    cnt_temp++;
    if (cnt_temp > SLEEPCOUNT) {
        strcpy(cmdline, "vcgencmd measure_temp");
        if ((fp = popen(cmdline, "r")) != NULL) {
            fgets(line, sizeof(line), fp);
            usleep(SLEEPTIME);
            line[strlen(line) - 1] = '\0';
            strcpy(cputemp, &line[5]);

            /* 標準出力クローズ */
            pclose(fp);
            cnt_temp = 0;
//            printf("%s\n", cputemp); /* for test */
        }
    }


    /*
     * ログファイルからデータを抽出する
     */
    sprintf(cmdline, "tail -n1 %s", dstarlogpath);

	/* コマンドの標準出力オープン */
	if ((fp = popen(cmdline, "r")) == NULL) {
		printf("File open error!\n");
    }

/* sample
M: 2019-03-16 00:28:57: Radio header decoded - My: JE3HCZ  /ID80  Your: DCS047BL  Rpt1: DIRECT    Rpt2: DIRECT    Flags: 00 00 00
M: 2019-03-16 00:28:57: Slow data set to "Linking to DCS047 B "
M: 2019-03-16 00:28:57: Slow data set to "Linked to DCS047 B  "
M: 2019-03-16 00:28:57: AMBE for JE3HCZ    Frames: 0.3s, Silence: 92.3%, BER: 0.0%
M: 2019-03-16 00:28:58: Transmitting to - My: JL3ZBS C/      Your: JE3HCZ    Rpt1: JL3ZBS G  Rpt2: JL3ZBS C  Flags: 01 00 00
M: 2019-03-16 00:29:00: Network header received - My: JL3ZBS  /INFO  Your: CQCQCQ    Rpt1: JL3ZBS G  Rpt2: JL3ZBS C  Flags: 00 00 00
M: 2019-03-16 00:29:00: Transmitting to - My: JL3ZBS  /INFO  Your: CQCQCQ    Rpt1: JL3ZBS G  Rpt2: JL3ZBS C  Flags: 00 00 00
M: 2019-03-16 00:29:07: Stats for JL3ZBS    Frames: 7.1s, Loss: 0.0%, Packets: 0/355
M: 2019-03-16 00:29:52: Radio header decoded - My: JE3HCZ  /ID80  Your: CQCQCQ    Rpt1: DIRECT    Rpt2: DIRECT    Flags: 00 00 00
M: 2019-03-16 00:29:57: AMBE for JE3HCZ    Frames: 5.5s, Silence: 0.0%, BER: 0.0%
M: 2019-03-16 00:29:58: Transmitting to - My: JL3ZBS C/      Your: JE3HCZ    Rpt1: JL3ZBS G  Rpt2: JL3ZBS C  Flags: 01 00 00
M: 2019-03-16 00:30:01: Network header received - My: JL3ZBS B/      Your: CQCQCQ    Rpt1: JL3ZBS G  Rpt2: JL3ZBS C  Flags: 00 00 00
M: 2019-03-16 00:30:01: Transmitting to - My: JL3ZBS B/      Your: CQCQCQ    Rpt1: JL3ZBS G  Rpt2: JL3ZBS C  Flags: 00 00 00
M: 2019-03-16 00:30:09: Stats for JL3ZBS B  Frames: 7.5s, Loss: 0.0%, Packets: 0/374
*/

	/* 過去のデータをクリアする  */
	memset(&status[0], '\0', sizeof(status));

	/* 標準出力を配列に取得 */
//	fgets(line, sizeof(line), fp);


	while ((fgets(line, sizeof(line), fp)) != NULL) {
		if ((tmpstr = strstr(line, "Linked")) != NULL) strncpy(status, tmpstr, 10);
	}

printf("%s\n", status);

	/* status に関する文字列があったら */
//	if ((tmpstr = strstr(line, "from")) != NULL) {
//		strncpy(status, line, 16);
//		strncat(status, tmpstr - 9, 8);
//	}
//	if ((tmpstr = strstr(line, "rig not")) != NULL) {
//		strcpy(status, "Check rig not connected.");
//	}


	pclose(fp);

	return (EXIT_SUCCESS);
}





