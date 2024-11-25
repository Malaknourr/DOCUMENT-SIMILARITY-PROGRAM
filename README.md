# Document Similarity Program - README
## Overview
- This program analyzes and compares two sets of words (or "string sets") to measure their similarity. The application allows users to load text from files or input strings manually, and it supports various operations such as tokenization, similarity computation, union, and intersection.

## Features
1 Tokenize strings or files into unique words.
2 Remove punctuation and convert all characters to lowercase for uniformity.
3 Perform operations like addition, removal, and clearing of words in string sets.
4 Calculate similarity between two sets using cosine similarity.
5 Compute union and intersection of two string sets.
6 Interactive menu-driven interface with demo examples.
7 Installation
8 Ensure you have a C++ compiler installed (e.g., GCC).
9 Save the program file as DocumentSimilarity.cpp.
10 Compilation

### Menu Options
Load Files: Load two text files as input for comparison.
Enter Text: Input two strings manually for comparison.
Run Demo Test Cases: Use predefined example strings for demonstration.
Exit: Close the program.
Operations on String Sets
Once initialized, the following operations are available:
Display tokens in Set 1 or Set 2.
Add new words to a set.
Remove specific words from a set.
Clear all tokens from a set.
Compute similarity between the two sets.
Compute the union of the two sets.
Compute the intersection of the two sets.
Exit to the main menu.
Demo Example
Select the "Run Demo Test Cases" option to see an automated demonstration of the program's features using example inputs.

#### Key Methods
processWord: Removes non-alphabetic characters and converts to lowercase.
stringFilter: Ensures unique tokens in a vector.
addStrings: Adds new tokens to the set.
removeStrings: Removes specific tokens from the set.
operator+: Returns the union of two sets.
operator*: Returns the intersection of two sets.
similarity: Computes cosine similarity between two sets.
Main Program
Provides an interactive menu for the user.
Handles file reading and text input.
Demonstrates operations through user input or predefined demo cases.
