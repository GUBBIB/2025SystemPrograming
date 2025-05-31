## 명령어
- **id -u**: 현재 사용자의 **UID(User ID)** 만 출력하는 명령어
```c
#include <stdio.h>
#include <unistd.h>

int main() {
    uid_t uid = getuid();   // 현재 사용자 UID 가져오기
    printf("%d\n", uid);    // UID 출력
    return 0;
}
```
## 설명

- ``unistd.h``에 정의된 ``getuid()`` 함수를 사용하여 현재 사용자 UID(User ID)를 가져온다.
- ``printf()``로 UID를 출력한다.
- ``id -u`` 명령어와 같은 방식으로 현재 사용자의 UID만 출력한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/a9d83a92-881e-4175-b415-e9a3082e6a86)