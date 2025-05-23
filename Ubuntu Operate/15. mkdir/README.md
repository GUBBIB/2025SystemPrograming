## 명령어
- **makdir**: 디렉토리 생성 명령어

```c
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s [디렉토리 이름]\n", argv[0]);
        return 1;
    }

    const char *dirname = argv[1];

    // 0755 권한: rwxr-xr-x
    if (mkdir(dirname, 0755) == -1) {
        perror("디렉토리 생성 실패");
        return 1;
    }

    printf("디렉토리 '%s' 생성 완료\n", dirname);
    return 0;
}
```
## 설명
- **명령줄 인자(argc, argv)** 를 활용하여 구현했습니다.
- ``sys/stat.h`` 라이브러리에 있는 **mkdir()** 함수를 통해서 디렉토리를 생성하며, 권한으로 **0755(사용자 rwx, 그룹 r-x, 기타 r-x)**를 준다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/ba940adc-f71a-4d68-af67-316888af008b)