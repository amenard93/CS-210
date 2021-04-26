
# Andrew Menard
# 04 / 23 / 2021
# Project 3
# CS210
#
# This is the source Python file for the grocery tracker program.
# The purpose of this application is to track how frequently grocery items
# are purchasedand see how frequently specific items are purchased.
# The three main functions are responsible for:
# - Reading the input file and listing each grocery item with the frequency of purchase
# - Taking user input (from c++) and showing frequency of purchase of specific user named item
# - Writing list of grocery items and their frequencies to a  new file to be used with c++ function

import re
import string


# Reads the input file and lists each grocery item with the frequency of purchase 
def ListOccurances():  
    text = open("InputP3.txt", "r")
    d = dict()
    # Open the file in read mode
  
    # Loop through each line of the file
    for line in text:
        # Remove the leading spaces and newline character
        line = line.strip()
  
        # Convert the characters in line to 
        # lowercase to avoid case mismatch
        line = line.lower()
  
        # Split the line into words
        words = line.split(" ")
  
        # Iterate over each word in line
        for word in words:
            # Check if the word is already in dictionary
            if word in d:
                # Increment count of word by 1
                d[word] = d[word] + 1
            else:
                # Add the word to dictionary with count 1
                d[word] = 1
  
    # Print the contents of dictionary
    for key in list(d.keys()):
        print(key, ":", d[key])

    text.close()



# Takes user input (from c++) and shows frequency of purchase of specific user named item
def FrequencyOfItem(item):
    text = open("InputP3.txt", "r")
    d = dict()
    # Open the file in read mode

    # Loop through each line of the file
    for line in text:
        # Remove the leading spaces and newline character
        line = line.strip()

        # Convert the characters in line to
        # lowercase to avoid case mismatch
        line = line.lower()

        # Split the line into words
        words = line.split(" ")

        # Iterate over each word in line
        for word in words:
            # Check if the word is already in dictionary
            if word in d:
                # Increment count of word by 1
                d[word] = d[word] + 1
            else:
                # Add the word to dictionary with count 1
                d[word] = 1

    if item in d:
        return d[item]
    else:
        return -1

    text.close()

# Writes list of grocery items and their frequencies to a  new file to be used with c++ function    
def Histogram():  
    text = open("InputP3.txt", "r")
    d = dict()
    # Open the file in read mode
  
    # Loop through each line of the file
    for line in text:
        # Remove the leading spaces and newline character
        line = line.strip()
  
        # Convert the characters in line to 
        # lowercase to avoid case mismatch
        line = line.lower()
  
        # Split the line into words
        words = line.split(" ")
  
        # Iterate over each word in line
        for word in words:
            # Check if the word is already in dictionary
            if word in d:
                # Increment count of word by 1
                d[word] = d[word] + 1
            else:
                # Add the word to dictionary with count 1
                d[word] = 1
  
    # writes to new file 
    with open('frequency.dat', 'w') as out_file:
    	for key in list(d.keys()):
    		print(key, d[key], file=out_file)