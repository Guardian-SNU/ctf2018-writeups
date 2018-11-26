# siha's diary4

> author: 최경재(siha) / difficulty: hard / points: 900

## Description

siha가 일기장 사이트에 새로운 기능을 추가했다!

## Hint
- 이 문제는 디지털 포렌식 문제라고도 볼 수 있다. (100)
- siha의 글을 읽고 싶다면 siha인 척 해야한다. siha는 예전에 한 실수를 몰래 숨겨두었다. (300)

## Write up

방명록에 여러번 글을 써보면 같은 이름으로 글이 써지는 것을 확인할 수 있고,
siha의 글은 읽을 수 없다는 것도 확인할 수 있다.

특정한 이름으로 글이 써진다는 점에서 그 이름이 쿠키에 저장되어 있다는 것을 유추할 수 있다.

쿠키를 [이런](https://www.kirsle.net/wizards/flask-session.cgi) 사이트에서 디코딩 해보면 username 값이 존재한다는 것을 확인할 수 있다.

목표는 이 username을 siha로 바꾸는 것이다.

flask의 쿠키를 조작하려면 secret key를 알아내야만 한다.
글 다운로드 기능을 사용하면 app.py를 다운로드 받을 수 있지만, secret key 값과 db의 위치가 모두 환경변수에 들어가 읽어 읽어낼 수 없다.

일기장의 내용을 잘 읽어보면, siha가 코드의 버전관리를 하고 있다는 점을 유추할 수 있고, 과거에 취약점을 수정했다는 사실도 알 수 있다.

```
/download?path=../.git/HEAD
``` 

git을 이용하여 버전관리를 할 것이라 추측하고 HEAD 파일에 접근해보면 다운로드가 되는 것을 확인할 수 있다.

이제, [GitTools](https://github.com/internetwache/GitTools)와 같은 도구를 이용하여 git 레포지토리를 덤프한 뒤,

로그를 찍고 커밋을 돌려보면? 플래그가 없다!

하지만 `git reflog` 커맨드로 HEAD 변경 내역을 살펴보면,

```
bf7a341 HEAD@{0}: commit: add new diary and fix vulnerability
0f620c8 HEAD@{1}: reset: moving to 0f620c827ed49bc08d18fed7ece143dc238c2cbb
3eac155 HEAD@{2}: commit: add new diary
ed1c2b7 HEAD@{3}: commit (initial): initial commit
```

reset이 있었다는 사실을 알수 있고,

`git fsck --lost-found` 커맨드로 숨겨진 커밋을 찾은 뒤,

`git show <commit>`로 해당 커밋을 조회하면 숨겨진 secret key를 찾을 수 있다.

```
-app.secret_key = 'test_secret_key'
+app.secret_key = '51h4_5up3r_53cr37_fl45k_k3y_h4h4_h0h0'
```

이제 해당 secret key를 사용하여 쿠키를 조작하면 siha의 방명록을 읽을 수 있고, siha의 방명록에 플래그가 적혀있다.

## How to run

```
unzip siha's_diary4.zip
source run.sh
python app.py
```

## flag

GuardianCTF{n3v3r_l34k_y0ur_617_d1r3c70ry}