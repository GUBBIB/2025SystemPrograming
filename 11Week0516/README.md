# 11주차 수업내용

# Unix 시스템 프로그래밍 정리 (chap6 \~ chap9)

---

#### 📌 리눅스 파일 시스템 구조

리눅스의 ext4 파일 시스템은 다음과 같은 네 가지 주요 영역으로 구성되어 있다:

1. **부트 블록 (Boot Block)**

   * 파일 시스템의 첫 번째 섹터에 위치
   * 시스템을 부팅하는 데 필요한 **부트스트랩 코드**가 저장됨

2. **슈퍼 블록 (Super Block)**

   * 파일 시스템의 전체적인 정보를 저장
   * 포함 정보:

     * 파일 시스템 전체 블록 수
     * 사용 가능한 inode 수
     * 사용 가능한 블록 수
     * 블록 크기 등

3. **i-리스트 (i-node List)**

   * 파일을 나타내는 **i-node** 구조체들의 배열
   * 하나의 블록에 약 40개의 i-node가 저장 가능

4. **데이터 블록 (Data Block)**

   * 실제 파일의 내용을 저장하는 영역

#### 📌 i-node 구조

각 파일은 고유한 i-node를 가지며, 파일에 대한 모든 메타데이터를 저장한다.

* 저장 정보:

  * 파일 타입 (일반 파일, 디렉터리, 장치 파일 등)
  * 파일 크기
  * 접근 권한
  * 소유자 및 그룹 ID
  * 최근 접근/수정 시간
  * 데이터 블록에 대한 포인터 (주소)

##### 📦 i-node 내부 블록 포인터 구성

* **직접 포인터 (Direct Pointers)**: 12개
* **간접 포인터 (Single Indirect)**: 1개 → 또 다른 블록 포인터 배열을 가리킴
* **이중 간접 포인터 (Double Indirect)**: 1개 → 간접 블록 배열을 가리키는 블록 포인터
* **삼중 간접 포인터 (Triple Indirect)**: 1개 → 이중 간접 포인터 배열을 가리킴

### 🔸 6.2 파일 입출력 구현

#### 📌 주요 커널 내부 자료구조

리눅스는 파일 입출력을 위한 내부 구조를 다음과 같이 관리함:

1. **파일 디스크립터 배열 (Fd Array)**

   * 프로세스마다 하나씩 존재
   * 열린 파일 테이블 항목을 가리키는 포인터 배열

2. **열린 파일 테이블 (Open File Table)**

   * 열린 모든 파일의 리스트
   * 각 엔트리는:

     * 파일 상태 플래그 (읽기, 쓰기, append 등)
     * 현재 오프셋
     * 연결된 i-node 포인터

3. **동적 i-node 테이블 (Active i-node Table)**

   * 열린 파일의 i-node 정보를 메모리에 유지

#### 📌 파일 열기 예시

```c
int fd = open("test.txt", O_RDONLY); // 읽기 전용으로 열기
```

#### 📌 파일 디스크립터 복제

```c
int newfd = dup(fd);        // 새로운 fd 생성
int newfd = dup2(fd, 4);    // 4번 fd에 덮어쓰기
```

### 🔸 6.3 파일 상태 정보

#### 📌 파일 정보 구조체: `struct stat`

```c
struct stat {
  mode_t st_mode;    // 파일 타입 및 접근 권한
  ino_t st_ino;      // i-node 번호
  dev_t st_dev;      // 장치 번호
  nlink_t st_nlink;  // 하드 링크 수
  uid_t st_uid;      // 소유자 ID
  gid_t st_gid;      // 그룹 ID
  off_t st_size;     // 파일 크기
  time_t st_atime;   // 마지막 접근 시간
  time_t st_mtime;   // 마지막 수정 시간
  time_t st_ctime;   // 마지막 상태 변경 시간
};
```

#### 📌 관련 함수들

```c
int stat(const char *path, struct stat *buf);
int fstat(int fd, struct stat *buf);
int lstat(const char *path, struct stat *buf);
```

#### 📌 파일 타입 판별 매크로

* `S_ISREG(mode)`: 일반 파일
* `S_ISDIR(mode)`: 디렉터리
* `S_ISCHR(mode)`: 문자 장치 파일
* `S_ISBLK(mode)`: 블록 장치 파일
* `S_ISLNK(mode)`: 심볼릭 링크

#### 📌 파일 권한 변경

```c
int chmod(const char *path, mode_t mode);
int fchmod(int fd, mode_t mode);
```

#### 📌 시간 변경

* `utime(path, NULL);` → 현재 시간으로 수정됨
* 구조체: `struct utimbuf { time_t actime; time_t modtime; };`

#### 📌 소유자 변경

* `chown(path, uid, gid)` / `fchown(fd, uid, gid)`
* superuser만 사용 가능

### 🔸 6.4 디렉터리 처리

#### 📌 디렉터리 탐색 함수

```c
DIR *opendir(const char *path);
struct dirent *readdir(DIR *dirp);
int closedir(DIR *dirp);
```

#### 📌 dirent 구조체

```c
struct dirent {
  ino_t d_ino;              // inode 번호
  char d_name[NAME_MAX+1]; // 파일 이름
};
```

#### 📌 디렉터리 파일 예시

```c
DIR *dp = opendir(".");
struct dirent *entry;
while ((entry = readdir(dp)) != NULL) {
  printf("%s\n", entry->d_name);
}
closedir(dp);
```

---

## 🔒 7장. 파일 및 레코드 잠금

### 🔸 7.1 파일 잠금 (flock)

#### 📌 개요

* 파일 또는 특정 영역을 여러 프로세스가 동시에 접근할 경우 데이터 손상이 발생할 수 있음
* `flock()` 시스템 호출은 **파일 전체에 대한 잠금**을 제공한다
* 주로 단순한 접근 제한이 필요한 경우 사용됨

#### 📌 잠금 종류

| 잠금 상태    | 공유 잠금 요청 | 배타 잠금 요청 |
| -------- | -------- | -------- |
| 없음       | 승인       | 승인       |
| 공유 잠금 존재 | 승인       | 거절       |
| 배타 잠금 존재 | 거절       | 거절       |

#### 📌 flock 함수 사용법

```c
#include <sys/file.h>
int flock(int fd, int operation);
```

* `operation` 값:

  * `LOCK_SH`: 공유 잠금 (여러 개 허용)
  * `LOCK_EX`: 배타 잠금 (하나만 허용)
  * `LOCK_UN`: 잠금 해제
  * `LOCK_NB`: 논블로킹 옵션 (잠겨있으면 즉시 실패)

#### 📌 예제 코드

```c
int fd = open("file.txt", O_WRONLY);
if (flock(fd, LOCK_EX) != 0) {
  perror("flock error");
  exit(1);
}

// 파일 작업 수행

flock(fd, LOCK_UN); // 잠금 해제
close(fd);
```

### 🔸 7.2 레코드 잠금 (fcntl)

#### 📌 개요

* 파일의 특정 범위(레코드)에 대해 잠금을 수행
* 동시 데이터 수정 시 정밀한 제어 가능

#### 📌 잠금 종류

| 현재 상태 | 읽기 잠금 요청 | 쓰기 잠금 요청 |
| ----- | -------- | -------- |
| 없음    | 승인       | 승인       |
| 읽기 잠금 | 승인       | 거절       |
| 쓰기 잠금 | 거절       | 거절       |

#### 📌 fcntl 함수 및 flock 구조체

```c
#include <fcntl.h>
int fcntl(int fd, int cmd, struct flock *lock);
```

```c
struct flock {
  short l_type;     // F_RDLCK, F_WRLCK, F_UNLCK
  short l_whence;   // SEEK_SET, SEEK_CUR, SEEK_END
  off_t l_start;    // 잠금 시작 오프셋
  off_t l_len;      // 잠금 길이 (0이면 EOF까지)
  pid_t l_pid;      // 프로세스 ID
};
```

* `F_SETLK`: 잠금 설정 (논블로킹)
* `F_SETLKW`: 잠금 설정 (차단)
* `F_GETLK`: 잠금 확인

#### 📌 레코드 잠금 예시

```c
struct flock lock;
lock.l_type = F_WRLCK;
lock.l_whence = SEEK_SET;
lock.l_start = 0;
lock.l_len = sizeof(struct record);
fcntl(fd, F_SETLKW, &lock); // 쓰기 잠금

// 작업 수행 후 해제
lock.l_type = F_UNLCK;
fcntl(fd, F_SETLK, &lock);
```

### 🔸 7.3 간단한 잠금 함수 (lockf)

#### 📌 개요

* `fcntl()`을 간단히 래핑한 인터페이스
* 현재 파일 위치 기준으로 특정 길이만큼 잠금 수행

#### 📌 lockf 함수

```c
#include <unistd.h>
int lockf(int fd, int cmd, off_t len);
```

* `cmd`:

  * `F_LOCK`: 잠금 설정 (차단)
  * `F_TLOCK`: 잠금 설정 (실패 시 -1)
  * `F_ULOCK`: 잠금 해제
  * `F_TEST`: 잠금 여부 확인

#### 📌 예제

```c
lseek(fd, pos, SEEK_SET);
lockf(fd, F_LOCK, sizeof(record));
// 작업
lockf(fd, F_ULOCK, sizeof(record));
```

### 🔸 7.4 권고 잠금 vs 강제 잠금

#### 📌 권고 잠금 (Advisory Locking)

* 리눅스, BSD 등 대부분 시스템에서 사용
* 잠금을 하지 않아도 시스템은 접근 허용 → 프로그래머 간 협약 필요

#### 📌 강제 잠금 (Mandatory Locking)

* 잠금이 설정된 파일은 커널이 접근을 막음 (드물게 사용)
* Linux는 `chmod +l` 설정으로 일부 구현 가능하나, 비표준적

---

# Unix 시스템 프로그래밍 정리 (chap6 \~ chap9)

---

## 👤 8장. 프로세스

### 🔸 8.1 쉘과 프로세스

#### 📌 쉘(Shell) 개요

* 사용자와 운영체제 사이의 명령 인터페이스
* 명령어 해석기 역할 (command processor)
* 사용자가 입력한 명령어를 받아 실행

#### 📌 복합 명령어

* 여러 명령을 한 줄에서 실행할 수 있음

```bash
$ 명령어1; 명령어2; 명령어3
$ (명령어1; 명령어2; 명령어3) > file.txt
```

#### 📌 전면 처리 / 후면 처리

* **전면 처리(foreground)**: 명령 실행 완료까지 기다림
* **후면 처리(background)**: `&` 기호 사용해 동시에 실행

```bash
$ find . -name "*.c" &
$ jobs            # 현재 background 작업 보기
$ fg %1           # 작업번호로 foreground 전환
```

### 🔸 8.2 프로그램 실행

#### 📌 exec 계열 함수

* 현재 프로세스 메모리를 완전히 대체하여 새 프로그램 실행

```c
#include <unistd.h>
int execl(const char *path, const char *arg, ..., NULL);
int execv(const char *path, char *const argv[]);
int execlp(const char *file, const char *arg, ..., NULL);
int execvp(const char *file, char *const argv[]);
```

#### 📌 main 함수 인수 전달

```c
int main(int argc, char *argv[]);
```

* `argc`: 인수 개수
* `argv`: 인수 문자열 배열

#### 📌 명령줄 인수 출력 예시

```c
for (int i = 0; i < argc; i++)
    printf("argv[%d] = %s\n", i, argv[i]);
```

#### 📌 환경 변수

* 모든 환경 변수 출력:

```c
extern char **environ;
for (char **ptr = environ; *ptr != NULL; ptr++)
    printf("%s\n", *ptr);
```

* 개별 접근: `getenv("HOME")`

* 설정:

```c
putenv("NAME=value");
setenv("NAME", "value", 1);
unsetenv("NAME");
```

### 🔸 8.3 프로그램 종료

#### 📌 종료 함수

```c
#include <stdlib.h>
void exit(int status);     // 정리 후 종료
void _exit(int status);    // 즉시 종료
```

* `exit()`은 stdio 버퍼 flush 등 수행
* `atexit()`으로 종료 핸들러 등록 가능

#### 📌 atexit() 예시

```c
void goodbye() { printf("종료 중\n"); }
atexit(goodbye);
```

### 🔸 8.4 프로세스 ID & 사용자 ID

#### 📌 프로세스 ID 관련 함수

```c
pid_t getpid(void);    // 현재 PID
pid_t getppid(void);   // 부모 PID
```

#### 📌 사용자 및 그룹 ID

```c
uid_t getuid(void);    // 실제 사용자 ID
uid_t geteuid(void);   // 유효 사용자 ID
gid_t getgid(void);    // 실제 그룹 ID
gid_t getegid(void);   // 유효 그룹 ID
```

#### 📌 ID 변경 함수 (superuser 권한 필요)

```c
int setuid(uid_t uid);
int seteuid(uid_t uid);
int setgid(gid_t gid);
int setegid(gid_t gid);
```

#### 📌 set-user-ID 실행파일

* 실행 시 해당 실행파일의 **소유자 권한**으로 실행됨
* 예: `/bin/passwd` 는 일반 사용자가 비밀번호 변경 가능하도록 함
* 파일 권한 표시: `-rws--x--x`

---

# Unix 시스템 프로그래밍 정리 (chap6 \~ chap9)

---

## 🔄 9장. 프로세스 제어

### 🔸 9.1 프로세스 생성: `fork()`

#### 📌 개요

* 부모 프로세스가 **자식 프로세스**를 생성
* `fork()` 시스템 호출 사용
* 자식은 부모의 주소공간을 **복제**하지만 독립적으로 동작

#### 📌 함수 원형

```c
#include <unistd.h>
pid_t fork(void);
```

* 부모에게는 자식의 PID 리턴
* 자식에게는 0 리턴

#### 📌 기본 예제

```c
int pid = fork();
if (pid == 0)
    printf("자식 프로세스\n");
else
    printf("부모 프로세스\n");
```

#### 📌 여러 자식 생성

```c
int pid1 = fork();
if (pid1 == 0) { /* 자식1 */ }
int pid2 = fork();
if (pid2 == 0) { /* 자식2 */ }
```

### 🔸 9.2 자식 종료 기다리기: `wait()` / `waitpid()`

#### 📌 함수 원형

```c
#include <sys/wait.h>
pid_t wait(int *status);
pid_t waitpid(pid_t pid, int *status, int options);
```

* 자식 프로세스가 종료될 때까지 부모가 대기
* 종료된 자식의 PID 반환, 종료 코드는 `status >> 8`로 추출

#### 📌 예제

```c
int pid = fork();
if (pid == 0) exit(3);
int status;
int child = wait(&status);
printf("자식 종료 코드: %d\n", status >> 8);
```

### 🔸 9.3 프로그램 실행: `exec()` 계열

#### 📌 exec 종류

| 함수     | 설명              |
| ------ | --------------- |
| execl  | 인수를 직접 나열       |
| execv  | 인수 배열 전달        |
| execlp | PATH 탐색 포함 + 나열 |
| execvp | PATH 탐색 + 배열    |

```c
execl("/bin/ls", "ls", "-l", NULL);
execvp("ls", argv);
```

* 호출에 성공하면 **돌아오지 않음**

#### 📌 fork + exec 패턴

```c
if (fork() == 0)
    execl("/bin/date", "date", NULL);
else
    wait(NULL);
```

#### 📌 명령어 실행 후 종료 코드 확인

```c
system("ls -l"); // 내부적으로 fork + exec + wait 사용
```

### 🔸 9.4 입출력 재지정

#### 📌 dup2()를 이용한 재지정

```c
int fd = open("out.txt", O_WRONLY|O_CREAT);
dup2(fd, 1); // stdout → out.txt
```

#### 📌 exec와 함께 사용

```c
if (fork() == 0) {
  int fd = open("result.txt", O_WRONLY|O_CREAT);
  dup2(fd, 1);
  execl("/bin/echo", "echo", "Hello", NULL);
}
```

### 🔸 9.5 프로세스 그룹

#### 📌 개요

* 관련된 여러 프로세스를 하나의 그룹으로 묶음
* **신호 전달** 등의 작업 단위로 사용

#### 📌 함수

```c
pid_t getpgrp(void); // 현재 프로세스 그룹 ID
```

#### 📌 예제

```c
printf("PID: %d, GID: %d\n", getpid(), getpgrp());
```

* `fork()`된 자식은 부모의 그룹 ID를 상속

---


<!--
요기 안에 있는 코드 로 Ubuntu 명령어 c로 하는거 쓰셈
chat6.pdf (06pdf 아님)
chat7.pdf
chat8.pdf
chat9.pdf

5/30일 부터 그거 50개 만들어서 발표
6/13일 깃허브 정리/50개 그거 발표

- gpt 한테 물어보셈 - 
리눅스 명령 구현 옵션 만드는 함수 
-->