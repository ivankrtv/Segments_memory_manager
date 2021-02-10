#include <iostream>
#include "memory.h"

#define MEMSIZE 10000
#define SEGNUM 100

struct seg
{
	int size;
	int start;
	int busy;
	int handle;
};

int h = 0; //handle сегментов, увеличивается на 1 с каждым новым сегментом
char mainmem[MEMSIZE];
seg segments[SEGNUM];

int AllocMemory(int a)
{
	if (a == 0) { return 0; }
	int i = 0,  freemem = MEMSIZE;

	for (i = 0; i < SEGNUM; i++) {
		if (segments[i].size == NULL) break;
		freemem -= segments[i].size;
	}
	if (freemem > a) {
		segments[i].size = a;
		segments[i].busy = 1;
		segments[i].handle = ++h;
		if (i == 0) { segments[i].start = 0; }
		else { segments[i].start = segments[i - 1].start + segments[i - 1].size; }
		
	}
	else { return 0; }

	return h;
}

void FreeMemory(int handle)
{
	int i;

	for (i = 0; i < SEGNUM; i++) {
		if (handle == segments[i].handle) break;
	}
	int start = segments[i].start;
	for (int j = 0; j < segments[i].size; j++) {
		mainmem[start + j] = NULL;
	}
	segments[i].busy = 0;
	Shake();
}

int WriteMemory(int handle, int Offset, int Size, char* Data)
{
	int i;
	
	for (i = 0; i < SEGNUM; i++) {
		if (handle == segments[i].handle) break;
	}
	if (Offset + Size > segments[i].size) { return 1; }
	int start = segments[i].start + Offset;
	for (int j = 0; j < Size; j++) {
		mainmem[start + j] = Data[j];
	}
	return 0;
}

int ReadMemory(int handle, int Offset, int Size, char* Data)
{
	int i = 0;
	for (i = 0; i < SEGNUM; i++) {
		if (handle == segments[i].handle) break;
	}
	if (Size > (segments[i].size - Offset)) { return 1; }
	int start = segments[i].start + Offset;
	for (int j = 0; j < Size; j++) {
		Data[j] = mainmem[start + j];
	}
	return 0;
}

void Shake()
{
	int i = 0;
	while (segments[i].handle != 0 && i < SEGNUM) {
		if (segments[i].busy == 0) {
			if (segments[i + 1].busy != 0) {
				for (int j = 0; j < segments[i + 1].size; j++) {
					mainmem[segments[i].start + j] = mainmem[segments[i + 1].start + j];
				}
				segments[i + 1].start = segments[i].start;
				int j;
				for (j = i; j < SEGNUM - 1; j++) {
					segments[j] = segments[j + 1];
				}
				segments[j] = { NULL };
			}
			else {
				segments[i + 1].start = segments[i].start;
				int j;
				for (j = i; j < SEGNUM - 1; j++) {
					segments[j] = segments[j + 1];
				}
				segments[j] = { NULL };
			}
		}
		else {
			if (i > 0) {
				if (segments[i].start != (segments[i - 1].start + segments[i - 1].size)) {
					int start = segments[i - 1].start + segments[i - 1].size;
					for (int j = 0; j < segments[i].size; j++) {
						mainmem[start + j] = mainmem[segments[i].start + j];
					}
					segments[i].start = start;
				}
			}
			i++;
		}
	}
}

void DumpMemory()
{
	int kol = 0, j = 0;
	while (segments[j].handle != NULL) {
		kol++;
		j++;
	}
	for (int i = 0; i < kol; i++) {
		printf("H:"); printf("%d ", segments[i].handle);
		printf("B:"); printf("%d ", segments[i].start);
		printf("S:"); printf("%d ", segments[i].size);
		if (segments[i].busy == 1) printf("Yes ");
		else printf("No ");
		for (int k = segments[i].start; k < (segments[i].start + 10); k++) {
			printf("%d", mainmem[k]);
		}
		printf("\n");
	}
}