# Youtube

> author: 김무환(minty99) / difficulty: easy / points: 100

## Description

텍스트 파일의 비밀을 알아내세요!
(플래그 형태는 GuardianCTF{???????????} 입니다. GuardianCTF 부분의 대소문자에 유의하세요)

## Hint 1 (20pt)

https://en.wikipedia.org/wiki/Letter_frequency

## Writeup

주어진 파일은 Mariah Carey의 All I Want For Christmas Is You라는 노래의 가사를 Letter Frequency 순서대로 변환한 것이다. (가장 많이 쓰이는 'e' -> 'a', 그 다음인 't' -> 'b' 이런 식으로 변환함)
이를 이용해 파일을 해독하면 노래 가사가 나오고, 시작 부분에 플래그를 만드는 방법이 주어진다.
> Get URL of this song's official music video in Youtube! Answer form: If URL is https://www.youtube.com/watch?v=?????????? then, you should submit GuardianCTF{??????????}

따라서 정답은 https://www.youtube.com/watch?v=yXQViqx6GMY, 즉 GuardianCTF{yXQViqx6GMY}

## How to run

Just deploy youtube.txt
