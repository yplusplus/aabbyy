if __name__ == '__main__':
    n = input()
    project = []
    for i in range(0, n):
        project.append(map(int, raw_input().split(' ')))
    project.sort(key=lambda x: -x[1])
    ans = 0
    cur = 0
    for p in project:
        cur = cur + p[0]
        if cur + p[1] > ans: ans = cur + p[1]
    print "Project %d: %d" %(len(project), ans)
