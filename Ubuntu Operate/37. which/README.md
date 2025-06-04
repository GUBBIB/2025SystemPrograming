## 명령어
- **which**: 디스크의 파일 시스템 사용량(전체, 사용 중, 사용 가능 공간 등) 을 사람이 읽기 좋게 출력하는 명령어

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s [명령어 이름]\n", argv[0]);
        return 1;
    }

    char *path_env = getenv("PATH");
    if (path_env == NULL) {
        fprintf(stderr, "PATH 환경변수를 찾을 수 없습니다.\n");
        return 1;
    }

    char *path_copy = strdup(path_env);
    char *dir = strtok(path_copy, ":");

    while (dir != NULL) {
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, argv[1]);

        if (access(full_path, X_OK) == 0) {
            printf("%s\n", full_path);
            free(path_copy);
            return 0;
        }

        dir = strtok(NULL, ":");
    }

    printf("%s: 명령어를 찾을 수 없습니다.\n", argv[1]);
    free(path_copy);
    return 1;
}
```
## 설명

- ``getenv("PATH")``를 통해 ``PATH`` 환경변수를 가져온다.
- ``strtok()``으로 ``:`` 구분자를 기준으로 디렉토리를 하나씩 분리한다.
- 각 디렉토리에 대해 ``명령어 이름``을 붙여 전체 경로를 만든 뒤, ``access(path, X_OK)``를 통해 실행 가능 여부를 확인한다.
- 찾으면 경로를 출력하고, 못 찾으면 오류 메시지를 출력한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/8f528449-b884-447a-871a-e75d6ed70350)