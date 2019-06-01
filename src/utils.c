// Created by: WestleyR
// email: westleyr@nym.hush.com
// Date: Apr 25, 2019
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

#include "utils.h"

int file_check_r(const char* path) {
    if (access(path, F_OK) != 0) {
        print_errorf("%s: No such file or directory\n", path);
        return(-1);
    }
    if (access(path, R_OK) != 0) {
        print_errorf("%s: Is not readable\n", path);
        return(-1);
    }

    struct stat file_info;

    if (stat(path, &file_info) != 0) {
        print_errorf("FAILED: while opening file stats: %s\n", path);
    }
    if ((S_ISREG(file_info.st_mode)) == 0) {
        print_errorf("%s: Is not a file\n", path);
        return(-1);
    }

//    FILE *file = fopen(path, "r");
//
//    if (file == NULL) {
//        print_errorf("FATAL: Unexpected failure when opening file: %s\n", path);
//        return(-1);
//    }

    struct stat info;
    if (lstat(path, &info) != 0) {
        print_errorf("unable to open stat on: %s\n", path);
        return(-1);
    }
    // Success! file (path) is a file, and is readable!
    return(0);
}

int file_check_w(const char* path) {
    if (access(path, F_OK) != 0) {
        print_errorf("%s: No such file or directory\n", path);
        return(-1);
    }
    if (access(path, W_OK) != 0) {
        print_errorf("%s: Is not writable\n", path);
        return(-1);
    }

    struct stat file_info;

    if (stat(path, &file_info) != 0) {
        print_errorf("FAILED: while opening file stats: %s\n", path);
    }
    if ((S_ISREG(file_info.st_mode)) != 0) {
        print_errorf("%s: Is a directory\n");
        return(-1);
    }

//    FILE *file = fopen(path, "r");
//
//    if (file == NULL) {
//        print_errorf("FATAL: Unexpected failure when opening file: %s\n", path);
//        return(-1);
//    }

    // Success! file (path) is a file, and is writable!
    return(0);
}

int is_dir(const char* path) {
    struct stat path_stat;
    stat(path, &path_stat);
    return(S_ISREG(path_stat.st_mode));
}

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

int get_file(FILE** file, const char* path) {
    *file = fopen(path, "r");

    if (file == NULL) {
        print_errorf("unable to open file: %s: %s\n", path, strerror(errno));
//        printf("Couldn't open file: %s\n", path);
//        perror(path);
        return(1);
    }

    struct stat info;
    if (lstat(path, &info) != 0) {
        print_errorf("unable to open stat on: %s\n", path);
//        perror(path);
        return(-1);
    }

    if (S_ISDIR(info.st_mode)) {
        print_errorf("%s: File is a directory\n", path);
//        printf("%s: File is a directory\n", path);
        return(-1);
    }
//    fclose(*file);

    return(0);
}

int get_file_w(FILE** file, const char* path) {
    *file = fopen(path, "w");

    if (file == NULL) {
        //print_errorf("unable to open file: %s: %s\n", path, strerror(errno));
        char* dir = dirname(strdup(path));
        if (access(dir, F_OK) != 0) {
            print_errorf("%s: No such file or directory\n", dir);
            return(-1);
        }
        if (access(dir, W_OK) != 0) {
            print_errorf("%s: Is not writable\n", dir);
            return(-1);
        }
        print_errorf("Unexpected failure, cant create file\n");
        return(-1);
    }

    return(0);
}

int remove_tab_line(char* ret, char* line, int spaces_set) {
    int count;

    for (count = 0; count <= strlen(line); count++) {
        if (line[count] == '\t') {
            strcat(ret, "    ");
        } else {
            add_char_to_string(ret, line[count]);
        }
    }

    return(0);
}

void print_red_space(char* line) {
    char *newl = line;
    newl[strcspn(newl, "\n")] = 0;
    if (newl[strlen(newl)-1] == ' ') {
        newl[strlen(newl)-1] = 0;
    }
    printf("%s%s%s%c%s\n\n", newl, RED, NEGATIVE, ' ', COLOR_RESET);

    return;
}

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
// End utils.c
//
