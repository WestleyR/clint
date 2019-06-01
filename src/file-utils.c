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

int gen_output_files(const char* in_file, char** out_file) {
    int i = 0;
    int err = 0;
    while (1) {
        if (out_file[i] == NULL) break;
        // copy the file
        if (copy_file(in_file, out_file[i]) != 0) {
            print_warningf("Skipping file: %s\n", out_file[i]);
            err = 1;
            //print_errorf("unable to copy file: %s -> %s: %s\n", TMP_FILE, file_out[i], strerror(errno));
            i++;
            continue;
        }
        i++;
    }
    return(err);
}

//
// End file-utils.c
//
