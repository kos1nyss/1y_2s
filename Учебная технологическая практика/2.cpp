#include <iostream>

int main()
{
	const int N = 1000;
	int mas_a[N] = { 1, 2, 3, 4, 5 };
	int mas_b[N] = { 0 };

	const char* f_pointer = (const char*)mas_a;
	char* t_pointer = (char*)mas_b;
	for (int i = 0; i < N; ++i)
	{
		*(t_pointer++) = *(f_pointer++);
	}
}