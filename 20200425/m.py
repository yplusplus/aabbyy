def test(s, a, b):
    res = len(s)
    if a not in s: res = res + 1;
    if b not in s: res = res + 1;
    return res

if __name__ == "__main__":
    cnt = 0
    ans = 0
    elements = set()
    while True:
        a = raw_input()
        if a == "-1": break;
        a, b = a.split(' ')[0:2]
        if cnt + 1 != test(elements, a, b):
            elements.add(a)
            elements.add(b)
            cnt = cnt + 1
        else:
            ans = ans + 1
    print ans
