## 명령어
- **df -T**: 파일 시스템의 사용량과 파일 시스템 타입을 함께 출력

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/statvfs.h>
#include <mntent.h>
#include <string.h>

int main() {
    FILE *mounts = setmntent("/proc/mounts", "r");
    if (!mounts) {
        perror("mount 정보 열기 실패");
        return 1;
    }

    struct mntent *ent;
    struct statvfs stat;

    printf("%-25s %-10s %10s %10s %10s %s\n", "Filesystem", "Type", "Size", "Used", "Available", "Mounted on");

    while ((ent = getmntent(mounts)) != NULL) {
        if (statvfs(ent->mnt_dir, &stat) != 0) {
            continue;
        }

        unsigned long total = stat.f_blocks * stat.f_frsize;
        unsigned long free  = stat.f_bfree  * stat.f_frsize;
        unsigned long avail = stat.f_bavail * stat.f_frsize;
        unsigned long used  = total - free;

        printf("%-25s %-10s %10lu %10lu %10lu %s\n",
               ent->mnt_fsname,
               ent->mnt_type,
               total / 1024,
               used / 1024,
               avail / 1024,
               ent->mnt_dir);
    }

    endmntent(mounts);
    return 0;
}
```
## 설명
- /proc/mounts를 열고 getmntent()로 마운트된 파일 시스템 정보를 순회한다.
- mntent 구조체에서 mnt_fsname, mnt_type, mnt_dir 정보를 얻는다.
- statvfs()로 사용량 정보를 가져온 뒤, 전체 / 사용 / 가용 용량을 계산한다.
- df -T 명령어처럼 각 파일 시스템의 이름, 타입, 총 용량, 사용 중, 사용 가능, 마운트 위치를 출력한다.
- 출력 단위는 KB(1024로 나눔).

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/2fe8322b-5058-41b8-b6e5-e7000ea3bffc)