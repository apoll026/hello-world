#!/sbin/sh
################################################################################
###  Script      Name     invalid_object    	                              ##
###===========================================================================##
###  Create      By       CHS                                                 ##
###---------------------------------------------------------------------------##
###  Create      Date     2000.02.15                                          ##
###  Modify      Date                                                         ##
###---------------------------------------------------------------------------##
###  Description                                                              ##
###---------------------------------------------------------------------------##
###                                                                           ##
################################################################################
###---------------------------------------------------------------------------##
###  ORACLE USER 환경 SETTING                                                 ##
###---------------------------------------------------------------------------##
###---------------------------------------------------------------------------##
###  Crontab이 돌기 위한 환경변수                                             ##
###---------------------------------------------------------------------------##

export ORACLE_BASE=/engn001/orasvc01
export ORACLE_HOME=$ORACLE_BASE/product/19.3.0
export ORACLE_SID=DBSVR30
export NLS_LANG=American_America.AL32UTF8
export TNS_ADMIN=$ORACLE_HOME/network/admin
export TMPDIR=$ORACLE_BASE/tmp
export ORACLE_DOC=$ORACLE_BASE/doc
export ORA_NLS33=$ORACLE_HOME/ocommon/nls/admin/data
export PATH=$ORACLE_HOME/bin:$ORACLE_HOME/OPatch:$ORACLE_HOME/adams/lib:$ORACLE_HOME/jdk/bin:$PATH
export LD_LIBRARY_PATH=$ORACLE_HOME/lib:/lib:/usr/lib
export LIBPATH=$ORACLE_HOME/lib:/lib:/usr/lib 

###---------------------------------------------------------------------------##
################################################################################
###
cd /engn002/acct/cron/uas_insa; sqlplus uas/youdpdls @exec_lgcard.sql;
