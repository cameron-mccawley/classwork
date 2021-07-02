import random
import string

def getPassword(length):
    letters = string.ascii_lowercase + string.digits + string.punctuation
    result = ''.join(random.choice(letters) for i in range(length))
    print("Password is: " + result)

def main():
    print("Please enter a password length ")
    length = input()
    getPassword(int(length))


if __name__ == "__main__":
    main()