## 명령어
- **date**: 현재 시간 출력
```c
#include <stdio.h>
#include <time.h>

int main() {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    const char *weekdays[] = { "일", "월", "화", "수", "목", "금", "토" };

    if (t != NULL) {
        printf("%04d년 %02d월 %02d일 (%s) %02d:%02d:%02d\n",
               t->tm_year + 1900,
               t->tm_mon + 1,
               t->tm_mday,
               weekdays[t->tm_wday],  // 여기만 수정
               t->tm_hour,
               t->tm_min,
               t->tm_sec);
    } else {
        perror("localtime 오류");
        return 1;
    }

    return 0;
}
```
## 설명
- **time()**: 현재 시각을 **1970년 1월 1일 기준**으로 **초 단위**로 반환
- **localtime()**: ``time_t`` 형식의 시간을 ``struct tm`` **구조체**로 변환하여 **년, 월, 일, 시, 분, 초** 등의 정보로 나눠줍니다.
- **tm 구조체**: ``localtime``을 통해서 얻은 구조체에서 시간, 날짜, 요일 등을 출력

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/a8fbd1b7-e720-493a-85ef-31f70db7fc8a)