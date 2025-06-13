# 2025SystemPrograming

## [1주차 수업내용](https://github.com/GUBBIB/2025SystemPrograming/tree/main/1Week0307)
- [Windows에서 Ubuntu 사용하는 방법 3가지](https://github.com/GUBBIB/2025SystemPrograming/tree/main/1Week0307)

## [2주차 수업내용](https://github.com/GUBBIB/2025SystemPrograming/tree/main/2Week0314)
- [tree패키지 및 mkdir 옵션 설명](https://github.com/GUBBIB/2025SystemPrograming/tree/main/2Week0314)

## [3주차 수업내용](https://github.com/GUBBIB/2025SystemPrograming/tree/main/3Week0321)
- [gcc설치 및 실행법법](https://github.com/GUBBIB/2025SystemPrograming/tree/main/3Week0321)

## [4주차 수업내용](https://github.com/GUBBIB/2025SystemPrograming/tree/main/4Week0328)
- [파일 명령어](https://github.com/GUBBIB/2025SystemPrograming/tree/main/4Week0328)

## [5주차 수업내용](https://github.com/GUBBIB/2025SystemPrograming/tree/main/5Week0404)
- [prompt에 대해서](https://github.com/GUBBIB/2025SystemPrograming/tree/main/5Week0404)

## [6주차 수업내용](https://github.com/GUBBIB/2025SystemPrograming/tree/main/6Week0411)
- [쉘에 대해서](https://github.com/GUBBIB/2025SystemPrograming/tree/main/6Week0411)

## [7주차 수업내용](https://github.com/GUBBIB/2025SystemPrograming/tree/main/7Week0418)
- [프로세스에 대해서](https://github.com/GUBBIB/2025SystemPrograming/tree/main/7Week0418)

## 중간 시험

## [9주차 수업내용](https://github.com/GUBBIB/2025SystemPrograming/tree/main/9Week0502)
- [유닉스 시스템에 대해서](https://github.com/GUBBIB/2025SystemPrograming/tree/main/9Week0502)


## [10주차 수업내용](https://github.com/GUBBIB/2025SystemPrograming/tree/main/10Week0509)
- [디렉토리 및 파일 구조](https://github.com/GUBBIB/2025SystemPrograming/tree/main/10Week0509)


## [11주차 수업내용](https://github.com/GUBBIB/2025SystemPrograming/tree/main/11Week0516)
- [리눅스 파일 시스템 구조](https://github.com/GUBBIB/2025SystemPrograming/tree/main/11Week0516)


## [12주차 수업내용](https://github.com/GUBBIB/2025SystemPrograming/tree/main/12Week0523)
- [프로세스 제어](https://github.com/GUBBIB/2025SystemPrograming/tree/main/12Week0523)


## [13주차 수업내용](https://github.com/GUBBIB/2025SystemPrograming/tree/main/13Week0530)
- [조기 종강](https://github.com/GUBBIB/2025SystemPrograming/tree/main/13Week0530)


<!-- 
PC WSL2 Ubuntu 계정 - ubuntu, 1111
노트북 WSL2 Ubuntu 계정 - ubuntu, 1111
-->

<!--
시스템프로그래밍05.pdf 안에
db~~.c 작성하기 기말 시험임

[ 깃허브 & C언어 ppt 1개 만 있어도 됨 ] ※ 발표 3분 이내
6/13일 까지 깃허브 정리한 ppt 있어야함 - 15점
ㄴ 깃허브 링크
ㄴ 내가 생각한 점수 

6/13일 까지 50개 운영체제 명령어 C언어로 구현 및 정리한 ppt - 개당 0.25점 총 15점
ㄴ 옵션 같은건 getopt getoptlong 을 써라 - gpt 물어보셈
ㄴ ppt 에 소스 넣을 필요는 없는데 
ㄴ 깃허브 에 소스 코드가 올라가야함
ㄴ 깃허브 링크
ㄴ 내가 생각한 점수

어떤 명령어를 c로만들었는지 ppt에 적기 
ㄴ 설명은 알아서 
-->

<!--
우리 ppt에 넣어야 할 거 1
Include conf/extra/httpd-vhosts.conf
httpd.conf 에서 위에 꺼 검색 후 주석(#) 제거
-->


<!--

  CREATE TABLE "MOVIEEXEC" 
   (	"NAME" VARCHAR2(100) constraint me_name UNIQUE, 
	"ADDRESS" VARCHAR2(255), 
	"CERTNO" NUMBER(*,0) constraint me_key Primary Key, 
	"NETWORTH" NUMBER(*,0),
    "SPOUSENAME" VARCHAR2(255),
    "GENDER" CHAR(6),

    CONSTRAINT "SEX_CHK" CHECK (gender in ('male', 'female')),
    constraint fk_movieExec_movieStar foreign key (spouseName) references movieStar(name)
   )


  CREATE TABLE "MOVIESTAR" 
   (	"NAME" VARCHAR2(100) constraint st_key primary key, 
	"ADDRESS" VARCHAR2(255), 
	"GENDER" CHAR(6), 
	"BIRTHDATE" DATE,
    "SPOUSENAME" VARCHAR2(255),
    
    CONSTRAINT "SEX_CHK" CHECK (gender in ('male', 'female')),
    constraint fk_movieStar_movieExec foreign key (spouseName) references movieExec(name)
   )
  CREATE TABLE "STUDIO" 
   (	"NAME" VARCHAR2(100) constraint std_key primary key, 
	"ADDRESS" VARCHAR2(255), 
	"PRESNO" NUMBER(*,0),
    "EMPNO" NUMBER(*,0)
   )

  CREATE TABLE "MOVIE" 
   (	"TITLE" VARCHAR2(255), 
	"YEAR" NUMBER(*,0), 
	"LENGTH" NUMBER(*,0), 
	"INCOLOR" CHAR(1), 
	"PRODUCERNO" NUMBER(*,0),
	    "DIRECTORNO" NUMBER(*,0),
	    "SOUNDSTUDIO" VARCHAR2(255),
    
    constraint mv_key primary key(title,year),
    constraint mv_chk CHECK (length > 50 and year > 1900 and year <= 2024),
    constraint fk_movie_movieExec foreign key (directorNo) references MovieExec(certNo) on delete set null,
    constraint fk_movie_studio foreign key (SoundStudio) references Studio(name) on delete set null
   )

  CREATE TABLE "STARSIN" 
   (	"MOVIETITLE" VARCHAR2(255), 
	"MOVIEYEAR" NUMBER(*,0), 
	"STARNAME" VARCHAR2(100),
    "GURANTEE" NUMBER(*,0),
    
    constraint stin_key primary key(movietitle,movieyear, starname),
    constraint chk_gurantee check (GURANTEE >= 10000),
    constraint fk_starsIn_movie foreign key (movieTitle, movieYear) references movie(title, year) on delete cascade,
    constraint fk_starsIn_movieStar foreign key (starName) references movieStar(name) on delete cascade
   )

  CREATE TABLE "CARTOON" 
   (	
    "TITLE" VARCHAR2(255), 
	"YEAR" NUMBER(*,0), 
	"VOICE" VARCHAR2(255),
    
    constraint pk_cartoon primary key (title, year, voice),
    constraint fk_cartoon_movie foreign key (title, year) references movie(title, year) on delete cascade, 
    constraint fk_cartoon_movieStar foreign key (voice) references movieStar(name) on delete cascade
   )



  ALTER TABLE "STARSIN" ADD constraint stin_fk1 FOREIGN KEY ("MOVIETITLE", "MOVIEYEAR")
	  REFERENCES "MOVIE" ("TITLE", "YEAR") -- ON DELETE CASCADE ENABLE
 /
  ALTER TABLE "STARSIN" ADD constraint stin_fk2 FOREIGN KEY ("STARNAME")
	  REFERENCES "MOVIESTAR" ("NAME") -- ON DELETE CASCADE ENABLE
/
create or replace view Prod_Studio (producer, p_title, studio, s_title) as
select e.name, pm.title, s.name, sm.title
from ((movieexec e left outer join movie pm on ( certno = pm.producerno )) left outer join 
    studio s on (certno = presno) ) left outer join movie sm on (s.name = sm.studioname);
commit;
quit;

1. 
SELECT me.name
FROM Movie m
JOIN MovieExec me certNo = diretorNo
WHERE LOWER(title) = 'star wars'

2.
SELECT *
FROM 

-->