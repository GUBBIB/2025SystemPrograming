## 명령어
- **sleep**: 주어진 초(seconds)만큼 프로그램 실행을 일시 중지하는 명령어

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s [초 단위 시간]\n", argv[0]);
        return 1;
    }

    int seconds = atoi(argv[1]);  // 문자열 → 정수 변환
    if (seconds < 0) {
        fprintf(stderr, "양의 정수를 입력하세요.\n");
        return 1;
    }

    sleep(seconds);  // 실행 일시 정지

    return 0;
}
```
## 설명

- unistd.h에 정의된 sleep() 함수는 초 단위로 프로그램을 일시 중지시킨다.
- atoi() 함수로 입력 문자열을 정수로 바꾼 뒤, 음수면 오류 처리한다.
- ./sleep_c 5라고 실행하면 5초 동안 멈췄다가 종료된다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/11664e4f-fafd-47e7-ba48-30b2e22ad1e8)