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
    readme = os.path.join(rootdir, 'readme.md')
    with open(readme, 'w') as f:
        for t in training:
            date, contest = t
            date.strip()
            contest.strip()
            contest = encode(contest).strip('\r\n')
            print >> f, date, '\t', contest
            print date, contest.__repr__()

if __name__ == '__main__':
    main()
