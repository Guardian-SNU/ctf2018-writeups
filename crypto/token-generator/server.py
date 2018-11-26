from Crypto.Cipher import AES
import binascii

with open('flag', 'rt') as f:
    flag = f.read().strip()

with open('key', 'rt') as f:
    key = binascii.unhexlify(bytes(f.read().strip().encode('ascii')))

def pad(s):
    pad_len = 16 - len(s) % 16
    return s + (chr(pad_len) * pad_len).encode('latin-1')

def enc(s):
    cipher = AES.new(key,AES.MODE_ECB)
    return cipher.encrypt(pad(s))

print('guardian token service')
while True:
    name = input(f'name?> ')
    auth_token = f'guardian-auth-token: {name} secret: {flag}'.encode('latin-1')
    print(f'your token is {binascii.hexlify(enc(auth_token))}')
