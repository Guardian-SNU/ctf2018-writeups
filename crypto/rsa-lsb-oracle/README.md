# RSA LSB Oracle

> difficulty: medium / points: 200

## Description

Do you know about oracle?

## Hint 1 (100pt)

https://ctf.rip/sharif-ctf-2016-lsb-oracle-crypto-challenge/

## write up

attack.py

## how to run

> python 3.6+

socat TCP-LISTEN:#port,fork,reuseaddr EXEC:"python server.py"

## how to deploy

server.py, flag 서버에 디플로이
server.py 공개
