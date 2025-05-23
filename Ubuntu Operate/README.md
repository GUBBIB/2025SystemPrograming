1. chmod, fchmod, dup, touch, utime, chown, mkdir, rmdir, 심볼릭 링크, 하드 링크


### ✅ C 언어로 구현하기 쉬운 Ubuntu 명령어 50선 (난이도순)

---

#### 🟢 레벨 1 (아주 쉬움)

| 명령어                    | 설명            |
| ---------------------- | ------------- |
| `pwd`                  | 현재 경로 출력      |
| `echo hello`           | 문자열 출력        |
| `clear`                | 화면 지우기        |
| `whoami`               | 현재 사용자 출력     |
| `date`                 | 현재 시간 출력      |
| `hostname`             | 호스트 이름 출력     |
| `uname`                | 커널 정보 출력      |
| `id`                   | 사용자 정보 출력     |
| `printenv PATH`        | 환경 변수 출력      |
| `exit`                 | 프로그램 종료       |
| `cd`                   | 디렉토리 변경       |
| `ls`                   | 현재 디렉토리 파일 목록 |
| `ls -a`                | 숨긴 파일 포함 목록   |
| `ls -l`                | 상세 정보 출력      |
| `ls -al`               | 숨김+상세 목록      |
| `ls -R`                | 재귀적 목록        |
| `mkdir test`           | 디렉토리 생성       |
| `mkdir -p test/subdir` | 하위 디렉토리 포함 생성 |
| `rmdir test`           | 디렉토리 삭제       |
| `touch test.txt`       | 빈 파일 생성       |
| `rm test.txt`          | 파일 삭제         |
| `rm -f test.txt`       | 강제 삭제         |
| `rm -r test_dir`       | 디렉토리 삭제 (재귀)  |
| `cat file.txt`         | 파일 내용 출력      |
| `head file.txt`        | 앞부분 출력        |
| `head -n 5 file.txt`   | 앞 n줄 출력       |
| `tail file.txt`        | 뒷부분 출력        |
| `tail -n 10 file.txt`  | 뒤 n줄 출력       |
| `env`                  | 환경 변수 전체 출력   |
| `printenv`             | 환경 변수 출력      |
| `set`                  | 쉘 변수 출력       |
| `id -u`                | UID 출력        |
| `id -g`                | GID 출력        |

---

#### 🔵 레벨 2 (쉬움)

| 명령어                       | 설명                 |
| ------------------------- | ------------------ |
| `file test.txt`           | 파일 타입 판단           |
| `ps`                      | 현재 프로세스 출력         |
| `ps -e`                   | 전체 프로세스 출력         |
| `who`                     | 로그인 사용자 출력         |
| `who -u`                  | 사용자 + 세부정보 출력      |
| `uptime`                  | 시스템 가동 시간          |
| `uname -a`                | 커널 정보 전체 출력        |
| `df`                      | 디스크 공간 사용량         |
| `df -h`                   | 사람이 읽기 쉬운 형식       |
| `du`                      | 디스크 사용량            |
| `du -h`                   | 사람이 읽기 쉬운 형식       |
| `which ls`                | 실행 파일 경로 찾기        |
| `whereis ls`              | 실행 파일/소스/매뉴얼 경로 찾기 |
| `find . -name "file.txt"` | 현재 경로에서 파일 탐색      |
| `find / -type f`          | 전체 파일 탐색           |
| `hostname -I`             | IP 주소 출력           |
| `ping -c 1 google.com`    | 네트워크 응답 테스트        |
| `curl http://example.com` | HTTP 요청            |

---