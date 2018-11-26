# Killer Queen
난이도: Normal
점수: 1st는 50, 2nd는 150?

## description
Have you headr about queen? I love it!

## How to run
혹시 ssh 서버로 올리나요? nc로만 해야되는거면 1st stage는 걍 삭제해야될듯
sudo 권한으로 ./set_auth.sh 실행
problem directory 에서 실행하면 됨.

## 1st stage
잘 보면 안에 fork하고, parent process가 child를 기다림. child가 SIGNUM 9에 의해 종료됐으면 flag 보여줌

GuardianCTF{XOR_is_very_easy}

## 2nd stage
encode 함수를 보면 string에서 iterate하면서 지금 index랑 다음 index를 xor함. 이를 거꾸로 하면 string을 알 수 있다. 

GuardianCTF{WoW_you_can_kill_me}

## hint
Do you know program named `kill`? when you kill child process, magic happen! 
