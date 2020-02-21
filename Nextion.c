#include "Nextion.h"

char	status[CHARSIZE]	= {'\0'};
char	status2[CHARSIZE]	= {'\0'};
char	linkref[CHARSIZE]	= {'\0'};
char	usercmd[CHARSIZE]	= {'\0'};
char	station[CHARSIZE]	= {'\0'};
char	ifname[CHARSIZE]	= {'\0'};
char	ipaddress[CHARSIZE]	= {'\0'};
char	localport[CHARSIZE]	= {'\0'};
char	modemtype[CHARSIZE]	= {'\0'};
char	cputemp[CHARSIZE]	= {'\0'};
char	dstarlogpath[CHARSIZE]	= {'\0'};
char	chklink[CHARSIZE]	= {'\0'};
char	chklink2[CHARSIZE]	= {'\0'};
char	chkstat[256]		= {'\0'};
char	chkstat2[256]		= {'\0'};
char	chkstat3[256]		= {'\0'};
int	cnt_temp		= SLEEPCOUNT;
int	net_flag		= 0;
int	rf_flag			= 0;
