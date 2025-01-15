!cd /engn002/acct/cron/uas_insa
spool lg_card.log
select to_char(sysdate, 'yyyymmdd hh24:mi:ss')  from dual; 
set serveroutput ON
alter PROCEDURE proc_make_fatp100 compile;
set pause off
@@make_lgcard.sql 
select to_char(sysdate, 'yyyymmdd hh24:mi:ss')  from dual; 
!sh lgcard_log.sh
exit
