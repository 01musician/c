long long fibonacci(long long N)
{
	if (N <= 1)
		return 1;
	else
		return fibonacci(N-1) + fibonacci(N-2);
}
