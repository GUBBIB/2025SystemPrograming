## 명령어
- **makdir -p**: 디렉토리 생성 명령어, 상위 디렉토리가 없으면 자동 생성 옵션

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int mkdir_p(const char *path) {
    char tmp[1024];
    char *p = NULL;
    size_t len;

    snprintf(tmp, sizeof(tmp), "%s", path);
    len = strlen(tmp);

    if (tmp[len - 1] == '/')
        tmp[len - 1] = '\0';  // 끝에 '/' 있으면 제거

    for (p = tmp + 1; *p; p++) {
        if (*p == '/') {
            *p = '\0';
            mkdir(tmp, 0755);  // 중간 경로 만들기 (실패해도 무시)
            *p = '/';
        }
    }

    return mkdir(tmp, 0755);  // 마지막 경로 만들기
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s [경로]\n", argv[0]);
        return 1;
    }

    if (mkdir_p(argv[1]) == -1 && errno != EEXIST) {
        perror("디렉토리 생성 실패");
        return 1;
    }

    printf("디렉토리 '%s' 생성 완료\n", argv[1]);
    return 0;
}
```
## 설명
- **명령줄 인자(argc, argv)** 를 활용하여 구현했습니다.

- **mkdir_p()** 함수는 ``/``로 구분된 경로를 단계별로 생성하여,
상위 디렉토리가 없는 경우에도 **자동으로 만들어준다.**

- ``sys/stat.h`` 헤더에 있는 **mkdir()** 함수를 통해서 디렉토리를 생성하며, 권한으로 **0755(사용자 rwx, 그룹 r-x, 기타 r-x)**를 준다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/fd7ae5ee-eaa9-4be1-a477-984888275a74)