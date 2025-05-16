1. ls [ 모든 옵션 ] - 이걸 내 방식대로 만들기 이걸 참고해서
```c++
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <getopt.h>

#define MAX_FILES 1024

typedef struct {
    char name[256];
    struct stat st;
} FileInfo;

FileInfo files[MAX_FILES];
int file_count = 0;

int show_all = 0;
int long_format = 0;
int reverse = 0;
int sort_by_time = 0;

void get_file_list(const char *path) {
    DIR *dir = opendir(path);
    if (!dir) {
        perror("opendir");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (!show_all && entry->d_name[0] == '.') continue;

        if (file_count >= MAX_FILES) break;

        snprintf(files[file_count].name, sizeof(files[file_count].name), "%s/%s", path, entry->d_name);
        stat(files[file_count].name, &files[file_count].st);
        file_count++;
    }

    closedir(dir);
}

int cmp_name(const void *a, const void *b) {
    return strcmp(((FileInfo *)a)->name, ((FileInfo *)b)->name);
}

int cmp_time(const void *a, const void *b) {
    return ((FileInfo *)b)->st.st_mtime - ((FileInfo *)a)->st.st_mtime;
}

void print_file_info(FileInfo *file) {
    struct stat *st = &file->st;
    char *name = strrchr(file->name, '/');
    name = name ? name + 1 : file->name;

    if (long_format) {
        // 권한
        printf( (S_ISDIR(st->st_mode)) ? "d" : "-");
        printf( (st->st_mode & S_IRUSR) ? "r" : "-");
        printf( (st->st_mode & S_IWUSR) ? "w" : "-");
        printf( (st->st_mode & S_IXUSR) ? "x" : "-");
        printf( (st->st_mode & S_IRGRP) ? "r" : "-");
        printf( (st->st_mode & S_IWGRP) ? "w" : "-");
        printf( (st->st_mode & S_IXGRP) ? "x" : "-");
        printf( (st->st_mode & S_IROTH) ? "r" : "-");
        printf( (st->st_mode & S_IWOTH) ? "w" : "-");
        printf( (st->st_mode & S_IXOTH) ? "x" : "-");

        // 링크 수, 소유자, 그룹, 크기, 수정시간
        struct passwd *pw = getpwuid(st->st_uid);
        struct group *gr = getgrgid(st->st_gid);
        char timebuf[64];
        strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", localtime(&st->st_mtime));

        printf(" %3lu %-8s %-8s %8ld %s ", st->st_nlink,
               pw ? pw->pw_name : "?", gr ? gr->gr_name : "?", st->st_size, timebuf);
    }

    printf("%s\n", name);
}

int main(int argc, char *argv[]) {
    int opt;
    static struct option long_options[] = {
        {"all", no_argument, 0, 'a'},
        {"long", no_argument, 0, 'l'},
        {"reverse", no_argument, 0, 'r'},
        {"time", no_argument, 0, 't'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "alrt", long_options, NULL)) != -1) {
        switch (opt) {
            case 'a': show_all = 1; break;
            case 'l': long_format = 1; break;
            case 'r': reverse = 1; break;
            case 't': sort_by_time = 1; break;
            default:
                fprintf(stderr, "Usage: %s [-a] [-l] [-r] [-t] [dir...]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    const char *path = (optind < argc) ? argv[optind] : ".";
    get_file_list(path);

    // 정렬
    qsort(files, file_count, sizeof(FileInfo),
          sort_by_time ? cmp_time : cmp_name);
    if (reverse) {
        for (int i = file_count - 1; i >= 0; i--)
            print_file_info(&files[i]);
    } else {
        for (int i = 0; i < file_count; i++)
            print_file_info(&files[i]);
    }

    return 0;
}

```

2. chmod, fchmod, dup, touch, utime, chown, mkdir, rmdir, 심볼릭 링크, 하드 링크