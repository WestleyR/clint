// Created by: WestleyR
// email: westleyr@nym.hush.com
// Date: Aug 10, 2019
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

int file_check_r(const char* path) {
    print_verbosef("Checking if: %s is readable...\n", path);

    char* dir = dirname(strdup(path));

    if (access(dir, F_OK) != 0) {
        print_errorf("%s: No such file or directory\n", dir);
        return(-1);
    }
    if (is_dir(dir) != 0) {
        print_errorf("%s: Is a file\n", dir);
        return(-1);
    }
    if (access(path, F_OK) != 0) {
        print_errorf("%s: No such file or directory\n", path);
        return(-1);
    }
    if (access(path, R_OK) != 0) {
        print_errorf("%s: Is not writable\n", path);
        return(-1);
    }
    if (is_dir(path) == 0) {
        print_errorf("%s: Is a directory\n", path);
        return(-1);
    }
    print_verbosef("pased file checks: %s\n", path);

    // Success! file (path) is a file, and is readable!
    return(0);
}

int file_check_w(const char* path) {
    print_verbosef("check if: %s is writeable...\n", path);
    char* dir = dirname(strdup(path));
    if (access(dir, F_OK) != 0) {
        print_verbosef("file_check_w(): checking file: %s\n", path);
        print_errorf("%s: No such file or directory\n", dir);
        return(-1);
    }
    if (is_dir(dir) != 0) {
        print_verbosef("file_check_w(): checking file: %s\n", path);
        print_errorf("%s: Is a file\n", dir);
        return(-1);
    }
    if (access(path, F_OK) != 0) {
        print_verbosef("file_check_w(): checking file: %s\n", path);
        print_errorf("%s: No such file or directory\n", path);
        return(-1);
    }
    if (access(path, W_OK) != 0) {
        print_verbosef("file_check_w(): checking file: %s\n", path);
        print_errorf("%s: Is not writable\n", path);
        return(-1);
    }
    if (is_dir(path) == 0) {
        print_verbosef("file_check_w(): checking file: %s\n", path);
        print_errorf("%s: Is a directory\n", path);
        return(-1);
    }
    print_verbosef("file_check_w(): pased file checks: %s\n", path);

    // Success! file (path) is a file, and is writable!
    return(0);
}

//
// End file-check.c
//
