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

int copy_file(const char* file1, const char* file2) {
    FILE* f1;
    FILE* f2;
    char ch;

    if (get_file(&f1, file1) != 0) {
        print_verbosef("copy_file(): unable to open file: %s\n", file1);
        return(255);
    }
//    if (make_file_w(file2) != 0) return(255);
    if (get_file_w(&f2, file2) != 0) {
        print_verbosef("copy_file(): unable to open file: %s\n", file2);
        return(255);
    }

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
