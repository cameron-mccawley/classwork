#Cameron McCawley - 933671391
#Leap year program

def leap_year(year):
    if(year % 4 == 0):
        if(year % 100 == 0):
            if(year % 400 == 0):
                return True
            else:
                return False
        else:
            return True
    else:
        return False

#start of program
if __name__ == "__main__":

    #prompt user for year
    year = input("Please enter a year: ")
    year = int(year)
    isLeapYear = leap_year(year)
    if(isLeapYear):
        print(str(year) + " is a leap year")
    else:
        print(str(year) + " is not a leap year")



