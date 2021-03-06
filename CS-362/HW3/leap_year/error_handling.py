#Cameron McCawley - 933671391
#Leap year program with error handling

#Function that prints whether or not the year is a leap year
def printIfLeapYear(isLeapYear, year):
    if(isLeapYear):
        print(str(year) + " is a leap year")
    else:
        print(str(year) + " is not a leap year")

#start of program
if __name__ == "__main__":

    #prompt user for year and do error handling
    while(True):
        try:
            year = input("Please enter a year: ")
            year = int(year)
            break
        except ValueError:
            print("Not a valid integer! Please try again...")

    if(year % 4 == 0):
        if(year % 100 == 0):
            if(year % 400 == 0):
                printIfLeapYear(True, year)
            else:
                printIfLeapYear(False, year)
        else:
            printIfLeapYear(True, year)
    else:
        printIfLeapYear(False, year)