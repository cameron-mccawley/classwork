def count_words(s):
    return len(s.split())

if __name__ == "__main__":
    string = input("Please enter a sentence: ")

    print("Number of words is " + str(count_words(string)))