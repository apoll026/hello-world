
/*****************************************************************************

xmsg_env.h    (c)Copyright Systems Technology Management Inc., 1993-1994
              All rights reserved.

              EDI message switching system's definition macro, global variables
              and function prototypes.

******************************************************************************/

#ifndef __XMSG_ENV__
#define __XMSG_ENV__

#define _ERR_TIMEOUT_		-2

/**
#ifdef _FIRMBANKING
#define _TCPTMP_PATH_		"/home/edi/xmsg/tmp/tcp.tmp."
#define _X25TMP_PATH_		"/home/edi/xmsg/tmp/x25.tmp."
#elif _POSEDI
#define _TCPTMP_PATH_		"/home/edi/work/tmp/tcp.tmp."
#define _X25TMP_PATH_		"/home/edi/work/tmp/x25.tmp."
#elif _BOOK_VAN
#define _TCPTMP_PATH_		"/home/xmsg/tmp/tcp.tmp."
#define _X25TMP_PATH_		"/home/xmsg/tmp/x25.tmp."
#endif 
**/
#define _TCPTMP_PATH_		"/home/edi/xmsg/tmp/tcp.tmp."
#define _X25TMP_PATH_		"/home/edi/xmsg/tmp/x25.tmp."

#define _ZMODEM_USER_INFO        "/home/edi/xmsg/bin/ZmodemUserProf.info"

/*************************************************************************
    Log Name Define
**************************************************************************/
extern FILE	*log_fd;

#define _PERROR_(x)	fprintf( log_fd, "[%s][%d]\n", P_time(x), errno ) ;
#define _S_PERROR_(x)	fprintf( stderr, "[%s][%d]\n", P_time(x), errno ) ;

/*************************************************************************
    Execute Name Define
**************************************************************************/
#define _XMSH_DAE_		"xmsh"

#define _TCP_RCVDAEMON_		"xmtcprecvd"
#define _TCP_DELMSG_		"tcpdelmsg"
#define _TCP_LSTMSG_		"tcplstmsg"
#define _TCP_RECV_		"tcprecv"
#define _TCP_SEND_		"tcpsend"
#define _TCP_SUM_		"tcpsummsg"

#define _XM_DELMSG_		"xmdelmsg"
#define _XM_DELSMSG_            "xmdelsmsg"

#define _X25_RCVDAEMON_		"xmx25recvd"
#define _X25_DELMSG_		"x25delmsg"
#define _X25_LSTMSG_		"x25lstmsg"
#define _X25_RECV_		"x25recv"
#define _X25_SEND_		"x25send"
#define _X25_SUM_		"x25summsg"

#define _T_XMSH_		P_time(_XMSH_DAE_)
#define _T_TCPRCV_		P_time(_TCP_RCVDAEMON_)
#define _T_X25RCV_		P_time(_X25_RCVDAEMON_)

/*************************************************************************
    TCP Value Define
**************************************************************************/

#define _TCP_LOGFILE_		"tcpstderr.tmp"
#define _TCP_MAXPRO_		5

#define _TCP_RCV_TIMEOUT_	120
#define _TCP_SND_TIMEOUT_	120

#define _TCP_REQGRP_		"Req. Ugrp."
#define _TCP_REQLOGIN_		"Req. Login"
#define _TCP_REQCMD_		"Req. Cmd.."
#define _TCP_REQMSGE_		"Req. MmsgE"
#define _TCP_REQFTPS_		"Req. ftpS."
#define _TCP_REQFTPR_		"Req. ftpR."
#define _TCP_REQFTPD_		"Req. ftpD."
#define _TCP_NRMEND_		"Normal END"
#define _TCP_ACKOK_		"Ans. OK..."
#define _TCP_CMDEXIT_		"exit"
#define _TCP_FEOF_		"Req.ftpEOF"

#define _TCP_DELSCR_		"XTCPDELTEST.SCR"
#define _TCP_LSTSCR_		"XTCPLSTTEST.SCR"
#define _TCP_GETSCR_		"XTCPGETTEST.SCR"
#define _TCP_ORIGSCR_		"XTCPORIGTEST.SCR"
#define _TCP_SUMSCR_		"XTCPSUM.SCR"

/*************************************************************************
    X25 Value Define
**************************************************************************/

#define _X25_LOGFILE_		"x25stderr.tmp"
#define _X25_MAXPRO_		5

#define _X25_RCV_TIMEOUT_	120
#define _X25_SND_TIMEOUT_	120

#define _X25_REQGRP_		"Req. Ugrp."
#define _X25_REQLOGIN_		"Req. Login"
#define _X25_REQCMD_		"Req. Cmd.."
#define _X25_REQMSGE_		"Req. MmsgE"
#define _X25_REQFTPS_		"Req. ftpS."
#define _X25_REQFTPR_		"Req. ftpR."
#define _X25_REQFTPD_		"Req. ftpD."
#define _X25_NRMEND_		"Normal END"
#define _X25_ACKOK_		"Ans. OK..."
#define _X25_CMDEXIT_		"exit"
#define _X25_FEOF_		"Req.ftpEOF"

#define _X25_PADADDR_		"12241185010"
/**
edisvr y2k test
#define _X25_PADADDR_		"7.1234567"
**/


#define _X25_DELSCR_		"XX25DEL.SCR"
#define _X25_LSTSCR_		"XX25LST.SCR"
#define _X25_GETSCR_		"XX25GET.SCR"
#define _X25_ORIGSCR_		"XX25ORIG.SCR"
#define _X25_SUMSCR_		"XX25SUM.SCR"

/*************************************************************************
    XM Value Define
**************************************************************************/

#define _XM_DELMSG_		"xmdelmsg"
#define _XM_GETMSG_		"xmgetmsg"

#endif
