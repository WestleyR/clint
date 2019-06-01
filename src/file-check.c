// Created by: WestleyR
// email: westleyr@nym.hush.com
// Date: Apr 32, 2019
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
    if (access(path, F_OK) != 0) {
        print_errorf("%s: No such file or directory\n", path);
        return(-1);
    }
    if (access(path, R_OK) != 0) {
        print_errorf("%s: Is not readable\n", path);
        return(-1);
    }

    struct stat file_info;

    if (stat(path, &file_info) != 0) {
        print_errorf("FAILED: while opening file stats: %s\n", path);
    }
    if ((S_ISREG(file_info.st_mode)) == 0) {
        print_errorf("%s: Is not a file\n", path);
        return(-1);
    }

//    FILE *file = fopen(path, "r");
//
//    if (file == NULL) {
//        print_errorf("FATAL: Unexpected failure when opening file: %s\n", path);
//        return(-1);
//    }

    struct stat info;
    if (lstat(path, &info) != 0) {
        print_errorf("unable to open stat on: %s\n", path);
        return(-1);
    }
    // Success! file (path) is a file, and is readable!
    return(0);
}

int file_check_w(const char* path) {
    if (access(path, F_OK) != 0) {
        print_errorf("%s: No such file or directory\n", path);
        return(-1);
    }
    if (access(path, W_OK) != 0) {
        print_errorf("%s: Is not writable\n", path);
        return(-1);
    }

    struct stat file_info;

    if (stat(path, &file_info) != 0) {
        print_errorf("FAILED: while opening file stats: %s\n", path);
    }
    if ((S_ISREG(file_info.st_mode)) != 0) {
        print_errorf("%s: Is a directory\n");
        return(-1);
    }

//    FILE *file = fopen(path, "r");
//
//    if (file == NULL) {
//        print_errorf("FATAL: Unexpected failure when opening file: %s\n", path);
//        return(-1);
//    }

    // Success! file (path) is a file, and is writable!
    return(0);
}

//
// End file-check.c
//
