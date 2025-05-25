## 명령어
- **head**: 파일의 처음 몇 줄을 출력하는 명령어 ``[ 기본값:10줄 ]``

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

- ``stdio.h``의 ``fopen()`` 함수를 사용하여 입력된 텍스트 파일을 **읽기 전용 모드("r")**로 연다.
- ``fgets()``를 통해 파일에서 **한 줄씩 읽고**, ``printf()``를 사용하여 화면에 출력한다.
- 출력된 줄의 수가 10줄에 도달하면 반복을 종료한다.
- 파일을 모두 출력한 뒤에는 ``fclose()``를 사용하여 파일을 닫는다.
- 이는 ``head`` 명령어와 동일하게, 텍스트 파일의 처음 10줄만 출력하는 동작을 수행한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/6b00072c-0de1-46ca-b7de-65a9f119d6dd)