# simple cipher

> difficulty: easy / points: 150

## Description

This is a simple cipher. Just crack it.

## Hint 1 (50pt)

https://en.wikipedia.org/wiki/Lorem_ipsum

## Hint 2 (50pt)

https://en.wikipedia.org/wiki/Affine_cipher

## write up

attack.py

실행하면 lorem ipsum텍스트를 무작위로 셔플해서 임의의 키로 affine암호화를 한 암호문을 보낸다.
키를 브루트 포스 해서 100라운드 통과하면 플래그 획득

## how to run

> python 3.6+

socat TCP-LISTEN:#port,fork,reuseaddr EXEC:"python server.py"

## how to deploy

server.py, flag 서버에 디플로이
코드 공개하지 말것
