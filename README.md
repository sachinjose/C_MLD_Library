Implemented a garbage collector for C programs which works on the principle of reachability of objects to detect memory leaks and analyzed its limitations and cost for being an inbuilt feature of C-like language.


Limitations of this Garbage collector 

This Garbage collector works if programming is done with C as a purely OOP language, since C is not an OOP language the below test cases won't work 

False leaks can be reported in the below scenarios

1. When storing pointer to a non-pointer data type

This operation isn't permitted in Java

2. Indirect reference to an object 

When a pointer points to a memory location that is not returned by calloc

3. Embedded Objects 
