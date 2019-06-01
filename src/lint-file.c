// Created by: WestleyR
// email: westleyr@nym.hush.com
// Date: May 25, 2019
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

#include "lint-file.h"

int diff_lint(char *path) {
    FILE *fr;

    if (get_file(&fr, path) != 0) {
        print_errorf("Failed to get file: %s: %s\n", path, strerror(errno));
        return(1);
    }

    if (fr == NULL) {
        print_errorf("File is NULL\n");
        return(32);
    }

    int c_line;
    int lines_count = 0;
    char line[256];
    int lint_errors = 0;
    int new_line_error = 0;

    while (fgets(line, sizeof line, fr) != NULL) {
        lines_count++;
        // Check for extra newlines
        if (line[0] == '\n') {
            if (new_line_error != 0) {
                printf("Extra newline: %s: %i\n\n", path, lines_count);
                new_line_error = 0;
                lint_errors++;
            }
            new_line_error = 1;
        } else {
            new_line_error = 0;
        }
        // check for extra spaces after a line
        for (c_line = 0; c_line <= strlen(line); c_line++) {
            if (line[c_line] == '\n') {
                if (line[c_line-1] == ' ') {
                    printf("Extra space after content: %s: %i:\n", path, lines_count);
                    print_red_space(line);
                    lint_errors++;
                    break;
                }
            }
        }
    }

    fclose(fr);

    print_verbosef("Total lint errors in %s: %i\n", path, lint_errors);

    return(0);
}

int linter_file(char* path) {
    printf("this function is not yet developt\n");

    return(2);
}

int lint_file(char* path, int diff_view) {
    if (diff_view != 0) {
        return(diff_lint(path));
    }
    return(linter_file(path));
}

//
// End lint-file.c
//
