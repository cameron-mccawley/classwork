import random
import sys
import time

def insertSort(arr):
    for i in range(1, len(arr)):
        key = arr[i]

        j = i-1
        while j >= 0 and key < arr[j]:
            arr[j+1] = arr[j]
            j -= 1
        arr[j+1] = key


if __name__ == "__main__":

    n = [5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000]
    #n = [200000]
    for num in n:
        arr = []
        for i in range(0, num):
            elem = random.randint(1, 10000)
            arr.append(elem)

        start = time.clock()
        insertSort(arr)
        end = time.clock()

        print("n = " + str(num) + " - Total excecution time: " + str(end - start) + " seconds")
