```c
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>

int main() {
    struct passwd *pw = getpwuid(getuid());
    if (pw != NULL) {
        printf("%s\n", pw->pw_name);
    } else {
        perror("getpwuid 오류");
        return 1;
    }
    return 0;
}
```
## 설명
- **getuid()**: 현재 사용자의 UID(User ID)를 반환
- **getpwuid(uid)**: ``getuid``로 얻은 ``uid``를 통해서 사용자 정보를 담은 **구조체(struct)** 를 반환

- **passwd 구조체**: ``getpwuid``를 통해 얻은 구조체에서 ``pw_name``을 출력
```c
#include <pwd.h>

struct passwd {
    char   *pw_name;       // 사용자 이름 ← 우리가 원하는 정보
    char   *pw_passwd;     // 암호 (대개 x 또는 *)
    uid_t   pw_uid;        // 사용자 ID
    gid_t   pw_gid;        // 그룹 ID
    char   *pw_gecos;      // 사용자 전체 이름
    char   *pw_dir;        // 홈 디렉토리
    char   *pw_shell;      // 로그인 셸
};
```


## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/e6e82748-e627-457c-a39e-b3f24ed39bf0)