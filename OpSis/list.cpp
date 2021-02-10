//#include <iostream>
//#include "list.h"
//
//#define MEMSIZE 10000
//#define PAGENUM 30
//#define PAGESIZE 1000
//
//struct pages {
//	int handle; // идентификатор выделяемого блока
//	int pagenum; // номер страницы
//	int isvirtual; // Если 1 - виртуальная, 0 - нет
//	int size;
//};
//
//int blk = 0; // идентификатор блоков
//pages page[PAGENUM] = { NULL };
//
//void InitMemory() {
//	int h = 0;
//	for (int i = 0; i < PAGENUM; i++) {
//		page[i].pagenum = ++h;
//		if (i > 9) page[i].isvirtual = 1;
//	}
//}
//
//int AllocMemory(int sz) {
//	int col = sz / PAGESIZE;
//	if (sz % PAGESIZE != 0) col++;
//	int count = 0;
//	for (int i = 0; i < PAGENUM; i++) {
//		if (page[i].handle == 0) count++;
//	}
//	if (count >= col) {
//		blk++;
//		for (int i = 0; i < PAGENUM; i++) {
//			if (col == 0) break;
//			if (page[i].handle == 0) {
//				page[i].handle = blk;
//				page[i].size = PAGESIZE;
//				if (i > 9) page[i].isvirtual = 1;
//			}
//		}
//	}
//	return blk;
//}