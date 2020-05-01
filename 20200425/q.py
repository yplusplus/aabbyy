if __name__ == '__main__':
    lst = [0, 1, 2]
    while len(lst) <= 40:
        lst.append(lst[-1] + lst[-2])
    while True:
        try:
            n = input()
            print lst[n]
        except EOFError:
            break

