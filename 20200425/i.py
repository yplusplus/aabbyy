if __name__ == '__main__':
    n = input()
    grade = []
    for i in range(0, n):
        g = map(int, raw_input().split(' '))
        g.append(sum(g))
        g.insert(0, i + 1)
#print g
        grade.append(g)

    grade.sort(key=lambda g: (-g[4], -g[1], -g[2], -g[3], g[0]))
#print grade
    for i in range(0, 5):
        print ' '.join(map(str, grade[i][0:-1]))
