## 명령어
- **rm -f**: 파일 조용한 삭제 명령어

```c
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        // 사용법 출력 (rm -f 형식이므로 인자는 1개만 받음)
        return 0;  // 조용히 종료
    }

    const char *filename = argv[1];

    // 삭제 시도 (실패해도 아무 메시지 없이 무시)
    unlink(filename);

    // 에러 메시지 없음 → rm -f는 조용히 실패를 무시함
    return 0;
}

```
## 설명
- ``unistd.h``에 정의된 **unlink()** 함수로 파일을 삭제한다.
- **에러**가 나도 **무시**하기때문에 별도의 ``if문``은 없다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/d52b9881-f300-4195-a440-1f3b4cbe1a23)