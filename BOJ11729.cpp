#include <stdio.h>

#define MAX_LEN 100
#define MAX_NUM 1000000000

class BigInt
{
private:
	int len;
	int num[MAX_LEN];

public:
	BigInt(int num=0)
	{
		for(int i=0;i<MAX_LEN;i++)
		{
			this->num[i]=0;
		}
		if(num>=MAX_NUM)
		{
			this->len=2;
			this->num[1]=num/MAX_NUM;
			this->num[0]=num%MAX_NUM;
		}
		else
		{
			len=1;
			this->num[0] = num;
		}
	}

	void printNum()
	{
		printf("%d",this->num[len-1]);
		for(int i=this->len-2;i>=0;i--)
		{
			printf("%09d",this->num[i]);
		}
		printf("\n");
	}

	BigInt operator+(const BigInt& num)
	{
		const BigInt& num1 = *this;
		const BigInt& num2 = num;
		BigInt result;

		int tmp=0;
		int carry=0;

		int big_len = (num1.len > num2.len) ? num1.len : num2.len;

		for(int i=0;i<big_len;i++)
		{
			tmp = num1.num[i] + num2.num[i] + carry;
			carry = tmp/MAX_NUM;
			result.num[i] = tmp%MAX_NUM;
		}

		if(carry)
		{
			result.num[big_len] = carry;
			result.len = big_len+1;
		}
		else
		{
			result.len = big_len;
		}

		return result;
	}

	void operator=(const BigInt& num)
	{
		BigInt& dest = *this;
		const BigInt& src = num;

		dest.len = src.len;
		for(int i=0;i<len;i++)
		{
			dest.num[i] = src.num[i];
		}
	}
};

void PrintProcess(int n, int start, int end)
{
	if(n==1)
	{
		printf("%d %d\n",start,end);
	}
	else
	{
		int bridge = 6-start-end;

		PrintProcess(n-1,start,bridge);
		printf("%d %d\n",start,end);
		PrintProcess(n-1,bridge,end);
	}
}

int main()
{
	int n;

	scanf("%d",&n);

	BigInt num=1;
	int k=1;

	for(k=1;k<n;k++)
	{
		num = num+num+1;
	}
	num.printNum();

	if(n<=20)
	{
		PrintProcess(n,1,3);
	}

    return 0;
}
