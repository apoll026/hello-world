package com.eazybytes.service.pkg.pkgreport.impl;

import com.eazybytes.mapper.pkg.pkgreport.Rgetfatm510Mapper;
import com.eazybytes.model.mybatis.rpt.Cgetfatm510;
import com.eazybytes.model.mybatis.rpt.Rgetfatm510;
import com.eazybytes.service.pkg.pkgreport.Rgetfatm510Service;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

@Slf4j
@Service
@Transactional
public class Rgetfatm510ServiceImpl implements Rgetfatm510Service {

    @Autowired
    private Rgetfatm510Mapper rgetfatm510Mapper;

    @Override
    public List<Map<String, Object>> callRgetfatm510(Cgetfatm510 param) {

        //log.info("i_acct_grp :: {}, i_gubun :: {} ",param.getI_acct_grp(), param.getI_gubun());
        try {
            rgetfatm510Mapper.callRgetfatm510(param);
            //if (param.getO_rc() != null) {
            //    for (Map<String, Object> list : param.getO_rc()) {
            //        log.info(" list key getAcct_name :: {} ", list.get("ACCT_NAME"));
            //    }
            //}
        } catch (Exception e) {
            log.error("callRgetfatm510 log :: {} ", e.getMessage());
        }
        return param.getO_rc();
    }

    @Override
    public List<Rgetfatm510> selectRgetfatm510(Cgetfatm510 param) {

        List<Rgetfatm510> rtn = null;
        //log.info("i_acct_grp :: {}, i_gubun :: {} ",param.getI_acct_grp(), param.getI_gubun());

        try {
            rtn = rgetfatm510Mapper.selectRgetfatm510(param);
            if (rtn != null) {
                for (Rgetfatm510 list : rtn) {
                    log.info(" rtn getAcct_name :: {}", list.getAcct_name());
                }
            }
        } catch (Exception e) {
            log.error("selectRgetfatm510 log :: {} ", e.getMessage());
        }
        return rtn;
    }

}
