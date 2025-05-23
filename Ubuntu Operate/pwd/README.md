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