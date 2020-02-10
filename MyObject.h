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
#include "Pool.h"

class MyObject {
public:
	int id;
	std::string name;
	void* nextPointer;
	static MyObject* create(int id, const std::string& name);
	static void profile();

	MyObject(const MyObject&) = delete;
	MyObject& operator=(const MyObject&) = delete;

	static void operator delete(void*);

	static Pool pool;

	static size_t numRows();
	static size_t numLiveCells();
	static size_t numFreeCells();
	static char* getFreeListPtr();
	friend std::ostream& operator<<(std::ostream& os, const MyObject& myObj);

private:
	MyObject(); // Default constructor
	// Parameterized constructor
	MyObject(int i, const std::string& nm) : name(nm) {
		this->id = i;
		this->nextPointer = nullptr;
	}
	void* operator new(size_t size);
};