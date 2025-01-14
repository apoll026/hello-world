package com.eazybytes.controller;

import com.eazybytes.constants.ApplicationConstants;
import com.eazybytes.model.jpa.Customer;
import com.eazybytes.repository.CustomerRepository;
import com.eazybytes.security.jwt.JwtUtils;
import com.eazybytes.security.services.UserDetailsImpl;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.core.env.Environment;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.security.authentication.AuthenticationManager;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.AuthenticationException;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.web.bind.annotation.*;

import java.sql.Date;
import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

@Slf4j
@RestController
@RequiredArgsConstructor
public class UserController {

    private final JwtUtils jwtUtils;

    private final Environment env;
    private final AuthenticationManager authenticationManager;
    private final CustomerRepository customerRepository;
    private final PasswordEncoder passwordEncoder;

    @PostMapping("/register")
    public ResponseEntity<String> registerUser(@RequestBody Customer customer) {
        try {
            String hashPwd = passwordEncoder.encode(customer.getPassword());
            customer.setPassword(hashPwd);
            customer.setCreateDt(new Date(System.currentTimeMillis()));
            Customer savedCustomer = customerRepository.save(customer);

            if (!savedCustomer.getUserName().isEmpty()) {
                return ResponseEntity.status(HttpStatus.CREATED).
                        body("Given user details are successfully registered");
            } else {
                return ResponseEntity.status(HttpStatus.BAD_REQUEST).
                        body("User registration failed");
            }
        } catch (Exception ex) {
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).
                    body("An exception occurred: " + ex.getMessage());
        }
    }

    @GetMapping("/user")
    public Customer getUserDetailsAfterLogin(Authentication authentication) {
        System.out.println("user init");
        System.out.println("user init = " + authentication.getName());
        Optional<Customer> optionalCustomer = customerRepository.findByUsername(authentication.getName());
        return optionalCustomer.orElse(null);
    }

    @PostMapping("/apiLogin")
    public ResponseEntity<?> apiLogin(@RequestBody Customer customer) {
        log.info("customer username,password {} :: {}", customer.getUserId(), customer.getPassword());
        Authentication authenticationRequest;
        try {
            authenticationRequest = authenticationManager
                    .authenticate(new UsernamePasswordAuthenticationToken(customer.getUserId(), customer.getPassword()));
        } catch (AuthenticationException exception) {
            Map<String, Object> map = new HashMap<>();
            map.put("message", "Bad credentials");
            map.put("status", false);
            return new ResponseEntity<Object>(map, HttpStatus.NOT_FOUND);
        }

        SecurityContextHolder.getContext().setAuthentication(authenticationRequest);
        UserDetailsImpl userDetails = (UserDetailsImpl) authenticationRequest.getPrincipal();

        String jwt = jwtUtils.generateTokenFromUsername(userDetails);

        Optional<Customer> response = customerRepository.findByUsername(authenticationRequest.getName());

        HttpHeaders httpHeaders = new HttpHeaders();
        httpHeaders.add(ApplicationConstants.JWT_HEADER, "Bearer " + jwt);

        return new ResponseEntity<>(response, httpHeaders, HttpStatus.OK);
    }

}
