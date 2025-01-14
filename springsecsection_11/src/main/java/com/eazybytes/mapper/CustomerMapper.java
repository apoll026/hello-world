package com.eazybytes.mapper;

import com.eazybytes.model.jpa.Customer;
import org.apache.ibatis.annotations.Mapper;

import java.util.List;

@Mapper
public interface CustomerMapper {

    List<Customer> selectUser(String username);

}
