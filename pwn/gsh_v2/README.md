# gsh v2
> author: 이진우(munji) / difficulty: hard / points: 500 + 700

## Description
Guardian SHell final
(Plz read `README.md` in the problem. It says how to solve this problem.)

## Write up
Use After Free를 이용하는 문제로 총 2개의 flag가 존재한다. gsh v1의 시리즈 문제로 역시 셸을 컨셉으로 했다.

A라는 파일을 만들고 B라는 링크를 만들어 A를 가리키게 한다. 그리고 A를 삭제하면 B는 여전히 삭제된 A를 가리키게 되어 UAF가 발생한다.

이를 통해 fastbin에서 heap 주소를 구할 수 있다.

첫 번째 플래그는 부모 디렉토리가 삭제 됐지만 삭제하는 루틴을 보면 디렉토리 하위 파일들은 free시키지 않기때문에 여전히 heap에 올라가있는 상태다. 즉, UAF를 통해 heap 주소를 구하고 content 포인터를 flag1.txt의 content로 바꿔주면 읽을 수 있다.

두 번째 플래그는 unsorted bin을 만들어 libc주소를 얻어내고 `__malloc_hook`을 `one_gadget`의 주소로 덮으면 된다.

## Hint
- `너와 나의 연결고리`: 30
- `We remove parent directory but flag file.. remains..?`: 100
- `__malloc_hook? one_gadget?? unsorted bin??????!?!?!?!?`: 400

## TODO
- player들에게는 바이너리패치해서 flag1을 다른 문자열로 바꾼 뒤 제공
