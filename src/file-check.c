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

int file_check_r(const char* path) {
    char* dir = dirname(strdup(path));
    if (access(dir, F_OK) != 0) {
        print_verbosef("file_check_r(): checking file: %s\n", path);
        print_errorf("%s: No such file or directory\n", dir);
        return(-1);
    }
    if (is_dir(dir) != 0) {
        print_verbosef("file_check_r(): checking file: %s\n", path);
        print_errorf("%s: Is a file\n", dir);
        return(-1);
    }
    if (access(path, F_OK) != 0) {
        print_verbosef("file_check_r(): checking file: %s\n", path);
        print_errorf("%s: No such file or directory\n", path);
        return(-1);
    }
    if (access(path, R_OK) != 0) {
        print_verbosef("file_check_r(): checking file: %s\n", path);
        print_errorf("%s: Is not writable\n", path);
        return(-1);
    }
    if (is_dir(path) == 0) {
        print_verbosef("file_check_r(): checking file: %s\n", path);
        print_errorf("%s: Is a directory\n", path);
        return(-1);
    }
    print_verbosef("file_check_r(): pased file checks: %s\n", path);



/*
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
    }*/

    // Success! file (path) is a file, and is readable!
    return(0);
}

int file_check_w(const char* path) {
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


/*    struct stat file_info;

    if (stat(path, &file_info) != 0) {
        print_errorf("FAILED: while opening file stats: %s\n", path);
    }
    if ((S_ISREG(file_info.st_mode)) != 0) {
        print_errorf("%s: Is a directory\n");
        return(-1);
    }
*/
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
