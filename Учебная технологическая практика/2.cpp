#include <iostream>

int main()
{
	const int N = 1000;
	int mas_a[N] = { 1, 2, 3, 4, 5 };
	int mas_b[N] = { 0 };

	const long long* pointer1 = (const long long*)mas_a;
	long long* t_pointer1 = (long long*)mas_b;
	int m = sizeof(int) * N / sizeof(long long);
	for (int i = 0; i < m; ++i)
	{
		*(t_pointer1++) = *(pointer1++);
	}
	char* pointer2 = (char*)pointer1;
	char* t_pointer2 = (char*)t_pointer1;

	m = (sizeof(int) * N) % sizeof(long long);
	for (int i = 0; i < m; i++) {
		*(t_pointer2++) = *(pointer2++);
	}
}