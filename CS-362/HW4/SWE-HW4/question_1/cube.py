
def calculate_volume(l, w, d):
    return l*w*d

if __name__ == "__main__":
    l = float(input("Please enter a length: "))
    w = float(input("Please enter a width: "))
    d = float(input("Please enter a depth: "))
    volume = calculate_volume(l, w, d)
    print("Result is: " + str(round(volume, 2)))