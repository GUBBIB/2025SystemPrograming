## 명령어
- **head -n**: 파일의 처음 몇 줄을 출력하는 명령어 

```c
#include <stdio.h>

#define MAX_LINE 1024
#define DEFAULT_LINE_COUNT 10

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

    char line[MAX_LINE];
    int count = 0;

    while (fgets(line, sizeof(line), fp) != NULL && count < DEFAULT_LINE_COUNT) {
        printf("%s", line);
        count++;
    }

    fclose(fp);
    return 0;
}
```
## 설명

- 프로그램 실행 시 ``줄 수``와 ``파일 이름``을 인자로 전달받아, ``execvp()`` 함수를 통해 시스템의 ``head -n [줄 수] [파일 이름]`` 명령어를 실행한다.
- ``char *args[]`` 배열에 명령어 인자들을 구성하고, ``execvp("head", args)``를 호출하여 현재 프로세스를 ``head``로 대체한다.
- 이로써 외부 명령어 ``head``가 직접 실행되어 지정된 줄 수만큼 파일 내용을 출력하게 된다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/b17fe484-f1c4-44de-af6d-5f629ad1d558)