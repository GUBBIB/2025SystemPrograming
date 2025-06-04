## 명령어
- **curl**: ``ping -c [횟수] [호스트명]``은 지정한 횟수만큼 **ICMP ping** 패킷을 보내는 명령어

```c
#include <stdio.h>
#include <curl/curl.h>

size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata) {
    size_t total_size = size * nmemb;
    fwrite(ptr, size, nmemb, stdout);  // 받은 데이터를 stdout에 출력
    return total_size;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s [URL]\n", argv[0]);
        return 1;
    }

    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "libcurl 초기화 실패\n");
        return 1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, argv[1]);               // 요청할 URL
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback); // 응답 처리 콜백
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);         // 리디렉션 따라가기

    CURLcode res = curl_easy_perform(curl);  // 요청 실행
    if (res != CURLE_OK) {
        fprintf(stderr, "요청 실패: %s\n", curl_easy_strerror(res));
    }

    curl_easy_cleanup(curl);  // 리소스 해제
    return 0;
}
```
## 설명

- libcurl은 HTTP 요청을 보낼 수 있는 C용 라이브러리
- curl_easy_setopt()으로 요청 설정
- curl_easy_perform()으로 실행
- write_callback()에서 받은 응답을 터미널에 출력

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/eacd8717-6c72-4c9f-a6e1-9cde15814a13)