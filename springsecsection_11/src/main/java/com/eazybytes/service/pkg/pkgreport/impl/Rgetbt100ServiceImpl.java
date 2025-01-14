package com.eazybytes.service.pkg.pkgreport.impl;

import com.eazybytes.mapper.pkg.pkgreport.Rgetbt100Mapper;
import com.eazybytes.service.pkg.pkgreport.Rgetbt100Service;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.HashMap;
import java.util.Map;

@Service
public class Rgetbt100ServiceImpl implements Rgetbt100Service{

    @Autowired
    private Rgetbt100Mapper rgetbt100Mapper;

    @Override
    public Map<String, Object> rgetbt100(String i_divs,
                                         String i_year,
                                         String i_month,
                                         String i_acct_code,
                                         String i_acct_grp,
                                         String i_cost_dept,
                                         String i_func_area,
                                         String i_dvsn_code,
                                         String i_main_dvsn,
                                         String i_main_yn,
                                         Map<String, Object> rtn) {
       Map<String, Object> result = new HashMap<>();
       rgetbt100Mapper.callRgtbt100(i_divs,
                i_year,
                i_month,
                i_acct_code,
                i_acct_grp,
                i_cost_dept,
                i_func_area,
                i_dvsn_code,
                i_main_dvsn,
                i_main_yn, result);
        return result;
    }
}
