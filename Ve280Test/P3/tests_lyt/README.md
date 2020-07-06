## Instructions for using the test written by lyt

Effects: check the handling of all the 13 possible errors of input files given in the project description, the three world files given, and two extra world files with answers not sure to be right.

Usage:
1. Put the folder tests_lyt somewhere in your disk.
1. Inside the folder, compile test.cpp using ``g++ -o test test.cpp``, or use the compiled test executable directly.
1. Put the test executable file inside the test_lyt folder, and put your compiled p3 executable file inside *the parent folder* of test_lyt.
1. In terminal, *change the working directory to test_lyt*, and run test using ``./test``. The program will use ``diff`` to check if your program's outputs are the same as the standard outputs.

**The given standard outputs are not guaranteed to be correct. If there are any problems, please raise a issue on GitHub.**
 
