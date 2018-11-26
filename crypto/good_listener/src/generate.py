from hangul_utils import split_syllable_char, split_syllables
import random


def generate(flag):
    cho_sung = {
        'ㄱ': 'k',
        'ㄴ': 'u',
        'ㄷ': 'i',
        'ㄹ': 'm',
        'ㅁ': 'y',
        'ㅂ': 'o',
        'ㅅ': 'n',
        'ㅇ': 'j',
        'ㅈ': 'l',
        'ㅊ': 'hl',
        'ㅋ': 'hk',
        'ㅌ': 'hi',
        'ㅍ': 'ho',
        'ㅎ': 'h',
        'ㅆ': 'nn',
        'ㄸ': 'ii',
        'ㄲ': 'kk',
        'ㅉ': 'll',
    }
    jung_sung = {
        'ㅏ': 'f',
        'ㅑ': '.g',
        'ㅓ': 'r',
        'ㅕ': 't',
        'ㅗ': 'v',
        'ㅛ': '.v',
        'ㅜ': 'b',
        'ㅠ': '.b',
        'ㅡ': 'g',
        'ㅣ': 'd',
        'ㅐ': 'fd',
        'ㅔ': 'c',
        'ㅟ': 'bd',
        'ㅘ': 'vf',
        'ㅚ': 'vd',
        'ㅢ': 'gd',
        'ㅝ': 'vr',
    }
    jong_sung = {
        'ㄱ': 'x',
        'ㄴ': 's',
        'ㄷ': ';z',
        'ㄹ': 'e',
        'ㅁ': 'z',
        'ㅂ': 'w',
        'ㅅ': 'q',
        'ㅇ': 'a',
        'ㅈ': ';e',
        'ㅊ': ';q',
        'ㅋ': ';x',
        'ㅌ': 'sz',
        'ㅍ': ';w',
        'ㅎ': ';s',
        'ㅆ': ';',
        'ㄶ': 'sa',
        'ㅄ': 'wq',
    }
    key_list = list()
    for c in flag:
        try:
            jamo = split_syllable_char(c)
            if len(jamo) == 2:
                k1, k2 = cho_sung[jamo[0]], jung_sung[jamo[1]]
                key_list += [k1, k2]
            else:
                k1, k2, k3 = cho_sung[jamo[0]], jung_sung[jamo[1]], jong_sung[jamo[2]]
                key_list += [k1, k2, k3]
        except ValueError:
            if c == ' ' or c == '\n':
                key_list.append(c)
            else:
                assert False, '"{}" is invalid'.format(c)
    keyset = list(set(''.join(key_list)))
    sound_map = {k: i for i, k in enumerate(keyset)}
    msg = '-'.join(['{:02x}'.format(sound_map[c]) for c in ''.join(key_list)])
    with open('keystroke.txt', 'wt') as f:
        f.write(msg)

if __name__ == '__main__':
    with open('flag.txt', 'rt') as f:
        flag = f.read().strip()
    generate(flag)
