## 명령어
- **stat**: 파일의 정보(크기, 권한, 마지막 수정 시간 등)를 출력하는 명령어

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

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

    struct passwd *pw = getpwuid(st.st_uid);
    struct group  *gr = getgrgid(st.st_gid);

    printf("  파일: %s\n", argv[1]);
    printf("  크기: %ld 바이트\n", st.st_size);
    printf("  권한: %o\n", st.st_mode & 0777);
    printf("  소유자: %s\n", pw ? pw->pw_name : "알 수 없음");
    printf("  그룹: %s\n", gr ? gr->gr_name : "알 수 없음");
    printf("  마지막 수정 시간: %s", ctime(&st.st_mtime));  // 개행 포함됨

    return 0;
}
```
## 설명

- sys/stat.h의 stat() 함수로 파일 정보를 가져온다.
- struct stat 구조체에는 파일의 크기, 권한, 소유자 등의 정보가 들어 있다.
- getpwuid(), getgrgid()로 사용자 이름과 그룹 이름을 얻는다.
- ctime() 함수로 마지막 수정 시간을 사람이 읽을 수 있는 형식으로 출력한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/4329219f-bac4-4ffa-8cd1-fad4b927b897)