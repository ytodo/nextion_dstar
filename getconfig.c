#include "nextion.h"

/*********************************************
 * 環境設定ファイルnextion.ini の内容を読む
 *********************************************/

FILE    *fp;

int getconfig(void)
{
    char    *ret;
    char    *cmdline;
    char    line[64]   = {'\0'};
    char    ifname[10] = {'\0'};
    char    ifaddr[20] = {'\0'};
    char    band[10]   = {'\0'};
    int     i = 0;

    /*
     * 設定ファイルをオープンする
     */
    if ((fp = fopen(CONFFILE, "r")) != NULL) {
        /* テーブルを読み込み変数に格納する */
        while ((fgets(line, sizeof(line), fp)) != NULL) {
            if ((ret = strstr(line, "callsign"))     != NULL) sscanf(line, "callsign=%[^\n]",     station);
            if ((ret = strstr(line, "localAddress")) != NULL) sscanf(line, "localAddress=%[^\n]", ipaddress);
            if ((ret = strstr(line, "modemType"))    != NULL) sscanf(line, "modemType=%[^\n]",    modemtype);
        }

        /* ファイルクローズ */
        fclose(fp);

        /* ステーション名にバンド名を追加設定 */
        if (strcmp(&station[7], "B") == 0) strcpy(band, " (70cm)");
        if (strcmp(&station[7], "C") == 0) strcpy(band, " (2m)");
        strcat(station, band);
    }

    /*
     * コマンドの標準出力オープン（ネットワークインターフェース名取得）
     */
    cmdline = "for DEV in `find /sys/devices -name net | grep -v virtual`; do ls $DEV/; done";
    if ((fp = popen(cmdline, "r")) != NULL) {
        fgets(ifname, sizeof(ifname), fp);
        ifname[strlen(ifname) - 1] = '\0';

        /* 標準出力クローズ */
        pclose(fp);
    }

    /*
     * コマンドの標準出力オープン（IPアドレスの取得）
     */
    cmdline = "hostname -I | cut -f1 -d' '";
    if ((fp = popen(cmdline, "r")) != NULL) {
        fgets(ifaddr, sizeof(ifaddr), fp);

        /* 設定IP アドレスと実際のIP アドレスの比較 */
        if (strcmp(ifaddr, ipaddress) == 0) {
            strcpy(ipaddress, "Different IP set!");
        } else {
            sprintf(ipaddress, "%s:%s", ifname, ifaddr);
        }

        /* 標準出力クローズ */
        pclose(fp);
    }

    return (0);
}

