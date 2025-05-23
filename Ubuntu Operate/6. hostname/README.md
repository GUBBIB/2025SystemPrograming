## 명령어
- **hostname**: 호스트 이름 출력
```c
#include <stdio.h>
#include <unistd.h>     // gethostname
#include <limits.h>     // HOST_NAME_MAX

int main() {
    char hostname[HOST_NAME_MAX + 1];  // 널 문자 포함 공간 확보

    if (gethostname(hostname, sizeof(hostname)) == 0) {
        printf("%s\n", hostname);
    } else {
        perror("gethostname 오류");
        return 1;
    }

    return 0;
}
```
## 설명
- **HOST_NAME_MAX**: ``limits.h`` 라이브러리에 정의된 상수이며 1을 더하는 이유는 문자열의 끝에 있는 ``널 문자(\\0)`` 때문이다. **※크기는 리눅스에서는 64**
- **gethostname(char *name, size_t len)**: hostname을 반환하는 함수

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/cf991eaa-861a-49dd-a505-9b53ba464ee3)

**※ hostname이 ip주소가 뜨는이유는 AWS를 사용하면 hostname이 기본적으로 ip주소로 만들어지기 때문이다.**