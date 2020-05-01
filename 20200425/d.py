if __name__ == '__main__':
    n = input()
    a = raw_input().split(' ')
    que= [[], [], []]
    i = 0
    for p in a:
        que[i % 3].append(p)
        i = i + 1

    for i in range(0, 3):
        print ' '.join(que[i])


