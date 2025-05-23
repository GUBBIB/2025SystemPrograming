## 명령어
- **ls -a**: 현재 디렉토리의 파일/디렉토리, 숨김처리 파일/디렉토리 이름 출력
```c
#include <stdio.h>
#include <dirent.h>

int main() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");  // 현재 디렉토리 열기
    if (dir == NULL) {
        perror("디렉토리 열기 실패");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        // 현재 디렉토리에서 항목 하나씩 출력
        if (entry->d_name[0] != '.') {
           printf("%s\n", entry->d_name);
    }   }

    closedir(dir);
    return 0;
}
```
## 설명
- **opendir()**: ``dirent.h`` 라이브러리를 통해서 DIR 타입의 포인터 변수를 만들고 ``opendir(".")`` 을 통해서 현재 디렉토리의 정보를 dir 변수에 넣는다.
- **entry = readdir(dir) != NULL**: 현재 디렉토리의 항목을 하나씩 읽고 **NULL**이 아니면 출력, **NULL**이면 while문을 나가고 ``closedir()``을 통해서 디렉토리를 닫는다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/4204470f-d3bd-4cb9-9ad8-b0e96287949a)