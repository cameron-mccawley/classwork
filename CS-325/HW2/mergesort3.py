
def mergeSort3(arr, start, end):
    if len(arr[start-1:end]) < 2:
        return arr
    else:
        m1 = start + ((end-start) // 3)   #get posistion of each third of array
        m2 = start + 2 * ((end-start) // 3)
    
        mergeSort3(arr, start, m1)      #recurse each section
        mergeSort3(arr, m1+1, m2+1)
        mergeSort3(arr, m2+2, end)

        merge(arr, start, m1, m2, end)  #merge together
        return arr

def merge(arr, start, m1, m2, end):
        left = arr[start-1:m1]
        mid = arr[m1:m2+1]
        right = arr[m2+1:end]

        left.append(float('inf'))  #need to append infinity so we always have a max at the end to compare to in the following loop
        mid.append(float('inf'))
        right.append(float('inf'))

        il = im = ir = 0

        for i in range(start-1, end):
            minimum = min(left[il], mid[im], right[ir]) #get lowest elem of the three sections at specific index
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

    f = open("data.txt")

    for line in f:
        arr = list(map(int, line.split(" "))) 
        length = arr.pop(0)                  #pop the first elem of the array (the length) into a variable
        mergeSort3(arr, 1, length)
        
        for i in range(length):
            print(arr[i], end = " ")
        print()
