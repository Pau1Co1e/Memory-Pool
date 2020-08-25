# Program---Memory-Pool-

-- Class-Based Heaps --

Every direct allocation on the heap will suffer some amount of overhead. This overhead occurs from the interataction 
between the new and delete operatators. This overhead can exponentially increase as the number of active heap objects
increase; leading to an excessive waste in memory.

Memory-Pool is able to solve this issue by managing individual heaps on a customized, class-by-class basis.
The basic idea is this: reserve enough memory space for any number of objects through a single heap allocation.
Next, pointers to all locations inside that array are returned while user(s) request a new object. This process 
is repeated for each object that is requested/created; potentially for any number of active memory blocks.
