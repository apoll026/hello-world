/* 
   1999년 7월 12일 

   unix 상에서 -m:* 등의 와일드 카드를 사용하게 되면 제대로 명령이 수행되지 않으므로 

   -m: 옵션의 경우 -m:199909 라고 주면 SCR 상에는 "-m:199909*"로 반영되게 수정했으며
                   -m:all 이라고 주면 SCR 상에는 "-m:*"로 반경되게 수정함. 

   -F: 옵션으로 사용자가 원하는 local output 화일을 지정할 수 있음.


 
   1999년 9월 7일 

   originator를 parameter로 받아서 조회할 수 있도록 수정 추가됨.
   -o:all로 주면 -o:*로 조회할 수 있도록함.



   1999년 9월 10일 

   중계 시스템 상 xmlstmsg의 옵션의 제약에 따라서 수행시 인수 값을 조정하여
   SCR 파일에 저장되도록 함.
   
   프로그램 수행시 parameter를 주지 않는 경우에는 원래의 SCR를 그냥 이용하게 하며
   인수가 있는 경우 그 인수만 SCR에 반영하게 함.
   원래 프로그램은 사용자가 인수를 2개중 1개를 줄 경우 원래의 SCR  파일에서
   나머지 1개 값을 받아서 이를 같이 이용하게 되어 있었는 데
   이러한 기능을 삭제함. -o 와 -m 옵션간의 충돌 때문에 이러한 기능은 
   사용상 오류를 낳을 수 있기 때문에 기능을 폐쇄함.   

   수정자 : 차민석  
*/

/****************************************************************************/
/*                                                                          */
/*  System      : XMSG System                                               */
/*  Subsystem   : Batch Firm Banking - TCP/IP Receiving Process             */
/*                                                                          */
/*  Function    : Message Receiving Process Using TCP/IP Protocol.          */
/*                                                                          */
/*  Attribute   :  file  name     task id.    priority    stack    ver      */
/*               [ tcprecv.c  ]   [      ]    [      ]    [   ]  [ 1.2 ]    */
/*                                                                          */
/*  ---- name ---- ------------ function -------------   -- date -- - ver - */
/*  (            ) (                                  )  (   .  .  )(  .  ) */
/*  (            ) (                                  )  (   .  .  )(  .  ) */
/*  (            ) (                                  )  (   .  .  )(  .  ) */
/*                                                                          */
/*                                                Updated By Hyun chul, Cho */
/*                                                Last Update : 98.05.15    */
/*                                                     Time   : 09:00       */
/****************************************************************************/
/**/
/****************************************************************************/
/*                                                                          */
/* [ Edition history ]                                                      */
/*                                                                          */
/* - no. - -- date -- ----- comments ----------------------------- -- by -- */
/* ( 01 )  (  .  .  ) (                                          )          */
/* ( 02 )  (98.05.15) ( stdout, stderr에 message를 출력하는 것을 ) Cho, H C */
/* (    )  (  .  .  ) ( log file에 출력, log file은 cfg file에   )          */
/* (    )  (  .  .  ) ( 기술된 갯수만큼 유지                     )          */
/* ( 03 )  (98.05.15) ( EDI Server의 IP Address 및 Port를 cfg    ) Cho, H C */
/* (    )  (  .  .  ) ( file에서 참조하게 함                     )          */
/*                                                                          */
/****************************************************************************/
/**/
/*****************************************************************************

 tcplstmsg.c (c)Copyright Systems Technology Management Co., 1994-1995
              All rights reserved.

              TCP File list receive program for message switching system
	      attach xmtcprecvd and xmsh and xmlstmsg and tcpftp

******************************************************************************/
/*****************************************************************************

   sys_errlist -> strerror 유닉스에서 리눅스서버로 교체로 변경 by pms 20100525

******************************************************************************/

#include "tcp_remote.h"
#include  <stdlib.h>
#include <string.h>

#define         TS       ( TimeString() )


// extern  char*   sys_errlist[];
extern __const char *__const sys_errlist[];

char*   _pzProFile = "TCPCLIENT.CFG";
char    szIPAddr[68];
int     nPortNo;
FILE*   LogFp;

/************************************************/
/*  Cho S.W : XMGETMSG.SCR UPDATE                */
/*  argument ---> writed  in file               */
/************************************************/
FILE         *fp;
int     Pre_Scrread();
int     Scr_Write();
char    Arg_buf[100];       /* temp buf */

char    FnameS[100];        /* output file name */
char    pnameS[100];        /* protocol : TCP/IP */
char    MnameS[100];        /* msg id */
char    TnameS[100];        /* type name */

/*added by mscha 19990907 */
char    OnameS[100];        /* originator name */

char    Update_Buf[200];


char    token1[100];        /* xmlstmsg : command */
char    token2[100];        /* msg id         */
char    token3[100];        /* originator name */
char    token4[100];        /* protocol             */
/************************************************/


/****************************************************************************/
/*   Function Name :                                                        */
/* ------------------------------------------------------------------------ */
/*   Function :                                                             */
/*   Argument :                                                             */
/*   Return   :                                                             */
/*   Edition history                                                        */
/* - No. - -- Date -- ----------- Comments ----------------------- -- By -- */
/* (    )  (  .  .  ) (                                          )          */
/* (    )  (  .  .  ) (                                          )          */
/****************************************************************************/

void    InitProc( pzPgmName )
char*   pzPgmName;
{
    LogFp = (FILE *)InitLog( pzPgmName );

    GetProfileString( "EDISVR", "IPADDR", "127.0.0.1", szIPAddr );
    GetProfileInt( "EDISVR", "PORTNO", 7000, &nPortNo );
}

/****************************************************************************/
/*   Function Name :                                                        */
/* ------------------------------------------------------------------------ */
/*   Function :                                                             */
/*   Argument :                                                             */
/*   Return   :                                                             */
/*   Edition history                                                        */
/* - No. - -- Date -- ----------- Comments ----------------------- -- By -- */
/* (    )  (  .  .  ) (                                          )          */
/* ( 02 )  (98.05.15) ( Add InitProc() Function                  ) Cho, H C */
/* (    )  (  .  .  ) ( EDI Server Connection 하는 부분 수정     ) Cho, H C */
/* (    )  (  .  .  ) (                                          )          */
/****************************************************************************/

main(argc, argv)
	int             argc;
	char           *argv[];
{

    int         sockfd;
    int         fd, sfd;
    struct      sockaddr_in     serv_addr;

    int         rc = 0, len = 0, nbytes = 0,i,j;
    int         exit_sw = 0;
    char        rCmd[80];
    char        filename[128];
    mode_t      SavedFileMask;

    /* =======   [S]  EDIT  002   ======= */
    InitProc( argv[0] );
    /* =======   [E]  EDIT  002   ======= */

    WriteLog( LogFp, "%s - =====  <<  XMLISTMSG JOB ---> START    >>  =====\n",
              TS );


    if ( argc > 1 ) {
        if ( argv[1][0] != '-' ) {
            WriteLog( LogFp, "%s - ERROR : Invalid Command Line Argument\n",
                      TS );
            exit(-1);
        }
    }

    if ( argc > 1 ) {
/* 

   Pre_Scrread()는 XTCTLST.SCR를 참조하여 각 값들을 입력하고 설정한다.
   전역변수인 token2,token3 등에도 값이 일차적으로 입력되게 된다.

   1999년 9월 10일 차민석 

*/
        rc = Pre_Scrread();
/*  

    SCR 화일에서 정보를 읽어서 값을 설정하는 부분을 
    모두 주석처리함.
    1999년 9월 10일 차민석 

        if ( argc > 1 ) {

                if ( MnameS[0] == NULL || MnameS[0] == 0x20 ) {
                        strcpy(MnameS, token2);
                }
                if ( OnameS[0] == NULL || OnameS[0] == 0x20 ) {
                        strcpy(OnameS, token3);
                }

     pnameS은 프로토콜과 관련된 내용으로 실제 프로그램상 SCRIPT 화일에 
     영향을 끼치지 않기 때문에 소스상에서 주석 처리 합니다.
     1999년 9월 10일 차민석 
                if ( pnameS[0] == NULL || pnameS[0] == 0x20 ) {
                        strcpy(pnameS, token4);
                }

        }
*/

/*

  실제 tcplstmsg 수행시 입력받은 인수를 이용하여 값을 바꾸어 넣고 있다.
  inmsum에 접속해서 실제 "xmlstmsg -m:xxxxxxx -o:****" 명령어를 수행할 수 있도록
  만들기 위해서 MnameS와 OnameS등을 추가하고 있다.

  1999년 9월 10일 차민석 
*/
        i = 0;
        while( i < argc ) {
                strcpy(Arg_buf, argv[i]);

                if ( strncmp("-F:", Arg_buf, 3) == 0 ) {
                        memset(FnameS, 0x00, sizeof(FnameS));
                        strcpy(FnameS, Arg_buf);
                }
                else if ( strncmp("-t:", Arg_buf, 3) == 0 ) {

                        memset(TnameS, 0x00, sizeof(TnameS));
                        strcpy(TnameS, Arg_buf);
                        
                }
                else if ( strncmp("-o:", Arg_buf, 3) == 0 ) {

                        memset(OnameS, 0x00, sizeof(OnameS));

                        if (strncmp("all",Arg_buf+3,3) == 0)
                        {
                          strcpy(OnameS,"-o:*");   
                        }
                        else
                        {
                            strcpy(OnameS, Arg_buf);
                        }
                }
/*
       사용자가 protocol과 관계된 인수를 입력하지 않으며
       또한 입력해도 본 프로그램에서는 반영이 되지 않으므로 
       주석 처리함.
       1999년 10월 9일 차민석
   
                else if ( strncmp("-p:", Arg_buf, 3) == 0 ) {
                        memset(pnameS, 0x00, sizeof(pnameS));
                        strcpy(pnameS, Arg_buf);
                }

*/
                else if ( strncmp("-m:", Arg_buf, 3) == 0 ) {

                        memset(MnameS, 0x00, sizeof(MnameS));
/* From here added by mscha 19990712 */
                        if (strncmp("all",Arg_buf+3,3) == 0)
                        {
                          strcpy(MnameS,"-m:*");   
                        }
                        else
                        {
                            strcpy(MnameS, Arg_buf);
                            strcat(MnameS,"*"); 
                        }
/* To here added by mscha 19990712 */
               }
               i++;
        }
/* 
   사용자들에게 입력받은 인수와 원래의 SCR 화일에 있던 것들을 처리하여 
   아래의 Update_Buf라는 String을 완성하고 있다.
   이 문자열을 아래 Scr_Write에서 새롭게 작성되는 tmp화일의 세번째 줄에 
   써준다. 

   새로운 tmp화일이 완성되면 아래 system 명령어를 이용하여 
   원래의 SCR화일을 백업한 후 변경하게 된다.

   1999년 9월 10일 차민석 
*/
        memset(Update_Buf, 0x00, sizeof(Update_Buf));

        sprintf(Update_Buf, "%cxmlstmsg %s %s -p:ITCP/IP%c # recv command",
                0x22, MnameS, OnameS, 0x22);

        rc = Scr_Write();
        system("cp XTCPLST.SCR XTCPLST.bak");
        system("cp XTCPLST.tmp XTCPLST.SCR");
    }


    /*
     * Fill the structure "serv_addr" with the addres of the
     * server that we want to connect with.
     */

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family        = AF_INET;
    serv_addr.sin_addr.s_addr   = inet_addr( szIPAddr );
    serv_addr.sin_port          = htons( nPortNo );

    /*
     * Open a TCP socket (an Internet stream socket).
     */

    if ((sockfd = socket(AF_INET, SOCK_STREAM,0)) < 0) {
        WriteLog( LogFp, "%s - ERROR : CREATE SOCKET - %s\n",
                  TS,  strerror(errno));
        exit( 1 );
    }

    /*
     * Connect to the server.
     */

    if (connect(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) <0) {
        WriteLog( LogFp, "%s - ERROR : CONNECT TO EDI SERVER - %s\n",
                  TS, strerror(errno));
        exit(1);
    }

    WriteLog( LogFp, "%s - CONNECT TO EDI SERVER FOR LIST MSG\n", TS );

    /*
     * Script file open and read.
     * user group, login id, passwd, command line, file path
     */
    if ((scr_fd = open(_TCP_LSTSCR_, O_RDONLY, 0)) < 0) {
        WriteLog( LogFp, "%s - ERROR : OPEN SCRIPT FILE - %s\n",
                  TS, strerror(errno));
        exit(1);
    }

    /* read tcp/ip user group */
    rc = Read_Scrfile(scr_fd);                  /* read user group */
    if (rc == 0) {
        WriteLog( LogFp, "%s - ERROR : READ USER GROUP IN SCRIPT FILE\n", TS );
        exit( 1 );
    }

    rc = Xcmd_Exect(xcmd_parm);                 /* extract user group */
    strcpy(tcpuser_group, xcmd_parm[0]);

    /* receive host command (request tcp user group) */
    rc = TCP_data_recv(sockfd);
    if (rc <= 0) TCP_exit(_TCP_LSTMSG_, rc, -1);
    
    if (strcmp(tcp_rbuf, _TCP_REQGRP_) != 0) {
        WriteLog( LogFp, "%s - ERROR : NOT HOST USER GROUP REQUEST\n", TS );
        exit( 1 );
    }

    strcpy(tcp_sbuf, tcpuser_group);
    rc = TCP_data_send(sockfd, strlen(tcp_sbuf));
    if (rc <= 0) TCP_exit(_TCP_LSTMSG_, rc, -2);

    /*
     * receive host command (request ID and passwd)
     */
    rc = TCP_data_recv(sockfd);
    if (rc <= 0) TCP_exit(_TCP_LSTMSG_, rc, -3);
    
    if (strcmp(tcp_rbuf, _TCP_REQLOGIN_) != 0) {
        WriteLog( LogFp, "%s - ERROR : NOT HOST USER ID REQUEST\n", TS );
        exit( 1 );
    }

    /* read tcp/ip user ID and passwd */
    rc = Read_Scrfile(scr_fd);                  /* read user ID and passwd */
    if (rc == 0) {
        WriteLog( LogFp, "%s - ERROR : READ USER ID IN SCRIPT FILE\n", TS );
        exit( 1 );
    }

    rc = Xcmd_Exect(xcmd_parm);                 /* extract user ID */
    /* tcp_sbuf set data send */

    rc = TCP_data_send(sockfd, strlen(tcp_sbuf));
    if (rc <= 0) TCP_exit(_TCP_LSTMSG_, rc, -4);

    /*
     * read Command line (loop command multi destination)
     */
    for (;;) {		/* start of command loop for xmsh */

	len = Read_Scrfile(scr_fd);		/* Script file 1 line read */
	if (len <= 0) {			/* command line in script file */
            exit_sw = 1;
	}

	rc = Xcmd_Exect(xcmd_parm);	/* only use check Script file syntex */
	strcpy(rCmd, tcp_sbuf);

        rc = TCP_data_recv(sockfd);		/* Receive host request cmd */
	if (rc <= 0) TCP_exit(_TCP_LSTMSG_, rc, -5);

        if (strcmp(tcp_rbuf, _TCP_REQCMD_) != 0) {
            WriteLog( LogFp, "%s - ERROR : NOT HOST COMMAND REQUEST\n", TS );
            exit( 1 );
        }

        if (exit_sw == 1)  strcpy(tcp_sbuf, _TCP_CMDEXIT_);

        if (exit_sw == 0) {
            strcpy(tcp_sbuf, rCmd);

            WriteLog( LogFp, "%s - SEND COMMAND : %s\n",
                  TS, strtok( rCmd, "#\n" ) );
        }

        len = strlen(tcp_sbuf) + 1;
        rc = TCP_data_send(sockfd, len);        /* Send Command Line */
        if (rc <= 0) TCP_exit(_TCP_LSTMSG_, rc, -6);

	if (exit_sw == 1) break;	/* Cmd line end PGM. end */

	len = Read_Scrfile(scr_fd);	/* Script file read recv filename */
	if (len == 0) {			/* receive file full path */
            WriteLog( LogFp, "%s - ERROR : NO FILE NAME IN SCRIPT FILE\n",
                      TS );
            exit( 1 );
	}

	rc = Xcmd_Exect(xcmd_parm);	/* extract receive file name */
	strcpy(filename, xcmd_parm[1]);

        /*
         * open receive file and data read
         */

        SavedFileMask = umask( 0 );

        if((sfd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0660)) < 0) {
            WriteLog( LogFp, "%s - ERROR : OPEN LIST FILE - %s\n", TS,
                      strerror(errno));
            exit( 1 );
        }   

        umask( SavedFileMask );

        /*
         * receive host command (request send sending filename)
         */
        for (;;) {				/* receive multimessage loop */

            rc = TCP_data_recv(sockfd);		/* Receive host request cmd */
	    if (rc <= 0) TCP_exit(_TCP_LSTMSG_, rc, -7);

                                                /* end of msg loop */
            if (strcmp(tcp_rbuf, _TCP_REQMSGE_) == 0){
                 strcpy (tcp_sbuf, _TCP_ACKOK_);
                 rc = TCP_data_send(sockfd, 11);
                 if (rc <= 0) TCP_exit(_TCP_LSTMSG_, rc, -8);
		 break;
	    }
                                                /* request receive */
            if (strcmp(tcp_rbuf, _TCP_REQFTPR_) != 0) {
                WriteLog( LogFp, "%s - ERROR : NO LIST OR INVALID COMMAND\n",
                          TS ); 
                exit( 1 );
            }

            strcpy (tcp_sbuf, _TCP_ACKOK_);
            rc = TCP_data_send(sockfd, 11);
            if (rc <= 0) TCP_exit(_TCP_LSTMSG_, rc, -8);

            /*
             * receive host command (request data receive command)
             */
            rc = TCP_data_recv(sockfd);     /* Receive host request cmd */
            if (rc <= 0) TCP_exit(_TCP_LSTMSG_, rc, -9);
                                            /* request data receive ? */
            if (strcmp(tcp_rbuf, _TCP_REQFTPD_) != 0) {
                WriteLog( LogFp, "%s - ERROR : NOT HOST REQUEST[%s]\n",
                          TS, _TCP_REQFTPD_ );
                exit( 1 );
            }

            strcpy (tcp_sbuf, _TCP_ACKOK_);
            rc = TCP_data_send(sockfd, 11);
            if (rc <= 0) TCP_exit(_TCP_LSTMSG_, rc, -10);

            /*
             * receive data from remote host
             */
            nbytes = 0;
            for(;;) {

                len = rc = TCP_data_recv(sockfd);
                if (rc <= 0) TCP_exit(_TCP_LSTMSG_, rc, -11);

                if(len <= 0) break;

                if (strcmp(tcp_rbuf, _TCP_FEOF_) == 0) {
                    if ((strlen(&tcp_rbuf[11]) == 10)
                    && (atoi(&tcp_rbuf[11]) == nbytes)) break;
                }

                if (write (sfd, tcp_rbuf, len) < 0) {
                    WriteLog( LogFp, "%s - ERROR : WRITE LIST DATA - %s\n",
                              TS, strerror(errno));
                    close(sfd);
                    close(fd);
                    close(sockfd);
                    exit(1);
                }

                strcpy (tcp_sbuf, _TCP_ACKOK_);
                rc = TCP_data_send(sockfd, 11);
                if (rc <= 0) TCP_exit(_TCP_LSTMSG_, rc, -12);

                nbytes += len;

            }                                       /* end of for */

            strcpy (tcp_sbuf, _TCP_ACKOK_);
            rc = TCP_data_send(sockfd, 11);
            if (rc <= 0) TCP_exit(_TCP_LSTMSG_, rc, -13);

        }                                       /* end of multi message loop */
        close(sfd);
    }                           /* end of  command loop for xmsh */
    rc = TCP_data_recv(sockfd);
    if (rc <= 0) TCP_exit(_TCP_LSTMSG_, rc, -14);

    if (strcmp(tcp_rbuf, _TCP_NRMEND_) != 0) {
        WriteLog( LogFp, "%s - ERROR : SERVER ABNORMALY ENDED\n", TS );
    } else {
        WriteLog( LogFp, "%s - =====  << LIST JOB ---> ALL DONE >>  =====\n\n",
                  TS );
    }

    close(sockfd);
    close(fd);

    exit(0);
}

/*
 * file 1 line read and data send
 */
int     Read_Scrfile(fd)
        int     fd;
{
    int     len = 0;
    int     rc;

    for (;;) {
        rc = read(fd, &tcp_sbuf[len], 1);
        if (rc == 0) break;
        if (rc == -1) {
            WriteLog( LogFp, "%s - ERROR : READ SCRIPT - %s\n",
                      TS, strerror(errno));
            exit(1);
        }
        if (tcp_sbuf[len] == 0x0a) {
            tcp_sbuf[len] == 0x00;
            break;
        }
        len++;
    }

    return(len);
}

/*
 * extract script command line
 */
int     Xcmd_Exect(xcmd_parm)
char    xcmd_parm[5][80];
{
        int     i, j, k, sw;

        i = j = k = sw = 0;
        for (i = 0; i < strlen(tcp_sbuf); i++) {
                if (tcp_sbuf[i] == '#') break;
                if (tcp_sbuf[i] == '\"') {
                        if (sw == 0) { sw = 1; k = 0; i++; }
                        else { sw =0; xcmd_parm[j][k] = 0x00; j++; }
                }
                if (sw == 1) {
                        xcmd_parm[j][k] = tcp_sbuf[i];
                        k++;
                }
        }
        if (sw == 1) {
            WriteLog( LogFp, "%s - ERROR : WRONG SCRIPT SYNTEX\n", TS );
            exit (1);

        }
        return(j);
}




int     Scr_Write()
{
    FILE    *fd;
    char    scrbuf[100];
    int     rc, i;

    if ((fd = fopen(_TCP_LSTSCR_, "r")) == NULL) {
        WriteLog( LogFp, "%s - ERROR : OPEN SCRIPT FILE - %s\n",
                  TS, strerror(errno));
        exit(1);
    }

    memset(scrbuf, 0x00, sizeof(scrbuf));

    if ((fp=fopen("XTCPLST.tmp", "w"))==NULL) {
        WriteLog( LogFp, "%s - ERROR : OPEN TEMP SCRIPT FILE - %s\n",
                  TS, strerror(errno));
        exit(-1);
    }

    i = 0;
/* 위에서 원래의 XTCPLST.SCR 을 읽기로 열고
                 XTCPLST.tmp 를 쓰기로 열어서
   처음 두줄 즉 그룹 ID와 ID&PASSWORD는 그대로 쓰고 
   세번째 줄 "xmgetmsg ..." 부분은 main 함수에서 사용자 인수를 받아서 준비된  Update_Buf로 쓰고
   마자막 줄은 프로토콜과 로컬에 저장될 화일을 입력하여 쓴다

   1999년 9월 10일 차민석 
*/
    while (fgets(scrbuf, sizeof(scrbuf), fd), !feof(fd)) {
        fprintf( fp, "%s", scrbuf);
        i++;
        if ( i > 1 ) break;
    }

    fprintf( fp, "%s\n", Update_Buf);

    if ( FnameS[0] == '-' )  strcpy(FnameS, &FnameS[3]);

    fprintf( fp, "%c%s%c,%c%s%c # send file path\n",
             0x22, xcmd_parm[0],0x22, 0x22, FnameS, 0x22);
    fclose(fp);
    fclose (fd);
    return 0;
}

int     Pre_Scrread()
{
    int rc, i, j, count_tt;
    int sab_count = 0;  /* start end  count */


    memset(token1, 0x00, sizeof(token1));
    memset(token2, 0x00, sizeof(token2));
    memset(token3, 0x00, sizeof(token3));
    memset(token4, 0x00, sizeof(token4));

    if ((scr_fd = open(_TCP_LSTSCR_, O_RDONLY, 0)) < 0) {
        WriteLog( LogFp, "%s - ERROR : OPEN SCRIPT FILE : %s - %s\n",
                  TS, _TCP_LSTSCR_, strerror(errno));
        exit(1);
    }

    rc = Read_Scrfile(scr_fd);                  /* read user group */
    if (rc == 0) {
        WriteLog( LogFp, "%s - ERROR : READ USER GROUP IN SCRIPT FILE\n", TS );
        exit(1);
    }
    rc = Read_Scrfile(scr_fd);               /* read ID & Password */
    rc = Read_Scrfile(scr_fd);                  /* read xmlistmsg line */

    i = 0; count_tt = 1; sab_count = 0; j = 0;
    while( 1 ) {

/*  from added by a h s 0423 : title allowd space and double quotation  */
        if ( tcp_sbuf[i] == '#' || i > 250 || sab_count >= 4) break;
/*  to   added by a h s 0423 : title allowd space and double quotation  */
        if ( tcp_sbuf[i] == '"') {
                i++;
                sab_count++;
                continue;
        }
        if ( tcp_sbuf[i] == 0x20 ) {
                j = 0;
                count_tt++;

        } else {
                if ( count_tt == 1 ) {
                        token1[j++] = tcp_sbuf[i];
                }
                if ( count_tt == 2 ) {
                        token2[j++] = tcp_sbuf[i];
                }
                if ( count_tt == 3 ) {
                        token3[j++] = tcp_sbuf[i];
                }
                if ( count_tt == 4 ) {
                        token4[j++] = tcp_sbuf[i];
                }
        }
        i++;
    }
    rc = Read_Scrfile(scr_fd);                  /* xmorign read */
    rc = Xcmd_Exect(xcmd_parm);                 /* extract user group */
    strcpy(FnameS, xcmd_parm[1]);
    close(scr_fd);
    return 0;
}


