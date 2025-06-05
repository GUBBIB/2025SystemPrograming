## 명령어
- **wc**: 텍스트 파일의 줄 수, 단어 수, 바이트 수를 세는 명령어

```c
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s [파일이름]\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("파일 열기 실패");
        return 1;
    }

    int lines = 0, words = 0, bytes = 0;
    int c, in_word = 0;

    while ((c = fgetc(fp)) != EOF) {
        bytes++;

        if (c == '\n')
            lines++;

        if (isspace(c)) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            words++;
        }
    }

    fclose(fp);

    printf("줄 수: %d, 단어 수: %d, 바이트 수: %d\n", lines, words, bytes);
    return 0;
}
```
## 설명
- fopen() 함수로 파일을 **읽기 전용 모드("r")**로 연는다.
- fgetc()로 문자를 한 개씩 읽으며:
    - '\n'이면 줄 수 증가
    - isspace()로 공백/탭/개행 등을 체크해 단어 경계 판단
    - bytes는 총 문자 개수 세어 바이트 수로 취급
- 파일 끝까지 읽은 후 fclose()로 닫는다

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/64f4af1b-26d4-4c6a-8a7d-94661abcbb91)