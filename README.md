# Program---Memory-Pool-
CS 3370
Programming Assignment 2
“Class-based Heaps”
As you know, every direct heap allocation via the new operator incurs some overhead so that the delete operator
will have the information it needs to properly clean up when you’re finished with the heap object. When many heap
objects are active at once, the wasted memory for the heap overhead for each object can be excessive. One solution is
to manage heaps on a custom, class-by-class basis.
The idea is to reserve enough space for many objects with a single heap allocation (a memory “block” capable of
holding some number of objects), and then return pointers to locations inside that array yourself as the user requests a
new object. You repeat this process as each block of objects gets used up, so you may have many memory blocks
active at once. So, you are essentially doing your own heap management for that class. This is library-developer skill
often expected of C++ programmers.
In this assignment, you will apply good software design techniques by separating the management of a memory pool
from the class of objects to be allocated from the pool. The class of objects here is named MyObject, and has the
following data members:
 int id;
 string name;
To force users to only place MyObject objects on the heap, so that you can manage all MyObject instances, make
the constructor private, and provide a static member function, create, which returns a pointer to a new heap object
(this is the Simple Factory Method design pattern). In other words, the MyObject class includes the following
member function definitions:
private:
 MyObject(int i, const string& nm): name(nm) { // Note initializer list
 id = i;
 }

public:
 static MyObject* create(int id, const string& name) { // Factory method
 return new MyObject(id, name);
 }
Define also a class named Pool, with at least the following member functions:
public:
 Pool(size_t elemSize, size_t blockSize = 5);
 ~Pool();
 void* allocate(); // Get a pointer inside a pre-allocated block for a new object
 void deallocate(void*); // Free an object's slot (push the address on the "free list")
Provide class-based versions of operator new and operator delete in MyObject that utilize a single,
shared (i.e., static) instance of class Pool. Pool manages a dynamic array of blocks, as discussed above, where each
block contains the number of bytes needed to hold blockSize elements of type MyObject, each of size
elemSize (= sizeof (MyObject)). You will initialize each element cell in a block of cells with an embedded
pointer to its successor cell, essentially constituting a logically linked list. (This is not a traditional linked list; it is
simulated initially such that each cell just holds the address of its neighbor to the right in its initial bytes until that cell
is put in use as a MyObject. Remember, the goal here is to preserve memory. See the next paragraph for more
detail.)
The Pool class contains a data member (pool, below) that holds a pointer to the head of the free list, as follows:
.
.
.
. . .
. . .
. . .
. . .
.
.
.
pool
each block is blocksize*elemSize bytes
free
You will build this data structure implicitly, one row (“block”) at a time, as needed. It starts out empty.
The MyObject class has a static Pool data member, initialized with elemSize equal to sizeof(MyObject).
Don’t forget to allocate space for MyObject’s Pool object at file scope in the file MyObject.cpp. When
MyObject::operator new executes, it merely calls Pool::allocate (via its static Pool object), which in
turn returns the pointer to the current open slot in a pool block, and also updates its internal free list pointer to point to
the next open slot for the next future call to allocate. When there are no more open slots, a Pool object
automatically expands it array of blocks by 1 more block (or row, if you will, as depicted above), and initializes those
pointers in logical linked-list fashion as you did in the first instance.
When a MyObject is deleted, MyObject::operator delete simply calls Pool::deallocate, which in
turn logically prepends the returned address to the head of the free list that the pool manages (don’t shrink the memory
allocation in the pool). Pool’s destructor needs to delete all heap resources it owns: each block/row, and the array
holding the pointers to the blocks. Using =delete in the appropriate places, disallow copy and assignment in both
MyObject and Pool. MyObject also needs an output operator (<<). See the driver in the file main.cpp for an
example of how to use these classes. Place the class definitions and member functions for these classes in separate
header and implementation files (i.e., Pool.h, Pool.cpp, MyObject.h, MyObject.cpp).
This is not a long program (about 150 lines or so). The tedious (but not overly difficult) part is doing the pointer
arithmetic and “poking” of addresses when you initialize a new block as a linked list. Each block is just an array of
bytes, so each element in the dynamic array pool is a char*; therefore, pool itself is a char**. You can’t allocate
an array of MyObjects directly for each row in Pool because, 1) Pool is generic (but not a template) and shouldn’t
know about MyObject, and 2) the default constructor for MyObject would execute for each element in each row,
which is wasteful – we just want raw, uninitialized memory for us to set up ourselves. The constructor for each
MyObject runs automatically when the object itself is created when MyObject::create invokes the new
operator, as you know.
Note that you need to insert trace statements in the correct places in Pool’s member functions, so your output will be
similar to the sample output. Use the default of 5 for blockSize. (In practice, of course, it will be much bigger). You
will also need a static MyObject::profile function that calls a non-static Pool::profile function that prints out
the free list (see below).


Here is the expected output from clang (Windows output will be similar):

  Initializing a pool with element size 32 and block size 5
  Live Cells: 0, Free Cells: 0
  Free list:
  Expanding pool...
  Linking cells starting at 0x7faea0402830
  Cell allocated at 0x7faea0402830
  Cell allocated at 0x7faea0402850
  Cell allocated at 0x7faea0402870
  Cell allocated at 0x7faea0402890
  Cell allocated at 0x7faea04028b0
  Expanding pool...
  Linking cells starting at 0x7faea0402920
  Cell allocated at 0x7faea0402920
  Cell allocated at 0x7faea0402940
  Cell allocated at 0x7faea0402960
  Cell allocated at 0x7faea0402980
  Cell allocated at 0x7faea04029a0
  Object 5 == {5,"5"}
  Cell deallocated at 0x7faea0402920
  Live Cells: 9, Free Cells: 1
  Free list:
  0x7faea0402920
  Creating another object:
  Cell allocated at 0x7faea0402920
  anotherObject == {100,anotherObject}
  Creating yet another object:
  Expanding pool...
  Linking cells starting at 0x7faea04029c0
  Cell allocated at 0x7faea04029c0
  yetAnotherObject == {120,yetAnotherObject}
  Live Cells: 11, Free Cells: 4
  Free list:
  0x7faea04029e0
  0x7faea0402a00
  0x7faea0402a20
  0x7faea0402a40
  Cell deallocated at 0x7faea0402920
  Cell deallocated at 0x7faea04029c0
  Cell deallocated at 0x7faea0402830
  Cell deallocated at 0x7faea0402850
  Cell deallocated at 0x7faea0402870
  Cell deallocated at 0x7faea0402890
  Cell deallocated at 0x7faea04028b0
  Cell deallocated at 0x7faea0402940
  Cell deallocated at 0x7faea0402960
  Cell deallocated at 0x7faea0402980
  Cell deallocated at 0x7faea04029a0
  Live Cells: 0, Free Cells: 15
  Free list:
  0x7faea04029a0
  0x7faea0402980
  0x7faea0402960
  0x7faea0402940
  0x7faea04028b0
  0x7faea0402890
  0x7faea0402870
  0x7faea0402850
  0x7faea0402830
  0x7faea04029c0
  0x7faea0402920
  0x7faea04029e0
  0x7faea0402a00
  0x7faea0402a20
  0x7faea0402a40
  Deleting 3 blocks
