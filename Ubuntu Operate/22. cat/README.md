## 명령어
- **cat**: 파일 내용을 출력하는 명령어

```c
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s [파일 이름]\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("파일 열기 실패");
        return 1;
    }

    int c;
    while ((c = fgetc(fp)) != EOF) {
        putchar(c);
    }

    fclose(fp);
    return 0;
}
```
## 설명

- ``stdio.h``의 ``fopen()`` 함수를 사용하여 입력된 텍스트 파일을 **읽기 전용 모드("r")**로 연다.
- ``fgetc()``를 통해 파일에서 **한 문자씩 읽어오고**, ``putchar()``로 화면에 출력한다.
- 파일의 끝(`EOF`)까지 반복하며 출력한 뒤, ``fclose()``로 파일을 닫는다.
- 텍스트 파일 하나의 전체 내용을 터미널에 출력하는 ``cat`` 명령어와 동일한 방식으로 동작한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/3bd44a32-10cc-48c4-98e9-995acf8616bc)