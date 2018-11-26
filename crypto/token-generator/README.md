# token generator

> difficulty: medium / points: 200

## Description

A vulnerable auth token generator. Can you get a secret?

## Hint 1 (5pt)

https://en.wikipedia.org/wiki/Block_cipher_mode_of_operation#Electronic_Codebook_(ECB)

## Hint 2 (100pt)

https://github.com/liamh95/CTF-writeups/tree/master/CSAW17/baby_crypt

## write up

AES ECB모드의 특성을 이용해서 한바이트씩 FLAG를 추측가능

## how to run

> python 3.6+

socat TCP-LISTEN:#port,fork,reuseaddr EXEC:"python server.py"

## how to deploy

server.py, flag, key 서버에 디플로이
server.py 공개
