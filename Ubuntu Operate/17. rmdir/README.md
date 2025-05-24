## 명령어
- **rmdir**: 디렉토리 삭제 명령어

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s [디렉토리 이름]\n", argv[0]);
        return 1;
    }

    const char *dirname = argv[1];

    if (rmdir(dirname) == -1) {
        perror("디렉토리 삭제 실패");
        return 1;
    }

    printf("디렉토리 '%s' 삭제 완료\n", dirname);
    return 0;
}
```
## 설명
- **명령줄 인자(argc, argv)** 를 활용하여 구현했습니다.

- ``unistd.h`` 헤더에 있는 **rmdir()** 함수를 통해서 디렉토리를 삭제한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/51d0c882-8c09-49a1-8179-39fb2d338f3c)