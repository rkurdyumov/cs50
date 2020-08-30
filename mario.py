while (True):
    try:
        n = int(input("Height: "))
        if n >= 1 and n <= 8:
            break
    except:
        continue

for i in range(1, n + 1):
    print(" " * (n - i) + "#" * i + "  " + "#" * i)
