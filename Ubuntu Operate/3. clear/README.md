```c
#include <stdio.h>

int main() {
    // ANSI 이스케이프 시퀀스로 화면 지우고, 커서 맨 위로 이동
    printf("\033[2J");   // 화면 전체 지우기
    printf("\033[H");    // 커서를 좌측 상단으로 이동
    fflush(stdout);      // 출력 즉시 반영

    return 0;
}
```

## 설명
- ``printf("\033[2J")``와 ``printf("\033[H")``를 이용해 직접 **ANSI escape 코드** 를 출력하여 화면을 지우고 커서를 초기 위치로 이동시켰습니다.

## 컴파일 및 실행화면
- 실행 전

![Image](https://github.com/user-attachments/assets/2cd401e1-03fb-4983-9c29-e9fd4364c783)

- 실행 후

![Image](https://github.com/user-attachments/assets/e3f4da39-3a70-42a8-aeb7-aa658925ac0b)