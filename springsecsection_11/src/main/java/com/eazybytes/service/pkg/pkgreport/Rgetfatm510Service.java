package com.eazybytes.service.pkg.pkgreport;

import com.eazybytes.model.mybatis.rpt.Cgetfatm510;
import com.eazybytes.model.mybatis.rpt.Rgetfatm510;

import java.util.List;
import java.util.Map;

public interface Rgetfatm510Service {

    List<Map<String, Object>> callRgetfatm510(Cgetfatm510 param);

    List<Rgetfatm510> selectRgetfatm510(Cgetfatm510 param);

}
