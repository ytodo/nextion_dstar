/********************************************************
 * dstarrepeaterd-yyyy-mm-dd.log を読み込み、
 * リンク処理の結果情報を取得する
 ********************************************************/

#include "nextion.h"

int displinkinfo(void)
{
    FILE    *fp;
    char    *tmpptr;
    char    cmdline[512]    = {'\0'};
    char    line[512]       = {'\0'};
    char    command[32]     = {'\0'};
    char    fname[32]       = {'\0'};

    /*
     * ログファイルからリフレクタへのリンク情報を抽出する
     */

    /* 日付入りログファイル名の作成 */
    timer = time(NULL);
    timeptr = gmtime(&timer);
    strftime(fname, sizeof(fname), "dstarrepeaterd-%Y-%m-%d.log", timeptr);
    sprintf(dstarlogpath, "%s%s", LOGDIR, fname);

    /* コマンドの標準出力オープン */
    sprintf(cmdline, "tail -n1 %s", dstarlogpath);
    if ((fp = popen(cmdline, "r")) != NULL ) {

        /* 接続リフレクタに関する標準出力を配列に取得 */
        fgets(line, sizeof(line), fp);

        /* [Linked] が含まれる行が有れば・・ */
        if ((tmpptr = strstr(line, "Linked")) != NULL) {

            /* 一巡して全く同じ内容ならパス */
            if (strncmp(tmpptr, tmpcheck, 20) != 0) {

                /* 一旦ダブりチェック用変数をクリアして新たに代入 */
                tmpcheck[0] = '\0';
                strncpy(tmpcheck, tmpptr, 20);

                /* リンク先リフレクタを取得 */
                linkref[0] = '\0';
                strncpy(linkref, tmpptr + 10, 8);
                linkref[8] = '\0';

                /* 接続時のログを取得 */
                status2[0] = '\0';
                strncpy(status2, tmpptr, 20);
                status2[20] = '\0';

                /* Nextion グローバル変数ref に接続中のリフレクタを代入 */
                sprintf(command, "IDLE.ref.txt=\"%s\"", linkref);
                sendcmd(command);
                sendcmd("IDLE.status.txt=ref.txt");
                sendcmd("IDLE.t1.txt=status.txt");

                /* ステータス２の表示 */
                sprintf(command, "IDLE.t2.txt=\"%s\"", status2);
                sendcmd(command);
            }
        }

        /* 標準出力クローズ */
        pclose(fp);

    } else {
        exit(EXIT_FAILURE);
    }

	return (EXIT_SUCCESS);
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
