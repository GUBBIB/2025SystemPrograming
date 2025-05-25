## 명령어
- **tail**: 파일의 마지막 몇 줄을 출력하는 명령어 ``[ 기본값: 10줄 ]``

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

- ``fopen()`` 함수로 텍스트 파일을 읽기 전용 모드로 연다.
- ``fgets()``를 사용해 한 줄씩 읽고, ``strdup()``으로 문자열을 동적으로 저장한다.
- 최대 1024줄까지 순환 버퍼 형태로 저장하여, 최근 줄만 유지하도록 한다.
- 읽은 줄의 총 개수가 10줄보다 많으면, ``count - 10``부터 출력한다.
- 출력 후 ``free()`` 함수를 통해 메모리를 해제한다.
- ``tail`` 명령어와 동일하게, 파일의 마지막 10줄만 출력한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/22668243-a17e-45ed-ad25-ea98bfa352d7)