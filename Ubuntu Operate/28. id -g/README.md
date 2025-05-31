## 명령어
- **id -g**: 현재 사용자의 **GID(기본 그룹 ID)** 만 출력하는 명령어
```c
#include <stdio.h>
#include <unistd.h>

int main() {
    gid_t gid = getgid();   // 현재 사용자 GID 가져오기
    printf("%d\n", gid);    // GID 출력
    return 0;
}
```
## 설명

- ``unistd.h``에 정의된 ``getgid()`` 함수를 사용하여 현재 사용자의 GID(Group ID)를 가져온다.
- ``printf()``로 GID를 출력한다.
- ``id -g`` 명령어와 같은 방식으로 현재 사용자의 기본 그룹 ID만 출력한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/60805165-0b0f-4e58-904a-460a34704931)