def printDivisors(n) :
    i = 1
    while i <= n :
        if (n % i==0) :
            print(str(i) + ", ", end='')
        i = i + 1

def main():
    print("Please enter a number: ")
    num = input()
    printDivisors(int(num))

if __name__ == "__main__":
    main()