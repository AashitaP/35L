First I had to figure out which part to parallelize, 
printing pixels seemed ideal for this as they are printed one at a time and hence no race conditions. 

Next I had to figure out the arguments to pthread_create: 
argument 3 has to be a function that divides the input by threads, 
so modifying the outer loop seemed like the way to go with the 
thread number being the 4th argument to pass into the function. 

I had to be careful while copying code to make another function 
as there are variables used in both the function and main, 
pixel variables can't be constants either as it produces errors while assigning inside main.

I realized while compiling that I forgot to modify the Makefile 
to link to lpthread and hence the progrsm was throwing errors.

It kept showing multithreading is not supported yet 
- I realized I forgot to comment out the return part.

After running it got different values than baseline 
- I realized that each thread was printing independentally 
within the function and I had to print together to get the correct order. 
To resolve this I created a temp array and a 3D array to store the values 
and print all the values in main after the threads finished.

before: 

real 44.75
user 44.65
sys 0.07

1-test.ppm : 

real	0m42.724s
user	0m42.710s
sys	0m0.004s

2-test:

real	0m21.459s
user	0m42.654s
sys	0m0.003s

4-test:

real	0m11.435s
user	0m44.953s
sys	0m0.002s

8-test:


real	0m5.981s
user	0m46.311s
sys	0m0.003s

This shows that performance improved proportional to the number of threads (i.e. around 8 times for 8-test).



