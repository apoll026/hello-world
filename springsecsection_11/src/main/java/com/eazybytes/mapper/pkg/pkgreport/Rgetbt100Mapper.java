package com.eazybytes.mapper.pkg.pkgreport;

import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;

import java.util.Map;

@Mapper
public interface Rgetbt100Mapper {
    /*
    (i_divs IN VARCHAR2,
    i_year IN VARCHAR2,
    i_month IN VARCHAR2,
    i_acct_code IN VARCHAR2,
    i_acct_grp IN VARCHAR2,
    i_cost_dept in VARCHAR2,
    i_func_area IN VARCHAR2,
    i_dvsn_code IN VARCHAR2,
    i_main_dvsn IN VARCHAR2,
    i_main_yn   IN VARCHAR2,
    o_rc OUT tp_rc)

    @Select("{ CALL PKG_REPORT.PROC_GET_BT100(#{i_divs, mode=IN, jdbcType=STRING}, " +
            "#{i_year, mode=IN, jdbcType=STRING}, " +
            "#{i_month, mode=IN, jdbcType=STRING}, " +
            "#{i_acct_code, mode=IN, jdbcType=STRING}, " +
            "#{i_acct_grp, mode=IN, jdbcType=STRING}, " +
            "#{i_cost_dept, mode=IN, jdbcType=STRING}, " +
            "#{i_func_area, mode=IN, jdbcType=STRING}, " +
            "#{i_dvsn_code, mode=IN, jdbcType=STRING}, " +
            "#{i_main_dvsn, mode=IN, jdbcType=STRING}, " +
            "#{i_main_yn, mode=IN, jdbcType=STRING}, " +
            "#{o_rc, mode=OUT, jdbcType=STRING}) }")
    */
    void callRgtbt100(@Param("i_divs") String i_divs,
                      @Param("i_year") String i_year,
                      @Param("i_month") String i_month,
                      @Param("i_acct_code") String i_acct_code,
                      @Param("i_acct_grp") String i_acct_grp,
                      @Param("i_cost_dept") String i_cost_dept,
                      @Param("i_func_area") String i_func_area,
                      @Param("i_dvsn_code") String i_dvsn_code,
                      @Param("i_main_dvsn") String i_main_dvsn,
                      @Param("i_main_yn") String i_main_yn,
                      @Param("o_rc") Map<String, Object> result);
}
