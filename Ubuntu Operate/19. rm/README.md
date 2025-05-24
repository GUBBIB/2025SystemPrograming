## 명령어
- **rm**: 파일 삭제 명령어

```c
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s [파일 이름]\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];

    if (unlink(filename) == -1) {
        perror("파일 삭제 실패");
        return 1;
    }

    printf("파일 '%s' 삭제 완료\n", filename);
    return 0;
}
```
## 설명
- ``unistd.h``에 정의된 **unlink()** 함수로 파일을 삭제한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/b183c897-4e00-4e43-8d3a-db87833a3d82)