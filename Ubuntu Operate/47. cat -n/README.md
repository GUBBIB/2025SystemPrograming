## 명령어
- **cat -n**: 텍스트 파일의 각 줄 앞에 줄 번호를 붙여 출력하는 명령어

```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s [파일명]\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("파일 열기 실패");
        return 1;
    }

    int c;
    int line = 1;
    int new_line = 1;

    while ((c = fgetc(file)) != EOF) {
        if (new_line) {
            printf("%6d  ", line++);
            new_line = 0;
        }

        putchar(c);

        if (c == '\n') {
            new_line = 1;
        }
    }

    fclose(file);
    return 0;
}
```
## 설명

- fopen() 함수로 파일을 읽기 전용 모드 "r"로 연다.
- fgetc()로 파일을 한 문자씩 읽어오고, putchar()로 출력한다.
- 줄 바꿈 문자 \n이 나오면 줄 번호를 증가시키고 다음 줄에도 번호를 붙인다.
- cat -n 명령어처럼 각 줄 앞에 줄 번호를 출력한다.
- 출력 포맷은 printf("%6d ", line++)처럼 줄 번호 6자리 정렬.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/a9b68d70-299b-40b3-97ab-56ba843da718)