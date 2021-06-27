# Portfolio for CS 210

### Summarize the project and what problem it was solving.
---

In this project, the goal was to develop a program that utilized both Python and C++ in order to read an input file that included the names of grocery items, count the number of times each item was listed, then create a file with the item counts.  Further, the program would allow you to see if a particular item was found via console input, and if so, it would output the number of times the item was found.  Finally, utilizing the generated item count file, the program would generate a histogram of the items and output them to the console, giving the user a visual representation of the list.

### What did you do particularly well?
---

For this project, I feel that my organization was particularly well done.  I wanted to experiment with adding multiple "home made" classes into a program, in this case the class I made containing the starter code and my own class for handling the program's functionality.  It was a fun little challenge to go through, and it's given me some good experience for in the future when I write more sophisticated programs.

### Where could you enhance your code? How would these improvements make your code more efficient, secure, and so on?
---

One particular area that I could enhance the code would be for the menu.  As it is right now, it is by no means flashy, and could benefit from some polish to make it more visually appealing.  Also, with the way that I handled input for the menu selections -- to output an error message and call the menu function again -- I noticed in the sidebar that the memory usage crept up with repeated invalid input.  At this point I'm unsure if it was due in part to the way I coded it that caused that slow leak of memory, or if something like that is just par for the course, but it would certainly be beneficial to find a way to write it so that memory usage wouldn't jump like that.

### Which pieces of the code did you find most challenging to write, and how did you overcome this? What tools or resources are you adding to your support network?
---

The most challenging part of this project was actually writing the Python functions, as there were a few steps that I was unfamiliar with syntax wise for that language, such as reading an input file.  Fortunately, with the help of StackExchange and a few tutorial sites for syntax, it was not that difficult to overcome.  I've utilized StackExchange for a while now, but the how-to sites, along with official documentation, are a new tool that I'll be sure to utilize moving forward.

### What skills from this project will be particularly transferable to other projects or course work?
---

Skills that will translate well to other work would include configuring Visual Studio to "link up" the two different languages so that they can work together.  While in this case it was only done with Python, I assume it is roughly the same process for almost any other language to configure the linker.

### How did you make this program maintainable, readable, and adaptable?
---

In order to make this program maintainable, readable, and adaptable, I first took the given starter code for utilizing Python function in C++ and put it in its own class.  Next, I created my own class for C++ for my own functions.  With the Python functions in their own file, I ended up with six different files for the program (not counting the input and output files, that is).  This way, if any edits needed to be made, it would be easy to find the function in question.  Further, all files were well commented that explained what each step was doing.
