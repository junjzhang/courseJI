Test for dlist_impl.h.

### Usage
1. Copy the cpp file to the directory you put your dlist_impl.h file.
1. Compile the program using "g++ -g -Wall -o dlist_test dlist_test.cpp" (-g is to facilitate valgrind's memory leak test).
1. Run the dlist_test executable to test.
1. If the test finished successfully, check memory leak using "valgrind --leak-check=full --log-file="log_file_name" ./dlist_test".

### Notes
The test is divided into parts for different methods, and the correctness of each part only depends on the correctness of previous parts, so if an assert fails, the problem must occur in this part.
