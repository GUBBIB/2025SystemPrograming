## 명령어
- **printenv**: 환경변수 값 출력
```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s [환경변수 이름]\n", argv[0]);
        return 1;
    }

    char *value = getenv(argv[1]);

    if (value != NULL) {
        printf("%s\n", value);
    }

    // value가 NULL이면 아무것도 출력하지 않음 (기존 printenv와 동일)

    return 0;
}
```
## 설명
- **명령줄 인자(argc, argv)** 를 활용하여 구현했습니다.
- **getenv()**: ``argv[1]``에 들은 **환경변수의 경로**를 가져온다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/fe7a0bf7-786c-40c9-9376-6fce92494899)