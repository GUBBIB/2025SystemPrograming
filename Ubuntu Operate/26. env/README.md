## 명령어
- **env**:  현재 환경 변수 전체 목록을 출력하는 명령어 

```c
#include <stdio.h>

extern char **environ;

int main() {
    for (char **env = environ; *env != NULL; env++) {
        printf("%s\n", *env);
    }
    return 0;
}
```
## 설명

- 전역 변수 ``environ``은 모든 환경 변수들을 문자열 배열 형태로 담고 있다.
- ``for`` 반복문으로 ``NULL``이 나올 때까지 환경 변수 문자열을 하나씩 출력한다.
- ``env`` 명령어처럼 현재 실행 환경의 모든 환경 변수를 출력한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/090bd055-0696-479e-b144-e752b9fd00b0)