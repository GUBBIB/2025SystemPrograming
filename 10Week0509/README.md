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

| 자원 구분 | 시스템 호출                                                                   |
| ----- | ------------------------------------------------------------------------ |
| 파일    | `open()`, `close()`, `read()`, `write()`, `dup()`, `lseek()`, `stat()` 등 |
| 프로세스  | `fork()`, `exec()`, `exit()`, `wait()`, `getpid()` 등                     |
| 메모리   | `malloc()`, `calloc()`, `free()` 등 *(라이브러리 함수)*                          |
| 시그널   | `signal()`, `alarm()`, `kill()`, `sleep()` 등                             |
| IPC   | `pipe()`, `socket()` 등                                                   |

---

## 3. 파일 관련 시스템 호출

### 3.1 파일 열기: `open()`

```c
int open(const char *path, int oflag, [mode_t mode]);
```

* `oflag` 예시: `O_RDONLY`, `O_WRONLY`, `O_RDWR`, `O_APPEND`, `O_CREAT`, `O_TRUNC`, `O_EXCL`, `O_NONBLOCK`, `O_SYNC`

### 3.2 파일 생성: `creat()`

```c
int creat(const char *path, mode_t mode);
```

### 3.3 파일 닫기: `close()`

```c
int close(int fd);
```

---

## 4. 데이터 입출력

### 4.1 읽기: `read()`

```c
ssize_t read(int fd, void *buf, size_t nbytes);
```

### 4.2 쓰기: `write()`

```c
ssize_t write(int fd, void *buf, size_t nbytes);
```

---

## 5. 파일 디스크립터 복제

```c
int dup(int oldfd);
int dup2(int oldfd, int newfd);
```

---

## 6. 파일 위치 포인터: `lseek()`

```c
off_t lseek(int fd, off_t offset, int whence);
```

* `SEEK_SET`, `SEEK_CUR`, `SEEK_END`

---

## 7. 레코드 기반 DB 구현 예제

### student.h 구조체 정의

```c
#define MAX 24
#define START_ID 1401001
struct student {
  char name[MAX];
  int id;
  int score;
};
```

* `dbcreate.c`: 학생 정보 입력 및 저장
* `dbquery.c`: 학번으로 검색
* `dbupdate.c`: 레코드 수정

---

## 8. 파일 시스템 구조

* 부트 블록, 슈퍼 블록, i-리스트, 데이터 블록으로 구성
* i-노드: 각 파일마다 존재, 메타데이터 포함 (타입, 소유자, 권한, 시간, 블록 주소 등)
* 블록 포인터: 직접 10개, 간접 1개, 이중간접 1개

---

## 9. 커널 내부 자료구조

* 파일 디스크립터 배열 (Fd Array): 프로세스 당 유지
* 열린 파일 테이블 (Open File Table): 상태 플래그, 현재 위치, i-node 포인터
* 동적 i-node 테이블: 실제 i-node 참조

---

## 10. 파일 상태 정보: `stat()` 계열

```c
int stat(const char *filename, struct stat *buf);
int fstat(int fd, struct stat *buf);
int lstat(const char *filename, struct stat *buf);
```

* 구조체: `st_mode`, `st_size`, `st_uid`, `st_gid`, `st_mtime`, `st_blocks` 등 포함

파일 타입 검사 매크로:

* `S_ISREG()`, `S_ISDIR()`, `S_ISCHR()`, `S_ISBLK()`, `S_ISFIFO()`, `S_ISSOCK()`, `S_ISLNK()`

---

## 11. 파일/디렉터리 권한 및 정보

* 권한 변경: `chmod()`, `fchmod()`
* 소유자 변경: `chown()`, `fchown()`, `lchown()`
* 시간 정보 변경: `utime()`

---

## 12. 디렉터리 다루기

* `opendir()`, `readdir()`, `closedir()`
* `mkdir()`, `rmdir()`로 디렉터리 생성 및 삭제
* `struct dirent`: `d_name`, `d_ino` 포함

---

## 13. 링크

### 하드 링크 vs 심볼릭 링크

* 하드 링크: 동일한 i-node를 참조 (같은 파일 시스템에서만)
* 심볼릭 링크: 경로 문자열을 참조, 다른 파일 시스템도 가능

### 관련 함수

```c
int link(const char *existing, const char *new);
int unlink(const char *path);
int symlink(const char *target, const char *linkpath);
int readlink(const char *path, char *buf, size_t bufsize);
```

---

## 핵심 정리

* 유닉스 파일 시스템은 i-node 기반으로 설계되어 있음
* 커널은 Fd 배열, OFT, i-node table로 파일 입출력을 관리
* 파일은 타입, 권한, 시간 정보 등을 포함하며 `stat()`으로 확인 가능
* 디렉터리도 파일이며 `readdir()` 등을 통해 접근 가능
* 하드링크와 소프트링크로 파일 이름을 다양하게 연결 가능

---

## 참고 자료

* 『리눅스 프로그래밍』 창병모, 생능출판
* [WSL2 가이드 - 44bits.io](https://www.44bits.io/ko/post/wsl2-install-and-basic-usage)


<!--
시스템프로그래밍06.pdf
시스템프로그래밍07.pdf

시스템프로그래밍06.pdf 안에
db~~.c 작성하기 기말 시험임
-->