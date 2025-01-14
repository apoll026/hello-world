package com.eazybytes.service.pkg.pkgreport;

import java.util.Map;

public interface Rgetbt100Service {

    Map<String, Object> rgetbt100(String i_divs,
                                  String i_year,
                                  String i_month,
                                  String i_acct_code,
                                  String i_acct_grp,
                                  String i_cost_dept,
                                  String i_func_area,
                                  String i_dvsn_code,
                                  String i_main_dvsn,
                                  String i_main_yn, Map<String, Object> rtn);

}
