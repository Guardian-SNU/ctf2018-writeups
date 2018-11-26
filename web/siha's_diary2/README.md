# siha's diary2

> author: 최경재(siha) / difficulty: easy / points: 200

## Description

웹 뉴비 siha가 일기장 사이트를 새롭게 업데이트 했다.
기존의 취약점은 고치고 새로운 기능을 추가했다는데 이번에도 siha의 사이트를 털어보자!

## Hint
- what is SSTI? (50)
- flask 프레임워크는 여러가지 설정을 담고있는 변수에 있다. (100)

## Write up

search 파라미터에 {{ 1+1 }}을 넣어보면 2가 출력되는 것을 확인할 수 있다.
이는 Server side template injection이 가능함을 뜻한다.

search 파라미터에 {{ config }} 를 넣으면 설정 중에 FLAG 값이 존재한다.

## How to run

```
pip install -r requirements.txt
python app.py
```

## flag

GuardianCTF{0h_y0u_kn0w_wh47_73mpl473_1nj3c710n_15}