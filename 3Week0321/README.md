# 3주차 수업내용

## Ubuntu
### 우분투 명령어 및 디렉토리 표기법
- ``.`` : 현재 디렉토리, 현재 위치를 의미한다.
- ``..`` : 상위 디렉토리를 의미한다.
- ``/`` : root
- ``~`` : 현재사용자의 홈 디렉토리를 의미한다. ``/home/사용자이름``

### 명령어 man이란?
- 특정 명령이나 자원들의 메뉴얼을 출력하는 명령어이다.

#### 사용법
```Ubuntu
$ man [options] [section] command
```

#### Manual Section
- man명령어를 실행 시키면 옆에 뜨는 숫자의 의미를 정리한 표이다.
![man옆에 숫자 의미](https://github.com/user-attachments/assets/5839b21b-26c4-491f-9951-8652f1d86c55)

### gcc 설치 및 C언어 실행 법
#### gcc설치
C언어를 실행시키기 위해 우선 gcc 컴파일러를 설치해야한다. 
 
1. 설치를 하기전 우선 apt패키지를 ``sudo apt update`` 명령어를 사용해서 업데이트 해준다.
2. 이후 ```sudo apt install gcc``` 명령어를 사용해서 gcc를 설치한다.

#### C프로그램 생성 및 실행 법
1. ```touch "이름"``` 을 이용해서 빈 파일을 만든다.
2. ```vim```, ```cat``` 등을 이용해서 파일안에 코드를 작성한다.
3. 만약 파일의 이름이 ``test.c``일 때, ```gcc test.c``` 명령어로 컴파일을 한다.<br>
**※ ``-o`` 옵션을 사용해서 만든게 아니라면 ``a.out`` 이라는 Object파일이 생성이 된다.**
4. ```./a.out``` 명령어를 실행하면 작성한 C언어 코드가 실행이된다.

### 참고
- [[Linux]리눅스 man 명령어 - man 페이지 사용법, 주요 옵션, 사용 예](https://ihp001.tistory.com/65)
- [- Ubuntu에 GCC 컴파일 설치 및 GCC 사용법](https://byd0105.tistory.com/9)


<!--
/: root
.: self
..: parent
~: home

man 및 명령어 뒤에 숫자 (1) 설명

ll, ls -sl 할 떄 나오는 영어 들 설명
chap03.pdf에 파일의 종류
ㄴ 일반 파일 = "-"
ㄴ 디렉토리는 = "d"

~/0321/hello.c 만드는데
touch 로 빈폴더 만들고 cat으로 내용 채운 뒤 ll 로 확인하는 과정
gcc 설치 -> 컴파일 -> 실행

sudo, apt 가 뭔지 
cat, more, head, tail, wc 명령어 

우분투에 vscode 설치해보기 
sudo apt install --classic code 
wsl 폴더 들어가기 



hello.c 랑 학번 이름 입력받는.c 올려야 함
-->