#include "MyObject.h"
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

Pool MyObject::pool = Pool(sizeof(MyObject), 5);

MyObject* MyObject::create(int id, const std::string& name) {
	MyObject* tempObj = new MyObject(id, name);
	return tempObj;
}

void MyObject::profile() {
	pool.profile();
}

void MyObject::operator delete(void* objectToDeallocate) {
	pool.deaallocate(objectToDeallocate);
}

// Mod with assert size == size of my object for bonus point(s)
void* MyObject::operator new(size_t size) {
	return pool.allocate();
}

size_t MyObject::numRows() {
	return pool.numRows();
}

size_t MyObject::numLiveCells() {
	return pool.numLiveCells();
}

size_t MyObject::numFreeCells() {
	return pool.numFreeCells();
}

char* MyObject::getFreeListPtr() {
	return nullptr;
}

std::ostream& operator<<(std::ostream& os, const MyObject& myObj) {
	os << "{" << myObj.id << "," << myObj.name << "}" << std::endl;
	return os;
}
