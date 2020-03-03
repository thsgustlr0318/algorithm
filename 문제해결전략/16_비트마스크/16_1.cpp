#include <iostream>
using namespace std;
#define MAX_N 100
int n;
unsigned char sieve[(MAX_N + 7) / 8];
//소수 판별
inline bool isPrime(int k) {
	return sieve[k >> 3] & (1 << (k & 7));
}
//k 마스킹
inline void setComposite(int k) {
	sieve[k >> 3] &= ~(1 << (k & 7));
}
void eratosthenes() {
	memset(sieve, 255, sizeof(sieve));
	setComposite(0);
	setComposite(1);
	int sqrtn = int(sqrt(n));
	for (int i = 2; i <= sqrtn; i++)
		if (isPrime(i))
			for (int j = i * i; j <= n; j+=i)
				setComposite(j);
}
int main()
{
	n = MAX_N;
	eratosthenes();
	for (int i = 0; i <= n; i++)
		if (isPrime(i))	printf("%d ", i);
	return 0;
}