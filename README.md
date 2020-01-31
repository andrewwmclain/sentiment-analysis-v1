# LAB 2 - Semantic Analysis, Part 1

**_Sentiment Analysis_** -  “The process of computationally identifying and categorizing opinions expressed in a piece of  text, especially in order to determine whether the writer's attitude towards a particular topic, product, etc. is positive, negative, or neutral.”  - Oxford Dictionaries.

## Goal
Write a C++ program that reads a file of movie reviews extracted from the Rotten Tomatoes movie website and uses it to build a database containing the words found in the file.   Your program will use this database to tell you whether a word indicates a generally positive, negative, or neutral sentiment.  This assignment will give you 1) more practice working with the `string` class, 2) practice working with 1-dimensional arrays,  3) experience reading text files, 4) allow you to implement the word database as an abstract data type (ADT). 

## Sample Run

Here are screen shots of two sample runs:

![Sample Run1](/images/SentimentAnalysis-p1-image1.png)

![Sample Run2](/images/SentimentAnalysis-p1-image2.png)

The program starts by prompting for the name of a file.  The file **aFewReviews.txt** was entered for the first run.  In the second run, a blank line was entered, indicating that the program should use the file called **movieReviews.txt**, which is much larger.     Both files are supplied with this assignment.

The program will build the database from the information in the file.  Afterwards, it prints out how long this process takes.  Your times will likely differ from the ones shown in the screenshots.

To give you some idea of whether your database implementation is correct, the program also prints summary information about the database.  The information your implementation prints should match what you see.

The program then enters a loop where the user is repeatedly prompted to enter a word.  For each word the user entered, the program responds by printing its occurrence and average score.  When a blank line is entered, the program terminates.

## How it works

The file **aFewReviews.txt** looks like this:

![aFewReviews.txt](/images/SentimentAnalysis-p1-image3.png)

It contains only three lines – the first and third lines are word wrapped in the screen shot because of their length.  Each line starts with an integer rating for a movie, followed by the text of the review.  The name of the movie is not given, because that isn’t important for what we are doing.

When the program opens a movie review file, it reads it line by line.  First it reads the numerical rating (score) and then in breaks the rest of the line into “words.”  For example, the eleven “words” it finds on the second line  would be the following:

* *This*
* *quiet*
* *,*
* introspective*
* *and*
* *entertaining*
* *independent*
* *is*
* *worth* 
* *seeking*
* *.*

Note that a comma by itself or a period by itself is treated as a “word.”  If there were no blank characters between the letters of a word and the punctuation mark, then the letters and the punctuation mark together would form a “word.”  Blank characters are used to break the string into words, but the blanks themselves never are “words” themselves.

Each time the program encounters a “word” it will record it in your in-memory “word database.” This database keeps track of how many times each word is seen (occurrence count) and maintains a running total of rating numbers (score total).

For example,
*	the word *escapades* is found once in the first review and nowhere else.  It would be recorded in the database with occurrence count of 1 and score total of 1 since the review it appeared once in a review that had rating 1.  Its average rating is 1/1 = 1.
*	the word *introspective* is found once in the second review and nowhere else.  It would be recorded in the database with occurrence count of 1 and score total of 4 since the review it appeared in had rating 4. Its average rating is 4/1 = 1.
*	The word *is* appears twice in the first review, and once in the second review.  Hence it will be stored in the database with occurrence count 3, and the score total will be 1+1+4 = 6.  Its average rating is 6/3 =2.
*	The words *This* and *this* (case matters!) each appear once.  “This” appears on line 2 which has a rating of 4, so its average score is 4.  “this” appears on line 1 which has a rating of 1, so its average score is 1.
*	The word *beautiful* does not appear on any line.  It is not stored in the database, but when you query for its rating, the neutral rating of 2.0 is displayed.

<!--
In general:

![formula1](https://latex.codecogs.com/gif.latex?score%28word%29%3D%5Csum_%7Bline%7D%7Bscore_%7Bline%7D*occurrences%28word%29_%7Bline%7D%7D)

Where:

 Variable | Description
 ---|---
 ![formula2](https://latex.codecogs.com/gif.latex?score_%7Bline%7D) | Is the score of the line you are currently reading
 ![formula3](https://latex.codecogs.com/gif.latex?occurences(word)_%7Bline%7D) | Is the number of occurrences of that word on the line
 
 For a given word, you read all the lines and calculate the value for each line and add them together. You will need to do this for each word.

-->

## Files you are given
In this lab, you are given all the files you will need for your CLion project.  

* **CMakeLists.txt** - This contains the information necessary to build the project.  This file should not be modified.

*	**main.cpp** – This file contains a completed `main` routine (which should not be modified) and a skeleton of the function `BuildDatabase` that you need to write.

*	**database.h** – This file has been completed for you.  It declares the four database interface functions used to access the database ADT.  These functions will be implemented in **database.cpp**.  This file should not be modified.

*	**database.cpp** – Except for `#include` and the definition of the constant neutral, the rest of this file’s implementation is left up to you.  You should finish the header comment for the file and add implementations for the four database interface functions.   Make sure a header comment precedes each of these four functions. 

##	Recommended first step

It is strongly recommended that you start by stubbing out the four functions in **database.cpp**.  In other words, add a skeleton implementation of each function to **database.cpp**.  That way your project will build, because right now the link step will fail with undefined references.

When you stub out `AddWordToDatabase` it would be a very good idea to have it temporarily print a line that said it was called and the values of the word and score parameters.  That will make it easier for you to check that your implementation of `BuildDatabase` is working correctly.

## Implementing `BuildDatabase`

When you write the function `BuildDatabase` you get another chance to develop your skill in using the `string` class.  In addition, you will practice reading from a text file.  Here’s a rough sketch of what you need to do:

1.	Open the file for reading.  You should check whether the file can be opened.  If not, you should print an informative message that includes the file name and return `false`.

2.	Call `InitDatabase` to initialize the database.  

3.	Begin a loop that continues until you hit the end of the file.  On each iteration of the loop

  *	Get the numerical score
  *	Get the rest of the line
  *	Break this line into “words”.  For each “word” you see, call `AddWordToDatabase` to record the “word” and associated score in the database.  
  HINT: there are multiple correct ways to write this logic, but you may want to consider using an `istringstream` object.

Before going further, spend enough time to check carefully that you are calling `AddWordToDatabase` with the correct words.

Here’s the start of what you might see with a correct implementation of `BuildDatabase`, and a stubbed implementation of `AddWordToDatabase` that prints a message showing the values of the parameters `word` and `score`:

![BuildDatabase](/images/SentimentAnalysis-p1-image4.png)

Don’t forget to check the return value of `AddWordToDatabase`.  If it returns `false`, then you need to stop building the database and return `false`.

Note: the following parameters passed into `BuildDatabase`: `capacity`, `words`, `counts`, `scores`, and `size` are part of the database ADT.  You will pass them as parameters to `InitDatabase` and `AddWordToDatabase`, but you must not examine or modify their values when you implement `BuildDatabase`, you may only call the functions of the ADT (the functions on `database.h`.  Doing so would violate the rules of it being an ABSTRACT data type.

## Implementing the database

You will be using three parallel arrays: `words`, `counts`, and `scores` to implement your database.   In this assignment, the `words` array will not be sorted.

The memory space for these arrays has been declared within the main function, and these arrays along with their capacity (the maximum number of words that can be stored in each array) and their current size (the number of words currently stored) are passed to the database interface functions in almost every call.

Yes, passing all these variables as parameters makes the code awkward!  One way to eliminate it would be to use global variables.  But we're not going to use global variables.  As we go through the course, we'll see how to clean this up.  For instance, in the next lab you will see how if we use a `struct` we will only have to pass one parameter.  Later in the course, when we learn how define our own classes, we won't have to pass any parameters!

Here are some notes about implementing each of these functions:

1.	`InitDatabase`

This function must be called once before adding words to the database.  All it needs to do is set the number of entries stored in the database to zero.


2.	`AddWordToDatabase`

This function first iterates through the `words` array to determine if `word` already appears in the array.  If it does, it increments the corresponding occurrence count by 1, adds the score to the score total, and returns true.
    If it does not find word in the `words` array, it will make sure that the number of elements stored has not reach its maximum.  If this is the case, it simply returns `false` to signal failure. 

Otherwise, it will add `word` to the end of the `words` array, add 1 to the end of the occurrence counts array, and add `score` to the end of the score totals array.  Don’t forget to increase the count of elements in the array that are filled!  You should return `true` to indicate success.

3. `FindWordInDatabase`

This function will iterate through the `words` array to determine if `word` appears in the array.  If it is found, it returns count of occurrences in the `occurrences` parameter, and the average score in `averageScore` parameter.  If it is not found, `occurrences` should be set to 0 and `averageScore` to `neutral`.

4. `GetInfoAboutDatabase`

This function will iterate through the entire database and keep track of the minimum and maximum count of occurrences, and the minimum and maximum average scores.  The `numberWords` parameter simply returns the count of elements stored in the database.  

## Additional files for testing

Make sure you test your code thoroughly.  You should do your own testing of course, but for your convenience we are providing two files representing extreme edge cases: **noReviews.txt** and **tooManyReviews.txt**.  Here’s what you should expect to see in these cases.

![BuildDatabase](/images/SentimentAnalysis-p1-image5.png)
![BuildDatabase](/images/SentimentAnalysis-p1-image6.png)

## Style

Your program needs to be orderly and readable.  If you are working a development team and don’t write clean looking code, you will be unpopular among your colleagues and may not work on that team very long.  Because of this your program will be graded on style as well as correctness.  Please refer to the style guidelines discussed in class and in reading assignments concerning

  *	Indention of code
  *	Consistent use of {}, preferably Stroustrup style (Check [Indentation Styles](https://en.wikipedia.org/wiki/Indentation_style))
  *	Meaningful names of identifiers
  *	Naming conventions for identifiers (camelCase for variables, CamelCase for function names. First word of a function name typically should be a verb.)
  *	No use of global variables. Global variables sometimes are appropriate, but not in the assignments we will be giving this quarter.
  *	Making sure object parameters are passed by reference (and declared const if appropriate)
  
## Documentation
    
At the start of your file you should have a header comment that gives the title of the assignment, the purpose, and your name.  Here is an example (from Lab 1) of what that could look like:

      
      /*
          Title:      Lab 1 – evalSteps.cpp
          Purpose:    implement the GetEvalSteps functions called by the main program to generate the evaluation
                      steps for an expression passed in as a parameter.
          Author:     Sally Johnson
          Date:       January 6, 2020
      */
      
Each subordinate function should also start with a header that describes what it does, it’s parameters, what it returns, and how errors are handled.  Here is an example (again from Lab 1):

   
    // Produce a string of evaluation steps for simplifying an expression
    // For example:
    //      if “2+3*4-5”  is passed to this function, the string “2+3*4-5 = 2+12-5\n        = 14-5\n        = 9”
    //      would be returned
    // Parameters:
    //      expression - an arithmetic expression
    // Returns:
    //      a string consisting of the evaluation steps needed to simplify the expression
    // Possible Error Conditions: 
    //      If evaluating the expression causes division by zero, this function crash.
    //      If evaluating the expression causes an oveflow, the results may not be reliable.
   

You should include additional comments in your code to describe what you are doing.   If it is hard to understand what a variable is for, add a comment after it.   It possible, though, to put in too many comments, so be judicious and make sure you have time left to do well in your other classes when it comes to commenting.

## Submitting your code
Your solution should be contained within files that were provided.  You MUST NOT modify the `main` routine, **CMakeFiles.txt** or **database.h**.

Make sure you test your code thoroughly.  We will try your code with our own test files, and we will programmatically test your database ADT with our own test program.  

Your code needs to be submitted by pushing into GitHub.  You will need to push your last version of your program before the lab deadline. As a good programming practice remember to commit frequently and to push every time you have a functioning version of your code.

## Grading
Correctness is essential.  Make sure your solution builds as described above and correctly handles the test cases displayed in the screen shot.  We will test on other input values as well. Your code must compile and should not have runtime errors (crash).

Even if your solution operates correctly, points will be taken off for:
- Not following the design described above
- Not adhering to style guidelines described above
- Using techniques not presented in class
- Programming error not caught by other testing
- Not following good programming practices

## Academic Integrity
This programming assignment is to be done on an individual basis. At the same time, it is understood that learning from your peers is valid and you are encouraged to talk among yourselves about programming in general and current assignments in particular.  Keep in mind, however, that each individual student must do the work in order to learn.  Hence, the following guidelines are established:
- Feel free to discuss any and all programming assignments but do not allow other students to look at or copy your code. Do not give any student an electronic or printed copy of any program you write for this class.
- Gaining the ability to properly analyze common programming errors is an important experience. Do not deprive a fellow student of his/her opportunity to practice problem solving: control the urge to show them what to do by writing the code for them.
- If you’ve given the assignment a fair effort and still need help, see the instructor or a lab assistant.
- **If there is any evidence that a program or other written assignment was copied from another student, neither student will receive any credit for it. This rule will be enforced.**
- Protect yourself: Handle throw-away program listings carefully, keep your repository private.

Refer to the ECS Department Policy on Academic Integrity that is included in the class syllabus.

## Grading Rubric Summary
The following aspects are going to be consider during grading. Make sure you comply with all of them.
- The program compiles (there will be no partial credit for programs that do not compile)
- Provides the correct output for the test cases
- Catches errors gracefully, the program does not crash on incorrect input
- The program outputs the information in the specified format
- The assignment follows all the instructions
- In general the program does not crash 
