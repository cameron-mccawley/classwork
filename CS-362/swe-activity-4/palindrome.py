def palindrome(s):
    return s.lower() == s[::-1].lower()

if __name__ == "__main__":
    string = input("Please enter a string: ")
    out = palindrome(string)


    if out:
        print("Yes")
    else:
        print("No")