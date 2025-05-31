## 명령어
- **uptime**: 얼마나 오래 켜져 있었는지(시작 이후 경과 시간)를 출력하는 명령어

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp = fopen("/proc/uptime", "r");
    if (fp == NULL) {
        perror("/proc/uptime 열기 실패");
        return 1;
    }

    double uptime_seconds;
    if (fscanf(fp, "%lf", &uptime_seconds) != 1) {
        perror("uptime 읽기 실패");
        fclose(fp);
        return 1;
    }

    fclose(fp);

    int days = (int)(uptime_seconds / 86400);
    int hours = ((int)uptime_seconds % 86400) / 3600;
    int minutes = ((int)uptime_seconds % 3600) / 60;

    printf("시스템 가동 시간: ");
    if (days > 0) {
        printf("%d일 ", days);
    }
    if (hours > 0 || days > 0) {
        printf("%d시간 ", hours);
    }
    printf("%d분\n", minutes);

    return 0;
}

```
## 설명

- ``/proc/uptime`` 파일은 시스템이 부팅된 이후 지난 초(second)를 담고 있다.
- 첫 번째 값(예: `10231.48`)만 ``fscanf()``로 읽어온다.
- 초 단위를 읽은 후 일(day), 시간(hour), 분(minute) 단위로 변환하여 출력한다.
- 텍스트 기반의 간단한 ``uptime`` 기능을 구현하였다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/2176474d-0f70-4ace-a050-6d0214e6327e)