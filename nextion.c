#include "nextion.h"

char    tmstr[256]             = {'\0'};
char	status[CHARSIZE] 	   = {'\0'};
char    status2[CHARSIZE]      = {'\0'};
char    linkref[CHARSIZE]      = {'\0'};
char	usercmd[CHARSIZE]	   = {'\0'};
char    station[CHARSIZE]      = {'\0'};
char    ipaddress[CHARSIZE]    = {'\0'};
char    modemtype[CHARSIZE]    = {'\0'};
char    cputemp[CHARSIZE]      = {'\0'};
char    dstarlogpath[CHARSIZE] = {'\0'};
char    tmpcheck[CHARSIZE]     = {'\0'};
char    refcheck[CHARSIZE]     = {'\0'};
char    statcheck[CHARSIZE]    = {'\0'};
int     cnt_temp               = SLEEPCOUNT;
