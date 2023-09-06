# !/usr/bin/env python3
def main():
    n = 0 
    while True:
        if 8*(n**2) < n**3:
            print(n)
            break
        n += 1
    

if __name__ == '__main__':
    main()