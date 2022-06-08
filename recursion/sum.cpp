#include <iostream>
#include <algorithm>

int A[] = {0,1,2,3,4,5,6};

int sum(int A[], int n) {
	if (1 > n)
		return 0;
	else
		return sum(A, n-1) + A[n-1];
}

int sum2(int A[], int lo, int hi) {
	if (lo == hi)
		return A[lo];
	else {
		int mi = (lo + hi) >> 1;
		return sum2(A, lo, mi) + sum2(A, mi+1, hi);
	}
}

void reverse(int* A, int lo, int hi) {
	if (lo < hi) {
		std::swap(A[lo], A[hi]);
		reverse(A,lo + 1, hi - 1);
	}
}

void printArray(int* A, int n) {
	for (int i = 0; i < n; ++i) {
		std::cout << A[i] << " ";
	}
	std::cout << std::endl;
}

inline __int64 sqr(__int64 a) { return a * a; }

__int64 power2(int n) {
	if (n == 0)
		return 1;  //递归基，否则视n的奇偶分别递归
	return (n & 1) ? sqr(power2(n >> 1)) << 1 : sqr(power2(n >> 1));
}

int main()
{
	std::cout << "sum2(A, 0, 6) = " << sum2(A, 0, 6) << std::endl;
	reverse(A, 0, 6);
	printArray(A, 7);
	std::cout << power2(2) << std::endl;
	return 0;
}