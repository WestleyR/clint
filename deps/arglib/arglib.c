// created by: WestleyR
// email: westleyr@nym.hush.com
// https://github.com/WestleyR/arglib
// date: Mar 9, 2018
// version-1.0.0.3
//
// The Clear BSD License
//
// Copyright (c) 2019 WestleyR
// All rights reserved.
//
// This software is licensed under a Clear BSD License.
//

#include <string.h>
#include <stdio.h>

#include "arglib.h"

int check_flag(char* input, char* sort_flag, char* long_flag) {
    if ((strcmp(input, sort_flag) == 0) || (strcmp(input, long_flag) == 0)) {
        return(0);
    }

    return(1);
}

char* get_val(char* input, char* out) {
    char* ret;
    ret = NULL;

    if (strstr(input, out)) {
        if (( ret = strchr(input, '=')) != NULL ) {
            ret++;
        }
    }

    return(ret);
}

int check_small_args(char* input, char* flag) {
    int string_len = 0;

    string_len = strlen(input);

    if (input[0] != '-') {
//        printf("ERROR: Not a valid option: %s\n", input);
//        return(1);
        return(0);
    }

    if (input[1] == '-') {
        return(0);
    }

    for (int i=1; i < string_len; i++) {
        if (strchr(flag, input[i]) == 0) {
            printf("-%c: Option not found.\n", input[i]);
            return(1);
        }
    }
    return(0);
}

int find_args(char* input, char* flag) {
    int string_len = 0;

    string_len = strlen(input);

    if (input[0] != '-') {
//        printf("ERROR: No: - found in: %s\n", input);
//        return(1);
        return(1);
    }
    if (input[1] == '-') {
        return(1);
    }

    for (int i=1; i < string_len; i++) {
        if (input[i] == flag[0]) {
            return(0);
        }
    }

    return(1);
}


//
// End arglib.c
//
