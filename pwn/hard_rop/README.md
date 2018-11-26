# Hard ROP
> author: 이진우(munji) / difficulty: easy / points: 150 + 200

## Description
ROP? Is it a new programming method?

## Write up
`vuln()`함수에서 대놓고 buffer overflow가 발생한다.
ROP를 이용하여 플래그를 얻어내면 되는 문제다.

첫번째 플래그는 전역변수에 파일을 읽고 써주는 함수가 제공되기 때문에 이 함수를 실행시키고, `pop rdi`가젯과 `puts()`를 통해 플래그를 출력시킬 수 있다.

두번째 플래그는 플래그 파일을 열고, 읽는 루틴까지 ROP로 직접 짜야한다. `fopen()`을 통해서 flag2.txt를 열 수 있다. 그리고 `fgets(buf, size ,fp)`를 실행시켜야 하는데 `fp`의 주소를 몰라서 막힐 수 있다. 물론, libc를 leak하고 그 안에서 찾을 순 있겠지만 그럴 필요는 없다.
`fopen()`으로 새로운 파일을 열면 `fd`가 자동으로 추가되기 때문에 `read(fd, buf, size)`를 이용하면 된다.

## Hint
- `With ropper, you can find gadgets easier! $ pip install ropper`: 20
- `fopen() makes new file descriptor, and read() uses file descriptor`: 100
