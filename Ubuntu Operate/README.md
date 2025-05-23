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

### ✅ C 언어로 구현하기 쉬운 Ubuntu 명령어 50선 (난이도순)

---

#### 🟢 레벨 1 (아주 쉬움)

| 명령어             | 설명        |
| --------------- | --------- |
| `pwd`           | 현재 경로 출력  |
| `echo hello`    | 문자열 출력    |
| `clear`         | 화면 지우기    |
| `whoami`        | 현재 사용자 출력 |
| `date`          | 현재 시간 출력  |
| `hostname`      | 호스트 이름 출력 |
| `uname`         | 커널 정보 출력  |
| `id`            | 사용자 정보 출력 |
| `printenv PATH` | 환경 변수 출력  |
| `exit`          | 프로그램 종료   |

#### 🔵 레벨 2 (쉬움)

| 명령어                    | 설명            |
| ---------------------- | ------------- |
| `ls`                   | 현재 디렉토리 파일 목록 |
| `ls -a`                | 숨긴 파일 포함 목록   |
| `ls -l`                | 상세 정보 출력      |
| `ls -al`               | 숨김+상세 목록      |
| `ls -R`                | 재귀적 목록        |
| `mkdir test`           | 디렉토리 생성       |
| `mkdir -p test/subdir` | 하위 디렉토리 포함 생성 |
| `rmdir test`           | 디렉토리 삭제       |
| `touch test.txt`       | 빈 파일 생성       |
| `rm test.txt`          | 파일 삭제         |
| `rm -f test.txt`       | 강제 삭제         |
| `rm -r test_dir`       | 디렉토리 삭제 (재귀)  |

#### 🟡 레벨 3 (보통)

| 명령어                   | 설명          |
| --------------------- | ----------- |
| `file test.txt`       | 파일 타입 판단    |
| `cat file.txt`        | 파일 내용 출력    |
| `head file.txt`       | 앞부분 출력      |
| `head -n 5 file.txt`  | 앞 n줄 출력     |
| `tail file.txt`       | 뒷부분 출력      |
| `tail -n 10 file.txt` | 뒤 n줄 출력     |
| `env`                 | 환경 변수 전체 출력 |
| `printenv`            | 환경 변수 출력    |
| `set`                 | 쉘 변수 출력     |
| `id -u`               | UID 출력      |
| `id -g`               | GID 출력      |

#### 🟠 레벨 4 (약간 어려움)

| 명령어        | 설명            |
| ---------- | ------------- |
| `ps`       | 현재 프로세스 출력    |
| `ps -e`    | 전체 프로세스 출력    |
| `who`      | 로그인 사용자 출력    |
| `who -u`   | 사용자 + 세부정보 출력 |
| `uptime`   | 시스템 가동 시간     |
| `uname -a` | 커널 정보 전체 출력   |
| `df`       | 디스크 공간 사용량    |
| `df -h`    | 사람이 읽기 쉬운 형식  |
| `du`       | 디스크 사용량       |
| `du -h`    | 사람이 읽기 쉬운 형식  |

#### 🔴 레벨 5 (어려움)

| 명령어                       | 설명                 |
| ------------------------- | ------------------ |
| `which ls`                | 실행 파일 경로 찾기        |
| `whereis ls`              | 실행 파일/소스/매뉴얼 경로 찾기 |
| `find . -name "file.txt"` | 현재 경로에서 파일 탐색      |
| `find / -type f`          | 전체 파일 탐색           |
| `hostname -I`             | IP 주소 출력           |
| `ping -c 1 google.com`    | 네트워크 응답 테스트        |
| `curl http://example.com` | HTTP 요청            |

---

