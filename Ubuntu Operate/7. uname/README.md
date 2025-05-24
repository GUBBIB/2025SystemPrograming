## 명령어
- **uname**: 커널 이름 출력
```c
#include <stdio.h>
#include <sys/utsname.h>

int main() {
    struct utsname buffer;

    if (uname(&buffer) == 0) {
        printf("%s\n", buffer.sysname);  // 커널 이름만 출력 (예: Linux)
    } else {
        perror("uname 오류");
        return 1;
    }

    return 0;
}
```
## 설명
- ``sys/utsname.h``에 정의된 **uname()** 함수로 커널 이름을 들고온다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/8ac5f987-7d49-4a68-ba1c-f333b1f1f282)