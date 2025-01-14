package com.eazybytes.repository;

import com.eazybytes.model.jpa.Customer;
import org.springframework.data.repository.CrudRepository;
import org.springframework.stereotype.Repository;

import java.util.Optional;

@Repository
public interface CustomerRepository extends CrudRepository<Customer,Long> {

    Optional<Customer> findByUsername(String username);

    Optional<Customer> findByUserId(String userId);

}
