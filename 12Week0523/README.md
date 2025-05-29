# 12주차 수업내용

## 9장 프로세스 제어 (Process Control)

### 9.1 프로세스 생성

#### ✅ fork() 시스템 호출

* 부모 프로세스가 자신을 복제하여 자식 프로세스를 생성함.
* 복제는 코드, 데이터, 힙, 스택 모두 동일한 상태로 이루어짐.
* **호출 시점에는 하나, 리턴은 두 번 일어남**

  * 자식 프로세스: `0` 리턴
  * 부모 프로세스: 자식 프로세스의 PID 리턴

```c
#include <sys/types.h>
#include <unistd.h>
pid_t fork(void);
```

#### 🧪 예제: fork1.c

```c
printf("[%d] 프로세스 시작\n", getpid());
pid = fork();
printf("[%d] 프로세스 : 리턴값 %d\n", getpid(), pid);
```

**실행 결과:**

* 부모: `[15065] 반환값 15066`
* 자식: `[15066] 반환값 0`

#### 💡 부모와 자식 프로세스 구별 방법

```c
if (pid == 0) {
  // 자식 프로세스 코드
} else {
  // 부모 프로세스 코드
}
```

#### 🧪 예제: fork2.c

```c
pid = fork();
if (pid == 0)
  printf("[Child] : Hello, world pid=%d\n", getpid());
else
  printf("[Parent] : Hello, world pid=%d\n", getpid());
```

#### 🧪 예제: fork3.c (두 개의 자식 프로세스 생성)

```c
pid1 = fork();
if (pid1 == 0) { exit(0); }
pid2 = fork();
if (pid2 == 0) { exit(0); }
printf("[PARENT] : Hello\n");
```

* **생성된 프로세스 수:** 4개 가능 (부모, 자식1, 자식2, 자식1의 자식2)

---

### 9.1.1 자식 프로세스 기다리기

#### ✅ wait()와 waitpid()

```c
#include <sys/wait.h>
pid_t wait(int *status);
pid_t waitpid(pid_t pid, int *status, int options);
```

* 자식 프로세스의 종료를 기다림
* 종료 코드 확인: `status >> 8`

#### 🧪 예제: forkwait.c

```c
pid = fork();
if (pid == 0) exit(1);
child = wait(&status);
printf("자식 %d 종료, 종료코드: %d\n", child, status >> 8);
```

#### 🧪 예제: waitpid.c (특정 자식 기다리기)

```c
pid1 = fork();
...
waitpid(pid1, &status, 0);
```

* 자식이 종료되는 순서를 제어할 수 있음.

---

### 9.2 프로그램 실행

#### ✅ exec() 계열 함수

* 현재 프로세스를 새로운 프로그램으로 완전히 대체함
* 성공하면 리턴하지 않음 (main()부터 다시 시작)

```c
int execl(char *path, char *arg0, ..., NULL);
int execv(char *path, char *argv[]);
int execlp(char *file, char *arg0, ..., NULL);
int execvp(char *file, char *argv[]);
```

#### 🧪 예제: execute1.c

```c
if (fork() == 0) {
  execl("/bin/echo", "echo", "hello", NULL);
  exit(1);
}
```

#### 🧪 예제: execute2.c (3개 명령 실행)

```c
fork(); execl("/bin/echo", ...);
fork(); execl("/bin/date", ...);
fork(); execl("/bin/ls", ...);
```

#### 🧪 예제: execute3.c (명령줄 인수 기반 실행)

```c
execvp(argv[1], &argv[1]);
```

#### ✅ system() 함수

* 내부적으로 fork + exec + waitpid 사용
* 명령 문자열을 쉘로 넘겨 실행

```c
int system(const char *cmd);
```

---

### 9.3 입출력 재지정

#### ✅ dup() / dup2()

```c
int dup(int oldfd);
int dup2(int oldfd, int newfd);
```

* `dup2(fd, 1);` → `stdout`을 파일 디스크립터 `fd`로 대체함

#### 🧪 예제: redirect1.c

```c
fd = open(argv[1], ...);
dup2(fd, 1);
printf("stdout\n"); fprintf(stderr, "stderr\n");
```

* `stdout`은 파일에 저장, `stderr`는 그대로 콘솔 출력

#### 🧪 예제: redirect2.c

```c
fork();
dup2(fd, 1);
execvp(argv[2], &argv[2]);
```

* 특정 명령의 출력을 파일로 리디렉션 가능

---

### 9.4 프로세스 그룹

#### ✅ 개념

* **프로세스 그룹:** 여러 프로세스의 논리적 묶음
* **그룹 리더:** 최초 프로세스 (GID == PID)

```c
pid_t getpgrp(void);
int setpgid(pid_t pid, pid_t pgid);
```

#### 🧪 예제: pgrp1.c / pgrp2.c

```c
setpgid(0, 0);  // 현재 프로세스를 새로운 그룹 리더로 설정
```

#### waitpid 옵션 (그룹 기준)

* `pid == -1` : 임의 자식
* `pid == 0` : 동일 그룹 자식
* `pid < -1` : 특정 그룹 자식 (abs(pid) 그룹 ID)

---

### 9.5 시스템 부팅 과정

#### ✅ 초기 프로세스 흐름

* **swapper**: 커널 내부 스케줄러
* **init**: `/etc/inittab` 기반 초기화
* **getty**: 로그인 대기
* **login**: 사용자 인증
* **shell**: 사용자 명령 수신

---

### 🎯 핵심 요약

* `fork()`: 부모를 복제해 자식 프로세스 생성
* `exec()`: 현재 프로세스를 새로운 프로그램으로 대체
* `wait()/waitpid()`: 자식 종료 대기 및 종료 코드 확인
* `dup2()`: 표준 출력 등 입출력 리디렉션
* `system()`: 문자열 명령 실행 (내부적으로 fork + exec + wait)
* `setpgid()`: 프로세스 그룹 설정
* **부팅 시 프로세스 흐름은 init → getty → login → shell**

<!--
chat9.pdf (09아님)

https://www.duckdns.org/domains - 깃헙으로 로그인 함
ㄴ 도메인 무료 호스팅
-->