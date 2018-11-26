from Crypto.PublicKey import RSA
from Crypto.Util.number import long_to_bytes, bytes_to_long

privkey = RSA.generate(1024)
pubkey = privkey.publickey()
with open('./flag', 'rt') as f:
    flag = f.read().strip().encode('utf-8')

def enc(s):
    return pubkey.encrypt(s % privkey.n, 0)[0]

def dec(c):
    return privkey.decrypt(c % privkey.n)

C = enc(bytes_to_long(flag))

print(f'n is {privkey.n}')
while True:
    select = input('[p]rint flag\n[e]ncrypt\n[d]ecrypt\n> ')
    c = select[0]
    if c == 'p':
        print(f'flag is {C}')
        continue
    arg = select.strip().split()[-1]
    if c == 'e':
        print(f'{enc(int(arg))}')
    elif c == 'd':
        if int(arg) == C:
            exit()
        print(f'{dec(int(arg))}')
    else:
        exit()
