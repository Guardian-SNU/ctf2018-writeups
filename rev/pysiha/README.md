# pysiha
> author: 이진우(munji) / difficulty: normal / points: 250

## Description
pyc.....si..ha..?

## Write up
`.pyc`파일은 decompile이 가능하다. 온라인에서 하든, `uncompyle6`을 사용하든 디컴파일을 하면 큰 숫자가 하나 있고, 이 숫자를 어떻게 해서 `exec()`으로 실행시키는 것을 확인할 수 있다. 이 숫자를 hex string으로 나타내고 hex decode를 하면 다른 파이썬 코드가 나오고 이 코드가 실행이 되는 것이다.

얻어낸 파이썬 코드를 보면 문자열을 입력받고, 한글자씩 xor연산을 시킨 뒤 base64로 인코딩, hex로 인코딩하여 나온 숫자를 answer와 비교해본다. 즉, 모두 역변환이 가능하므로 answer를 hex decode하고 base64로 디코딩시킨 뒤 0x30으로 xor시키면 플래그가 나온다.
