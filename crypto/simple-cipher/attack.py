from pwn import *
context.log_level = 'debug'

def egcd(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = egcd(b % a, a)
        return (g, x - (b // a) * y, y)

def modinv(a, m):
    g, x, y = egcd(a, m)
    if g != 1:
        raise Exception('modular inverse does not exist')
    else:
        return x % m

def v(c):
    return ord(c) - ord('a')

def trans(c, a, b):
    ainv = modinv(a, 26)
    if not c.isalpha():
        return c
    return chr(((v(c) + 26 - b) * ainv) % 26 + ord('a'))

def enc(s, a, b):
    return ''.join(map(lambda x: trans(x, a, b), s))

r = remote('localhost', 9999)
for i in xrange(100):
    r.readuntil('100\n')
    c = r.readline().strip()
    found = False
    for a in xrange(1, 26):
        if egcd(a, 26)[0] != 1:
            continue
        for b in xrange(26):
            m = enc(c, a, b)
            if m.find('lorem') != -1:
                print 'wow'
                print m, a, b
                found = True
                break
        if found:
            break
    r.sendline(m)

r.interactive()
