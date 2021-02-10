#include <iostream>
#include "memory.h"

int main()
{
	AllocMemory(1010);
	AllocMemory(50);
	AllocMemory(100);
	AllocMemory(20);
	DumpMemory();

	char a[3] = { 1, 2, 3};
	WriteMemory(1, 2, 3, a);
	WriteMemory(2, 0, 3, a);
	char b[5];
	ReadMemory(2, 1, 5, b);
	WriteMemory(4, 2, 5, b); 

	DumpMemory();

	FreeMemory(1);
	FreeMemory(3);
	DumpMemory();
}
