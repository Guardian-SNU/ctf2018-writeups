# Easy Calc
> author: 이진우(munji) / difficulty: normal / points: 200 + 400

## Description
Easy Calc Easy Calc!
But harder than Hard ROP
Why? Because "easy" means hard at pwnable!

## Write up
두 Obj를 계산할때 첫번째 Object의 타입에 맞춰서 계산한다.
즉, Int와 Str을 더하면 두 Object를 Int로 취급하기에 heap주소를 leak할 수 있다.
4번 메뉴를 통해 heap에 flag를 올려놓고 위 방법을 통해 heap base addr를 얻은 뒤 flag 가 올라가 있는 주소를 값으로 가지는 Int Obj를 생성한다.
그 후 Str + Int 연산을 하면 둘 다 Str 취급을 할 것이고 flag1을 얻어낼 수 있다.

두번째 플래그는 셸을 얻는것이 의도된 풀이다.
Int에 got table의 주소를 넣고 Str + Int를 하면 libc addr를 얻을 수 있고, 이를 통해 system의 주소를 알 수 있다.

assignment(`=`) 연산시에 일부러 두번째 Obj에 첫번째 Obj의 값을 넣도록 했는데 이를 통해서 Int Obj에 string을 assign할 수 있기 때문이다. got table의 주소를 값으로 가지는 Int를 만들고 system함수의 주소를 packing한 문자열을 값으로 가지는 Str Obj을 만든뒤 대입(`=`연산)하면 got table에 system의 주소를 덮을 수 있다.

## Hint
- `Type Confusion? But.. I'm checking type well!`: 100
- `Why assigning order is.. weird?`: 150
