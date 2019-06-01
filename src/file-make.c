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

int make_file_w(const char* fname) {
    char *path = strdup(fname);

    print_verbosef("make_file_w(): Making/emptying writable file at: %s\n", path);

    if (make_file_w(path) != 0) {
        if (check_error_gen(path) != 0) return(-1);
        print_errorf("make_file_w(): unexpected error: unable to make/clean file: %s\n", path);
        return(-1);
    }

    // Success! file (path) created/cleaned, and is writable!
    return(0);
}

//
// End file-utils-gets.c
//
