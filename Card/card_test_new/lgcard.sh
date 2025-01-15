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

date
echo "************ LGÄ«µå ***************"
/app/acct/proc/uas/uas_test_new/pc_card_use_load
echo "=================  end  ===================="

