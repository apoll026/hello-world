alter session set nls_date_format = 'YYYY-MM-DD';

var p_msg varchar2(1000);
Exec proc_make_fatp100(:p_msg)
/
print
/
