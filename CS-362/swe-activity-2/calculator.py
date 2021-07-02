def add(x, y):
    return x+y

def sub(x, y):
    return x-y

def mult(x, y):
    return x*y

def div(x, y):
    return x/y

def main():
    print("Select operation: +, -, *, /")
    while True:
        operator = input()
        if operator in ('+', '-', '*', '/'):
            num1 = float(input("Enter first number: "))
            num2 = float(input("Enter second number: "))

            if operator == '+':
                print(num1, "+", num2, "=", add(num1, num2))

            elif operator == '-':
                print(num1, "-", num2, "=", sub(num1, num2))

            elif operator == '*':
                print(num1, "*", num2, "=", mult(num1, num2))

            elif operator == '/':
                print(num1, "/", num2, "=", div(num1, num2))
            break
        else:
            print("Invalid input")

if __name__ == "__main__":
    main()