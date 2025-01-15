/*
 * Definitions for TCP client/ server programs
 */

#include	<stdio.h>
#include	<fcntl.h>
#include	<sys/stat.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<sys/errno.h>

#include	"xmsg_env.h"

/* EDIXMSG */
/*
#define SERV_TCP_PORT  6044  
*/
/* 0x1771 : FIRM BANKING */
/*
#define SERV_TCP_PORT  6001  
*/
/* 0x177A : POS-EDI      */
/**
#define SERV_TCP_PORT  6010  
**/
#define SERV_TCP_PORT  6001  

#define SERV_HOST_ADDR	"165.243.17.130" /* host addr for server */

extern	int	errno;
char	*pname;

char	pgm_name[80];
char	scr_file[128];			/* script file name */

char	tcp_rbuf[128];
char	tcp_sbuf[128];
int	scr_fd;
char	tcpuser_group[20];
char	xcmd_parm[5][80];
int     parm_count;
