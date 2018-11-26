import random

m = '''Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.'''.lower().split()

with open('./flag', 'rt') as f:
    flag = f.read().strip()

def v(c):
    return ord(c) - ord('a')

def trans(c, a, b):
    if not c.isalpha():
        return c
    return chr((v(c) * a + b) % 26 + ord('a'))

def enc(s, a, b):
    return ''.join(map(lambda x: trans(x, a, b), s))

def gcd(a, b):
    if b == 0:
        return a
    return gcd(b, a % b)

def gen_rand_key():
    while True:
        a = random.randint(1, 25)
        if gcd(a, 26) == 1:
            break
    b = random.randint(0, 25)
    return a, b

rounds = 5

for i in range(rounds):
    random.shuffle(m)
    cur = ' '.join(m)
    print(f'round {i + 1} / {rounds}')
    a, b = gen_rand_key()
    c = enc(cur, a, b)
    print(f'{c}')
    guess = input('give me original message> ').strip()
    if guess != cur:
        exit()

print(f'flag is {flag}')
