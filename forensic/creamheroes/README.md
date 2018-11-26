# Creamheroes
> author: 신동진(maro) / difficulty: normal / points: 300

## Description

maro가 숨겨진 사진을 고양이들 사이에 숨겨놓았다고 한다.

## Hint 1

https://en.wikipedia.org/wiki/JPEG#Syntax_and_structure (10)

## Hint 2

https://en.wikipedia.org/wiki/Portable_Network_Graphics#File_header (50)

## Writeup

7개의 jpg 파일은 모두 EOI 이후에 연속된 0들 이후에 데이터가 더 붙어 있고, 이 중 하나는 IHDR으로 시작하여
png 파일임을 알 수 있다.
IHDR이 포함된 데이터를 시작으로 하여, 나머지 6개 파일을 6! = 720가지 조합해보고 이 중 올바른 플래그가 들어있는
이미지를 확인할 수 있다.

*flag: GuardianCTF{C4TS_4RE_Sup3r_cute_N0_obj3cti0n_a110wed}*

## How to run

 - Just deploy `creamheroes.zip`
