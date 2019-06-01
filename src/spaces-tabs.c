// Created by: WestleyR
// email: westleyr@nym.hush.com
// Date: Apr 4, 2019
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
#include <string.h>

#include "main-clint.h"
#include "spaces-tabs.h"
#include "file-utils.h"

#include "logger/logger.h"
#include "c-utils/c-utils.h"

//#include "color.h"

int tabs_view_diff(const char* file_path, int spaces_set) {
    print_verbosef("Viewing the diff\n");

    print_errorf("diff not avalibal\n");

    return(38);

    FILE *fr;
    if (get_file(&fr, file_path) != 0) {
        print_verbosef("Failed to get file: %s\n", file_path);
        return(1);
    }
    if (fr == NULL) {
        print_errorf("PANIC: file is NULL\n");
        return(32);
    }

//    int c_line;
//    int lines_count = 0;
//    char line[128];
//
//    while (fgets(line, sizeof line, fr) != NULL) {
//        lines_count++;
//        for (c_line = 0; c_line <= strlen(line); c_line++) {
//            if (line[c_line] == '\t') {
//                printf("\nTAB on line: %s:%i\n", file_path, lines_count);
//                printf("%s:%i:%s--%s%s", file_path, lines_count, RED, line, COLOR_RESET);
//                printf("%s:%i:%s++%s%s", file_path, lines_count, GREEN, remove_tab_line(line, spaces_set), COLOR_RESET);
//                ret[0] = '\0';
//                tab_count++;
//            }
//        }
//    }
//    fclose(fr);
//
//    printf("\n");
//    print_verbosef("Total tabs in %s: %i\n", file_path, tab_count);
//
    return(0);
}

int convert_spaces_to_tabs(char* file_path, char** file_out, char* tmp_file, int spaces_set) {
    print_verbosef("Converting %i spaces to tabs\n", spaces_set);

    FILE *fr;
    if (get_file(&fr, file_path) != 0) {
        print_verbosef("Failed to get file: %s\n", file_path);
        return(1);
    }
    if (fr == NULL) {
        print_errorf("PANIC: file is NULL\n");
        return(32);
    }

    int c_line;
    int lines_count = 0;
    char line[128];
    FILE *fw;
    int start_spaces = 0;

    char new_line[256];
    new_line[0] = '\0';
    int tabs = 0;
    int did_start = 0;
    int done_line = 0;
    int total_tab_count = 0;

    if (get_file_w(&fw, tmp_file) != 0) {
        print_verbosef("Unable to get tmp file: %s\n", tmp_file);
        return(255);
    }
    if (fw == NULL) {
        print_errorf("PANIC: unable to open tmp file: %s\n", tmp_file);
        return(255);
    }

    while (fgets(line, sizeof line, fr) != NULL) {
        lines_count++;
        for (c_line = 0; c_line <= strlen(line); c_line++) {
            if ((c_line == 0) && (line[0] == ' ')) {
                did_start = 1;
            }
            if ((did_start != 0) && (line[c_line] == ' ')) {
                start_spaces++;
            }

            if (line[c_line] != ' ') {
                did_start = 0;
                start_spaces = 0;
                done_line = 1;
            }

            if (done_line != 0) {
                add_char_to_string(new_line, line[c_line]);
            }

            if (start_spaces >= spaces_set) {
                tabs = start_spaces / spaces_set;
                if (tabs > 0) {
                    for (int i = 0; i < tabs; i++) {
                        add_char_to_string(new_line, '\t');
                        total_tab_count++;
                    }
                }
                start_spaces = 0;
                tabs = 0;
            }
        }

        fputs(new_line, fw);

        new_line[0] = '\0';
        done_line = 0;
    }
    fclose(fw);
    fclose(fr);


    int ret_err = 0;

    if (file_out[0] != NULL) {
        if (gen_output_files(tmp_file, file_out) != 0) {
            print_verbosef("Aborting: not removing: %s\n", file_path);
            ret_err = 1;
            if (copy_file(tmp_file, file_path) != 0) return(255);
        }
        rename(file_path, "/tmp/clint_build.bck");
    } else {
        print_verbosef("Not makeing new file, rewriting old file: %s\n", file_path);
        if (copy_file(tmp_file, file_path) != 0) return(255);
//        print_errorf("Unexpected failure: unable to make file: %s\n", file_path);
//        return(255);
        //rename(TMP_FILE, file_path);
    }

    print_verbosef("Total tabs added: %i\n", total_tab_count);

    return(ret_err);
}

// tabs_to_spaces ...
int spaces_to_tabs(char* file_path, char** file_out, char* tmp_file, int spaces_set, int diff_view) {
    if (diff_view != 0) {
        return(tabs_view_diff(file_path, spaces_set));
    }

    return(convert_spaces_to_tabs(file_path, file_out, tmp_file, spaces_set));

}

//
// End spaces-tabs.c
//
