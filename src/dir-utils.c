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

int is_dir(const char* path) {
    struct stat path_stat;
    stat(path, &path_stat);
    return(S_ISREG(path_stat.st_mode));
}

//
// End dir-utils.c
//
