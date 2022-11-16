# My Log Parser
A Quake III log parser, written in C and C++.

## About the project:
This project was made as a test for a Quality Engineer position at CloudWalk, with the intent of measuring my general software engineering skills.

## Programming language choice:
- As a fan of John Carmack's magnum opus and its legacy, i could not write this parser on a language different than C++.
- Being a low level language, C++ code is faster as it gets compilled instantly to machine code, so its an efficient programming language for a parser.
- C++ programming expresses capability of troubleshooting and finding a root cause for errors, attributes which are, in my opinion, very important for the position.

## Implementation idea
1. Use a OS native function to filter usefull lines from the original log;
2. Compare string pointers from between non-variant parts of the log("Kill:", "killed", "by");
3. Store substrings between those words in classes using c++'s OOP;
4. Manipulate and rank that information.
[Implementation Idea](flowchart.png)
