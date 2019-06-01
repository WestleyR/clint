// Created by: WestleyR
// email: westleyr@nym.hush.com
// Date: Mat 18, 2019
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

#define DEFAULT_SPACES 4

#include "main-clint.h"
#include "tabs-spaces.h"
#include "spaces-tabs.h"
#include "lint-file.h"
#include "file-utils.h"

#include "arglib/arglib.h"
#include "logger/logger.h"

char* SCRIPT_NAME;

char* help_sort() {
    char* sort_help = "OPTIONS:\n\
  -h, --help     : print help menu.\n\
  -v, --verbose  : verbose.\n\
  -d, --diff     : only print the diff.\n\
  -t, --tabs     : convert spaces (default 4) to tabs.\n\
  -s, --spaces   : convert tabs to spaces (default 4).\n\
  -S, --sset=int : change the spaces setting.\n\
  -l, --lint     : lint a file.\n\
  -V, --version  : print version.";

    return(sort_help);
}

void help_menu() {
    printf("DESCRIPTION:\n");
    printf("  Convert tabs to spaces and spaces to tabs\n");
    printf("  in source code and text files.\n");
    printf("\n");
    printf("USAGE:\n");
    printf("  $ %s [option] <file>\n", SCRIPT_NAME);
    printf("\n");
    printf("%s\n", help_sort());
    printf("\n");
    printf("EXAMPLES:\n");
    printf("  $ %s -vs -S4 file.go\n", SCRIPT_NAME);
    printf("  $ %s -vt file.go\n", SCRIPT_NAME);
    printf("\n");
    printf("This software is licensed under a Clear BSD License.\n");
    printf("Copyright (c) 2019 WestleyR, All rights reserved.\n");
    printf("Source code: https://github.com/WestleyR/clint\n");
    return;
}

void version_print() {
    printf("%s\n", CLINT_VERSION);
    return;
}

int main(int argc, char **argv) {
    SCRIPT_NAME = argv[0];

    if (argc <= 1) {
        help_menu();
        return(1);
    }

    char *path = NULL;
    int diff_view = 0;
    int verbose_print = 0;
    int sp_t = 0;
    int ts_s = 0;
    int lint = 0;

    int opt = 0;
//    char* file_out = "";
    char *file_out[512] = {};
    int fcount = 0;
    int spaces_set = DEFAULT_SPACES;

    static struct option long_options[] = {
        {"verbose", no_argument, 0, 'v'},
        {"tabs", no_argument, 0, 't'},
        {"spaces", no_argument, 0, 's'},
        {"lint", no_argument, 0, 'l'},
        {"diff", no_argument, 0, 'd'},
        {"sset", required_argument, 0, 'S'},
        {"out", required_argument, 0, 'o'},
        {"version", no_argument, 0, 'V'},
        {NULL, 0, 0, 0}
    };

//    while ((opt = getopt_long(argc, argv,":o:S:vVdtsl", long_options, 0)) != -1) {
    while ((opt = getopt_long(argc, argv,"o:S:vVhdtsl", long_options, 0)) != -1) {
        switch (opt) {
             case 'v':
                 verbose_print = 1;
                 break;
             case 's':
                 ts_s = 1;
                 break;
             case 't':
                 sp_t = 1;
                 break;
             case 'l':
                 lint = 1;
                 break;
             case 'd':
                 diff_view = 1;
                 break;
             case 'S':
                 spaces_set = atoi(optarg);
                 break;
             case 'o':
                 file_out[fcount] = optarg;
                 fcount++;
//                 file_out = optarg;
                 break;
             case 'V':
                 version_print();
                 return(0);
                 break;

             case 'h':
                 help_menu();
                 return(0);
                 break;

             default:
                 printf("\n%s\n\n", help_sort());
                 return(22);
        }
    }

    if (argc - optind > 1) {
        print_errorf("more then one input file; using last one\n");
    }

    if (optind < argc) {
        for (int i = optind; i < argc; i++) {
            path = argv[i];
        }
    } else {
        print_errorf("No file specifyed\n");
        return(123);
    }

    if ((ts_s == 0) && (sp_t == 0) && (lint == 0)) {
        print_errorf("neither '-s', '-t', nor '-l' given; nothing to do\n");
        return(22);
    }

    if ((ts_s + sp_t + lint) > 1) {
        print_errorf("only one of '-s', '-t' or '-l' may be set\n");
        return(22);
    }

    set_verbose(verbose_print);

    // Double check
    if (path == NULL) {
        print_errorf("No file specifyed\n");
        return(123);
    }

    if (file_check_r(path) != 0) {
        print_verbosef("Failed to get file\n");
        return(255);
    }

    if (sp_t != 0) {
        if (spaces_to_tabs(path, file_out, spaces_set, diff_view) != 0) {
            print_errorf("Unable to convert spaces to tabs\n");
            return(255);
        }
        return(0);
    }

    if (lint != 0) {
        if (lint_file(path, diff_view) != 0) {
            print_errorf("Unable to lint file\n");
            return(255);
        }
        return(0);
    }

    if (ts_s != 0) {
        if (tabs_to_spaces(path, spaces_set, diff_view) != 0) {
            print_errorf("Unable to convert tabs-to-spaces\n");
            return(255);
        }
    }

    return(0);
}

//
// End main-clint.c
//
