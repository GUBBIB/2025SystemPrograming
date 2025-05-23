## 명령어
- **pwd**: 현재 경로를 추력하는 명령어
```c
#include <stdio.h>
#include <unistd.h>   // getcwd 함수
#include <limits.h>   // PATH_MAX 상수

int main() {
    char cwd[PATH_MAX];  // 현재 작업 디렉토리를 저장할 버퍼

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);  // 현재 디렉토리 경로 출력
    } else {
        perror("getcwd 오류");  // 오류 메시지 출력
        return 1;
    }

    return 0;
}
```
## 구현 설명
- ``getcwd(char *buf, size_t size)`` 함수를 통해서 현재 위치를 저장할 수 있다.
- **PATH_MAX**는 ``limits.h``에 정의된 상수이다. **※ 크기는 4096**

## 컴파일 및 실행화면
![Image](https://github.com/user-attachments/assets/fa61f2c7-2b38-476d-b91d-fc9fd3e5c13a)