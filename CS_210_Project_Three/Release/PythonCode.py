import re
import string

def Read():
    # this is an internal function to read the text file 'InputFile' and parse the data into a dictionary for use
    # in other functions
    with open('InputFile.txt', 'r') as reader:
        #after opening, place items into a list
        lines = [line.rstrip() for line in reader]
        # create a dictionary based on the number of times an item appears using the list we just made
        groceries = {x:lines.count(x) for x in lines}
        #print(groceries)
        return groceries

def LookFor(s):
    #copy the dictionary made from our file
    groceries = Read()
    if s in groceries:
        # if our search term from C++ is in our dictionary, this will cast the value to an int, then return the value
        # for C++ to use later
        # case sensitiviy is handled in the C++, so it isn't checked for in here, since the items in the text file
        # all had their first character capitalized, and that was carried over in our generated dictionary
        value = int(groceries[s])
        return value
    else:
        # if the term isnt in the dictionary, return 0, letting C++ know nothing was found with that term
        value = 0
        return value

def PrintItems():
    # copy dictionary of items and quantities
    groceries = Read()
    #iterate through the dictionary to print out each item and quantity
    for key in groceries:
        print(key, ': ', groceries[key])

def MakeFile():
    # copy dictionary
    groceries = Read()
    # iterate over dictionary, writing key and value each to a line
    with open("frequency.dat", 'w') as writer:
        for key, value in groceries.items():
            writer.write('%s %s\n' % (key, value))
    return 0