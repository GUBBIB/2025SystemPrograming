# 9주차 수업내용

# 유닉스 시스템 프로그래밍 요약 (종합)

---

## 1. 시스템 프로그래밍 개요

* \*\*커널(Kernel)\*\*은 하드웨어 자원을 관리하며 주요 서비스를 제공:

  * 파일 관리
  * 프로세스 관리
  * 메모리 관리
  * 통신 관리
  * 주변장치 관리

* **시스템 호출(System Call)**: 커널에 서비스를 요청하는 프로그래밍 인터페이스

---

## 2. 주요 시스템 호출 요약

| 자원 구분 | 시스템 호출                                                         |
| ----- | -------------------------------------------------------------- |
| 파일    | `open()`, `close()`, `read()`, `write()`, `dup()`, `lseek()` 등 |
| 프로세스  | `fork()`, `exec()`, `exit()`, `wait()`, `getpid()` 등           |
| 메모리   | `malloc()`, `calloc()`, `free()` 등 *(라이브러리 함수)*                |
| 시그널   | `signal()`, `alarm()`, `kill()`, `sleep()` 등                   |
| IPC   | `pipe()`, `socket()` 등                                         |

---

## 3. 파일 관련 시스템 호출

### 3.1 파일 열기: `open()`

```c
int open(const char *path, int oflag, [mode_t mode]);
```

* 성공 시 파일 디스크립터 리턴, 실패 시 -1
* `oflag` 예시:

  * `O_RDONLY`, `O_WRONLY`, `O_RDWR`, `O_APPEND`, `O_CREAT`, `O_TRUNC`, `O_EXCL`, `O_NONBLOCK`, `O_SYNC`

### 3.2 파일 생성: `creat()`

```c
int creat(const char *path, mode_t mode);
```

* 쓰기 전용으로 파일 생성, 내부적으로는 `open(..., O_CREAT | O_TRUNC)`와 같음

### 3.3 파일 닫기: `close()`

```c
int close(int fd);
```

* 성공 시 0, 실패 시 -1

---

## 4. 데이터 입출력

### 4.1 읽기: `read()`

```c
ssize_t read(int fd, void *buf, size_t nbytes);
```

* 성공 시 읽은 바이트 수, 파일 끝 시 0, 실패 시 -1

### 4.2 쓰기: `write()`

```c
ssize_t write(int fd, void *buf, size_t nbytes);
```

* 성공 시 실제 기록된 바이트 수 반환

### 예시: 파일 복사

```c
while ((n = read(fd1, buf, BUFSIZ)) > 0)
    write(fd2, buf, n);
```

---

## 5. 파일 디스크립터 복제: `dup()`, `dup2()`

```c
int dup(int oldfd);
int dup2(int oldfd, int newfd);
```

* 동일한 파일을 가리키는 새 파일 디스크립터 생성

---

## 6. 파일 위치 포인터 제어: `lseek()`

```c
off_t lseek(int fd, off_t offset, int whence);
```

* `whence`: `SEEK_SET`, `SEEK_CUR`, `SEEK_END`

### 예시

* `lseek(fd, 0, SEEK_SET)` : 파일 시작
* `lseek(fd, sizeof(record), SEEK_CUR)` : 다음 레코드

---

## 7. 구조체와 레코드 기반 파일 처리

### student.h

```c
#define MAX 24
#define START_ID 1401001
struct student {
  char name[MAX];
  int id;
  int score;
};
```

### 데이터베이스 파일 생성: dbcreate.c

* 학생 정보를 입력받아 파일에 `lseek + write`로 저장

### 데이터 조회: dbquery.c

* 학번 입력 → `lseek()` 후 `read()` → 출력

### 레코드 수정: dbupdate.c

* 학번 입력 → `lseek()` 후 `read()` → 수정 → `lseek()` → `write()`

---

## 8. 핵심 정리

* **파일 디스크립터**는 열린 파일을 식별하는 숫자
* `open()`으로 파일 열고, `read()`/`write()`로 입출력, `close()`로 닫음
* `lseek()`으로 위치 이동, `dup()`으로 디스크립터 복제
* 구조체 기반 레코드 파일 처리 가능 (`lseek()`으로 위치 조절)
* 시스템 호출은 커널의 기능을 활용하는 핵심 수단

---

## 참고 자료

* 『리눅스 프로그래밍』 창병모, 생능출판
* [WSL2 가이드 - 44bits.io](https://www.44bits.io/ko/post/wsl2-install-and-basic-usage)

<!--
시스템프로그래밍05.pdf

args, argv 뭔지
파일 열기 예에서 0600, 0666 이 뭐냐면 유저 임
xxd 명령어, hexdump 명령어
매직넘버
-->