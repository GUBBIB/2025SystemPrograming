## 명령어
- **tail -n**: 파일의 마지막 n개 줄을 출력하는 명령어 

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 1024
#define MAX_LINE_LENGTH 1024
#define DEFAULT_TAIL_LINES 10

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s [파일 이름]\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("파일 열기 실패");
        return 1;
    }

    char *lines[MAX_LINES];
    int count = 0;

    // 한 줄씩 읽고 배열에 저장
    while (!feof(fp)) {
        char buffer[MAX_LINE_LENGTH];
        if (fgets(buffer, sizeof(buffer), fp)) {
            lines[count % MAX_LINES] = strdup(buffer);
            count++;
        }
    }
    fclose(fp);

    // 출력 시작 인덱스 계산
    int start = count > DEFAULT_TAIL_LINES ? count - DEFAULT_TAIL_LINES : 0;

    // 출력
    for (int i = start; i < count; i++) {
        printf("%s", lines[i % MAX_LINES]);
        free(lines[i % MAX_LINES]); // 메모리 해제
    }

    return 0;
}
```
## 설명

- ``argv[1]``에서 출력할 줄 수를 정수로 파싱하고, ``argv[2]``의 파일을 ``fopen()``으로 읽기 전용으로 연다.
- ``fgets()``로 줄 단위로 읽고, ``strdup()``으로 복사하여 순환 배열에 저장한다.
- 총 줄 개수에서 출력할 줄 수를 뺀 인덱스부터 출력하고, ``free()``로 메모리를 해제한다.
- ``tail -n [줄 수] [파일명]`` 명령어와 같은 방식으로 동작한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/10aba588-5e9a-4e2d-b39b-b9b72e15f820)