# true_random_number
==An attempt to create a true random number depending on the unpredicted behaviour of the CPU by running a competition between two threads.

The idea is as follows:
1. Create a 32-bit array to represent the generated random number in binary.
2. Create two threads with the **same** priority.
3. Run both threads at the exact same time as much as possible.
4. Let the CPU manage the competition between the threads on the same array.
5. One thread changes the bit to 1's (on) and the second to 0's (off).
6. Convert the generated binary to decimal which plays as a seed to generate the final random number.

Note that this approach heavily depends on the OS, Linux in particular and not suitable for other OS. Also it depends on the number of Cores andthe System Architecture.
More research and investigation is required.

![ALT TEXT](https://github.com/John-Almardeny/true_random_number/blob/master/true_random.gif?raw=true) 
