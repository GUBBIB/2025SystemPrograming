## 명령어
- **basename**: 무한히 **ICMP ping** 패킷을 보내는 명령어

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

    printf("%s\n", basename(path));  // 경로에서 파일 이름 추출
    return 0;
}
```
## 설명

- libgen.h에 정의된 basename() 함수는 문자열에서 가장 마지막 / 이후의 부분을 반환한다.
- 원본 문자열을 직접 수정하므로, snprintf()로 복사한 후 사용한다.
- 경로를 인수로 받아서 파일명만 추출한 뒤 출력한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/c0e37d9a-36e2-489c-897a-0941c99bce0e)