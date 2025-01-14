package com.eazybytes.mapper.pkg.pkgreport;

import com.eazybytes.model.mybatis.rpt.Cgetfatm510;
import com.eazybytes.model.mybatis.rpt.Rgetfatm510;
import org.apache.ibatis.annotations.Mapper;

import java.util.List;
import java.util.Map;

@Mapper
public interface Rgetfatm510Mapper {

    List<Map<String, Object>> callRgetfatm510(Cgetfatm510 param);

    List<Rgetfatm510> selectRgetfatm510(Cgetfatm510 param);

}
