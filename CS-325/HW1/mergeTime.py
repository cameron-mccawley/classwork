import random
import time
import sys

def mergeSort(arr):
    if len(arr) > 1:
        mid = len(arr)//2    
        left = arr[:mid]
        right = arr[mid:]

        mergeSort(left)
        mergeSort(right)

        i = j = k = 0

        while i < len(left) and j < len(right):
            if left[i] < right[j]:
                arr[k] = left[i]
                i += 1
            else:
                arr[k] = right[j]
                j += 1
            k += 1

        while i < len(left):
            arr[k] = left[i]
            i += 1
            k += 1

        while j < len(right):
            arr[k] = right[j]
            j += 1
            k += 1


if __name__ == "__main__":
    
    n = [5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000]
    #n = [200000]
    for num in n:
        arr = []
        for i in range(0, num):
            elem = random.randint(1, 10000)
            arr.append(elem)

        start = time.clock()
        mergeSort(arr)
        end = time.clock()

        print("n = " + str(num) + " - Total excecution time: " + str(end - start) + " seconds")



