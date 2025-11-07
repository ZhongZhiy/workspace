t = int(input())
while t >= 1:
    n = int(input())
    a = list(map(int, input().split()))
    cnt = 0
    for i in range(1, 101):
        if a.count(i) > 2:
            cnt+=1
    print(cnt)

