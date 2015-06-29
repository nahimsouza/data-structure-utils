/**

=========================================================================================
					  	     URI 1252 - Sort! Sort!! And Sort!!!
					 www.urionlinejudge.com.br/judge/en/problems/view/1252
=========================================================================================


*/

#include <stdio.h>
#include <stdlib.h>

long long M;

int isEven(long long n) {
	return (n%2 == 0);
}

int isOdd(long long n) {
	return (n%2 != 0);
}


int cmpfunc (const void * a, const void * b)
{
	long long A = *(long long*)a;
	long long B = *(long long*)b;

	if ((A % M) > (B % M)) {
		return 1;
	} else if ((A % M) == (B % M)){
		if (isEven(A) && isOdd(B)) {
			return 1;
		} else if (isOdd(A) && isOdd(B) && A < B) {
			return 1;
		} else if (isEven(A) && isEven(B) && A > B) {
			return 1;
		}
	} else {
		return -1;
	}

   return 0;
}

void swap(long long v[], long long i, long long j){
	long long aux;

	aux = v[i];
	v[i] = v[j];
	v[j] = aux;

}

void bsort(long long v[], long long N, long long M) {

	long long i,j;
	
	for (i = 0; i < N-1; i++) {
		for (j = i+1; j < N; j++) {
			// compare
			if ((v[i] % M) > (v[j] % M)) {
				swap(v,i,j);
			} else if ((v[i] % M) == (v[j] % M)){
				if (isEven(v[i]) && isOdd(v[j])) {
					swap(v, i, j);
				} else if (isOdd(v[i]) && isOdd(v[j]) && v[i] < v[j]) {
					swap(v, i, j);
				} else if (isEven(v[i]) && isEven(v[j]) && v[i] > v[j]) {
					swap(v, i, j);
				}
			}
		}
	}
	
}

long long main() {

	long long N;
	long long v[10000];
	long long i;

	scanf("%lld %lld", &N, &M);
	while (!(N == 0 && M == 0)) {

		for (i = 0; i < N; i++) {
			scanf ("%lld", &v[i]);			
		}

		// bubble sort
		// bsort(v, N, M);
		
		// quick sort
		qsort(v, N, sizeof(long long), cmpfunc);

		printf("%lld %lld\n", N, M);	

		for (i = 0; i < N; i++) {
			printf ("%lld\n", v[i]);			
		}

		scanf("%lld %lld", &N, &M);
	}

	printf("0 0\n");

	return 0;
}
