long long factorial(long long N)
{
	if (N == 0)
		return 1;
	else
		return N * factorial(N-1);
}
