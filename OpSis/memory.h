#pragma once

int AllocMemory(int a);
void FreeMemory(int handle);
int WriteMemory(int handle, int Offset, int Size, char* Data);
int ReadMemory(int handle, int Offset, int Size, char* Data);
void Shake();
void DumpMemory();