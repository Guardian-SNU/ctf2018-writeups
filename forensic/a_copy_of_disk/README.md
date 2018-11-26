# Good Listener
> author: 신동진(maro) / difficulty: difficult / points: 600

## Description

당신은 maro에게 중요한 디스크의 복사본을 요청했다. 그런데, 짜잔!
당신에게 온 복사본은 그 복사본이 아니었다. 분노한 당신은 maro에게 따졌으나
그는 분명히 당신에게 필요한 걸 주었다고 말하고 있다. 데이터를 찾아내라.

## Hint 1

RGBA (250)

## Hint 2

플로피 디스크는 어떤 파일 시스템을 사용하는가? (250)

## Writeup

이미지를 확대하면 각 픽셀에 옅은 색 차이로 16진수가 쓰여있는 것을 알 수 있다.
굉장히 옅게 쓰여있어 알아보기 어려우나, RGB값이 아닌 alpha 채널로 마스킹되어 있고
각 숫자는 모두 같은 모양으로 쓰여있으므로 이를 어렵지 않게 데이터화할 수 있다.

이 바이너리는 헤더와 구조를 보면 FAT 덤프인 것을 알 수 있다. (정확히는 FAT12로, 실제로
floppy disk에 사용되는 파일 포맷이다)
`mount`등의 명령어를 이용해 파일 시스템을 열어보면 안에서 flag.txt를 찾을 수 있다.

*flag: GuardianCTF{i_t01d_y0u_th1s_i5_th3_pr0p3r_0n3}*

## How to run

 - Just deploy `copy.png`
