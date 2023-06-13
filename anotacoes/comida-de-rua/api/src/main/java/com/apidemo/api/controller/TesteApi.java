package com.apidemo.api.controller;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class TesteApi {
    
    @GetMapping("/")
    public String hello() {
        return "Hello World!";
    }
}
