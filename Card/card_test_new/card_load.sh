###---------------------------------------------------------------------------##
###  Crontab이 돌기 위한 환경변수                                             ##
###---------------------------------------------------------------------------##
#
LANG=ko_KR.EUC
ORACLE_SID=DBSVR30
ORACLE_BASE=/app/oracle
ORA_NLS=/app/oracle/ocommon/nls/admin/data
ORACLE_DOC=/app/oracle/doc
ORA_NLS33=/app/oracle/product/10.2.0/ocommon/nls/admin/data
NLS_LANG=American_America.KO16KSC5601
TNS_ADMIN=/app/oracle/product/10.2.0/network/admin
ORACLE_HOME=/app/oracle/product/10.2.0
PATH=$ORACLE_HOME/bin:$PATH:
LD_LIBRARY_PATH=/app/oracle/product/10.2.0/lib:/lib:/usr/lib:/usr/local/lib
export LANG ORACLE_SID ORACLE_BASE ORA_NLS ORA_NLS33 ORACLE_DOC NLS_LANG TNS_ADMIN ORACLE_HOME PATH
export LD_LIBRARY_PATH
###---------------------------------------------------------------------------##
work_date=`date   +%Y%m%d`
echo $PATH
echo $work_date
/usr/bin/date >> /app/acct/bin/card_test_new/card.log
/usr/bin/cd /app/acct/bin/card_test_new
sh /app/acct/bin/card_test_new/lgcard.sh >> /app/acct/bin/card_test_new/card.log

cd /app/acct/bin/card_test_new/card_log
del_dir=`./Dday -8`
rm -fR $del_dir
target_dd=`date   +/app/acct/bin/card_test_new/card_log/%Y%m%d`
target_hms=`date   +%Y%m%d%H%M%S`
mkdir $target_dd
cd $target_dd
mv /app/acct/bin/card_test_new/card.log card.log
mv card.log $target_hms
