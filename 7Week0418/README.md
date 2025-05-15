
# 유닉스 시스템 프로그래밍 요약 (숙명여대 창병모)

---

## 6장 프로세스

### 6.1 프로세스

* 실행 중인 프로그램을 \*\*프로세스(process)\*\*라고 함
* 각 프로세스는 고유한 **PID**를 가짐
* 부모 프로세스에 의해 생성

#### 프로세스 종류

* **시스템 프로세스**: 부팅 시 생성되어 시스템 운영에 필요한 기능 수행 (예: 데몬)
* **사용자 프로세스**: 사용자의 명령/프로그램 실행을 위해 생성됨

#### 프로세스 상태 확인

```bash
$ ps
$ ps -f
$ ps -ef | more
```

* 출력 항목: UID, PID, PPID, C, STIME, TTY, TIME, CMD

#### 특정 프로세스 검색: pgrep

```bash
$ pgrep sshd
$ pgrep -l sshd
$ pgrep -ln sshd
```

옵션: `-l`, `-n`, `-x`, `-f`, `-a`

### 6.2 작업 제어

* **후면 처리**: `$ 명령어 &`
* **쉘 일시 중지**: `sleep 초`
* **강제 종료**: Ctrl+C
* **일시 정지**: Ctrl+Z
* **전면 전환**: `fg [%작업번호]`
* **후면 전환**: `bg [%작업번호]`

### 6.3 프로세스 제어

#### 종료: kill

```bash
$ kill PID
$ kill %작업번호
```

#### 대기: wait

```bash
$ wait [PID]
```

#### 우선순위 조정

```bash
$ nice -n 10 명령어
$ renice -n 5 -p PID
```

### 6.4 사용자 ID

* 프로세스는 UID, GID 보유
* `id`, `echo $UID $EUID`로 확인
* **유효 사용자 ID**: 파일 권한 판별 시 사용

---

## 7장 인터넷과 서버

### 7.1 네트워크 구성

* **LAN**, **라우터**, **게이트웨이**, **WAP** 등 기본 개념

### 7.2 인터넷

* **IP**: 주소지정, 패킷 분할/조립
* **TCP**: 신뢰성 있는 전송
* **호스트명/도메인명**: 사람이 이해하기 쉬운 이름
* `hostname`, `ip addr`, `nslookup` 명령 사용

### 7.3 서버 설치

#### 웹 서버 (Apache)

```bash
# apt install apache2 php mariadb-server
# systemctl start apache2
# systemctl enable apache2
# firewall-cmd --permanent --add-service=http
# firewall-cmd --reload
```

* 기본 루트: `/var/www/html`

#### FTP 서버 (vsFTPD)

```bash
# apt install vsftpd
# systemctl start vsftpd.service
# firewall-cmd --add-service=ftp
```

#### SSH

```bash
# apt install ssh
# systemctl start ssh
```

### 7.4 파일 전송

#### FTP, SFTP 명령

```bash
$ ftp/sftp 사용자@호스트
ftp> put/get 파일명
ftp> lcd, cd, pwd, quit 등
```

#### 윈도우에서 사용

* OpenSSH 클라이언트
* FileZilla

---

## 7장 파일 및 레코드 잠금

### 7.1 파일 잠금

* `flock(fd, LOCK_EX)`로 **파일 전체**에 배타 잠금 가능
* `LOCK_SH`, `LOCK_EX`, `LOCK_UN`, `LOCK_NB` 제공

### 7.2 레코드 잠금

* `fcntl(fd, cmd, &lock)` 사용
* `F_WRLCK`: 쓰기 잠금, `F_RDLCK`: 읽기 잠금

#### 구조체

```c
struct flock {
  short l_type;
  off_t l_start;
  short l_whence;
  off_t l_len;
  pid_t l_pid;
};
```

---

## 8장 파일 유틸리티

### 8.1 파일 찾기 (find)

```bash
$ find 디렉터리 -name '*.c' -print
$ find . -size +1024 -user chang -type f -exec rm {} \;
```

* 다양한 옵션: `-name`, `-type`, `-size`, `-perm`, `-atime`, `-mtime`, `-exec`

### 8.2 파일 필터링 (grep)

```bash
$ grep -n -i 'pattern' 파일명
$ ps -ef | grep chang
```

* 정규식 지원: `.`, `*`, `[]`, `[^]`, `^`, `$`

### 8.3 정렬 (sort)

```bash
$ sort [-r] [-k 필드번호] 파일명
$ sort -o 결과.txt 원본.txt
```

* 옵션: `-n`, `-r`, `-f`, `-b`, `-t`

---

이 문서는 리눅스 기반의 유닉스 시스템에서 **프로세스, 서버 설정, 파일 유틸리티, 잠금 메커니즘** 등에 대한 핵심 내용을 다룹니다.

<!--
- pdf -
chap06
chap07
chap08


백그라운드로 돌려라 = &
ㄴ ex) sleep 10 & 이러면 sleep이 10초동안 백그라운드로 돌아감
백그라운드롤 앞으로, 전면 작업으로 = fg 명령어



-->
<!--
dothome - 도메인 무료 호스팅, 돈 쌈
2학기에 뭐 이상한거 개설됨

-->