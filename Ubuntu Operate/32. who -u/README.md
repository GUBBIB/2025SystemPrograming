## 명령어
- **who -u**: 현재 실행 중인 프로세스 목록을 구체적으로 출력하는 명령어

```c
#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>

#define IDLE_THRESHOLD 60  // 60초 단위로 idle 시간 계산

int main() {
    struct utmp entry;
    int fd = open(_PATH_UTMP, O_RDONLY);
    if (fd == -1) {
        perror("utmp 열기 실패");
        return 1;
    }

    printf("USER     TTY      DATE       TIME     IDLE     PID\n");

    while (read(fd, &entry, sizeof(entry)) == sizeof(entry)) {
        if (entry.ut_type == USER_PROCESS) {
            char timebuf[32];
            struct tm *lt = localtime((time_t *) &entry.ut_tv.tv_sec);
            strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M", lt);

            // idle 시간 계산
            char tty_path[64];
            snprintf(tty_path, sizeof(tty_path), "/dev/%s", entry.ut_line);
            struct stat st;
            int idle_minutes = -1;

            if (stat(tty_path, &st) == 0) {
                time_t now = time(NULL);
                idle_minutes = (now - st.st_atime) / 60;
            }

            // IDLE 시간 형식
            char idle_buf[16];
            if (idle_minutes < 0) {
                snprintf(idle_buf, sizeof(idle_buf), "?");
            } else if (idle_minutes == 0) {
                snprintf(idle_buf, sizeof(idle_buf), ".");
            } else {
                snprintf(idle_buf, sizeof(idle_buf), "%02d:%02d", idle_minutes / 60, idle_minutes % 60);
            }

            printf("%-8s %-8s %s %-8s %d\n",
                   entry.ut_user,
                   entry.ut_line,
                   timebuf,
                   idle_buf,
                   entry.ut_pid);
        }
    }

    close(fd);
    return 0;
}
```
## 설명

- ``utmp.h``의 ``_PATH_UTMP``를 열고, ``ut_type == USER_PROCESS``인 사용자 항목만 필터링한다.
- ``ut_pid`` 필드를 통해 해당 사용자의 프로세스 ID를 출력한다.
- ``ut_line``을 기반으로 ``/dev/ttyX`` 경로를 생성하고, ``stat()``의 ``st_atime``을 통해 idle 시간(입력 없던 시간)을 계산한다.
- idle 시간은 분 단위로 계산하여 출력하며, 0분이면 ``.``을, 음수거나 오류면 ``?``로 출력한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/092ff9a1-9b1d-4498-aa04-2ef1e73e0b86)