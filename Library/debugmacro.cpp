void TEST()
{

	int values[] = {
		10,
		100,
		1000,
		10000,
		50000,
		100000,
		500000,
		1000000
	};

	int siz = sizeof(values) / sizeof(int);
	double avg_cpi = 0;

	puts("");
	puts("|         n | Runtime(s) |    TPI(ms)   |");
	puts("|----------:|:----------:|:------------:|");

	for (int k = 0; k < siz; ++k)
	{
		int n = values[k];
		for (int i = 0; i < n; ++i)
		{
			if (rand() & 1)
			{
				inputstring[i] = 'A' + (rand() % 26);
			}
			else if (rand() & 1)
			{
				inputstring[i] = 'a' + (rand() % 26);
			}
			else
			{
				inputstring[i] = '0' + (rand() % 10);
			}

		}
		inputstring[n] = 0;

		time_t start = clock();
		getsuffixarray(); // builds the suffix array
		time_t stop = clock();

		double time = (double)(stop - start) / CLOCKS_PER_SEC;
		double cpi = (double)(stop - start) / (n * log2(n));
		printf("| `%7d` |   `%5.3f`  | `%0.8f` |\n", n, time, cpi);

		if (k) avg_cpi += (values[k] - values[k - 1]) * cpi;
		else avg_cpi += values[k] * cpi;
	}
	avg_cpi /= values[siz - 1];

	printf("\n");
	printf("**Average *Time Per Instructions*** = `%.10f ms`\n", avg_cpi);
}