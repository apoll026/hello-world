/* 
   1999�� 7�� 12�� 

   unix �󿡼� -m:* ���� ���ϵ� ī�带 ����ϰ� �Ǹ� ����� ����� ������� �����Ƿ� 

   -m: �ɼ��� ��� -m:199909 ��� �ָ� SCR �󿡴� "-m:199909*"�� �ݿ��ǰ� ����������
                   -m:all �̶�� �ָ� SCR �󿡴� "-m:*"�� �ݰ�ǰ� ������. 

   -F: �ɼ����� ����ڰ� ���ϴ� local output ȭ���� ������ �� ����.


 
   1999�� 9�� 7�� 

   originator�� parameter�� �޾Ƽ� ��ȸ�� �� �ֵ��� ���� �߰���.
   -o:all�� �ָ� -o:*�� ��ȸ�� �� �ֵ�����.



   1999�� 9�� 10�� 

   �߰� �ý��� �� xmlstmsg�� �ɼ��� ���࿡ ���� ����� �μ� ���� �����Ͽ�
   SCR ���Ͽ� ����ǵ��� ��.
   
   ���α׷� ����� parameter�� ���� �ʴ� ��쿡�� ������ SCR�� �׳� �̿��ϰ� �ϸ�
   �μ��� �ִ� ��� �� �μ��� SCR�� �ݿ��ϰ� ��.
   ���� ���α׷��� ����ڰ� �μ��� 2���� 1���� �� ��� ������ SCR  ���Ͽ���
   ������ 1�� ���� �޾Ƽ� �̸� ���� �̿��ϰ� �Ǿ� �־��� ��
   �̷��� ����� ������. -o �� -m �ɼǰ��� �浹 ������ �̷��� ����� 
   ���� ������ ���� �� �ֱ� ������ ����� �����.   

   ������ : ���μ�  
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
/* ( 02 )  (98.05.15) ( stdout, stderr�� message�� ����ϴ� ���� ) Cho, H C */
/* (    )  (  .  .  ) ( log file�� ���, log file�� cfg file��   )          */
/* (    )  (  .  .  ) ( ����� ������ŭ ����                     )          */
/* ( 03 )  (98.05.15) ( EDI Server�� IP Address �� Port�� cfg    ) Cho, H C */
/* (    )  (  .  .  ) ( file���� �����ϰ� ��                     )          */
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

   sys_errlist -> strerror ���н����� ������������ ��ü�� ���� by pms 20100525

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
/* (    )  (  .  .  ) ( EDI Server Connection �ϴ� �κ� ����     ) Cho, H C */
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

   Pre_Scrread()�� XTCTLST.SCR�� �����Ͽ� �� ������ �Է��ϰ� �����Ѵ�.
   ���������� token2,token3 ��� ���� ���������� �Էµǰ� �ȴ�.

   1999�� 9�� 10�� ���μ� 

*/
        rc = Pre_Scrread();
/*  

    SCR ȭ�Ͽ��� ������ �о ���� �����ϴ� �κ��� 
    ��� �ּ�ó����.
    1999�� 9�� 10�� ���μ� 

        if ( argc > 1 ) {

                if ( MnameS[0] == NULL || MnameS[0] == 0x20 ) {
                        strcpy(MnameS, token2);
                }
                if ( OnameS[0] == NULL || OnameS[0] == 0x20 ) {
                        strcpy(OnameS, token3);
                }

     pnameS�� �������ݰ� ���õ� �������� ���� ���α׷��� SCRIPT ȭ�Ͽ� 
     ������ ��ġ�� �ʱ� ������ �ҽ��󿡼� �ּ� ó�� �մϴ�.
     1999�� 9�� 10�� ���μ� 
                if ( pnameS[0] == NULL || pnameS[0] == 0x20 ) {
                        strcpy(pnameS, token4);
                }

        }
*/

/*

  ���� tcplstmsg ����� �Է¹��� �μ��� �̿��Ͽ� ���� �ٲپ� �ְ� �ִ�.
  inmsum�� �����ؼ� ���� "xmlstmsg -m:xxxxxxx -o:****" ��ɾ ������ �� �ֵ���
  ����� ���ؼ� MnameS�� OnameS���� �߰��ϰ� �ִ�.

  1999�� 9�� 10�� ���μ� 
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
       ����ڰ� protocol�� ����� �μ��� �Է����� ������
       ���� �Է��ص� �� ���α׷������� �ݿ��� ���� �����Ƿ� 
       �ּ� ó����.
       1999�� 10�� 9�� ���μ�
   
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
   ����ڵ鿡�� �Է¹��� �μ��� ������ SCR ȭ�Ͽ� �ִ� �͵��� ó���Ͽ� 
   �Ʒ��� Update_Buf��� String�� �ϼ��ϰ� �ִ�.
   �� ���ڿ��� �Ʒ� Scr_Write���� ���Ӱ� �ۼ��Ǵ� tmpȭ���� ����° �ٿ� 
   ���ش�. 

   ���ο� tmpȭ���� �ϼ��Ǹ� �Ʒ� system ��ɾ �̿��Ͽ� 
   ������ SCRȭ���� ����� �� �����ϰ� �ȴ�.

   1999�� 9�� 10�� ���μ� 
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
/* ������ ������ XTCPLST.SCR �� �б�� ����
                 XTCPLST.tmp �� ����� ���
   ó�� ���� �� �׷� ID�� ID&PASSWORD�� �״�� ���� 
   ����° �� "xmgetmsg ..." �κ��� main �Լ����� ����� �μ��� �޾Ƽ� �غ��  Update_Buf�� ����
   ���ڸ� ���� �������ݰ� ���ÿ� ����� ȭ���� �Է��Ͽ� ����

   1999�� 9�� 10�� ���μ� 
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


