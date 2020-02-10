#include "Pool.h"
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

Pool::Pool(size_t elemSize, size_t blockSize) {
	std::cout << "Initializing a pool with element size " << elemSize << " and block size " << blockSize << std::endl;
	this->elemSize = elemSize;
	this->blockSize = blockSize;
	this->numOfFreeCells = 0;
	this->numOfLiveCells = 0;
	this->numOfBlocks = 0;
	this->numOfRows = 0;
	this->pool = nullptr;
	this->freePointer = nullptr;
}

Pool::~Pool() {
	std::cout << "Deleting " << this->numOfBlocks << " blocks" << std::endl;

	for (size_t i = 0; i < this->numOfBlocks; i++) {
		delete[] this->pool[i];
	}

	delete[] this->pool;
}

void* Pool::allocate() {
	if (this->freePointer == nullptr) {
		this->grow();
	}

	void* temp = getFreePointer();
	this->freePointer = *reinterpret_cast<int**>(this->freePointer);
	this->numOfFreeCells = this->numOfFreeCells - 1;
	this->numOfLiveCells++;

	std::cout << "Cell allocated at 0x" << temp << std::endl;
	return temp;
}

void Pool::deaallocate(void* pointerToDeallocate) {
	void* temp = pointerToDeallocate;
	if (pointerToDeallocate == nullptr || this->numOfLiveCells <= 0) {
		std::cout << "no valid objects to deallocate" << std::endl;
	}

	// do we really need these 2 lines
	void** deallocatePtr = reinterpret_cast<void**>(pointerToDeallocate);
	*deallocatePtr = this->getFreePointer();

	this->freePointer = static_cast<char*>(pointerToDeallocate);
	this->numOfFreeCells++;
	this->numOfLiveCells--;
	std::cout << "Cell deallocated at 0x" << temp << std::endl;
}

size_t Pool::numLiveCells() {
	return this->numOfLiveCells;
}

size_t Pool::numFreeCells() {
	return this->numOfFreeCells;
}

size_t Pool::numRows() {
	return this->numOfRows;
}

void* Pool::getFreePointer() {
	return this->freePointer;
}

void Pool::grow() {
	if (this->numOfBlocks <= 0) {
		this->pool = new char* [this->numOfBlocks + 1];
		this->pool[this->numOfBlocks] = new char[this->elemSize * this->blockSize];

		this->freePointer = this->pool[this->numOfBlocks++];
	}
	else {
		char** temp = new char* [this->numOfBlocks + 1];

		// need to fix third parameter?
		std::memcpy(&temp[0], &pool[0], (sizeof(char*) * this->numOfBlocks));

		delete[] pool;
		pool = temp;

		pool[this->numOfBlocks] = new char[this->blockSize * this->elemSize];

		this->freePointer = pool[this->numOfBlocks++];
	}

	std::cout << "Expanding pool..." << std::endl;
	std::cout << "Linking cells starting at  0x" << static_cast<void*>(getFreePointer()) << std::endl;

	char* current = (char*)this->freePointer;
	char* target = current + this->elemSize;

	//std::cout << static_cast<void*>(current) << std::endl;

	for (size_t i = 0; i < this->blockSize; i++)
	{
		if (i == this->blockSize - 1)
			new (current) char* (nullptr);
		else
		{
			new (current) char* (target);
			current = target;
			target += this->elemSize;

			//std::cout << static_cast<void*>(current) << std::endl;
		}
	}
	this->numOfFreeCells += this->blockSize; // (this->numOfFreeCells == 5) += (this->blockSize == 5)
	std::cout << std::endl;
}

void Pool::profile() {
	std::cout << "Live Cells: " << this->numOfLiveCells << ", Free Cells: " << this->numOfFreeCells << std::endl;
	std::cout << "Free List:" << std::endl;

	char* current = (char*)(this->freePointer);

	while (current) {
		char** temp = reinterpret_cast<char**>(current);
		std::cout << "0x" << static_cast<void*>(current) << std::endl;
		current = *temp;
	}
	std::cout << std::endl;
}