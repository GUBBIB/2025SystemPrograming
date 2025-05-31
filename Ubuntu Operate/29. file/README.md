## 명령어
- **file**: 파일의 **종류(type)**를 출력하는 명령어
```c
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s [파일명]\n", argv[0]);
        return 1;
    }

    struct stat st;
    if (stat(argv[1], &st) == -1) {
        perror("stat 실패");
        return 1;
    }

    printf("%s: ", argv[1]);

    if (S_ISREG(st.st_mode)) {
        printf("regular file\n");
    } else if (S_ISDIR(st.st_mode)) {
        printf("directory\n");
    } else if (S_ISLNK(st.st_mode)) {
        printf("symbolic link\n");
    } else if (S_ISCHR(st.st_mode)) {
        printf("character device\n");
    } else if (S_ISBLK(st.st_mode)) {
        printf("block device\n");
    } else if (S_ISFIFO(st.st_mode)) {
        printf("FIFO/pipe\n");
    } else if (S_ISSOCK(st.st_mode)) {
        printf("socket\n");
    } else {
        printf("unknown type\n");
    }

    return 0;
}
```
## 설명

- ``sys/stat.h``의 ``stat()`` 함수로 파일 메타데이터를 구조체로 받아온다.
- ``st_mode``의 비트 값을 ``S_ISREG()``, ``S_ISDIR()`` 등 매크로로 검사하여 파일의 타입을 판별한다.
- ``file`` 명령어처럼 해당 파일이 일반 파일인지, 디렉토리인지, 심볼릭 링크인지 등을 출력한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/5972b3a6-46f1-42d5-85e0-405cb818d92e)