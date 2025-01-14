package com.eazybytes.controller;

import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.web.bind.annotation.*;


@Slf4j
@RestController
@RequiredArgsConstructor
@RequestMapping("/api/note")
public class NotesController {


    @GetMapping("/note")
    public void note() {

    }

}
