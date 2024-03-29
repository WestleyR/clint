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

int check_error_gen(const char* path) {
    char* dir = dirname(strdup(path));
    if (access(dir, F_OK) != 0) {
        print_errorf("%s: No such file or directory\n", dir);
        return(-1);
    }
    if (access(dir, W_OK) != 0) {
        print_errorf("%s: Is not writable\n", dir);
        return(-1);
    }
    if (is_dir(dir) != 0) {
        print_errorf("%s: Is a file\n", dir);
        return(-1);
    }
    if (access(path, W_OK) != 0) {
        print_errorf("%s: Is not writable\n", path);
        return(-1);
    }
    if (is_dir(dir) != 0) {
        print_errorf("%s: Is a file\n", dir);
        return(-1);
    }

    // File should be able to exist, why did it fail?
    return(0);
}

//
// End file-error.c
//
