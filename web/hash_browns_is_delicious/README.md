# Hash browns is delicious

> author: 최경재(siha) / difficulty: medium / points: 300

## Description

매일 아침으로 해시 브라운을 먹을 정도로 해시를 좋아하는 siha는, 작년 Google이 해시 함수인 SHA1를 깨트리는 데에 성공했다는 소식을 듣고 깜짝 놀랐다.

그러나 논문을 읽기가 귀찮았던 siha는 CTF 참가자들에게 대신 해시를 깨트리는 일을 시켜보기로 하였다.


## Hint
- php의 비교 연산자는 '==' 와 '===' 두 가지가 있다. (30)
- http://php.net/manual/en/language.operators.comparison.php (150)

## Write up

php에서 '0e[0-9]+' 는 0으로 취급된다.

```
md5(0e000000000000000000000329568726) = 0e910477264496664586831669209832

sha1(0e1290633704) = 0e19985187802402577070739524195726831799
```

## How to run

Nginx 등을 사용하여 index.php 파일을 제공, flag.php는 직접 접근 하지 못하도록 할 것.

## flag

GuardianCTF{d0n7_u53_md5_5h41_4nd_php}
