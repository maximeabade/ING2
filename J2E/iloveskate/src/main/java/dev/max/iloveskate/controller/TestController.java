package dev.max.iloveskate.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;

@Controller
public class TestController {
    @GetMapping("/test-not-found")
    public String get() {
        return "errors/notAvailable";
    }
}
