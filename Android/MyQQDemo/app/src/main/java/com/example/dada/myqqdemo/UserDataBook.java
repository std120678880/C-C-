package com.example.dada.myqqdemo;

import org.litepal.crud.DataSupport;

public class UserDataBook extends DataSupport{
    private String QQ_number;
    private String Password;

    public String getQQ_number(){
        return QQ_number;
    }
    public String getPassword(){
        return Password;
    }
    public void setQQ_number(String number){
        this.QQ_number = number;
    }
    public void setPassword(String password){
        this.Password = password;
    }
}
