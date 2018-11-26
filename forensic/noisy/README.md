# Noisy 

> author: 신동진(maro) / difficulty: normal / points: 450

## Description

이미지 파일로부터 데이터를 추출하세요.

## Hint 1

총 81개의 QR코드가 존재한다. (20)

## Hint 2

자연수를 QR 코드로 나타내려면 어떻게 할 수 있을까? (60)

## Writeup

`noisy.png`의 81개인 100x100 영역은 각각 QR code 이미지이다.
각각을 decode하면 정수를 하나씩 얻는데, 이 숫자들을 이진수로 나타내면
대부분 길이가 25이고 아니면 약간 더 짧다. 이를 5x5의 흑백 이미지로 나타내고
81개를 원래 위치대로 붙이면 하나의 큰 QR코드를 얻고, 이를 decode하면 플래그를 얻는다.

*flag: GuardianCTF{qRc0d3_fr4cTa1}*

## How to run

 - Just deploy `noisy.png`
