/*
A tridiagonal matrix is a square matrix in which all elements that are not on the major diagonal and the two diagonals adjacent to it are zero (Figure 2.13).

The elements in the band formed by these three diagonals are represented by rows in an array b, with a[0][0] being stored in b[0].

Obtain an algorithm to determine the value of a[i][j],
0 ≤ i, j < n, from the array b.

[ x  x  0  0  0 ]
[ x  x  x  0  0 ]
[ 0  x  x  x  0 ]
[ 0  0  x  x  x ]
[ 0  0  0  x  x ]

x → non-zero elements (stored in b)

0 → zero elements (not stored)

-----------
Algorithm:
	if | j - i | =< 1 :
		offset = j - i
        return b[i + offset]
    else:
        return 0
because the difference between the row and column index of an element within the diagonal band,
is always one or 0 or -1.The mid term of the diagonal band of a row always has index, row=col
*/
#include<cstddef>

int value_at(int row, int col, int* b){
    int offset = col - row;
    if(abs(offset) =< 1){
        return b[i + offset]
    }
    return 0;
}
