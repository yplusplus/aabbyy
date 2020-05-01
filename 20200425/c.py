def check(s):
    words = s.split(' ')
    count = {}
    for w in words:
        if w in count:
            count[w] = count[w] + 1
        else:
            count[w] = 1

    cnt = 0
    for k, v in count.items():
       if v == 1:
           cnt = cnt + 1
    #print count
    if cnt * 2 >= len(words):
        return True

    return False

if __name__ == '__main__':
    while True:
        s = raw_input()
        if s == "#": break
        ok = check(s)
        print "yes" if ok else "no"

