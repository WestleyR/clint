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

int make_file_w(const char* fname) {
    char *path = strdup(fname);

    print_verbosef("Makeing writable file at: %s\n", path);

    if (access(path, F_OK) == 0) {
        if (access(path, R_OK) != 0) {
            print_errorf("%s: Is not readable\n", path);
            return(-1);
        }
    }

    FILE *file = fopen(path, "w");
    if (file == NULL) {
        print_verbosef("FATAL: Unexpected failure when opening file: %s\n", path);
        char* dir = dirname(path);
        if (access(dir, F_OK) != 0) {
            print_errorf("%s: No such file or directory\n", dir);
            return(-1);
        }
        if (access(dir, W_OK) != 0) {
            print_errorf("%s: Is not writable\n", dir);
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
        print_errorf("Unexpected failure, cant create file\n");
        return(-1);
    }
    if (access(path, W_OK) != 0) {
        print_errorf("%s: Created file is not writable\n", path);
        return(-1);
    }
    fclose(file);

    // Success! file (path) created, and is writable!
    return(0);
}

//
// End file-utils-gets.c
//
