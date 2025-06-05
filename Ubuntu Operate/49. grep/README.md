## 명령어
- **df -T**: 주어진 파일에서 특정 문자열이 포함된 줄을 출력하는 명령어

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "사용법: %s [검색할 문자열] [파일명]\n", argv[0]);
        return 1;
    }

    const char *keyword = argv[1];
    const char *filename = argv[2];

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("파일 열기 실패");
        return 1;
    }

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, keyword) != NULL) {
            printf("%s", line);
        }
    }

    fclose(file);
    return 0;
}
```
## 설명
- fopen()으로 파일을 읽기 모드로 연다.
- fgets()로 한 줄씩 읽는다.
- strstr()로 해당 줄에 검색어가 포함되어 있는지 확인한다.
- 포함되어 있으면 printf()로 해당 줄을 출력한다.
- 파일을 모두 읽고 나면 fclose()로 닫는다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/edd47960-9ffe-4b23-8b55-80801bc7d0b9)