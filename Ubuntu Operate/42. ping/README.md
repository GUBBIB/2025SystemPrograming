## 명령어
- **ping**: 무한히 **ICMP ping** 패킷을 보내는 명령어

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s [호스트명 또는 IP 주소]\n", argv[0]);
        return 1;
    }

    char command[256];
    // -c 4 제거 → 무한 ping
    snprintf(command, sizeof(command), "ping %s", argv[1]);

    int result = system(command);

    if (result == -1) {
        perror("ping 실행 실패");
        return 1;
    }

    return 0;
}
```
## 설명

- argv[1]에서 호스트명 또는 IP 주소를 입력받는다.
- 문자열 결합 함수인 snprintf()로 ping [주소] 명령어 문자열을 구성한다.
- system() 함수를 사용하여 ping 명령어를 실행한다.
- -c 옵션을 사용하지 않았기 때문에, ICMP 패킷을 무한 반복 전송하며, Ctrl+C로 수동 종료해야 한다.
- 외부 명령어를 호출하므로, 로컬에 ping 명령어가 설치되어 있어야 한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/473e05e0-1cb8-4c23-a0a5-3c2c0298ccbd)