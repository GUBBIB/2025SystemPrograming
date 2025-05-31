## 명령어
- **df -h**: 디스크의 파일 시스템 사용량(전체, 사용 중, 사용 가능 공간 등) 을 사람이 읽기 좋게 출력하는 명령어

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/statvfs.h>

void print_size(unsigned long bytes) {
    const char *units[] = {"B", "K", "M", "G", "T"};
    int i = 0;
    double size = bytes;

    while (size >= 1024 && i < 4) {
        size /= 1024;
        i++;
    }

    printf("%6.2f%s", size, units[i]);
}

int main() {
    struct statvfs fs;

    if (statvfs("/", &fs) != 0) {
        perror("statvfs 실패");
        return 1;
    }

    unsigned long total = fs.f_blocks * fs.f_frsize;
    unsigned long free = fs.f_bfree * fs.f_frsize;
    unsigned long available = fs.f_bavail * fs.f_frsize;
    unsigned long used = total - free;

    printf("파일시스템       총용량   사용중   사용가능  마운트지점\n");
    printf("/dev/root      ");
    print_size(total);
    printf("  ");
    print_size(used);
    printf("  ");
    print_size(available);
    printf("  /\n");

    return 0;
}
```
## 설명

- ``statvfs()`` 함수로 루트 디렉토리(/)의 파일시스템 정보를 불러온다.
- 용량은 바이트 단위로 계산하고, 사람이 보기 쉬운 단위(B, K, M, G, T)로 변환하여 출력한다.
- ``print_size()`` 함수는 자동으로 적절한 단위를 선택해 2자리 소수까지 포맷하여 출력한다.
- ``df -h`` 명령어와 동일한 형식으로 동작한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/84e092d3-9849-4a96-86a9-a35eb589ae60)