## 명령어
- **ping -c**: ``ping -c [횟수] [호스트명]``은 지정한 횟수만큼 **ICMP ping** 패킷을 보내는 명령어

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/ip_icmp.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>

unsigned short checksum(void *b, int len) {
    unsigned short *buf = b;
    unsigned int sum = 0;
    unsigned short result;

    for (sum = 0; len > 1; len -= 2)
        sum += *buf++;
    if (len == 1)
        sum += *(unsigned char*)buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "사용법: %s [횟수] [호스트명]\n", argv[0]);
        return 1;
    }

    int count = atoi(argv[1]);
    char *host = argv[2];

    struct hostent *h;
    struct sockaddr_in addr;
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

    if (sockfd < 0) {
        perror("소켓 생성 실패 (루트 권한 필요)");
        return 1;
    }

    h = gethostbyname(host);
    if (!h) {
        fprintf(stderr, "호스트 이름 해석 실패\n");
        return 1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    memcpy(&addr.sin_addr, h->h_addr, h->h_length);

    for (int i = 0; i < count; i++) {
        char packet[64];
        struct icmp *icmp_hdr = (struct icmp *) packet;
        memset(packet, 0, sizeof(packet));
        icmp_hdr->icmp_type = ICMP_ECHO;
        icmp_hdr->icmp_code = 0;
        icmp_hdr->icmp_id = getpid();
        icmp_hdr->icmp_seq = i + 1;
        icmp_hdr->icmp_cksum = checksum(icmp_hdr, sizeof(packet));

        if (sendto(sockfd, packet, sizeof(packet), 0, (struct sockaddr*)&addr, sizeof(addr)) <= 0) {
            perror("패킷 전송 실패");
        } else {
            printf("ping #%d → %s 전송 완료\n", i + 1, inet_ntoa(addr.sin_addr));
        }

        sleep(1);
    }

    close(sockfd);
    return 0;
}
```
## 설명

- socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)로 ICMP용 소켓 생성
- gethostbyname()으로 도메인 이름을 IP로 변환
- ICMP_ECHO 패킷을 생성하고, 지정된 횟수만큼 sendto()로 전송
- 실제 응답 받는 부분(recvfrom, 응답 시간 측정)은 생략됨 (간단 버전)

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/94e09ac3-e659-46c1-b9a5-2e33ffafe4b0)