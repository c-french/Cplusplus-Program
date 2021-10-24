# Briefly summarize your client, Artemis Financial, and their software requirements. Who was the client? What issue did they want you to address?

Artemis Financial is a financial consulting company that creates individualized plans for their customers, including savings, retirement, insurance, and investments.  They wanted me to examine their web based application to discover and mitigate security vulnerabilities in it.

# What did you do particularly well in identifying their software security vulnerabilities? Why is it important to code securely? What value does software security add to a company’s overall wellbeing?

I feel that I did particularly well with the manual review, finding important security issues to address, such as finding a line of code that could open the software to SQL injection attacks.  It is important to code securely not only so that sensitive data is protected, but also to help preserve a business's integrity.  Security leaks can lead to distrust with customers and loss of business, so making sure the system is coded securely is important no matter what kind of data a business handles.

# What about the process of working through the vulnerability assessment did you find challenging or helpful?

While more time intensive than difficult, researching the vulnerabilities from the dependency check was the one part that took the most time to complete in the report.  It was helpful to me though, as it gave me an opportunity to learn about different potential attacks, such as the "Billion Laughs Attack" and other entity expansion attacks that I may otherwise have never heard about, or even considered as a possible vulnerability in a system.

# How did you approach the need to increase layers of security? What techniques or strategies would you use in the future to assess vulnerabilities and determine mitigation techniques?

In order to increase the layers of security, I started with the manual code review to find flaws there.  Once those were identified, I went on to check software dependencies to see if an issue was hiding in there.  In a later project, I then went on to propose and implement an encryption method to further mitigate vulnerabilites.  In the future, I will likely use all of these techniques to mitigate vulnerabilities, as they each play a separate yet important role in the health of the software.

# How did you ensure the code and software application were functional and secure? After refactoring code, how did you check to see whether you introduced new vulnerabilities?

After refactoring, an additional dependency check was run to ensure no additional vulnerabilities were added with the addition of new libraries.  The check showed up the same as before the refactoring, so no additional vulnerabilities were added.

# What resources, tools, or coding practices did you employ that you might find helpful in future assignments or tasks?

The biggest tool I'm sure to find helpful in the future is the dependency check tool.  In addition to that, coding practices, such as sanitizing user input before using it as a parameter, are important to have in my toolkit moving forward.

# Employers sometimes ask for examples of work that you have successfully completed to demonstrate your skills, knowledge, and experience. What from this particular assignment might you want to showcase to a future employer?

In particular, I feel that sections 1, 3, 5 will help showcase to a potential employer my security know-how.  In most lines of work, it's important to understand the customer's issue, know how to find the issue, and know how to address the issue.  These sections in particular outline just that.  
