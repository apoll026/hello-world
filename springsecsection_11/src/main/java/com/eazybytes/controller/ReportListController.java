package com.eazybytes.controller;

import com.eazybytes.model.mybatis.rpt.Cgetfatm510;
import com.eazybytes.model.mybatis.rpt.Rgetfatm510;
import com.eazybytes.service.pkg.pkgreport.Rgetbt100Service;
import com.eazybytes.service.pkg.pkgreport.Rgetfatm510Service;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;
import java.util.Map;

@Slf4j
@RestController
@RequiredArgsConstructor
@RequestMapping("/api/rpt")
public class ReportListController {

    private final Rgetbt100Service rgetbt100Service;
    private final Rgetfatm510Service rgetfatm510Service;

    @GetMapping("/rgetbt100")
    public Map<String, Object> reportGetBt100() {
        String i_divs = "Y";
        String i_year = "2024";
        String i_month = "12";
        String i_acct_code = "";
        String i_acct_grp = "";
        String i_cost_dept = "";
        String i_func_area = "";
        String i_dvsn_code = "";
        String i_main_dvsn = "Z100";
        String i_main_yn = "N";

        Map<String, Object> result = rgetbt100Service.rgetbt100(i_divs,
                i_year,
                i_month,
                i_acct_code,
                i_acct_grp,
                i_cost_dept,
                i_func_area,
                i_dvsn_code,
                i_main_dvsn,
                i_main_yn, null);
        return result;
    }

    @PostMapping("/rgetfatm510")
    public ResponseEntity<List<Map<String, Object>>> callRgetfatm510() {
        String i_acct_grp = "1103";
        String i_gubun = "1";

        log.info("callRgetfatm510 i_acct_grp :: {}, i_gubun :: {} ",i_acct_grp, i_gubun);
        Cgetfatm510 rgetfatm510 = new Cgetfatm510();
        rgetfatm510.setI_acct_grp(i_acct_grp);
        rgetfatm510.setI_gubun(i_gubun);
        rgetfatm510.setO_rc(null);
        List<Map<String, Object>> result = rgetfatm510Service.callRgetfatm510(rgetfatm510);
        return new ResponseEntity<>(result, HttpStatus.OK);
    }

    @PostMapping("/sgetfatm510")
    public ResponseEntity<List<Rgetfatm510>> selectRgetfatm510() {
        String i_acct_grp = "1103";
        String i_gubun = "1";

        log.info("selectRgetfatm510 i_acct_grp :: {}, i_gubun :: {} ",i_acct_grp, i_gubun);

        Cgetfatm510 rgetfatm510 = new Cgetfatm510();
        rgetfatm510.setI_acct_grp(i_acct_grp);
        rgetfatm510.setI_gubun(i_gubun);
        List<Rgetfatm510> result = rgetfatm510Service.selectRgetfatm510(rgetfatm510);
        return new ResponseEntity<>(result, HttpStatus.OK);
    }

}
