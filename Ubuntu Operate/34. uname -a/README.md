## 명령어
- **uname -a**: 운영체제에 대한 전체 시스템 정보를 출력하는 명령어

```c
#include <stdio.h>
#include <sys/utsname.h>

int main() {
    struct utsname buffer;

    if (uname(&buffer) == -1) {
        perror("uname 실패");
        return 1;
    }

    printf("%s %s %s %s %s\n",
           buffer.sysname,   // 운영 체제 이름
           buffer.nodename,  // 호스트 이름
           buffer.release,   // 커널 릴리즈
           buffer.version,   // 커널 버전
           buffer.machine    // 하드웨어 정보
    );

    return 0;
}
```
## 설명

- ``sys/utsname.h``의 ``uname()`` 함수는 시스템 정보를 담은 ``utsname`` 구조체를 반환한다.
- 구조체의 각 필드를 활용하여 운영 체제, 노드 이름, 커널 버전, 하드웨어 정보 등을 출력한다.
- ``uname -a`` 명령어와 동일하게 전체 시스템 정보를 출력한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/d32af6a2-3b5c-4f39-b4ab-5aeb58d905dc)