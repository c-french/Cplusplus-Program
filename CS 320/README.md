# How can I ensure that my code, program, or software is functional and secure?

Functionality can be ensured by the use of tests such as these given test classes.  The tests help confirm that the corresponding code meets the requirements given, implying that the code is functional.  In larger programs and systems, more testing, such as integration testing or system testing may be required to ensure full functionality, but ultimately it is a similar process - creating tests that, should the code pass, will show that it meets requirements.

Security can be accomplished through proper coding practices for smaller programs, and for larger works dependency check tools can also be used to find possible vulnerabilities from imported libraries.

# How do I interpret user needs and incorporate them into a program?

Interviews and surveys are a good way to gather user needs and find what features may be the most important to implement.  After the program has made progress through the development cycle, acceptance testing may also be used to see if the program truly does meet user expectations, or if more work needs to be done.

# How do I approach designing software?

In designing software, first I take a look at the requirements to see the "main goals" of the program, as well to see if certain parameters are set, such as a string field for an object needing to only accept a given range of characters.  From there, writing up UML diagrams helps to blueprint the program-to-be and understand the interactions between classes. After that, the actual coding of the program begins.  As the classes are written, corresponding test classes are written as well.  Next, the tests are run and changes are made as necessary.  Once testing fails to find bugs with the required functionalities of the classes, the program is complete.
