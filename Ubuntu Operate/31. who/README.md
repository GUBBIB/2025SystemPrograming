## 명령어
- **who**: 현재 실행 중인 프로세스 목록을 출력하는 명령어

```c
#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

int main() {
    struct utmp entry;

    // utmp 파일 열기
    int fd = open(_PATH_UTMP, O_RDONLY);
    if (fd == -1) {
        perror("utmp 열기 실패");
        return 1;
    }

    printf("USER     TTY      DATE       TIME\n");

    while (read(fd, &entry, sizeof(entry)) == sizeof(entry)) {
        if (entry.ut_type == USER_PROCESS) {
            char timebuf[32];
            struct tm *lt = localtime((time_t *) &entry.ut_tv.tv_sec);
            strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M", lt);

            printf("%-8s %-8s %s\n", entry.ut_user, entry.ut_line, timebuf);
        }
    }

    close(fd);
    return 0;
}
```
## 설명

- ``utmp.h``의 ``_PATH_UTMP`` 경로(`/var/run/utmp`)에서 로그인 세션 정보를 읽는다.
- ``utmp`` 구조체 배열을 순회하면서 ``ut_type == USER_PROCESS``인 항목만 출력한다.
- 사용자 이름(`ut_user`), 터미널 이름(`ut_line`), 로그인 시간(`ut_tv`)을 출력한다.
- ``strftime()``과 ``localtime()``을 사용하여 시간을 사람이 읽기 좋은 형식으로 변환한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/4740de97-8322-497e-a5ff-b79338e11e31)