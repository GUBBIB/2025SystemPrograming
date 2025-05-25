## 명령어
- **rm -r**: 디렉토리 및 내부 파일/디렉토리 재귀적 삭제

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

int remove_recursive(const char *path) {
    struct stat st;

    if (lstat(path, &st) == -1) {
        perror("lstat 실패");
        return -1;
    }

    // 파일 또는 심볼릭 링크면 unlink()
    if (!S_ISDIR(st.st_mode)) {
        return unlink(path);
    }

    // 디렉토리인 경우
    DIR *dir = opendir(path);
    if (!dir) {
        perror("디렉토리 열기 실패");
        return -1;
    }

    struct dirent *entry;
    char fullpath[1024];

    while ((entry = readdir(dir)) != NULL) {
        // "." ".." 무시
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        // 재귀적으로 삭제
        if (remove_recursive(fullpath) == -1) {
            closedir(dir);
            return -1;
        }
    }

    closedir(dir);

    // 디렉토리 자체 삭제
    return rmdir(path);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s [디렉토리 또는 파일]\n", argv[0]);
        return 1;
    }

    if (remove_recursive(argv[1]) == -1) {
        perror("삭제 실패");
        return 1;
    }

    printf("'%s' 삭제 완료\n", argv[1]);
    return 0;
}
```
## 설명

- ``sys/stat.h`` 헤더에 정의된 **`lstat()`** 함수를 사용하여, 입력된 경로가 **파일인지 디렉토리인지** 판별한다.
- 경로가 **파일**일 경우, ``unlink()`` 함수를 이용해 삭제한다.
- 경로가 **디렉토리**일 경우, ``dirent.h``의 ``readdir()``을 사용해 내부 항목을 하나씩 확인하고,
  각 항목에 대해 **재귀적으로 `remove_recursive()`**를 호출한다.
- 내부 항목이 파일이면 ``unlink()``로 삭제하고, 디렉토리면 다시 ``remove_recursive()``를 통해 같은 과정을 반복한다.
- 디렉토리 내부가 모두 비워진 뒤에는 ``rmdir()`` 함수를 사용하여 **디렉토리 자체를 삭제**한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/3bd44a32-10cc-48c4-98e9-995acf8616bc)