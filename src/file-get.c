// Created by: WestleyR
// email: westleyr@nym.hush.com
// Date: Jun 1, 2019
// https://github.com/WestleyR/clint
// version-1.0.0
//
// The Clear BSD License
//
// Copyright (c) 2019 WestleyR
// All rights reserved.
//
// This software is licensed under a Clear BSD License.
//

#include "file-utils.h"

int get_file(FILE** file, const char* path) {
    *file = fopen(path, "r");

    if (*file == NULL) {
        if (file_check_r(path) != 0) return(255);
        print_errorf("Unexpected failure: unable to open file: %s\n", path);
        return(255);
    }
    return(0);
}

int get_file_w(FILE** file, const char* path) {
    *file = fopen(path, "w");

    if (*file == NULL) {
        if (file_check_w(path) != 0) return(255);
        print_errorf("get_file_w(): Unexpected failure: unable to open file: %s\n", path);
        return(255);
    }

    return(0);
}

//
// End file-get.c
//
