3275885598
San Kim
kim503@usc.edu

For problem 1, the PDF file with my responses is called "problem1.pdf".
For problem 2, the PDF file with my responses is called "problem2.pdf".


For the cave exploration problem, just type:
make cave
Then do:
./cave
and input strings accordingly.


For the functor.h and functor.cpp, I fully implemented NumStrComp in functor.h
and used functor.cpp just for testing purposes (I added a NumStrComp object and
a cout statement that mirrored the previous two comparators). Again, since the
documentation was a bit vague on what to do with functor.cpp if we didn't need
it for NumStrComp definition/implementation, it is here but commented out, but 
functor.h contains the entirety of the NumStrComp struct implementation. 

For fatalist.cpp, I #include < algorithm > because I was told a piazza post allowed
us to use the sort() function in c++. If it is not allowed, the commented out
sections of the code: the int kmerge ... block as well as the two mergeSort 
calls right after each of the two calls to sort() will utilize the mergeSort 
that I wrote earlier and will do the same job (albeit slower but still in 
nlogn when we set k as a constant)--the sort function is also O(nlogn) but just
better implemented so either sorts both produce nlogn time complexities regardless.
I apologize for the two code sections--I chose the overall faster sort() implementation
only due to not being entirely sure whether or not it was allowed (with strong evidence
via piazza posts and other people pointing towards that it was okay).


For problem 4 part c, the answers are in "hw5.txt" as requested in the documentation.