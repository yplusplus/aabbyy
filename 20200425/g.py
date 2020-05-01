if __name__ == '__main__':
    n = input()
    cash = raw_input().split(' ')
    count = {}
    for c in cash:
        if c in count:
            count[c] = count[c] + 1
        else:
            count[c] = 1
     
    cnt = 0
    ans = ''
    for k, v in count.items():
        if v > cnt:
            ans = k
            cnt = v

    print ans
