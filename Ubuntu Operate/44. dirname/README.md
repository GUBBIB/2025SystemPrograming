## 명령어
- **dirname**: 경로에서 디렉토리 이름만 추출하는 명령어

```c
#include <stdio.h>
#include <string.h>
#include <libgen.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s [경로]\n", argv[0]);
        return 1;
    }

    char path[1024];
    snprintf(path, sizeof(path), "%s", argv[1]);

    printf("%s\n", dirname(path));  // 경로에서 디렉토리 경로 추출
    return 0;
}
```
## 설명

- libgen.h에 정의된 dirname() 함수는 문자열에서 마지막 '/' 앞부분을 반환한다.
- dirname()은 원본 문자열을 수정하므로, snprintf()로 복사한 후 사용한다.
- 경로가 포함된 파일이나 디렉토리 경로를 받아 디렉토리 부분만 출력한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/828d918e-2cb0-43a3-80dd-ea761ad958b0)