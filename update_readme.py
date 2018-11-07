#!/usr/bin/python
import os

rootdir = '.'

def encode(string):
    try:
        string.decode('utf8')
        return string
    except:
        pass
    try:
        string = string.decode('gbk')
        return string.encode('utf-8')
    except:
        return 'unknown encoding'

def walk():
    training = []
    files = os.listdir(rootdir)
    for d in files:
        path = os.path.join(rootdir, d)
        if not os.path.isdir(path):
            continue
        txt = os.path.join(path, 'readme.txt')
        md = os.path.join(path, 'readme.md')
        readme_path = ''
        if os.path.exists(txt):
            readme_path = txt
        elif os.path.exists(md):
            readme_path = md
        else:
            continue
        with open(readme_path) as f:
            training.append((d, f.read()))
    return training

def main():
    training = walk()
    readme = os.path.join(rootdir, 'readme.txt')
    contests = []
    for t in training:
        date, contest = t
        date.strip()
        contest.strip()
        contest = encode(contest).strip('\r\n')
        contests.append((date, contest))

    contests.sort()
    with open(readme, 'w') as f:
        for date, contest in contests:
            print >> f, date, '\t', contest
            print date, '\t', contest

if __name__ == '__main__':
    main()
