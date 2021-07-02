
def generate_name(first, last):
    return first + " " + last


if __name__ == "__main__":
    first = input("Please enter your first name: ")
    last = input("Please enter your last name: ")
    print("Full name is: " + generate_name(first, last))