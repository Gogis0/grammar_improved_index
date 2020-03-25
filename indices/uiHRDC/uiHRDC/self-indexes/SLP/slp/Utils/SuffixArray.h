#ifndef SUFFIXARRAY_H_
#define SUFFIXARRAY_H_

/* 
   Adaptation of the original implementation...

   Copyright 1999, N. Jesper Larsson, all rights reserved.

   This file contains an implementation of the algorithm presented in "Faster
   Suffix Sorting" by N. Jesper Larsson (jesper@cs.lth.se) and Kunihiko
   Sadakane (sada@is.s.u-tokyo.ac.jp).

   This software may be used freely for any purpose. However, when distributed,
   the original source must be clearly stated, and, when the source code is
   distributed, the copyright notice must be retained and any alterations in
   the code must be clearly marked. No warranty is given regarding the quality
   of this software.*/

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define KEY(p)          (V[*(p)+(h)])
#define SWAP(p, q)      (tmp=*(p), *(p)=*(q), *(q)=tmp)
#define MED3(a, b, c)   (KEY(a)<KEY(b) ?                        \
        (KEY(b)<KEY(c) ? (b) : KEY(a)<KEY(c) ? (c) : (a))       \
        : (KEY(b)>KEY(c) ? (b) : KEY(a)>KEY(c) ? (c) : (a)))

#ifndef CHECK
/* Nonzero CHECK means check that sort is correct. Very slow for repetitive
   files.*/
#define CHECK 0
#endif

#ifndef PRINT
/* 0 for no printing. 1 to print suffix numbers in sorted order. 2 to print
   first MAXPRINT characters of each suffix in sorted order (makes sense only
   if the input is text and COMPACT is 0).*/
#define PRINT 1
#endif
#ifndef MAXPRINT
#define MAXPRINT 10
#endif

#ifndef COMPACT
/* 0 to use alphabet 0...UCHAR_MAX without checking what appears. 1 to limit
   the alphabet to the range l...k-1 that actually appears in the input. 2 to
   transform the alphabet into 1...k-1 with no gaps and minimum k, preserving
   the order.*/
#define COMPACT 1
#endif

#define MIN(a, b) ((a)<=(b) ? (a) : (b))

class SuffixArray
{
public:
	SuffixArray();
	int* sort(unsigned char *text, ulong length);
	~SuffixArray();
	
protected:
	int *I,                  /* group array, ultimately suffix array.*/
	   *V,                          /* inverse array, ultimately inverse of I.*/
	   r,                           /* number of symbols aggregated by transform.*/
	   h;                           /* length of already-sorted prefixes.*/	

	int scmp3(unsigned char *p, unsigned char *q, int *l, int maxl);	

	void update_group(int *pl, int *pm);
	void select_sort_split(int *p, int n);
	int choose_pivot(int *p, int n);
	void sort_split(int *p, int n);
	void bucketsort(int *x, int *p, int n, int k);
	int transform(int *x, int *p, int n, int k, int l, int q);
	void suffixsort(int *x, int *p, int n, int k, int l);
};


#endif /*SUFFIXARRAY_H_*/
