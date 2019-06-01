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

int copy_file(const char* file1, const char* file2) {
    FILE* f1;
    FILE* f2;
    char ch;

    errno = 0;

//    print_verbosef("Copying file from: %s to: %s...\n", file1, file2);

    if (get_file(&f1, file1) != 0) {
        //print_debugf("unable to get file: %s: %s\n", file1, strerror(errno));
        return(255);
    }

/*    f2 = fopen(file2, "w");
    if (f2 == NULL) {
        fclose(f1);
        print_errorf("copy_file: unable to open file: %s: %s\n", file2, strerror(errno));
        return(errno);
    }*/

    if (make_file_w(file2) != 0) return(255);

    if (get_file_w(&f2, file2) != 0) return(255);

    while ((ch = fgetc(f1)) != EOF) {
        if (ch == EOF) break;
        fputc(ch, f2);
    }

    fclose(f1);
    fclose(f2);

    print_verbosef("File copyed successfull: %s -> %s\n", file1, file2);

    return(0);
}

//
// End file-copy.c
//
