```c
#include <stdio.h>

int main(int argc, char *argv[]) {
    // 인자가 1개 이상 있으면 (argv[0]은 실행 파일 이름)
    for (int i = 1; i < argc; i++) {
        printf("%s", argv[i]);
        if (i < argc - 1) {
            printf(" "); // 단어 사이 공백
        }
    }
    printf("\n"); // 마지막에 줄바꿈
    return 0;
}
```
## 설명


## 컴파일 및 실행화면
![Image](https://github.com/user-attachments/assets/615196a4-a22e-459f-ba3b-cc73a21c90ab)