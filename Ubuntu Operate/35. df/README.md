## 명령어
- **df**: 디스크의 파일 시스템 사용량(전체, 사용 중, 사용 가능 공간 등) 을 출력하는 명령어

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/statvfs.h>

int main() {
    struct statvfs fs;

    // 루트 디렉토리("/")의 파일시스템 정보 얻기
    if (statvfs("/", &fs) != 0) {
        perror("statvfs 실패");
        return 1;
    }

    unsigned long total = fs.f_blocks * fs.f_frsize;
    unsigned long free = fs.f_bfree * fs.f_frsize;
    unsigned long available = fs.f_bavail * fs.f_frsize;
    unsigned long used = total - free;

    printf("파일시스템   총용량     사용중     사용가능   마운트지점\n");
    printf("/dev/root    %.2fG    %.2fG    %.2fG      /\n",
           total / (1024.0 * 1024 * 1024),
           used / (1024.0 * 1024 * 1024),
           available / (1024.0 * 1024 * 1024));

    return 0;
}
```
## 설명

- ``sys/statvfs.h`` 헤더의 ``statvfs()`` 함수는 특정 경로에 대한 파일시스템 정보를 구조체에 채운다.
- ``f_blocks`` × ``f_frsize`` 로 전체 블록 크기를 계산한다.
- ``f_bfree``: 전체 블록 중 사용 가능한 총 블록 (루트 포함)
- ``f_bavail``: 일반 사용자에게 사용 가능한 블록
- 사용량 = 전체 - f_bfree
- 출력은 루트("/") 기준이며, 실제 ``df`` 명령어처럼 마운트된 위치의 디스크 사용량 정보를 보여준다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/1efa53c4-1f22-4f99-b7f0-9aab237727f2)