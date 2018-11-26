from pwn import *

table = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~'

header = 'A' * 11
footer = 'A'
injected_index = 2

result = 'AAAAAA secret: '
footer = 'AAAAAA' + 'A' * 16
offset = len(result)

def gen_msg(x, code):
    message = '''Agent,
Greetings. My situation report is as follows:
{0}
My agent identifying code is: {1}.
Down with the Soviets,
006
'''.format(x, code)
    return message

'''
guardian-auth-to
ken: AAAAAAAAAAA
AAAAA secret: ?A
AAAAAAAAAAAAAAAA
AAAAA secret: F
'''
'''
Agent, Greetings
. My situation r
eport is as foll
ows: AAAAAAAAAAA
de is: picoctf{?
AAAAAAAA My agen
t identifying co
de is: picoctf{?
'''

'''
Agent, Greetings
. My situation r
eport is as foll
ows: AAAAAAAAAAA
de is: picoCTF{0
AAAAAAAA My agen
t identifying co
de is: picoCTF{C
ODE.  Down with the Soviets,
006

'''


prev = ''

i = len(prev)
result += prev

def split(d, n):
    result = []
    while True:
        cur = d[:n]
        if cur == '':
            break
        result.append(cur)
        d = d[n:]
    return result


r = remote('ctf.snucse.org', 40002)
while '}' not in result:
    for c in string.printable:
        found = False
        while True:
            try:
                cur = header + result[-15:] + c + 'A' * (16 - i % 16)
                cur += footer
                r.sendlineafter('name?> ', cur)
                r.readuntil('your token is b\'')
                data = r.readline().strip()[:-1]
                block = data[injected_index*32:(injected_index+1)*32]
                data = data[(injected_index+1)*32:]
            except EOFError:
                pass
            break

        if block in split(data, 32):
            result += c
            found = True
            break
    if not found:
        print i
        exit()
    print result[offset:]
    i += 1
print result[offset:]
