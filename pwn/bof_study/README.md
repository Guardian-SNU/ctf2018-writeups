# BOF study
> author: 이진우(munji) / difficulty: baby / points: 10 + 20

## Description
Do you know Gangnam Style? Do you know BOF?
Let's learn baby hackers!

## Write up
위쪽에 있는 check 버퍼를 `\x11\x22\x33\x44\x55\x66`으로 맞춰주면 첫번째 플래그를 얻을 수 있다.
또, bof를 이용해서 return address에 두번째 플래그를 출력시켜주는 함수의 주소를 넣으면 두번째 플래그가 출력된다.

## Hint
- `BOF is Buffer Overflow` (0 points)
- `eip? return address?? stack frame???` (3 points)

