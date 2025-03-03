#include <iostream>
#include <vector>

#define _Wait() std::cout << "\nPress enter to continue..."; std::cin.get()
#define _New(count) for (int i = 0; i < count; i++) std::cout << '\n';

int maxSubSum1(const std::vector<int>& a)
{
	int maxSum = 0;

	for (int i = 0; i < a.size(); ++i)
	{
		for (int j = i; j < a.size(); ++j)
		{
			int thisSum = 0;

			for (int k = i; k < a.size(); ++k)
			{
				thisSum += a[k];
			}

			if (thisSum > maxSum)
				maxSum = thisSum;
		}
	}

	return maxSum;
}
int maxSubSum2(const std::vector<int>& a)
{
	int maxSum = 0;

	for (int i = 0; i < a.size(); ++i)
	{
		int thisSum = 0;

		for (int j = i; j < a.size(); ++j)
		{

			thisSum += a[j];

			if (thisSum > maxSum)
				maxSum = thisSum;
		}
	}

	return maxSum;
}
int maxSubSum3(const std::vector<int>& a)
{
	int maxSum = 0;

	for (int i = 0; i < a.size(); ++i)
		maxSum += a[i];


	return maxSum;
}


int main()
{
	std::vector<int> nums{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	int result = maxSubSum3(nums);

	std::cout << "Result: " << result << '\n';

	_Wait();
	return 0;
}



long fib(int n)
{
	if (n <= 1) return 1;

	else return fib(n - 1) + fib(n - 2);

}

int sum(int n)
{

	int partialSum = 0;

	for (int i = 1; i <= n; i++)
		partialSum += i * i * i;

	return partialSum;

}

int EXAMPLE_1()
{
	int N = 20;

	//int result = sum(N);
	int result = fib(N);

	std::cout << "Result (" << N << "): " << result << '\n';

	_Wait();

	return 0;
}
