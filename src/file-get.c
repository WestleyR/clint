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

int get_file(FILE** file, const char* path) {
    *file = fopen(path, "r");


    if (*file == NULL) {
        if (file_check_r(path) != 0) return(255);
        print_errorf("Unexpected failure: unable to open file: %s\n", path);
        return(255);
    }
/*
    struct stat info;
    if (lstat(path, &info) != 0) {
        print_errorf("unable to open stat on: %s\n", path);
//        perror(path);
        return(-1);
    }

    if (S_ISDIR(info.st_mode)) {
        print_errorf("%s: File is a directory\n", path);
//        printf("%s: File is a directory\n", path);
        return(-1);
    }
//    fclose(*file);
*/
    return(0);
}

int get_file_w(FILE** file, const char* path) {
    *file = fopen(path, "w");

    if (*file == NULL) {
        if (file_check_w(path) != 0) return(255);
        print_errorf("get_file_w(): Unexpected failure: unable to open file: %s\n", path);
        return(255);

        //print_errorf("unable to open file: %s: %s\n", path, strerror(errno));
/*        char* dir = dirname(strdup(path));
        if (access(dir, F_OK) != 0) {
            print_errorf("%s: No such file or directory\n", dir);
            return(-1);
        }
        if (access(dir, W_OK) != 0) {
            print_errorf("%s: Is not writable\n", dir);
            return(-1);
        }
        print_errorf("Unexpected failure, cant create file\n");
        return(-1);*/
    }

    return(0);
}

//
// End file-get.c
//
