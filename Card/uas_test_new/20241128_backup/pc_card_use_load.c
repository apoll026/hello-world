
/* Result Sets Interface */
#ifndef SQL_CRSR
#  define SQL_CRSR
  struct sql_cursor
  {
    unsigned int curocn;
    void *ptr1;
    void *ptr2;
    unsigned int magic;
  };
  typedef struct sql_cursor sql_cursor;
  typedef struct sql_cursor SQL_CURSOR;
#endif /* SQL_CRSR */

/* Thread Safety */
typedef void * sql_context;
typedef void * SQL_CONTEXT;

/* Object support */
struct sqltvn
{
  unsigned char *tvnvsn; 
  unsigned short tvnvsnl; 
  unsigned char *tvnnm;
  unsigned short tvnnml; 
  unsigned char *tvnsnm;
  unsigned short tvnsnml;
};
typedef struct sqltvn sqltvn;

struct sqladts
{
  unsigned int adtvsn; 
  unsigned short adtmode; 
  unsigned short adtnum;  
  sqltvn adttvn[1];       
};
typedef struct sqladts sqladts;

static struct sqladts sqladt = {
  1,1,0,
};

/* Binding to PL/SQL Records */
struct sqltdss
{
  unsigned int tdsvsn; 
  unsigned short tdsnum; 
  unsigned char *tdsval[1]; 
};
typedef struct sqltdss sqltdss;
static struct sqltdss sqltds =
{
  1,
  0,
};

/* File name & Package Name */
struct sqlcxp
{
  unsigned short fillen;
           char  filnam[20];
};
static struct sqlcxp sqlfpn =
{
    19,
    "pc_card_use_load.pc"
};


static unsigned int sqlctx = 40553259;


static struct sqlexd {
   unsigned long  sqlvsn;
   unsigned int   arrsiz;
   unsigned int   iters;
   unsigned int   offset;
   unsigned short selerr;
   unsigned short sqlety;
   unsigned int   occurs;
            short *cud;
   unsigned char  *sqlest;
            char  *stmt;
   sqladts *sqladtp;
   sqltdss *sqltdsp;
   unsigned char  **sqphsv;
   unsigned long  *sqphsl;
            int   *sqphss;
            short **sqpind;
            int   *sqpins;
   unsigned long  *sqparm;
   unsigned long  **sqparc;
   unsigned short  *sqpadto;
   unsigned short  *sqptdso;
   unsigned int   sqlcmax;
   unsigned int   sqlcmin;
   unsigned int   sqlcincr;
   unsigned int   sqlctimeout;
   unsigned int   sqlcnowait;
            int   sqfoff;
   unsigned int   sqcmod;
   unsigned int   sqfmod;
   unsigned char  *sqhstv[46];
   unsigned long  sqhstl[46];
            int   sqhsts[46];
            short *sqindv[46];
            int   sqinds[46];
   unsigned long  sqharm[46];
   unsigned long  *sqharc[46];
   unsigned short  sqadto[46];
   unsigned short  sqtdso[46];
} sqlstm = {12,46};

/* SQLLIB Prototypes */
extern sqlcxt (/*_ void **, unsigned int *,
                   struct sqlexd *, struct sqlcxp * _*/);
extern sqlcx2t(/*_ void **, unsigned int *,
                   struct sqlexd *, struct sqlcxp * _*/);
extern sqlbuft(/*_ void **, char * _*/);
extern sqlgs2t(/*_ void **, char * _*/);
extern sqlorat(/*_ void **, unsigned int *, void * _*/);

/* Forms Interface */
static int IAPSUCC = 0;
static int IAPFAIL = 1403;
static int IAPFTL  = 535;
extern void sqliem(/*_ char *, int * _*/);

typedef struct { unsigned short len; unsigned char arr[1]; } VARCHAR;
typedef struct { unsigned short len; unsigned char arr[1]; } varchar;

/* CUD (Compilation Unit Data) Array */
static short sqlcud0[] =
{12,4274,840,0,0,
5,0,0,1,0,0,539,105,0,0,4,4,0,1,0,1,97,0,0,1,10,0,0,1,10,0,0,1,10,0,0,
36,0,0,2,1412,0,515,239,0,0,46,46,0,1,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,
97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,9,0,0,1,97,0,0,1,97,0,0,1,9,0,0,1,97,0,0,1,
9,0,0,1,9,0,0,1,9,0,0,1,9,0,0,1,9,0,0,1,9,0,0,1,97,0,0,1,9,0,0,1,97,0,0,1,97,0,
0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,
0,0,1,9,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,
97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,3,0,0,1,9,0,0,
235,0,0,3,0,0,541,326,0,0,0,0,0,1,0,
};


/********************************************************************/
/*                                                                  */
/* 화 일 명 : pc_b999_load                                          */
/*                                                                  */
/* 작 성 자 :                                                       */
/*                                                                  */
/* 작 성 일 :                                                       */
/*                                                                  */
/********************************************************************/
/*                                                                  */
/* 내    용 : FirmBanking Data load                                 */
/* 사용Table: FATP101                                               */
/*                                                                  */
/********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string.h>
char *getenv();

#define SQLCODE      sqlca.sqlcode
#define SUCCESS      0
#define FAILURE      -1
#define SQL_OK       0
#define SQL_NO_DATA  1403
#define SQL_DUP      -1
#define VCHINIT(vchar) memset(&(vchar),0x00,sizeof((vchar)))

/* EXEC SQL BEGIN DECLARE SECTION; */ 

   static  char buffer[650];
   static  char chck[1 + 1];                   /* 구분자              */  
   static  char card_cmpn[3 + 1];              /* 카드회사구분        */  
   static  char card_gubn[1 + 1];              /* 카드구분            */  
   static  char card_kind[1 + 1];              /* 카드구분            */  
   static  char recp_date[8 + 1];              /* 접수일자            */  
   static  char card_slip_num[13 + 1];         /* 전표번호(카드)      */ 
   static  char rqst_num[10 + 1];              /* 청구고객번호        */  
   static  char dome_divs[1 + 1];              /* 거래구분(국/외)     */  
   static  /* varchar card_num[16 + 1]; */ 
struct { unsigned short len; unsigned char arr[17]; } card_num;
           /* 카드번호            */  
   static  char use_date[8 + 1];               /* 사용일자            */  
   static  char join_stor_num[13 + 1];         /* 가맹점번호          */  
   static  char cmpn_num[10 + 1];              /* 사업자 번호         */  
   static  char sign_use_amt[1 + 1];           /* 사용금액 부호       */  
   static  char use_amt[13 + 1];               /* 사용금액            */  
   static  char sign_vat[1 + 1];               /* 부가세부호          */  
   static  char vat[13 + 1];                   /* 부가세              */  
   static  char sign_serv_amt[1 + 1];          /* 봉사료부호          */  
   static  char serv_amt[13 + 1];              /* 봉사료금액          */  
   static  char sign_forn_amt[1 + 1];          /* 외화부호            */  
   static  char forn_amt[13 + 1];              /* 외화금액            */  
   static  char curc_code[4 + 1];              /* 통화코드            */  
   static  char sign_date[8 + 1];               /* 결재일자            */  
   static  char plan_date[8 + 1];               /* 입금예정일자        */  
   static  char reco_num[10 + 1];              /* 승인번호            */  
   static  char reco_date[8 + 1];              /* 승인일자            */  
   static  char reco_time[6 + 1];              /* 승인시간            */  
   static  char rqst_zip[8 + 1];               /* 청구지우편번호      */  
   static  /* varchar join_stor_name[40 + 1]; */ 
struct { unsigned short len; unsigned char arr[41]; } join_stor_name;
     /* 가맹점명            */  
   static  /* varchar join_repr[12 + 1]; */ 
struct { unsigned short len; unsigned char arr[13]; } join_repr;
          /* 가맹점대표자        */  
   static  /* varchar join_addr1[70 + 1]; */ 
struct { unsigned short len; unsigned char arr[71]; } join_addr1;
         /* 가맹점주소1         */  
   static  /* varchar join_addr2[100 + 1]; */ 
struct { unsigned short len; unsigned char arr[101]; } join_addr2;
        /* 가맹점주소2         */  
   static  /* varchar join_zip[8 + 1]; */ 
struct { unsigned short len; unsigned char arr[9]; } join_zip;
            /* 가맹점우편번호      */  
   static  /* varchar join_tel[19 + 1]; */ 
struct { unsigned short len; unsigned char arr[20]; } join_tel;
           /* 가맹점전화번호      */  
   static  /* varchar join_cond[20 + 1]; */ 
struct { unsigned short len; unsigned char arr[21]; } join_cond;
          /* 가맹점업태          */  
   static  char    join_type_code[3 + 1];      /* 가맹점업종코드      */  
   static  /* varchar join_type[50 + 1]; */ 
struct { unsigned short len; unsigned char arr[51]; } join_type;
          /* 가맹점업종명        */  
   static  char exhg_amt[13 + 1];              /* 승인시 환율         */  
   static  char ctry_code[4 + 1];              /* 국가코드            */  
   static  /* varchar ctry_name[50 + 1]; */ 
struct { unsigned short len; unsigned char arr[51]; } ctry_name;
          /* 국가명              */  
   static  char pre_recp_date[8 + 1];          /* 원전표접수일자      */ 
   static  char pre_card_slip[13 + 1];         /* 원전표전표번호      */ 
   static  char recp_bank_code[5 + 1];         /* 접수은행코드        */ 
   static  char recp_bran[22 + 1];             /* 접수은행명          */ 
   static  char cmt_num[4 + 1];                /* cmt기업번호         */ 
   static  char data_date[8 + 1];              /* 자료생성일자        */ 
   static  int seq;                            /* SEQ                 */  
   static  char data_use_yn[1 + 1];            /* 자료사용구분        */ 
   static  /* varchar rest_data[56 + 1]; */ 
struct { unsigned short len; unsigned char arr[57]; } rest_data;
          /* 남은 자료들         */  
   static  int f_int;                          /* 화일 체크           */  
  
char    *uid = "uas/youdpdls@DBSVR30";
/*   char    *uid = "fa/suioe9z@DBSVR04"; */
/*    char    *uid = "uas/aaa@DBTST04"; */

/* EXEC SQL END DECLARE SECTION; */ 


/* EXEC SQL INCLUDE sqlca.h;
 */ 
/*
 * $Header: sqlca.h 24-apr-2003.12:50:58 mkandarp Exp $ sqlca.h 
 */

/* Copyright (c) 1985, 2003, Oracle Corporation.  All rights reserved.  */
 
/*
NAME
  SQLCA : SQL Communications Area.
FUNCTION
  Contains no code. Oracle fills in the SQLCA with status info
  during the execution of a SQL stmt.
NOTES
  **************************************************************
  ***                                                        ***
  *** This file is SOSD.  Porters must change the data types ***
  *** appropriately on their platform.  See notes/pcport.doc ***
  *** for more information.                                  ***
  ***                                                        ***
  **************************************************************

  If the symbol SQLCA_STORAGE_CLASS is defined, then the SQLCA
  will be defined to have this storage class. For example:
 
    #define SQLCA_STORAGE_CLASS extern
 
  will define the SQLCA as an extern.
 
  If the symbol SQLCA_INIT is defined, then the SQLCA will be
  statically initialized. Although this is not necessary in order
  to use the SQLCA, it is a good pgming practice not to have
  unitialized variables. However, some C compilers/OS's don't
  allow automatic variables to be init'd in this manner. Therefore,
  if you are INCLUDE'ing the SQLCA in a place where it would be
  an automatic AND your C compiler/OS doesn't allow this style
  of initialization, then SQLCA_INIT should be left undefined --
  all others can define SQLCA_INIT if they wish.

  If the symbol SQLCA_NONE is defined, then the SQLCA variable will
  not be defined at all.  The symbol SQLCA_NONE should not be defined
  in source modules that have embedded SQL.  However, source modules
  that have no embedded SQL, but need to manipulate a sqlca struct
  passed in as a parameter, can set the SQLCA_NONE symbol to avoid
  creation of an extraneous sqlca variable.
 
MODIFIED
    lvbcheng   07/31/98 -  long to int
    jbasu      12/12/94 -  Bug 217878: note this is an SOSD file
    losborne   08/11/92 -  No sqlca var if SQLCA_NONE macro set 
  Clare      12/06/84 - Ch SQLCA to not be an extern.
  Clare      10/21/85 - Add initialization.
  Bradbury   01/05/86 - Only initialize when SQLCA_INIT set
  Clare      06/12/86 - Add SQLCA_STORAGE_CLASS option.
*/
 
#ifndef SQLCA
#define SQLCA 1
 
struct   sqlca
         {
         /* ub1 */ char    sqlcaid[8];
         /* b4  */ int     sqlabc;
         /* b4  */ int     sqlcode;
         struct
           {
           /* ub2 */ unsigned short sqlerrml;
           /* ub1 */ char           sqlerrmc[70];
           } sqlerrm;
         /* ub1 */ char    sqlerrp[8];
         /* b4  */ int     sqlerrd[6];
         /* ub1 */ char    sqlwarn[8];
         /* ub1 */ char    sqlext[8];
         };

#ifndef SQLCA_NONE 
#ifdef   SQLCA_STORAGE_CLASS
SQLCA_STORAGE_CLASS struct sqlca sqlca
#else
         struct sqlca sqlca
#endif
 
#ifdef  SQLCA_INIT
         = {
         {'S', 'Q', 'L', 'C', 'A', ' ', ' ', ' '},
         sizeof(struct sqlca),
         0,
         { 0, {0}},
         {'N', 'O', 'T', ' ', 'S', 'E', 'T', ' '},
         {0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0}
         }
#endif
         ;
#endif
 
#endif
 
/* end SQLCA */


FILE *fp;

int main()
{
   char f_file[90];
   char file_nm[9];
/*
   system( "rm /app/acct/fb/card/card_use_lg/lgusedata.dat");
*/

system( "/app/acct/proc/uas/pc_xtcp_get_make");
   system( "sh /app/acct/fb/card/card_use_lg/edi_get.sh");

 /*   DB Connect */
   /* EXEC SQL CONNECT :uid; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 4;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.iters = (unsigned int  )10;
   sqlstm.offset = (unsigned int  )5;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)256;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (unsigned char  *)uid;
   sqlstm.sqhstl[0] = (unsigned long )0;
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         short *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned long )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlstm.sqlcmax = (unsigned int )100;
   sqlstm.sqlcmin = (unsigned int )2;
   sqlstm.sqlcincr = (unsigned int )1;
   sqlstm.sqlctimeout = (unsigned int )0;
   sqlstm.sqlcnowait = (unsigned int )0;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



   f_int = 0;

   /*화일 수신자료*/
   if (( fp=fopen( "/app/acct/fb/card/card_use_lg/lgusedata.dat", "r" )) != NULL )
   {
      seq = 0;
      while ( fgets( buffer,650,fp ) != NULL )
      {
        strncpy(chck,&buffer[0],1);
      if (strncmp(chck, "H", 1) == 0)
      {
         f_int = 1;
         seq = 0;
         strncpy(data_date,&buffer[22],8);
         
      }
      else if (strncmp(chck, "D", 1) == 0)
      {
         f_int = 1;
         printf( "chck   == %s\n", chck );

         VCHINIT(card_num); 
         VCHINIT(join_stor_name);  
         VCHINIT(join_repr); 
         VCHINIT(join_addr1);  
         VCHINIT(join_addr2);  
         VCHINIT(join_zip); 
         VCHINIT(join_tel); 
         VCHINIT(join_cond);  
         VCHINIT(join_type);  
         VCHINIT(ctry_name);  
         VCHINIT(rest_data);  

         strncpy( card_cmpn,"001", 3);
         strncpy( card_gubn, &buffer[2], 1);
         strncpy( recp_date, &buffer[4], 8);
         strncpy( card_slip_num, &buffer[13], 13);
         strncpy( rqst_num, &buffer[27], 10);
         strncpy( rqst_zip, &buffer[38], 8);
         strncpy( dome_divs, &buffer[47], 1);
         strncpy( dome_divs, &buffer[47], 1);
	 strncpy( card_num.arr, &buffer[49],16 );
         card_num.len = strlen(card_num.arr);
         strncpy( use_date, &buffer[66], 8);
         strncpy( join_stor_num, &buffer[75], 10);
	 strncpy( join_stor_name.arr, &buffer[86],40 );
         join_stor_name.len = strlen(join_stor_name.arr);
         strncpy( cmpn_num, &buffer[127], 10);
	 strncpy( join_repr.arr, &buffer[138],12 );
         join_repr.len = strlen(join_repr.arr);
	 strncpy( join_addr1.arr, &buffer[151],70 );
         join_addr1.len = strlen(join_addr1.arr);
	 strncpy( join_addr2.arr, &buffer[222],100 );
         join_addr2.len = strlen(join_addr2.arr);
	 strncpy( join_zip.arr, &buffer[323],8 );
         join_zip.len = strlen(join_zip.arr);
	 strncpy( join_tel.arr, &buffer[332],19 );
         join_tel.len = strlen(join_tel.arr);
         /*strncpy( join_cond,"X", 1);*/
         strncpy( join_type_code, &buffer[352], 3);
	 strncpy( join_type.arr,  &buffer[356], 50);
         join_type.len = strlen(join_type.arr);
         strncpy( sign_use_amt, &buffer[407], 1);
         strncpy( use_amt, &buffer[409], 13);
         strncpy( sign_vat, &buffer[423], 1);
         strncpy( vat, &buffer[425], 13);
         strncpy( sign_serv_amt, &buffer[439], 1);
         strncpy( serv_amt, &buffer[441], 13);
         strncpy( sign_forn_amt, &buffer[455], 1);
         strncpy( forn_amt, &buffer[457], 13);
         strncpy( curc_code, &buffer[471], 3);
         strncpy( ctry_code, &buffer[475], 3);
	 strncpy( ctry_name.arr,  &buffer[479], 50);
         ctry_name.len = strlen(ctry_name.arr);
         strncpy( sign_date, &buffer[530], 8);
         strncpy( plan_date, &buffer[539], 8);
         strncpy( reco_num, &buffer[548], 8);
         strncpy( reco_date, &buffer[557], 8);
         strncpy( reco_time, &buffer[566], 6);
         strncpy( pre_recp_date, &buffer[573], 8);
         strncpy( pre_card_slip, &buffer[582], 13);
         strncpy( rest_data.arr, &buffer[596], 55);
         rest_data.len = strlen(rest_data.arr);
         strncpy( card_kind,"M", 1);
         /*****카드이용자명부터...*******/

            printf( "card_gubn   == %s\n", card_gubn );
            printf( "card_kind   == %s\n", card_kind);
            printf( "recp_date   == %s\n", recp_date );
            printf( "card_slip_num   == %s\n", card_slip_num );
            printf( "rqst_num   == %s\n", rqst_num );
            printf( "rqst_zip   == %s\n", rqst_zip );
            printf( "dome_divs   == %s\n", dome_divs );
            printf( "card_num   == %s\n", card_num.arr );
            printf( "use_date   == %s\n", use_date );
            printf( "join_stor_num   == %s\n", join_stor_num );
            printf( "join_stor_name   == %s\n", join_stor_name.arr );
            printf( "cmpn_num   == %s\n", cmpn_num);
            printf( "join_repr   == %s\n", join_repr.arr );
            printf( "join_addr1   == %s\n", join_addr1.arr );
            printf( "join_addr2   == %s\n", join_addr2.arr );
            printf( "join_zip   == %s\n", join_zip.arr );
            printf( "join_tel   == %s\n", join_tel.arr );
            printf( "join_cond   == %s\n", join_cond.arr);
            printf( "join_type_code   == %s\n", join_type_code);
            printf( "join_type   == %s\n", join_type.arr);
            printf( "sign_use_amt   == %s\n", sign_use_amt );
            printf( "use_amt   == %s\n", use_amt );
            printf( "sign_vat   == %s\n", sign_vat );
            printf( "vat   == %s\n", vat );
            printf( "sign_serv_amt   == %s\n", sign_serv_amt );
            printf( "serv_amt   == %s\n", serv_amt );
            printf( "sign_forn_amt   == %s\n", sign_forn_amt );
            printf( "forn_amt   == %s\n", forn_amt );
            printf( "curc_code   == %s\n", curc_code );
            printf( "exhg_amt   == %s\n", exhg_amt );
            printf( "ctry_code   == %s\n", ctry_code );
            printf( "ctry_name   == %s\n", ctry_name.arr );
            printf( "sign_date   == %s\n", sign_date );
            printf( "plan_date   == %s\n", plan_date );
            printf( "reco_num   == %s\n", reco_num );
            printf( "reco_date   == %s\n", reco_date );
            printf( "reco_time   == %s\n", reco_time );
            printf( "pre_recp_date   == %s\n", pre_recp_date);
            printf( "pre_card_slip   == %s\n", pre_card_slip );
            printf( "recp_bank_code   == %s\n", recp_bank_code);
            printf( "recp_bran   == %s\n", recp_bran);
             
            printf( "rest_data  == %s\n",rest_data );
            
            seq = seq + 1;

            /* EXEC SQL 
               INSERT INTO FATP101
                     (CARD_CMPN, CARD_GUBN, CARD_KIND, RECP_DATE, 
	              CARD_SLIP_NUM, RQST_NUM, RQST_ZIP, DOME_DIVS, 
	              CARD_NUM, USE_DATE, JOIN_STOR_NUM, JOIN_STOR_NAME, 
	              CMPN_NUM, JOIN_REPR, JOIN_ADDR1, JOIN_ADDR2, 
	              JOIN_ZIP, JOIN_TEL, JOIN_COND, JOIN_TYPE_CODE, 
	              JOIN_TYPE, SIGN_USE_AMT, USE_AMT, SIGN_VAT , 
	              VAT, SIGN_SERV_AMT, SERV_AMT, SIGN_FORN_AMT, 
	              FORN_AMT, CURC_CODE, EXHG_AMT, CTRY_CODE, 
	              CTRY_NAME, SIGN_DATE, PLAN_DATE, RECO_NUM, 
	              RECO_DATE, RECO_TIME, PRE_RECP_DATE, PRE_CARD_SLIP, 
	              RECP_BANK_CODE, RECP_BRAN, CMT_NUM, DATA_DATE, 
	              SEQ, DATA_USE_YN, UPD_EMPNO, UPD_DATE, UPD_ID , REST_DATA 
                     )
               VALUES ( :card_cmpn, TRIM(:card_gubn), TRIM(:card_kind), TRIM(:recp_date), 
                        nvl(TRIM(:card_slip_num),'X'), nvl(TRIM(:rqst_num), 'X'), 
                        nvl(TRIM(:rqst_zip),'X'), nvl(TRIM(:dome_divs),'X'), 
                        nvl(TRIM(:card_num),'X'), nvl(TRIM(:use_date),'X'), 
                        nvl(TRIM(:join_stor_num),'X'), nvl(TRIM(:join_stor_name),'X') , 
                        nvl(TRIM(:cmpn_num),'X'), nvl(TRIM(:join_repr),'X'), 
                        nvl(TRIM(:join_addr1),'X'), nvl(TRIM(:join_addr2),'X'), 
                        nvl(TRIM(:join_zip),'X'), nvl(TRIM(:join_tel),'X'), 
                        nvl(TRIM(:join_cond),'X'), nvl(TRIM(:join_type_code),'X'), 
                        nvl(TRIM(:join_type),'X'), nvl(TRIM(:sign_use_amt),'+'), 
                        to_number(:use_amt),       nvl(TRIM(:sign_vat),'+') , 
                        to_number(:vat),           nvl(TRIM(:sign_serv_amt),'+'), 
                        to_number(:serv_amt), nvl(TRIM(:sign_forn_amt),'+'), 
                        to_number(:forn_amt), nvl(TRIM(:curc_code),'X'), 
                        nvl(to_number(:exhg_amt),0), nvl(TRIM(:ctry_code), 'X'),
                        nvl(TRIM(:ctry_name),'X'), nvl(TRIM(:sign_date),'X'), 
                        nvl(TRIM(:plan_date),'X'), nvl(TRIM(:reco_num),'X'), 
                        nvl(TRIM(:reco_date),'X'), nvl(TRIM(:reco_time),'X'), 
                        nvl(TRIM(:pre_recp_date),'X'), nvl(TRIM(:pre_card_slip),'X'), 
                        nvl(TRIM(:recp_bank_code),'X'), nvl(TRIM(:recp_bran),'X'), 
                        nvl(TRIM(:cmt_num),'X'), nvl(TRIM(:data_date),'X'), 
                        to_number(:seq), 'N', 'auto', SYSDATE, 'auto' , TRIM(:rest_data) 
                      ); */ 

{
            struct sqlexd sqlstm;
            sqlstm.sqlvsn = 12;
            sqlstm.arrsiz = 46;
            sqlstm.sqladtp = &sqladt;
            sqlstm.sqltdsp = &sqltds;
            sqlbuft((void **)0,
              "insert into FATP101 (CARD_CMPN,CARD_GUBN,CARD_KIND,RECP_DATE,\
CARD_SLIP_NUM,RQST_NUM,RQST_ZIP,DOME_DIVS,CARD_NUM,USE_DATE,JOIN_STOR_NUM,JO\
IN_STOR_NAME,CMPN_NUM,JOIN_REPR,JOIN_ADDR1,JOIN_ADDR2,JOIN_ZIP,JOIN_TEL,JOIN\
_COND,JOIN_TYPE_CODE,JOIN_TYPE,SIGN_USE_AMT,USE_AMT,SIGN_VAT,VAT,SIGN_SERV_A\
MT,SERV_AMT,SIGN_FORN_AMT,FORN_AMT,CURC_CODE,EXHG_AMT,CTRY_CODE,CTRY_NAME,SI\
GN_DATE,PLAN_DATE,RECO_NUM,RECO_DATE,RECO_TIME,PRE_RECP_DATE,PRE_CARD_SLIP,R\
ECP_BANK_CODE,RECP_BRAN,CMT_NUM,DATA_DATE,SEQ,DATA_USE_YN,UPD_EMPNO,UPD_DATE\
,UPD_ID,REST_DATA) values (:b0,trim(:b1),trim(:b2),trim(:b3),nvl(trim(:b4),'\
X'),nvl(trim(:b5),'X'),nvl(trim(:b6),'X'),nvl(trim(:b7),'X'),nvl(trim(:b8),'\
X'),nvl(trim(:b9),'X'),nvl(trim(:b10),'X'),nvl(trim(:b11),'X'),nvl(trim(:b12\
),'X'),nvl(trim(:b13),'X'),nvl(trim(:b14),'X'),nvl(trim(:b15),'X'),nvl(trim(\
:b16),'X'),nvl(trim(:b17),'X'),nvl(trim(:b18),'X'),nvl(trim(:b19),'X'),nvl(t\
rim(:b20),'X'),nvl(trim(:b21),'+'),to_number(:b22),nvl(trim(:b23),'+'),to_nu\
mber(:b24),nvl(trim(:b25),'+'),to_number(:b26),nvl(");
            sqlstm.stmt = "trim(:b27),'+'),to_number(:b28),nvl(trim(:b29),'\
X'),nvl(to_number(:b30),0),nvl(trim(:b31),'X'),nvl(trim(:b32),'X'),nvl(trim(:\
b33),'X'),nvl(trim(:b34),'X'),nvl(trim(:b35),'X'),nvl(trim(:b36),'X'),nvl(tri\
m(:b37),'X'),nvl(trim(:b38),'X'),nvl(trim(:b39),'X'),nvl(trim(:b40),'X'),nvl(\
trim(:b41),'X'),nvl(trim(:b42),'X'),nvl(trim(:b43),'X'),to_number(:b44),'N','\
auto',SYSDATE,'auto',trim(:b45))";
            sqlstm.iters = (unsigned int  )1;
            sqlstm.offset = (unsigned int  )36;
            sqlstm.cud = sqlcud0;
            sqlstm.sqlest = (unsigned char  *)&sqlca;
            sqlstm.sqlety = (unsigned short)256;
            sqlstm.occurs = (unsigned int  )0;
            sqlstm.sqhstv[0] = (unsigned char  *)card_cmpn;
            sqlstm.sqhstl[0] = (unsigned long )4;
            sqlstm.sqhsts[0] = (         int  )0;
            sqlstm.sqindv[0] = (         short *)0;
            sqlstm.sqinds[0] = (         int  )0;
            sqlstm.sqharm[0] = (unsigned long )0;
            sqlstm.sqadto[0] = (unsigned short )0;
            sqlstm.sqtdso[0] = (unsigned short )0;
            sqlstm.sqhstv[1] = (unsigned char  *)card_gubn;
            sqlstm.sqhstl[1] = (unsigned long )2;
            sqlstm.sqhsts[1] = (         int  )0;
            sqlstm.sqindv[1] = (         short *)0;
            sqlstm.sqinds[1] = (         int  )0;
            sqlstm.sqharm[1] = (unsigned long )0;
            sqlstm.sqadto[1] = (unsigned short )0;
            sqlstm.sqtdso[1] = (unsigned short )0;
            sqlstm.sqhstv[2] = (unsigned char  *)card_kind;
            sqlstm.sqhstl[2] = (unsigned long )2;
            sqlstm.sqhsts[2] = (         int  )0;
            sqlstm.sqindv[2] = (         short *)0;
            sqlstm.sqinds[2] = (         int  )0;
            sqlstm.sqharm[2] = (unsigned long )0;
            sqlstm.sqadto[2] = (unsigned short )0;
            sqlstm.sqtdso[2] = (unsigned short )0;
            sqlstm.sqhstv[3] = (unsigned char  *)recp_date;
            sqlstm.sqhstl[3] = (unsigned long )9;
            sqlstm.sqhsts[3] = (         int  )0;
            sqlstm.sqindv[3] = (         short *)0;
            sqlstm.sqinds[3] = (         int  )0;
            sqlstm.sqharm[3] = (unsigned long )0;
            sqlstm.sqadto[3] = (unsigned short )0;
            sqlstm.sqtdso[3] = (unsigned short )0;
            sqlstm.sqhstv[4] = (unsigned char  *)card_slip_num;
            sqlstm.sqhstl[4] = (unsigned long )14;
            sqlstm.sqhsts[4] = (         int  )0;
            sqlstm.sqindv[4] = (         short *)0;
            sqlstm.sqinds[4] = (         int  )0;
            sqlstm.sqharm[4] = (unsigned long )0;
            sqlstm.sqadto[4] = (unsigned short )0;
            sqlstm.sqtdso[4] = (unsigned short )0;
            sqlstm.sqhstv[5] = (unsigned char  *)rqst_num;
            sqlstm.sqhstl[5] = (unsigned long )11;
            sqlstm.sqhsts[5] = (         int  )0;
            sqlstm.sqindv[5] = (         short *)0;
            sqlstm.sqinds[5] = (         int  )0;
            sqlstm.sqharm[5] = (unsigned long )0;
            sqlstm.sqadto[5] = (unsigned short )0;
            sqlstm.sqtdso[5] = (unsigned short )0;
            sqlstm.sqhstv[6] = (unsigned char  *)rqst_zip;
            sqlstm.sqhstl[6] = (unsigned long )9;
            sqlstm.sqhsts[6] = (         int  )0;
            sqlstm.sqindv[6] = (         short *)0;
            sqlstm.sqinds[6] = (         int  )0;
            sqlstm.sqharm[6] = (unsigned long )0;
            sqlstm.sqadto[6] = (unsigned short )0;
            sqlstm.sqtdso[6] = (unsigned short )0;
            sqlstm.sqhstv[7] = (unsigned char  *)dome_divs;
            sqlstm.sqhstl[7] = (unsigned long )2;
            sqlstm.sqhsts[7] = (         int  )0;
            sqlstm.sqindv[7] = (         short *)0;
            sqlstm.sqinds[7] = (         int  )0;
            sqlstm.sqharm[7] = (unsigned long )0;
            sqlstm.sqadto[7] = (unsigned short )0;
            sqlstm.sqtdso[7] = (unsigned short )0;
            sqlstm.sqhstv[8] = (unsigned char  *)&card_num;
            sqlstm.sqhstl[8] = (unsigned long )19;
            sqlstm.sqhsts[8] = (         int  )0;
            sqlstm.sqindv[8] = (         short *)0;
            sqlstm.sqinds[8] = (         int  )0;
            sqlstm.sqharm[8] = (unsigned long )0;
            sqlstm.sqadto[8] = (unsigned short )0;
            sqlstm.sqtdso[8] = (unsigned short )0;
            sqlstm.sqhstv[9] = (unsigned char  *)use_date;
            sqlstm.sqhstl[9] = (unsigned long )9;
            sqlstm.sqhsts[9] = (         int  )0;
            sqlstm.sqindv[9] = (         short *)0;
            sqlstm.sqinds[9] = (         int  )0;
            sqlstm.sqharm[9] = (unsigned long )0;
            sqlstm.sqadto[9] = (unsigned short )0;
            sqlstm.sqtdso[9] = (unsigned short )0;
            sqlstm.sqhstv[10] = (unsigned char  *)join_stor_num;
            sqlstm.sqhstl[10] = (unsigned long )14;
            sqlstm.sqhsts[10] = (         int  )0;
            sqlstm.sqindv[10] = (         short *)0;
            sqlstm.sqinds[10] = (         int  )0;
            sqlstm.sqharm[10] = (unsigned long )0;
            sqlstm.sqadto[10] = (unsigned short )0;
            sqlstm.sqtdso[10] = (unsigned short )0;
            sqlstm.sqhstv[11] = (unsigned char  *)&join_stor_name;
            sqlstm.sqhstl[11] = (unsigned long )43;
            sqlstm.sqhsts[11] = (         int  )0;
            sqlstm.sqindv[11] = (         short *)0;
            sqlstm.sqinds[11] = (         int  )0;
            sqlstm.sqharm[11] = (unsigned long )0;
            sqlstm.sqadto[11] = (unsigned short )0;
            sqlstm.sqtdso[11] = (unsigned short )0;
            sqlstm.sqhstv[12] = (unsigned char  *)cmpn_num;
            sqlstm.sqhstl[12] = (unsigned long )11;
            sqlstm.sqhsts[12] = (         int  )0;
            sqlstm.sqindv[12] = (         short *)0;
            sqlstm.sqinds[12] = (         int  )0;
            sqlstm.sqharm[12] = (unsigned long )0;
            sqlstm.sqadto[12] = (unsigned short )0;
            sqlstm.sqtdso[12] = (unsigned short )0;
            sqlstm.sqhstv[13] = (unsigned char  *)&join_repr;
            sqlstm.sqhstl[13] = (unsigned long )15;
            sqlstm.sqhsts[13] = (         int  )0;
            sqlstm.sqindv[13] = (         short *)0;
            sqlstm.sqinds[13] = (         int  )0;
            sqlstm.sqharm[13] = (unsigned long )0;
            sqlstm.sqadto[13] = (unsigned short )0;
            sqlstm.sqtdso[13] = (unsigned short )0;
            sqlstm.sqhstv[14] = (unsigned char  *)&join_addr1;
            sqlstm.sqhstl[14] = (unsigned long )73;
            sqlstm.sqhsts[14] = (         int  )0;
            sqlstm.sqindv[14] = (         short *)0;
            sqlstm.sqinds[14] = (         int  )0;
            sqlstm.sqharm[14] = (unsigned long )0;
            sqlstm.sqadto[14] = (unsigned short )0;
            sqlstm.sqtdso[14] = (unsigned short )0;
            sqlstm.sqhstv[15] = (unsigned char  *)&join_addr2;
            sqlstm.sqhstl[15] = (unsigned long )103;
            sqlstm.sqhsts[15] = (         int  )0;
            sqlstm.sqindv[15] = (         short *)0;
            sqlstm.sqinds[15] = (         int  )0;
            sqlstm.sqharm[15] = (unsigned long )0;
            sqlstm.sqadto[15] = (unsigned short )0;
            sqlstm.sqtdso[15] = (unsigned short )0;
            sqlstm.sqhstv[16] = (unsigned char  *)&join_zip;
            sqlstm.sqhstl[16] = (unsigned long )11;
            sqlstm.sqhsts[16] = (         int  )0;
            sqlstm.sqindv[16] = (         short *)0;
            sqlstm.sqinds[16] = (         int  )0;
            sqlstm.sqharm[16] = (unsigned long )0;
            sqlstm.sqadto[16] = (unsigned short )0;
            sqlstm.sqtdso[16] = (unsigned short )0;
            sqlstm.sqhstv[17] = (unsigned char  *)&join_tel;
            sqlstm.sqhstl[17] = (unsigned long )22;
            sqlstm.sqhsts[17] = (         int  )0;
            sqlstm.sqindv[17] = (         short *)0;
            sqlstm.sqinds[17] = (         int  )0;
            sqlstm.sqharm[17] = (unsigned long )0;
            sqlstm.sqadto[17] = (unsigned short )0;
            sqlstm.sqtdso[17] = (unsigned short )0;
            sqlstm.sqhstv[18] = (unsigned char  *)&join_cond;
            sqlstm.sqhstl[18] = (unsigned long )23;
            sqlstm.sqhsts[18] = (         int  )0;
            sqlstm.sqindv[18] = (         short *)0;
            sqlstm.sqinds[18] = (         int  )0;
            sqlstm.sqharm[18] = (unsigned long )0;
            sqlstm.sqadto[18] = (unsigned short )0;
            sqlstm.sqtdso[18] = (unsigned short )0;
            sqlstm.sqhstv[19] = (unsigned char  *)join_type_code;
            sqlstm.sqhstl[19] = (unsigned long )4;
            sqlstm.sqhsts[19] = (         int  )0;
            sqlstm.sqindv[19] = (         short *)0;
            sqlstm.sqinds[19] = (         int  )0;
            sqlstm.sqharm[19] = (unsigned long )0;
            sqlstm.sqadto[19] = (unsigned short )0;
            sqlstm.sqtdso[19] = (unsigned short )0;
            sqlstm.sqhstv[20] = (unsigned char  *)&join_type;
            sqlstm.sqhstl[20] = (unsigned long )53;
            sqlstm.sqhsts[20] = (         int  )0;
            sqlstm.sqindv[20] = (         short *)0;
            sqlstm.sqinds[20] = (         int  )0;
            sqlstm.sqharm[20] = (unsigned long )0;
            sqlstm.sqadto[20] = (unsigned short )0;
            sqlstm.sqtdso[20] = (unsigned short )0;
            sqlstm.sqhstv[21] = (unsigned char  *)sign_use_amt;
            sqlstm.sqhstl[21] = (unsigned long )2;
            sqlstm.sqhsts[21] = (         int  )0;
            sqlstm.sqindv[21] = (         short *)0;
            sqlstm.sqinds[21] = (         int  )0;
            sqlstm.sqharm[21] = (unsigned long )0;
            sqlstm.sqadto[21] = (unsigned short )0;
            sqlstm.sqtdso[21] = (unsigned short )0;
            sqlstm.sqhstv[22] = (unsigned char  *)use_amt;
            sqlstm.sqhstl[22] = (unsigned long )14;
            sqlstm.sqhsts[22] = (         int  )0;
            sqlstm.sqindv[22] = (         short *)0;
            sqlstm.sqinds[22] = (         int  )0;
            sqlstm.sqharm[22] = (unsigned long )0;
            sqlstm.sqadto[22] = (unsigned short )0;
            sqlstm.sqtdso[22] = (unsigned short )0;
            sqlstm.sqhstv[23] = (unsigned char  *)sign_vat;
            sqlstm.sqhstl[23] = (unsigned long )2;
            sqlstm.sqhsts[23] = (         int  )0;
            sqlstm.sqindv[23] = (         short *)0;
            sqlstm.sqinds[23] = (         int  )0;
            sqlstm.sqharm[23] = (unsigned long )0;
            sqlstm.sqadto[23] = (unsigned short )0;
            sqlstm.sqtdso[23] = (unsigned short )0;
            sqlstm.sqhstv[24] = (unsigned char  *)vat;
            sqlstm.sqhstl[24] = (unsigned long )14;
            sqlstm.sqhsts[24] = (         int  )0;
            sqlstm.sqindv[24] = (         short *)0;
            sqlstm.sqinds[24] = (         int  )0;
            sqlstm.sqharm[24] = (unsigned long )0;
            sqlstm.sqadto[24] = (unsigned short )0;
            sqlstm.sqtdso[24] = (unsigned short )0;
            sqlstm.sqhstv[25] = (unsigned char  *)sign_serv_amt;
            sqlstm.sqhstl[25] = (unsigned long )2;
            sqlstm.sqhsts[25] = (         int  )0;
            sqlstm.sqindv[25] = (         short *)0;
            sqlstm.sqinds[25] = (         int  )0;
            sqlstm.sqharm[25] = (unsigned long )0;
            sqlstm.sqadto[25] = (unsigned short )0;
            sqlstm.sqtdso[25] = (unsigned short )0;
            sqlstm.sqhstv[26] = (unsigned char  *)serv_amt;
            sqlstm.sqhstl[26] = (unsigned long )14;
            sqlstm.sqhsts[26] = (         int  )0;
            sqlstm.sqindv[26] = (         short *)0;
            sqlstm.sqinds[26] = (         int  )0;
            sqlstm.sqharm[26] = (unsigned long )0;
            sqlstm.sqadto[26] = (unsigned short )0;
            sqlstm.sqtdso[26] = (unsigned short )0;
            sqlstm.sqhstv[27] = (unsigned char  *)sign_forn_amt;
            sqlstm.sqhstl[27] = (unsigned long )2;
            sqlstm.sqhsts[27] = (         int  )0;
            sqlstm.sqindv[27] = (         short *)0;
            sqlstm.sqinds[27] = (         int  )0;
            sqlstm.sqharm[27] = (unsigned long )0;
            sqlstm.sqadto[27] = (unsigned short )0;
            sqlstm.sqtdso[27] = (unsigned short )0;
            sqlstm.sqhstv[28] = (unsigned char  *)forn_amt;
            sqlstm.sqhstl[28] = (unsigned long )14;
            sqlstm.sqhsts[28] = (         int  )0;
            sqlstm.sqindv[28] = (         short *)0;
            sqlstm.sqinds[28] = (         int  )0;
            sqlstm.sqharm[28] = (unsigned long )0;
            sqlstm.sqadto[28] = (unsigned short )0;
            sqlstm.sqtdso[28] = (unsigned short )0;
            sqlstm.sqhstv[29] = (unsigned char  *)curc_code;
            sqlstm.sqhstl[29] = (unsigned long )5;
            sqlstm.sqhsts[29] = (         int  )0;
            sqlstm.sqindv[29] = (         short *)0;
            sqlstm.sqinds[29] = (         int  )0;
            sqlstm.sqharm[29] = (unsigned long )0;
            sqlstm.sqadto[29] = (unsigned short )0;
            sqlstm.sqtdso[29] = (unsigned short )0;
            sqlstm.sqhstv[30] = (unsigned char  *)exhg_amt;
            sqlstm.sqhstl[30] = (unsigned long )14;
            sqlstm.sqhsts[30] = (         int  )0;
            sqlstm.sqindv[30] = (         short *)0;
            sqlstm.sqinds[30] = (         int  )0;
            sqlstm.sqharm[30] = (unsigned long )0;
            sqlstm.sqadto[30] = (unsigned short )0;
            sqlstm.sqtdso[30] = (unsigned short )0;
            sqlstm.sqhstv[31] = (unsigned char  *)ctry_code;
            sqlstm.sqhstl[31] = (unsigned long )5;
            sqlstm.sqhsts[31] = (         int  )0;
            sqlstm.sqindv[31] = (         short *)0;
            sqlstm.sqinds[31] = (         int  )0;
            sqlstm.sqharm[31] = (unsigned long )0;
            sqlstm.sqadto[31] = (unsigned short )0;
            sqlstm.sqtdso[31] = (unsigned short )0;
            sqlstm.sqhstv[32] = (unsigned char  *)&ctry_name;
            sqlstm.sqhstl[32] = (unsigned long )53;
            sqlstm.sqhsts[32] = (         int  )0;
            sqlstm.sqindv[32] = (         short *)0;
            sqlstm.sqinds[32] = (         int  )0;
            sqlstm.sqharm[32] = (unsigned long )0;
            sqlstm.sqadto[32] = (unsigned short )0;
            sqlstm.sqtdso[32] = (unsigned short )0;
            sqlstm.sqhstv[33] = (unsigned char  *)sign_date;
            sqlstm.sqhstl[33] = (unsigned long )9;
            sqlstm.sqhsts[33] = (         int  )0;
            sqlstm.sqindv[33] = (         short *)0;
            sqlstm.sqinds[33] = (         int  )0;
            sqlstm.sqharm[33] = (unsigned long )0;
            sqlstm.sqadto[33] = (unsigned short )0;
            sqlstm.sqtdso[33] = (unsigned short )0;
            sqlstm.sqhstv[34] = (unsigned char  *)plan_date;
            sqlstm.sqhstl[34] = (unsigned long )9;
            sqlstm.sqhsts[34] = (         int  )0;
            sqlstm.sqindv[34] = (         short *)0;
            sqlstm.sqinds[34] = (         int  )0;
            sqlstm.sqharm[34] = (unsigned long )0;
            sqlstm.sqadto[34] = (unsigned short )0;
            sqlstm.sqtdso[34] = (unsigned short )0;
            sqlstm.sqhstv[35] = (unsigned char  *)reco_num;
            sqlstm.sqhstl[35] = (unsigned long )11;
            sqlstm.sqhsts[35] = (         int  )0;
            sqlstm.sqindv[35] = (         short *)0;
            sqlstm.sqinds[35] = (         int  )0;
            sqlstm.sqharm[35] = (unsigned long )0;
            sqlstm.sqadto[35] = (unsigned short )0;
            sqlstm.sqtdso[35] = (unsigned short )0;
            sqlstm.sqhstv[36] = (unsigned char  *)reco_date;
            sqlstm.sqhstl[36] = (unsigned long )9;
            sqlstm.sqhsts[36] = (         int  )0;
            sqlstm.sqindv[36] = (         short *)0;
            sqlstm.sqinds[36] = (         int  )0;
            sqlstm.sqharm[36] = (unsigned long )0;
            sqlstm.sqadto[36] = (unsigned short )0;
            sqlstm.sqtdso[36] = (unsigned short )0;
            sqlstm.sqhstv[37] = (unsigned char  *)reco_time;
            sqlstm.sqhstl[37] = (unsigned long )7;
            sqlstm.sqhsts[37] = (         int  )0;
            sqlstm.sqindv[37] = (         short *)0;
            sqlstm.sqinds[37] = (         int  )0;
            sqlstm.sqharm[37] = (unsigned long )0;
            sqlstm.sqadto[37] = (unsigned short )0;
            sqlstm.sqtdso[37] = (unsigned short )0;
            sqlstm.sqhstv[38] = (unsigned char  *)pre_recp_date;
            sqlstm.sqhstl[38] = (unsigned long )9;
            sqlstm.sqhsts[38] = (         int  )0;
            sqlstm.sqindv[38] = (         short *)0;
            sqlstm.sqinds[38] = (         int  )0;
            sqlstm.sqharm[38] = (unsigned long )0;
            sqlstm.sqadto[38] = (unsigned short )0;
            sqlstm.sqtdso[38] = (unsigned short )0;
            sqlstm.sqhstv[39] = (unsigned char  *)pre_card_slip;
            sqlstm.sqhstl[39] = (unsigned long )14;
            sqlstm.sqhsts[39] = (         int  )0;
            sqlstm.sqindv[39] = (         short *)0;
            sqlstm.sqinds[39] = (         int  )0;
            sqlstm.sqharm[39] = (unsigned long )0;
            sqlstm.sqadto[39] = (unsigned short )0;
            sqlstm.sqtdso[39] = (unsigned short )0;
            sqlstm.sqhstv[40] = (unsigned char  *)recp_bank_code;
            sqlstm.sqhstl[40] = (unsigned long )6;
            sqlstm.sqhsts[40] = (         int  )0;
            sqlstm.sqindv[40] = (         short *)0;
            sqlstm.sqinds[40] = (         int  )0;
            sqlstm.sqharm[40] = (unsigned long )0;
            sqlstm.sqadto[40] = (unsigned short )0;
            sqlstm.sqtdso[40] = (unsigned short )0;
            sqlstm.sqhstv[41] = (unsigned char  *)recp_bran;
            sqlstm.sqhstl[41] = (unsigned long )23;
            sqlstm.sqhsts[41] = (         int  )0;
            sqlstm.sqindv[41] = (         short *)0;
            sqlstm.sqinds[41] = (         int  )0;
            sqlstm.sqharm[41] = (unsigned long )0;
            sqlstm.sqadto[41] = (unsigned short )0;
            sqlstm.sqtdso[41] = (unsigned short )0;
            sqlstm.sqhstv[42] = (unsigned char  *)cmt_num;
            sqlstm.sqhstl[42] = (unsigned long )5;
            sqlstm.sqhsts[42] = (         int  )0;
            sqlstm.sqindv[42] = (         short *)0;
            sqlstm.sqinds[42] = (         int  )0;
            sqlstm.sqharm[42] = (unsigned long )0;
            sqlstm.sqadto[42] = (unsigned short )0;
            sqlstm.sqtdso[42] = (unsigned short )0;
            sqlstm.sqhstv[43] = (unsigned char  *)data_date;
            sqlstm.sqhstl[43] = (unsigned long )9;
            sqlstm.sqhsts[43] = (         int  )0;
            sqlstm.sqindv[43] = (         short *)0;
            sqlstm.sqinds[43] = (         int  )0;
            sqlstm.sqharm[43] = (unsigned long )0;
            sqlstm.sqadto[43] = (unsigned short )0;
            sqlstm.sqtdso[43] = (unsigned short )0;
            sqlstm.sqhstv[44] = (unsigned char  *)&seq;
            sqlstm.sqhstl[44] = (unsigned long )sizeof(int);
            sqlstm.sqhsts[44] = (         int  )0;
            sqlstm.sqindv[44] = (         short *)0;
            sqlstm.sqinds[44] = (         int  )0;
            sqlstm.sqharm[44] = (unsigned long )0;
            sqlstm.sqadto[44] = (unsigned short )0;
            sqlstm.sqtdso[44] = (unsigned short )0;
            sqlstm.sqhstv[45] = (unsigned char  *)&rest_data;
            sqlstm.sqhstl[45] = (unsigned long )59;
            sqlstm.sqhsts[45] = (         int  )0;
            sqlstm.sqindv[45] = (         short *)0;
            sqlstm.sqinds[45] = (         int  )0;
            sqlstm.sqharm[45] = (unsigned long )0;
            sqlstm.sqadto[45] = (unsigned short )0;
            sqlstm.sqtdso[45] = (unsigned short )0;
            sqlstm.sqphsv = sqlstm.sqhstv;
            sqlstm.sqphsl = sqlstm.sqhstl;
            sqlstm.sqphss = sqlstm.sqhsts;
            sqlstm.sqpind = sqlstm.sqindv;
            sqlstm.sqpins = sqlstm.sqinds;
            sqlstm.sqparm = sqlstm.sqharm;
            sqlstm.sqparc = sqlstm.sqharc;
            sqlstm.sqpadto = sqlstm.sqadto;
            sqlstm.sqptdso = sqlstm.sqtdso;
            sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



             if(SQLCODE == SQL_DUP)
               {
                       printf("FATP101 INSERT 01  ERROR : %d\n",sqlca.sqlcode);
                     /*  close(fp);
                       EXEC SQL ROLLBACK WORK;
                       return FAILURE;*/
                }
              else if(SQLCODE != SQL_OK ){
                       printf("FATP101 INSERT 01  ERROR : %d\n",sqlca.sqlcode);
                      /* close(fp);
                       EXEC SQL ROLLBACK WORK;
                       return FAILURE;*/
                }
         }
         else if (strncmp(chck, "T", 1) == 0)
         {
            f_int =1; 
         }
     } 
   }
   else
   {
      f_int = 0;
      printf("lgusedata.dat 파일을 찾을수 없습니다!\n");
      printf( "f_int   == %d\n", f_int);
   }
   close(fp);

  /*
   strcpy( f_file,"mv /app/fund/fb/reg_result/FBS_CHB.dat /app/fund/fb/reg_result/" );
   strcat( f_file, "chb_" ); 
   strcat( f_file, file_nm ); 
   strcat( f_file, ".dat" );
   printf( "full file name %s\n", f_file );
   system( f_file );
  */

   /***화일이 없을 때****/
   if (f_int == 0)
   {
       printf( "f_int   == %d\n", f_int);
       system( "rm /app/acct/fb/card/card_use_lg/lgusedata.dat");
   }
   else
   {
       printf( "f_int   == %d\n", f_int);
       system( "sh /app/acct/fb/card/card_use_lg/lgdata_bk.sh");
   }
   /* EXEC SQL COMMIT; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 46;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )235;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)256;
   sqlstm.occurs = (unsigned int  )0;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


   return SUCCESS;
}
