
def get_average(lst):
    return sum(lst)/len(lst)

if __name__ == "__main__":
    list = [0.00000001,  2.0000300000001, 0.000004323444, 0.003233333, 0.1]
    average = get_average(list)
    print(average)