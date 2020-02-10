// Project:  Memory Pool
// Name: 
// Submitted: 
// I declare that the following source code was written by me, or provided
// by the instructor for this project. I understand that copying source
// code from any other source, providing source code to another student, 
// or leaving my code on a public web site constitutes cheating.
// I acknowledge that  If I am found in violation of this policy this may result
// in a zero grade, a permanent record on file and possibly immediate failure of the class.

/* Reflection (1-2 paragraphs):  I really enjoyed writing this program, but had trouble with... I learned about...   */

#include <cstddef>
#include <cassert>
#include <new>
#include <list>
#include <iostream>

class Pool {
public:
	Pool(size_t elemSize, size_t blockSize = 5);
	~Pool();
	void* allocate();
	void deaallocate(void*);

	Pool(const Pool&) = default;
	Pool& operator= (const Pool&) = default;

	size_t numLiveCells();
	size_t numFreeCells();
	size_t numRows();
	void* getFreePointer();

	void grow();
	void profile();

private:
	char** pool;
	void* freePointer;
	size_t elemSize;
	size_t blockSize;
	size_t numOfBlocks;
	size_t numOfLiveCells;
	size_t numOfFreeCells;
	size_t numOfRows;
};