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

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <libgen.h>
#include <dirent.h>
#include <unistd.h>

#include "c-utils/c-utils.h"
#include "colorc/colorc.h"
#include "logger/logger.h"

// get_file will check, and return a FILE* (as readonly) from a path. Will
// print a error if one occures.
int get_file(FILE**, const char*);

int get_file_w(FILE**, const char*);

int is_dir(const char*);

int copy_file(const char*, const char*);

int file_check_r(const char*);

int file_check_w(const char*);

int make_file_w(const char*);

int gen_output_files(const char*, char**);


//
// End file-utils.c
//
