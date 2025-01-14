package com.eazybytes.model.jpa;

import com.fasterxml.jackson.annotation.JsonIgnore;
import com.fasterxml.jackson.annotation.JsonProperty;
import jakarta.persistence.*;
import lombok.Getter;
import lombok.Setter;

import java.sql.Date;

@Entity
@Table(name="GSC_USER", schema="PUB")
@Getter
@Setter
public class Customer {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "USER_ID") //USER_ID
    private String userId; //id

    @Column(name = "SSO_USER_TYPE")
    private String role;
    // CORP_CODE
    // EMP_NO
    @Column(name = "EMP_NO")
    private String empNo;

    @Column(name = "EMAIL")
    private String email;

    @Column(name = "USER_NM")
    private String username;
    // USER_ENG_NM
    // TITLE_NM
    // TITLE_ENG_NM
    // TITLE_CD
    // CMPN_NM
    // CMPN_ENG_NM
    // DEPT_NM
    // DEPT_ENG_NM
    // DEPT_CD

    @Column(name = "MOBILE_NUM")
    private String mobileNumber;

    @JsonProperty(access = JsonProperty.Access.WRITE_ONLY)
    @Column(name = "PASSWORD_SHA512")
    private String password;

    @Column(name = "UPD_DATE")
    @JsonIgnore
    private Date createDt;

    private boolean isTwoFactorEnabled = false;
    //@OneToMany(mappedBy = "customer", fetch = FetchType.EAGER)
    //@JsonIgnore
    //private Set<Authority> authorities;

    public Customer(String userName, String email, String password) {
        this.userName = userName;
        this.email = email;
        this.password = password;
    }

    public Customer(String userName, String email) {
        this.userName = userName;
        this.email = email;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Customer)) return false;
        return userId != null && userId.equals(((Customer) o).getUserId());
    }

    @Override
    public int hashCode() {
        return getClass().hashCode();
    }

}
