## 명령어
- **id**: 사용자 정보 출력
```c
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

int main() {
    uid_t uid = getuid();                 // 사용자 UID
    gid_t gid = getgid();                 // 그룹 GID

    struct passwd *pw = getpwuid(uid);    // 사용자 정보
    struct group *gr = getgrgid(gid);     // 그룹 정보

    if (pw == NULL || gr == NULL) {
        perror("사용자 또는 그룹 정보를 가져올 수 없습니다");
        return 1;
    }

    printf("uid=%d(%s) gid=%d(%s)\n", uid, pw->pw_name, gid, gr->gr_name);

    return 0;
}
```
## 설명
- **getuid()**: **사용자 UID(User ID)** 반환
- **getgid()**: **그룹 ID** 반환
- **getpwuid()**: ``UID``를 통해서 **구조체** 반환
- **getgrgid()**: ``GID``를 통해서 **구조체** 반환
- **구조체**: ``UID``, ``GID`` 구조체를 통해서 각 name을 출력

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/c4943a63-cec3-4a79-83b6-2cec0b2d7aac)