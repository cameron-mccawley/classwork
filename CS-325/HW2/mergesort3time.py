import random
import time
import sys


def mergeSort3(arr, start, end):
    if len(arr[start-1:end]) < 2:
        return arr
    else:
        m1 = start + ((end-start) // 3) #get start of each section
        m2 = start + 2 * ((end-start) // 3)
    
        mergeSort3(arr, start, m1) #divide
        mergeSort3(arr, m1+1, m2+1)
        mergeSort3(arr, m2+2, end)

        merge(arr, start, m1, m2, end) #conquor 
        return arr

def merge(arr, start, m1, m2, end):
        left = arr[start-1:m1]
        mid = arr[m1:m2+1]
        right = arr[m2+1:end]

        left.append(float('inf')) #append infinity so we have a true max to compare to
        mid.append(float('inf'))
        right.append(float('inf'))

        il = im = ir = 0

        for i in range(start-1, end):
            minimum = min(left[il], mid[im], right[ir])
            if minimum == left[il]:
                arr[i] = left[il]
                il += 1
            elif minimum == mid[im]:
                arr[i] = mid[im]
                im += 1
            else:
                arr[i] = right[ir]
                ir += 1


if __name__ == "__main__":
    samples = 20      # this is how many times we should run each iteration and take the average
    n = [5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000]
    for num in n:
        diff = 0
        for x in range(samples):
            arr = []
            for i in range(0, num):
                elem = random.randint(1, 10000)
                arr.append(elem)

            start = time.clock()
            mergeSort3(arr, 1, len(arr))
            end = time.clock()
            diff += (end - start) 
        diff /= samples #take the avgerage 
        print("n = " + str(num) + " - Total execution time on average: " + str(diff) + " seconds")
