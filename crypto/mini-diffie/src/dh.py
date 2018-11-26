def main():
    flag = 'GuardianCTF{prime_factor}'
    k = int(''.join([str(ord(c)) for c in flag])) // 25
    p = 26 * k
    g = 3
    gap = 25 * k
    gbp = 7 * k
    print(f'p : {p}')
    print(f'g^a mod p : {gap}')
    print(f'g^b mod p : {gbp}')

    b = 5
    s = pow(gap, b, p)
    print(s)


if __name__ == '__main__':
    main()
