## 명령어
- **whereis**: 명령어 관련 파일(실행파일, man 파일 등) 위치 모두 확인

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char *paths[] = {
    "/bin",
    "/usr/bin",
    "/sbin",
    "/usr/sbin",
    "/usr/local/bin",
    "/usr/share/man/man1"
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s [명령어 이름]\n", argv[0]);
        return 1;
    }

    const char *cmd = argv[1];
    char fullpath[1024];

    for (int i = 0; i < sizeof(paths) / sizeof(paths[0]); i++) {
        snprintf(fullpath, sizeof(fullpath), "%s/%s", paths[i], cmd);

        // 실행 파일 또는 매뉴얼 존재 여부 확인
        if (access(fullpath, F_OK) == 0) {
            printf("%s\n", fullpath);
        } else {
            // man 파일은 압축된 경우도 있음
            snprintf(fullpath, sizeof(fullpath), "%s/%s.1.gz", paths[i], cmd);
            if (access(fullpath, F_OK) == 0) {
                printf("%s\n", fullpath);
            }
        }
    }

    return 0;
}
```
## 설명

- ``whereis`` 명령어는 실행파일과 man 페이지의 경로를 알려준다.
- ``access()`` 함수를 통해 미리 지정한 경로들에서 해당 파일이 존재하는지 확인한다.
- 실행 파일(`bin` 등)과 man 파일(`.1.gz`) 디렉토리(`/usr/share/man/man1`) 등을 순회하며 출력한다.
- 옵션 없이 ``whereis [명령어이름]``만 지원한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/8901b781-b650-4a80-ba2e-7ed5da75f234)