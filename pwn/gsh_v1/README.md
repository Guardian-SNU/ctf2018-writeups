# gsh v1
> author: 이진우(munji) / difficulty: normal / points: 100 + 200

## Description
Guardian SHell prototype

## Write up
Format String Bug를 이용하는 문제로 총 2단계의 stage로 구성되어있다. 간단하고, 허접한 shell을 컨셉으로 잡았다.

echo 커맨드에서 FSB가 발생하는데 %x만 사용해서 스택에 올라가있는 첫번째 플래그를 읽을 수 있다.

두번째 플래그의 존재는 ls 커맨드에서 힌트를 주는데 ls를 실행시키면 2개의 플래그가 존재하는 것을 볼 수 있다.
두번째 플래그를 읽으려면 shell을 획득해야 하는데 쉬움 난이도이므로 system함수와 `/bin/sh`문자열을 일부러 제공했다.
FSB를 이용하여 `gsh()`의 return address를 덮던가, `strncmp()`함수의 GOT table을 `system()`으로 덮으면 쉘을 얻을 수 있다.

## Hint
- `What's FSB..? Let's google it!`: 5 points
- `GOT table? Let's try to run /bin/sh!`: 50


