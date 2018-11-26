# siha's diary1

> author: 최경재(siha) / difficulty: easy / points: 100

## Description

웹 뉴비 siha가 파이썬 프레임워크인 flask를 사용하여 일기장 사이트를 만들었다.
siha는 파이썬 코드에 플래그를 적어두었다고 하는데, 그가 숨겨놓은 플래그를 읽어보자!

## Hint
- app.py의 내용을 읽으려면 어떻게 해야할까? (10)
- LFI (20)

## Write up

일기장 내용을 읽어보면 app.py라는 이름의 파이썬 파일이 있음을 알 수 있다.

http://localhost:5000/diary?path=myfirstwebsite.txt

일기장을 읽을 때 path 변수에 파일명을 넣는 것을 알 수 있는데, 이 부분에 ../app.py를 넣어주면 app.py 코드를 읽을 수 있다.

## How to run

```
pip install -r requirements.txt
python app.py
```

## flag

GuardianCTF{y0u_5h0uld_f1l73r_u53r_1npu7}