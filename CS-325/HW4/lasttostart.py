#Greedy activity selector using start-last method
# Based on CRLS chapter 16.1 algorithm
def activity_selector(acts):
    selectedActivity = []
    insertion_sort(acts, key=lambda x: x['start']) #sort by starting time increasing
    
    activityTime = max([x['finish'] for x in acts]) #find max (used as the first appended to solution)

    while acts:
        act = acts.pop()
        if act['finish'] <= activityTime: #Is is compatible?
            selectedActivity.append({
                'index': act['index'],
                'start': act['start']
            })
            activityTime = act['start']

    return selectedActivity

#Insertion sort for dictionaries O(n^2)
#didnt use merge sort because that's really hard with dictionaries 
def insertion_sort(list, *, key):
    for i in range(1, len(list)): #loop invariant is stored
        d = list[i]
        for j in range(i-1, -1, -1):
            if key(list[j]) <= key(d):
                break
            list[j+1] = list[j]
        else:
            j-=1
        list[j+1] = d
            
#File IO and dictionary manipulation
if __name__ == "__main__":
    f = open("act.txt", "r")

    lines = f.read().splitlines()
    lines.append("0") #for the last activity set
    
    actSets = []
    act = []

    #Go through each line, if line is length of 1, then everything before it can be added as an activity
    for line in lines:
        line_arr = []
        for num in line.split(" "):
            line_arr.append(int(num))
            
        if len(line_arr) == 1 or line_arr == 0:
            if len(act):
                actSets.append(act)
                act = []
        else:
            #use a dictionary to hold activity data
            act.append({
                'index': line_arr[0],
                'start': line_arr[1],
                'finish': line_arr[2]
            })


    #print results
    n = 1
    for sets in actSets:
        print("Set " + str(n))
        selected = activity_selector(sets)
        insertion_sort(selected, key=lambda x: x['start']) # This is just to reverse the array so that it prints in the correct order
        print("Number of activities selected = " + str(len(selected)))
        print("Activities: " + (" ".join([str(x['index']) for x in selected])) + "\n")
        n += 1
    