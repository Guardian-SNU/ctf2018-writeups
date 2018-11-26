# Bank Robber
> author: 이진우(munji) / difficulty: easy / points: 150

## Description
Hi, new hacker!
Can you rob bank?

## Write up
아주 단순한 race condition.
처음 500원을 가지고 있는데 500원을 2번 예금하면 -500원이 되고, unsigned여서 돈이 매우 커진다(integer underflow).
이 상태로 flag 메뉴로 가면 플래그를 읽을 수 있다.

## Hint
- `What's race condition?` (10 points)
- `What's integer underflow, overflow` (10 points)
