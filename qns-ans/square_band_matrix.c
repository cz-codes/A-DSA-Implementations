/*
Qn: Square Band Matrix

A square band matrix D_{n,a} is an n × n matrix in which all the nonzero
terms lie in a band centred around the main diagonal. The band includes
the main diagonal and (a − 1) diagonals below and above the main diagonal
(Figure 2.14).

(a)
How many elements are there in the band D_{n,a}?

(b)
What is the relationship between i and j for elements d_{i,j} in the
band D_{n,a}?

(c)
Assume that the band of D_{n,a} is stored sequentially in a
one-dimensional array b by diagonals, starting with the lowermost
diagonal. For example, the band matrix D_{4,3} of Figure 2.14 would have
the following representation:

d20, d31, d10, d21, d32, d00, d11, d22, d33, d01, d12, d23, d02, d13

Obtain an addressing formula for the location of an element d_{i,j} in
the lower band of D_{n,a}.

(Location of d10 = 2 in the example above.)
*/

#include<stdio.h>

int lower_index_calc(int i , int j, int n, int a){
	int diagonals_before = 0;
	int k = i - j;

	//Calculate Number of elements in diagonals before k;
	for(int r = k+1; r <= a-1; r++){
		diagonals_before = n - r;
	}

	return  diagonals_before + j;

}

void set_lower_band(int *b,int i, int j, int n, int a , int value){
	if( i>j && i-j<=a-1){
		int idx = lower_index_calc(i, j, n, a);
		b[idx] = value;
	}
}

int get_lower_band_value(int *b,int i, int j, int n, int a ){
	if( i>j && i-j<=a-1){
		int idx = lower_index_calc(i, j, n, a);
		return b[idx];
	}
	return 0;
}

void main(){
	int b[100];
	int i=0;
	int j=0;

	int value = 10;
	set_lower_band(b,2,0,4,3,value);
	int retrive = get_lower_band_value(b,2,0,4,3);
	printf("Retrived Value: %d\n",retrive);
}

