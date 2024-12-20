# Timus Solutions

My solutions to the problems of the Timus Online Judge.
Each solution includes a description about the strategy I used to solve the problem, along with a brief performance analysis, the time complexity and the space complexity of the solution.

#### Important note:

Because I've been faced too many times with the "Runtime error (access violation)" verdict on Timus problems (mostly on geometry problems), here are a few things to look out for in care you're trying to figure out what might go wrong with your code (mostly for me to remember):
- division by zero
- not enought memory declared
- precission errors
- the sorting might fail if the comparator is not safe (again, prevalently happening in geometry problems)
- the reading might fail with doubles (this may or may not cause errors, I'll leave this here because I'm paranoid)

- **you might get Runtime error because you're using G++, try Clang++ instead**
