## 명령어
- **ps**: 현재 실행 중인 프로세스 목록을 출력하는 명령어

```c
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int is_number(const char *str) {
    while (*str) {
        if (!isdigit(*str)) return 0;
        str++;
    }
    return 1;
}

int main() {
    DIR *proc = opendir("/proc");
    struct dirent *entry;

    if (!proc) {
        perror("/proc 열기 실패");
        return 1;
    }

    printf("  PID CMD\n");

    while ((entry = readdir(proc)) != NULL) {
        if (is_number(entry->d_name)) {
            char path[512];  // 넉넉하게 늘림
            char cmdline[256];
            FILE *fp;

            // PID 길이를 제한
            if (strlen(entry->d_name) > 20) continue;

            snprintf(path, sizeof(path), "/proc/%s/comm", entry->d_name);

            fp = fopen(path, "r");
            if (fp) {
                if (fgets(cmdline, sizeof(cmdline), fp)) {
                    cmdline[strcspn(cmdline, "\n")] = '\0';
                    printf("%5s %s\n", entry->d_name, cmdline);
                }
                fclose(fp);
            }
        }
    }

    closedir(proc);
    return 0;
}
```
## 설명

- ``/proc`` 디렉토리에서 숫자로 된 PID 디렉토리만 필터링한다.
- 각 ``/proc/[PID]/comm`` 파일을 열어 프로세스 이름을 읽어온다.
- ``fgets()``로 이름을 읽고, PID와 함께 출력한다.
- ``ps`` 명령어처럼 현재 실행 중인 프로세스 목록을 확인할 수 있다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/32621883-ae44-4486-a63f-bb5ee17ef6c0)