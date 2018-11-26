import decimal
from pwn import *
from Crypto.Util.number import long_to_bytes

r = remote('localhost', 9999)
r.readuntil('n is ')
n = int(r.readline().strip())
k = n.bit_length()
decimal.getcontext().prec = k

r.sendline('p')
r.readuntil('flag is ')
c = int(r.readline().strip())

r.sendline('e 2')
r.readuntil('> ')
p2 = int(r.readline().strip())

lower = decimal.Decimal(0)
upper = decimal.Decimal(n)

p = p2

for i in xrange(k):
    mid = (lower + upper) / 2
    r.sendline('d ' + str(c * p % n))
    r.readuntil('> ')
    cur = int(r.readline().strip())
    if cur % 2 == 0:
        upper = mid
    else:
        lower = mid
    p = p * p2 % n
    print(int(upper))
print long_to_bytes(int(upper))
r.interactive()
