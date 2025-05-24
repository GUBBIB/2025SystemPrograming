## 명령어
- **touch**: 파일이 없으면 생성, 있으면 마지막 수정 시간 갱신 명령어

```c
#include <stdio.h>
#include <fcntl.h>
#include <utime.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s [파일 이름]\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    int fd;

    // 파일 열기 (없으면 생성), O_WRONLY 안 써도 시간 갱신 가능
    fd = open(filename, O_CREAT | O_WRONLY, 0644);
    if (fd == -1) {
        perror("파일 열기 실패");
        return 1;
    }
    close(fd);  // 파일만 열고 닫기

    // 시간 정보 갱신
    if (utime(filename, NULL) == -1) {
        perror("시간 갱신 실패");
        return 1;
    }

    return 0;
}
```
## 설명
- **명령줄 인자(argc, argv)** 를 활용하여 구현했습니다.

- ``open()`` 에서 ``fcntl.h`` 에 정의된 **상수(O_CREAT, O_WRONLY)**들을 사용하여 파일이 존재하면 열고, 없으면 **0644권한(사용자 rw-, 그룹 r--, 기타 r--)**의 파일을 생성한 뒤, 즉시 닫는다.

- ``utime.h``에 정의된 **utime()** 함수로 파일의 접근시간과 수정시간을 변경한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/f5fe9a37-3288-4518-aa50-6a7cd76493a4)