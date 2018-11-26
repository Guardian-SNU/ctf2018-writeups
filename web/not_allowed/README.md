# NOT ALLOWD

> author: 최경재(siha) / difficulty: easy / points: 100

## Description

들어갈 수 없다.

## Hint
- 들어가자마자 창이 닫히는 이유는 javascript 스크립트가 실행되기 때문이다.
- curl, wget 등의 도구를 사용해보자.

## Write up

사이트에 들어가면 window.close() 가 실행되어 창이 바로 닫힌다.
curl, wget 등으로 사이트 코드를 바로 읽어주면 main.js의 존재를 알 수 있고,
main.js 를 읽어보면 URL 인코딩된 플래그가 있다.

## How to run

serve index.html directly