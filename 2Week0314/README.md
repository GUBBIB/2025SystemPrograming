# 2주차 수업내용

## Tree
**우분투** 에서 **폴더 구조** 를 **깔끔하게 파일트리 형식**으로 볼 수 있게 해주는 패키지이다.<br>
``sudo apt install tree`` 명령어로 설치가 가능하며 ``tree`` 명령어로 폴더 구조를 볼 수 있다.

## mkdir 명령어
``mkdir`` : 디렉토리를 **만들 때** 사용하는 명령어
### 옵션 -m, -p, -v, -Z 
- ``-m(--mode)`` : **퍼미션(권한)** 설정 옵션
- ``-p(--parents)`` : **상위 디렉토리** 가 없을 경우 **자동**으로 생성<br>
- ``-v(--verbose)`` : 디렉토리 생성시 마다 메시지 출력

```
mkdir -p -v  f/s1/s2/s3
mkdir: created directory 'f'
mkdir: created directory 'f/s1'
mkdir: created directory 'f/s1/s2'
mkdir: created directory 'f/s1/s2/s3'
```
- ``-Z`` : **selinux** 설정 옵션

        selinux란 커널을 보호하기 위한 도구이며 커널에 내장된 보안 모듈이다.
- ``{}`` : 한번에 여러개의 디렉토리 생성
```
mkdir a/{1, 2, 3} #사용 후 tree 사용시
tree

a
ㄴ 1
ㄴ 2
ㄴ 3
```

![디렉토리 및 파일 생성 후 tree 명령어](https://github.com/user-attachments/assets/f355e5ce-f80e-4798-8798-ccdb7cebd286)

## 참고
- [리눅스 mkdir 명령어 사용법 ( -m, -p, -v, -Z)](https://leevisual.tistory.com/66)