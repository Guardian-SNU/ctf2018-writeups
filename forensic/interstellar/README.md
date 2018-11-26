# Interstellar

> author: 김무환(minty99) / difficulty: normal / points: 200 (Lv1: 100, Lv2: 100)

## Description

Capture the flag!
You can try level 2 after solve level 1.

## Hint 1 (for level 1) (40pt)

https://en.wikipedia.org/wiki/Base64

## Hint 2 (for level 1) (50pt)

텍스트 파일은 아닌 거 같고... 그럼 뭐지? 다른 방식으로 열어보자.

## Hint 3 (for level 2) (20pt)

이미지 파일에 정보를 숨기는 방법이 있을까? 또, 과연 그냥 숨겨놓았을까?

## Writeup
- Level 1: 압축을 풀면 나오는 텍스트 파일은 base64 decoding을 하면 zip 형태의 압축파일이 된다. 압축을 해제하면 level1.txt와 level2.zip을 얻는다. level1.txt는 사실 PNG(또는 JPG로도 열린다) 형태의 그림 파일이다. 그림 파일을 열면 플래그가 적혀 있다. 이 플래그를 사용하면 level2.zip의 압축을 해제할 수 있다. 해제하면 level2.jpg를 얻는다.
- Level 2: level2.jpg를 Hex Editor로 열어서 맨 끝부분을 보면 DO_YOU_WANT_FLAG?뒤에 이상한 문자열이 보인다. 이 문자열을 ASCII 코드 기준으로 -1씩 해주면 플래그가 된다.

## How to run
- Just deploy interstellar.zip
