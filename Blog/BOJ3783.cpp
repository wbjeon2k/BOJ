//BOJ3783

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

const int base = 100000;
int T;

struct bigInt {
#define ll long long
	int lastdigit;
	const ll base = 100000;
	// 5 digit chunk
	ll digits[505];

	bigInt() {
		lastdigit = 0;
		memset(digits, 0, sizeof(digits));
	}

	bigInt operator = (bigInt rhs) {
		lastdigit = rhs.lastdigit;
		for (int i = 0; i < 505; ++i) {
			digits[i] = rhs.digits[i];
		}
		return *this;
	}
};

int pow10(int n) {
	int ret = 1;
	for (int i = 0; i < n; ++i) {
		ret *= 10;
	}
	return ret;
}

void zero_justify(bigInt& n) {

	while (n.lastdigit > 0 && n.digits[n.lastdigit] == 0) {
		--(n.lastdigit);
	}
}


void init(const string& s, bigInt& n) {
	// get input. 5 digit chunks
	memset(n.digits, 0, sizeof(n.digits));
	int ssize = s.size();
	int idx, chunk;
	idx = 0;
	for (int i = 0; i < ssize; i += 5) {
		chunk = 0;
		for (int j = 0; j < 5; ++j) {
			int tidx = ssize - 1 - i - j;
			if (tidx >= 0) {
				chunk += (s[tidx] - '0') * pow10(j);
			}
		}
		n.digits[idx] = chunk;
		++idx;
	}

	n.lastdigit = idx;

	zero_justify(n);
}

int compare(bigInt& lhs, bigInt& rhs) {
	//lhs < rhs:1, lhs>rhs:-1, lhs == rhs:0

	if (lhs.lastdigit < rhs.lastdigit) {
		return 1;
	}
	if (lhs.lastdigit > rhs.lastdigit) {
		return -1;
	}
	int maxdigit = max(lhs.lastdigit, rhs.lastdigit);
	for (int i = maxdigit; i >= 0; --i) {
		if (lhs.digits[i] > rhs.digits[i]) {
			return -1;
		}
		if (lhs.digits[i] < rhs.digits[i]) {
			return 1;
		}
	}

	return 0;

}

void digitshift(bigInt& n, int d) {
	// mutiply 100000(base)
	if (n.lastdigit == 0 && n.digits[0] == 0) return;

	for (int i = n.lastdigit; i >= 0; --i) {
		n.digits[i + d] = n.digits[i];
	}

	for (int i = 0; i < d; ++i) {
		n.digits[i] = 0;
	}

	n.lastdigit += d;

	zero_justify(n);
	return;
}

bigInt operator + (bigInt lhs, bigInt rhs) {
	bigInt ret;

	ll carry = 0;

	ret.lastdigit = max(lhs.lastdigit, rhs.lastdigit) + 1;

	for (int i = 0; i <= ret.lastdigit; ++i) {
		ll tmp = lhs.digits[i] + rhs.digits[i] + carry;
		ret.digits[i] = tmp % lhs.base;
		carry = tmp / lhs.base;
	}

	zero_justify(ret);

	return ret;
}

bigInt operator + (bigInt lhs, ll rhs) {
	bigInt ret = lhs;

	ll carry = 0;

	ret.digits[0] += rhs;
	ret.lastdigit++;

	for (int i = 0; i <= ret.lastdigit; ++i) {
		ll tmp = ret.digits[i] + carry;
		ret.digits[i] = tmp % lhs.base;
		carry = tmp / lhs.base;
	}

	zero_justify(ret);

	return ret;
}

bigInt operator - (bigInt lhs, ll rhs) {
	bigInt ret = lhs;

	ll borrow = 0;

	ret.digits[0] -= rhs;

	for (int i = 0; i <= ret.lastdigit; ++i) {
		ll tmp = ret.digits[i] - borrow;
		if (ret.digits[i] > 0) {
			borrow = 0;
		}
		if (tmp < 0) {
			tmp += lhs.base;
			borrow = 1;
		}

		ret.digits[i] = tmp % lhs.base;
	}

	zero_justify(ret);

	return ret;
}

bigInt operator * (bigInt lhs, bigInt rhs) {
	bigInt ret;

	int ldigit = lhs.lastdigit, rdigit = rhs.lastdigit;

	for (int i = 0; i <= ldigit; ++i) {
		for (int j = 0; j <= rdigit; ++j) {
			ll tmp = lhs.digits[i] * rhs.digits[j];
			ret.digits[i + j] += tmp;
		}
	}

	ll carry = 0;
	ret.lastdigit = ldigit + rdigit + 1;

	for (int i = 0; i <= ret.lastdigit; ++i) {
		ll tmp = ret.digits[i] + carry;
		ret.digits[i] = tmp % lhs.base;
		carry = tmp / lhs.base;
	}

	zero_justify(ret);

	return ret;
}

bigInt operator / (bigInt lhs, long long rhs) {
	if (rhs == 0) return lhs;

	long long tmp, r = 0;
	bigInt q = lhs;
	for (int i = lhs.lastdigit; i >= 0; --i) {
		tmp = lhs.base * r + q.digits[i];
		q.digits[i] = tmp / rhs;
		r = tmp % rhs;
	}

	zero_justify(q);
	return q;
}

bool operator > (bigInt lhs, bigInt rhs) {
	if (compare(lhs, rhs) == -1) {
		return true;
	}
	else return false;
}

bool operator < (bigInt lhs, bigInt rhs) {
	if (compare(lhs, rhs) == 1) {
		return true;
	}
	else return false;
}

bool operator <= (bigInt lhs, bigInt rhs) {
	return !(rhs < lhs);
}

bool operator >= (bigInt lhs, bigInt rhs) {
	return !(rhs > lhs);
}

bool operator == (bigInt lhs, bigInt rhs) {
	if (compare(lhs, rhs) == 0) {
		return true;
	}
	else return false;
}

void print10(bigInt a) {
	//print the number with 10 decimal digits
	if (a.lastdigit < 20) {
		printf("0.");
		for (int i = 19; i >= 18; --i) printf("%05d", (int)a.digits[i]);
		return;
	}
	for (int i = a.lastdigit; i >= 18; --i) {
		if (i == a.lastdigit) printf("%d", (int)a.digits[i]);
		else printf("%05d", (int)a.digits[i]);
		if (i == 20) printf(".");
	}
}

void print(bigInt n) {

	printf("%d", (int)n.digits[n.lastdigit]);
	for (int i = n.lastdigit - 1; i >= 0; --i) printf("%05d", (int)n.digits[i]);
	return;
}

void proc() {
	//ifstream cin;
	//cin.open("input.txt");

	cin >> T;
	while (T--) {
		string s;
		cin >> s;
		bigInt lo, hi, target;

		init("0", lo);
		init(s, hi);

		digitshift(hi,60);
		//multiply hi large enough to guarantee the precision
		//shift 60 digits -> decimal separator starts from (60/3)

		target = hi;
		bigInt mid;
		//binary search
		while (lo <= hi) {
			mid = (lo + hi) / 2;
			
			if (mid * (mid * mid) > target)
				hi = mid - 1;
			else
				lo = mid + 1;
		}

		lo = lo - 1;

		print10(lo);

		printf("\n");
	}
}

void test() {
	bigInt a, b;
	init("100000", b);
	init("99999", a);

	bigInt c = a*b;
	print(c);
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	//test();
	proc();
	return 0;
}

/*
//3rd trial.
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

const int base = 100000;
int T;

struct bigInt {
#define ll long long
	int lastdigit;
	const ll base = 100000;
	ll digits[505];

	bigInt() {
		lastdigit = 0;
		memset(digits, 0, sizeof(digits));
	}

	bigInt operator = (bigInt rhs) {
		lastdigit = rhs.lastdigit;
		for (int i = 0; i < 505; ++i) {
			digits[i] = rhs.digits[i];
		}
		return *this;
	}
};

int pow10(int n) {
	int ret = 1;
	for (int i = 0; i < n; ++i) {
		ret *= 10;
	}
	return ret;
}

void zero_justify(bigInt& n) {

	while (n.lastdigit > 0 && n.digits[n.lastdigit] == 0) {
		--(n.lastdigit);
	}
}


void init(const string& s, bigInt& n) {
	memset(n.digits, 0, sizeof(n.digits));
	int ssize = s.size();
	int idx, chunk;
	idx = 0;
	for (int i = 0; i < ssize; i += 5) {
		chunk = 0;
		for (int j = 0; j < 5; ++j) {
			int tidx = ssize - 1 - i - j;
			if (tidx >= 0) {
				chunk += (s[tidx] - '0') * pow10(j);
			}
		}
		n.digits[idx] = chunk;
		++idx;
	}

	n.lastdigit = idx;

	zero_justify(n);
}

int compare(bigInt& lhs, bigInt& rhs) {
	//lhs < rhs:1, lhs>rhs:-1, lhs == rhs:0

	if (lhs.lastdigit < rhs.lastdigit) {
		return 1;
	}
	if (lhs.lastdigit > rhs.lastdigit) {
		return -1;
	}
	int maxdigit = max(lhs.lastdigit, rhs.lastdigit);
	for (int i = maxdigit; i >= 0; --i) {
		if (lhs.digits[i] > rhs.digits[i]) {
			return -1;
		}
		if (lhs.digits[i] < rhs.digits[i]) {
			return 1;
		}
	}

	return 0;

}

void digitshift(bigInt& n, int d) {
	if (n.lastdigit == 0 && n.digits[0] == 0) return;

	for (int i = n.lastdigit; i >= 0; --i) {
		n.digits[i + d] = n.digits[i];
	}

	for (int i = 0; i < d; ++i) {
		n.digits[i] = 0;
	}

	n.lastdigit += d;

	zero_justify(n);
	return;
}

bigInt operator + (bigInt lhs, bigInt rhs) {
	bigInt ret;

	ll carry = 0;

	ret.lastdigit = max(lhs.lastdigit, rhs.lastdigit) + 1;
	//ret.lastdigit = 1000;

	for (int i = 0; i <= ret.lastdigit; ++i) {
		ll tmp = lhs.digits[i] + rhs.digits[i] + carry;
		ret.digits[i] = tmp % lhs.base;
		carry = tmp / lhs.base;
	}

	zero_justify(ret);

	return ret;
}

bigInt operator + (bigInt lhs, ll rhs) {
	bigInt ret = lhs;

	ll carry = 0;

	ret.digits[0] += rhs;
	ret.lastdigit++;
	for (int i = 0; i <= 500; ++i) {
		ll tmp = ret.digits[i] + carry;
		ret.digits[i] = tmp % lhs.base;
		carry = tmp / lhs.base;
	}

	zero_justify(ret);

	return ret;
}

bigInt operator - (bigInt lhs, ll rhs) {
	bigInt ret = lhs;

	ll borrow = 0;

	ret.digits[0] -= rhs;

	for (int i = 0; i <= 500; ++i) {
		ll tmp = ret.digits[i] - borrow;
		if (ret.digits[i] > 0) {
			borrow = 0;
		}
		if (tmp < 0) {
			tmp += lhs.base;
			borrow = 1;
		}

		ret.digits[i] = tmp % lhs.base;
	}

	zero_justify(ret);

	return ret;
}

bigInt operator * (bigInt lhs, bigInt rhs) {
	bigInt ret;

	int ldigit = lhs.lastdigit, rdigit = rhs.lastdigit;

	for (int i = 0; i <= ldigit; ++i) {
		for (int j = 0; j <= rdigit; ++j) {
			ll tmp = lhs.digits[i] * rhs.digits[j];
			ret.digits[i + j] += tmp;
		}
	}

	ll carry = 0;
	ret.lastdigit = 500;

	for (int i = 0; i <= ret.lastdigit; ++i) {
		ll tmp = ret.digits[i] + carry;
		ret.digits[i] = tmp % lhs.base;
		carry = tmp / lhs.base;
	}

	zero_justify(ret);

	return ret;
}

bigInt operator / (bigInt lhs, long long rhs) {
	if (rhs == 0) return lhs;

	long long tmp, r = 0;
	bigInt q = lhs;
	for (int i = lhs.lastdigit; i >= 0; --i) {
		tmp = lhs.base * r + q.digits[i];
		q.digits[i] = tmp / rhs;
		r = tmp % rhs;
	}

	zero_justify(q);
	return q;
}

bool operator > (bigInt lhs, bigInt rhs) {
	if (compare(lhs, rhs) == -1) {
		return true;
	}
	else return false;
}

bool operator < (bigInt lhs, bigInt rhs) {
	if (compare(lhs, rhs) == 1) {
		return true;
	}
	else return false;
}

bool operator <= (bigInt lhs, bigInt rhs) {
	return !(rhs < lhs);
}

bool operator >= (bigInt lhs, bigInt rhs) {
	return !(rhs > lhs);
}

bool operator == (bigInt lhs, bigInt rhs) {
	if (compare(lhs, rhs) == 0) {
		return true;
	}
	else return false;
}

void print10(bigInt a) {
	if (a.lastdigit < 40) {
		printf("0.");
		for (int i = 39; i >= 38; --i) printf("%05d", (int)a.digits[i]);
		return;
	}
	for (int i = a.lastdigit; i >= 38; --i) {
		if (i == a.lastdigit) printf("%d", (int)a.digits[i]);
		else printf("%05d", (int)a.digits[i]);
		if (i == 40) printf(".");
	}
}

void print(bigInt n) {

	printf("%d", (int)n.digits[n.lastdigit]);
	for (int i = n.lastdigit - 1; i >= 0; --i) printf("%05d", (int)n.digits[i]);
	return;
}

void proc() {
	//ifstream cin;
	//cin.open("input.txt");

	cin >> T;
	while (T--) {
		string s;
		cin >> s;
		bigInt lo, hi, target;

		init("0", lo);
		init(s, hi);

		digitshift(hi,120);

		target = hi;
		bigInt mid;
		while (lo <= hi) {
			mid = (lo + hi) / 2;
			bigInt fmid = mid * (mid * mid);
			if (fmid > target)
				hi = mid - 1;
			else
				lo = mid + 1;
		}

		lo = lo - 1;

		print10(lo);

		printf("\n");
	}
}

void test() {
	bigInt a, b;
	init("100000", b);
	init("99999", a);

	bigInt c = a*b;
	print(c);
	return;
}

int main() {
	//test();
	proc();
	return 0;
}
*/

/*
//2nd trial. TLE
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

class bigInt {



public:

	int point;
	const int Msize = 100100;
	int digits[2020];
	int sign;
	int lastdigit;
	const int base = 100000;
	const int digitbase = 5;

	friend bigInt operator + (bigInt, bigInt);
	friend bigInt operator - (bigInt, bigInt);
	friend bigInt operator * (bigInt, bigInt);
	friend bigInt operator / (bigInt, bigInt);
	friend bool operator > (bigInt,bigInt);
	friend bool operator < (bigInt, bigInt);
	friend bool operator == (bigInt, bigInt);
	//bigInt custommult(bigInt, bigInt);

	bigInt absolute();

	bigInt() {
		memset(digits, 0, sizeof(digits));
		sign = 1;
		lastdigit = 0;
		point = 100;
	}

	void zero_justify() {

		while (this->lastdigit > 0 && digits[this->lastdigit] == 0) {
			--(this->lastdigit);
		}

		if (this->lastdigit == 0 && digits[0] == 0) this->sign = 1;
	}

	bigInt(const string& s) {
		memset(digits, 0, sizeof(digits));
		int ssize = s.size();

		for (int i = 0; i < ssize; ++i) {
			this->digits[ssize - i - 1] = s[i] - '0';
		}

		this->sign = 1;
		this->lastdigit = ssize - 1;

		zero_justify();
	}

	void print() {
		for (int i = this->lastdigit; i>= 0; --i) {
			printf("%d", digits[i]);
		}
		return;
	}

	bigInt operator = (const bigInt& a) {
		for (int i = 0; i < 1000; ++i) {
			this->digits[i] = a.digits[i];
		}
		this->lastdigit = a.lastdigit;
		this->sign = a.sign;
		return *this;
	}

	static int compare(bigInt& lhs, bigInt& rhs) {
		//lhs < rhs:1, lhs>rhs:-1, lhs == rhs:0
		if (lhs.sign == -1 && rhs.sign == 1) {
			return 1;
		}
		if (lhs.sign == 1 && rhs.sign == -1) {
			return -1;
		}
		if (lhs.lastdigit < rhs.lastdigit) {
			return 1;
		}
		if (lhs.lastdigit > rhs.lastdigit) {
			return -1;
		}
		if (lhs.sign == 1 && rhs.sign == 1) {
			int maxdigit = max(lhs.lastdigit, rhs.lastdigit);
			for (int i = maxdigit; i >= 0; --i) {
				if (lhs.digits[i] > rhs.digits[i]) {
					return -1;
				}
				if (lhs.digits[i] < rhs.digits[i]) {
					return 1;
				}
			}

			return 0;
		}
	}

	void digitshift(int d) {
		if (this->lastdigit == 0 && this->digits[0] == 0) return;

		for (int i = this->lastdigit; i >= 0; --i) {
			this->digits[i + d] = this->digits[i];
		}

		for (int i = 0; i < d; ++i) {
			this->digits[i] = 0;
		}

		this->lastdigit += d;

		this->zero_justify();
		return;
	}

	void pointchk() {
		if (this->point != 300) {
			exception();
		}
	}

};

bigInt bigInt::absolute() {
	bigInt ret = *this;
	ret.sign = 1;

	return ret;
}

bigInt operator + (bigInt lhs, bigInt rhs) {
	bigInt ret;
	if (lhs.sign == 1 && rhs.sign == -1) {
		bigInt tmp = rhs.absolute();
		ret = (lhs - tmp);
		return ret;
	}
	if (lhs.sign == -1 && rhs.sign == 1) {
		bigInt tmp = lhs.absolute();
		ret = rhs - tmp;
		return ret;
	}

	int carry = 0;

	ret.lastdigit = max(lhs.lastdigit, rhs.lastdigit) + 1;
	//ret.lastdigit = 1000;

	for (int i = 0; i <= ret.lastdigit; ++i) {
		int tmp = lhs.digits[i] + rhs.digits[i] + carry;
		ret.digits[i] = tmp % 10;
		carry = tmp / 10;
	}

	ret.zero_justify();

	return ret;
}

bigInt operator - (bigInt lhs, bigInt rhs) {
	bigInt ret;

	if (lhs.sign == -1 && rhs.sign == 1) {
		bigInt tmp = lhs.absolute();
		ret = tmp + rhs;
		ret.sign = -1;
		return ret;
	}

	if (lhs.sign == 1 && rhs.sign == -1) {
		bigInt tmp = lhs.absolute();
		ret = tmp + rhs;
		ret.sign = 1;
		return ret;
	}

	if (rhs > lhs) {
		bigInt ret = rhs - lhs;
		ret.sign = -1;
		return ret;
	}

	int borrow = 0;

	ret.lastdigit = max(lhs.lastdigit, rhs.lastdigit);

	for (int i = 0; i <= ret.lastdigit; ++i) {
		int tmp = lhs.digits[i] - borrow - rhs.digits[i];
		if (lhs.digits[i] > 0) {
			borrow = 0;
		}
		if (tmp < 0) {
			tmp += 10;
			borrow = 1;
		}

		ret.digits[i] = tmp % 10;
	}

	ret.zero_justify();

	return ret;
}

bigInt operator * (bigInt lhs, bigInt rhs) {
	bigInt ret;

	int ldigit = lhs.lastdigit, rdigit = rhs.lastdigit;

	for (int i = 0; i <= ldigit; ++i) {
		for (int j = 0; j <= rdigit; ++j) {
			int tmp = lhs.digits[i] * rhs.digits[j];
			ret.digits[i + j] += tmp;
		}
	}

	int carry = 0;
	ret.lastdigit = 2000;

	for (int i = 0; i <= ret.lastdigit; ++i) {
		int tmp = ret.digits[i] + carry;
		ret.digits[i] = tmp % 10;
		carry = tmp / 10;
	}

	/*
	for (int i = 100; i <= 1100; ++i) {
		ret.digits[i - 99] = ret.digits[i];
	}
	

ret.sign = lhs.sign * rhs.sign;

ret.zero_justify();

return ret;
}

bigInt custommult(bigInt lhs, bigInt rhs) {
	bigInt ret;

	int ldigit = lhs.lastdigit, rdigit = rhs.lastdigit;

	for (int i = 0; i <= ldigit; ++i) {
		for (int j = 0; j <= rdigit; ++j) {
			int tmp = lhs.digits[i] * rhs.digits[j];
			ret.digits[i + j] += tmp;
		}
	}

	int carry = 0;
	ret.lastdigit = 2000;

	for (int i = 0; i <= ret.lastdigit; ++i) {
		int tmp = ret.digits[i] + carry;
		ret.digits[i] = tmp % 10;
		carry = tmp / 10;
	}


	for (int i = 100; i <= 2000; ++i) {
		ret.digits[i - 100] = ret.digits[i];
	}


	ret.sign = lhs.sign * rhs.sign;

	ret.zero_justify();

	return ret;
}

bigInt operator / (bigInt lhs, bigInt rhs) {
	if (rhs.lastdigit == 0 && rhs.digits[0] == 0) return lhs;

	bigInt q("0"), r("0");
	for (int i = lhs.lastdigit; i >= 0; --i) {
		r.digitshift(1);
		++q.lastdigit;
		r.digits[0] = lhs.digits[i];
		while (r > rhs || r == rhs) {
			q.digits[i]++;
			bigInt tmp = (r - rhs);
			r = tmp;
		}
	}

	q.zero_justify();
	//q.digitshift(100);
	return q;
}

bool operator > (bigInt lhs, bigInt rhs) {
	if (bigInt::compare(lhs, rhs) == -1) {
		return true;
	}
	else return false;
}

bool operator < (bigInt lhs, bigInt rhs) {
	if (bigInt::compare(lhs, rhs) == 1) {
		return true;
	}
	else return false;
}

bool operator == (bigInt lhs, bigInt rhs) {
	if (bigInt::compare(lhs, rhs) == 0) {
		return true;
	}
	else return false;
}

void customprint(bigInt a) {
	if (a.lastdigit < 100) {
		printf("0.");
		for (int i = 99; i >= 0; --i) printf("%d", a.digits[i]);
		return;
	}
	for (int i = a.lastdigit; i >= 0; --i) {
		printf("%d", a.digits[i]);
		if (i == 100) printf(".");
	}
}

void customprint10(bigInt a) {
	if (a.lastdigit < 100) {
		printf("0.");
		for (int i = 99; i >= 90; --i) printf("%d", a.digits[i]);
		return;
	}
	for (int i = a.lastdigit; i >= 90; --i) {
		printf("%d", a.digits[i]);
		if (i == 100) printf(".");
	}
}

bigInt roundup20(bigInt a) {
	bigInt ret = a;
	if (a.digits[80] < 5) return ret;

	int idx = 80;
	ret.digits[80] = 10;
	while (idx <= ret.lastdigit) {
		if (ret.digits[idx] > 9) {
			ret.digits[idx] = 0;
			ret.digits[idx + 1]++;
			if (idx == ret.lastdigit) {
				ret.lastdigit++;
			}
		}
		++idx;
	}

	return ret;
}

int T;
bigInt target;
bigInt f(bigInt x) {
	return custommult(x, custommult(x, x));
}

bigInt bisection(bigInt l, bigInt h) {
	bigInt lo, hi, mid;
	lo = l, hi = h;


	int loop = 50;
	bigInt two("2"), tmp("100000"), div("1000");
	tmp.digitshift(100);
	//div.digitshift(100);
	if (hi > tmp) {
		hi = hi / div;
		loop = 40;
	}
	//two.digitshift(100);



	for (int i = 0; i < loop; ++i) {
		bigInt fmid;
		mid = (lo + hi) / two;
		fmid = f(mid);
		if (fmid < target) {
			lo = mid;
		}
		else if (fmid > target) {
			hi = mid;
		}
	}

	return mid;
}

void proc() {
	cin >> T;
	while (T--) {
		string s, e;
		cin >> s;
		bigInt lo("0"), hi(s), ans;
		//lo.digitshift(100);
		hi.digitshift(100);
		target = hi;
		ans = bisection(lo, hi);
		/*
		for (int i = 0; i < 2000; ++i) {
			printf("%d", ans.digits[i]);
		}
		
		//customprint(ans);
		//printf("\n");
		//bigInt rup = ;
		customprint10(roundup20(ans));
		printf("\n");
	}
}



void test() {
	bigInt a("30"), b("15"), c, d("1");

	//c.print();
	a.digitshift(100);
	b.digitshift(100);
	d.digitshift(100);
	c = custommult(b, b);
	c.print();
}

int main() {
	//test();
	proc();

	return 0;
}
*/

/*
//1st trial. floating point precision error.
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int T;
double target;

double f(double x) {
	return ((x * x) * x) - target;
}

double bisection(double l, double h) {
	double lo, hi, mid;
	lo = l, hi = h;

	for (int i = 0; i < 100; ++i) {
		double fmid;
		mid = (lo + hi) / 2;
		fmid = f(mid);
		if (fmid < 0) {
			lo = mid;
		}
		else if (fmid > 0) {
			hi = mid;
		}
	}

	return mid;
}

int main() {
	cin >> T;
	while (T--) {
		cin >> target;
		double ans = bisection(0, target);
		printf("%.10lf\n", ans);
	}
}
*/

/*
//second trial. TLE
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

class bigInt {

public:

#define ll long long

	int point;
	const int Msize = 100100;
	ll digits[2020];
	int sign;
	int lastdigit;
	const ll base = 100000;
	const int digitbase = 5;

	friend bigInt operator + (bigInt, bigInt);
	friend bigInt operator - (bigInt, bigInt);
	friend bigInt operator * (bigInt, bigInt);
	friend bigInt operator / (bigInt, bigInt);
	friend bool operator > (bigInt,bigInt);
	friend bool operator < (bigInt, bigInt);
	friend bool operator == (bigInt, bigInt);

	bigInt absolute();

	bigInt() {
		memset(digits, 0, sizeof(digits));
		sign = 1;
		lastdigit = 0;
		point = 100;
	}

	void zero_justify() {

		while (this->lastdigit > 0 && digits[this->lastdigit] == 0) {
			--(this->lastdigit);
		}

		if (this->lastdigit == 0 && digits[0] == 0) this->sign = 1;
	}

	int pow10(int n) {
		int ret = 1;
		for (int i = 0; i < n; ++i) {
			ret *= 10;
		}
		return ret;
	}

	bigInt(const string& s) {
		memset(digits, 0, sizeof(digits));
		int ssize = s.size();
		int idx, chunk;
		idx = 0;
		for (int i = 0; i < ssize; i += 5) {
			chunk = 0;
			for (int j = 0; j < 5; ++j) {
				int tidx = ssize - 1 - i - j;
				if (tidx >= 0) {
					chunk += (s[tidx] - '0') * pow10(j);
				}
			}
			digits[idx] = chunk;
			++idx;
		}

		this->sign = 1;
		this->lastdigit = idx;

		zero_justify();
	}

	void print() {

		printf("%d", (int)this->digits[this->lastdigit]);
		for (int i = this->lastdigit - 1; i >= 0; --i) printf("%05d", (int)digits[i]);
		return;
	}

	bigInt operator = (const bigInt& a) {
		for (int i = 0; i < 1000; ++i) {
			this->digits[i] = a.digits[i];
		}
		this->lastdigit = a.lastdigit;
		this->sign = a.sign;

		return *this;
	}

	static int compare(bigInt& lhs, bigInt& rhs) {
		//lhs < rhs:1, lhs>rhs:-1, lhs == rhs:0
		if (lhs.sign == -1 && rhs.sign == 1) {
			return 1;
		}
		if (lhs.sign == 1 && rhs.sign == -1) {
			return -1;
		}
		if (lhs.lastdigit < rhs.lastdigit) {
			return 1;
		}
		if (lhs.lastdigit > rhs.lastdigit) {
			return -1;
		}
		if (lhs.sign == 1 && rhs.sign == 1) {
			int maxdigit = max(lhs.lastdigit, rhs.lastdigit);
			for (int i = maxdigit; i >= 0; --i) {
				if (lhs.digits[i] > rhs.digits[i]) {
					return -1;
				}
				if (lhs.digits[i] < rhs.digits[i]) {
					return 1;
				}
			}

			return 0;
		}
	}

	void digitshift(int d) {
		if (this->lastdigit == 0 && this->digits[0] == 0) return;

		for (int i = this->lastdigit; i >= 0; --i) {
			this->digits[i + d] = this->digits[i];
		}

		for (int i = 0; i < d; ++i) {
			this->digits[i] = 0;
		}

		this->lastdigit += d;

		this->zero_justify();
		return;
	}

};

bigInt bigInt::absolute() {
	bigInt ret = *this;
	ret.sign = 1;

	return ret;
}

bigInt operator + (bigInt lhs, bigInt rhs) {
	bigInt ret;
	if (lhs.sign == 1 && rhs.sign == -1) {
		ret = (lhs - rhs.absolute());
		return ret;
	}
	if (lhs.sign == -1 && rhs.sign == 1) {
		ret = rhs - lhs.absolute();
		return ret;
	}

	int carry = 0;

	ret.lastdigit = max(lhs.lastdigit, rhs.lastdigit) + 1;
	//ret.lastdigit = 1000;

	for (int i = 0; i <= ret.lastdigit; ++i) {
		int tmp = lhs.digits[i] + rhs.digits[i] + carry;
		ret.digits[i] = tmp % lhs.base;
		carry = tmp / lhs.base;
	}

	ret.zero_justify();

	return ret;
}

bigInt operator - (bigInt lhs, bigInt rhs) {
	bigInt ret;

	if (lhs.sign == -1 && rhs.sign == 1) {
		bigInt tmp = lhs.absolute();
		ret = tmp + rhs;
		ret.sign = -1;
		return ret;
	}

	if (lhs.sign == 1 && rhs.sign == -1) {
		bigInt tmp = lhs.absolute();
		ret = tmp + rhs;
		ret.sign = 1;
		return ret;
	}

	if (rhs > lhs) {
		bigInt ret = rhs - lhs;
		ret.sign = -1;
		return ret;
	}

	int borrow = 0;

	ret.lastdigit = max(lhs.lastdigit, rhs.lastdigit);

	for (int i = 0; i <= ret.lastdigit; ++i) {
		int tmp = lhs.digits[i] - borrow - rhs.digits[i];
		if (lhs.digits[i] > 0) {
			borrow = 0;
		}
		if (tmp < 0) {
			tmp += lhs.base;
			borrow = 1;
		}

		ret.digits[i] = tmp % lhs.base;
	}

	ret.zero_justify();

	return ret;
}

bigInt operator * (bigInt lhs, bigInt rhs) {
	bigInt ret;

	int ldigit = lhs.lastdigit, rdigit = rhs.lastdigit;

	for (int i = 0; i <= ldigit; ++i) {
		for (int j = 0; j <= rdigit; ++j) {
			ll tmp = lhs.digits[i] * rhs.digits[j];
			ret.digits[i + j] += tmp;
		}
	}

	int carry = 0;
	ret.lastdigit = 2000;

	for (int i = 0; i <= ret.lastdigit; ++i) {
		ll tmp = ret.digits[i] + carry;
		ret.digits[i] = tmp % lhs.base;
		carry = tmp / lhs.base;
	}

	/*
	for (int i = 100; i <= 1100; ++i) {
		ret.digits[i - 99] = ret.digits[i];
	}
	

ret.sign = lhs.sign * rhs.sign;

ret.zero_justify();

return ret;
}

bigInt custommult(bigInt lhs, bigInt rhs) {
	bigInt ret;

	int ldigit = lhs.lastdigit, rdigit = rhs.lastdigit;

	for (int i = 0; i <= ldigit; ++i) {
		for (int j = 0; j <= rdigit; ++j) {
			ll tmp = lhs.digits[i] * rhs.digits[j];
			ret.digits[i + j] += tmp;
		}
	}

	ll carry = 0;
	ret.lastdigit = 2000;

	for (int i = 0; i <= ret.lastdigit; ++i) {
		ll tmp = ret.digits[i] + carry;
		ret.digits[i] = tmp % lhs.base;
		carry = tmp / lhs.base;
	}


	for (int i = 300; i <= 2000; ++i) {
		ret.digits[i - 300] = ret.digits[i];
	}


	ret.sign = lhs.sign * rhs.sign;

	ret.zero_justify();

	return ret;
}

bigInt operator / (bigInt lhs, bigInt rhs) {
	if (rhs.lastdigit == 0 && rhs.digits[0] == 0) return lhs;

	bigInt q("0"), r("0");
	for (int i = lhs.lastdigit; i >= 0; --i) {
		r.digitshift(1);
		++q.lastdigit;
		r.digits[0] = lhs.digits[i];
		while (r > rhs || r == rhs) {
			q.digits[i]++;
			bigInt tmp = (r - rhs);
			r = tmp;
		}
	}

	q.zero_justify();
	//q.digitshift(100);
	return q;
}

bigInt operator / (bigInt lhs, long long rhs) {
	if (rhs == 0) return lhs;

	long long tmp, r = 0;
	bigInt q = lhs;
	for (int i = lhs.lastdigit; i >= 0; --i) {
		tmp = lhs.base * r + q.digits[i];
		q.digits[i] = tmp / rhs;
		r = tmp % rhs;
	}

	q.zero_justify();
	return q;
}


bool operator > (bigInt lhs, bigInt rhs) {
	if (bigInt::compare(lhs, rhs) == -1) {
		return true;
	}
	else return false;
}

bool operator < (bigInt lhs, bigInt rhs) {
	if (bigInt::compare(lhs, rhs) == 1) {
		return true;
	}
	else return false;
}

bool operator == (bigInt lhs, bigInt rhs) {
	if (bigInt::compare(lhs, rhs) == 0) {
		return true;
	}
	else return false;
}

void customprint(bigInt a) {
	if (a.lastdigit < 300) {
		printf("0.");
		for (int i = 299; i >= 295; --i) printf("%05d", (int)a.digits[i]);
		return;
	}
	for (int i = a.lastdigit; i >= 295; --i) {
		if (i == a.lastdigit) printf("%d", (int)a.digits[i]);
		else printf("%05d", (int)a.digits[i]);
		if (i == 300) printf(".");
	}
}

void customprint10(bigInt a) {
	if (a.lastdigit < 300) {
		printf("0.");
		for (int i = 299; i >= 298; --i) printf("%05d", (int)a.digits[i]);
		return;
	}
	for (int i = a.lastdigit; i >= 298; --i) {
		if (i == a.lastdigit) printf("%d", (int)a.digits[i]);
		else printf("%05d", (int)a.digits[i]);
		if (i == 300) printf(".");
	}
}

void print10(bigInt a) {
	if (a.lastdigit < 30) {
		printf("0.");
		for (int i = 29; i >= 28; --i) printf("%05d", (int)a.digits[i]);
		return;
	}
	for (int i = a.lastdigit; i >= 28; --i) {
		if (i == a.lastdigit) printf("%d", (int)a.digits[i]);
		else printf("%05d", (int)a.digits[i]);
		if (i == 30) printf(".");
	}
}

bigInt roundup200(bigInt a) {
	bigInt ret = a;
	int rounddigit = 210;

	if (a.lastdigit < 303) rounddigit = 296;
	else if (a.lastdigit < 308) rounddigit = 260;
	else if (a.lastdigit < 313) rounddigit = 250;


	if ((a.digits[rounddigit] % 10) < 5) return ret;

	int idx = rounddigit, seed = 10 - (a.digits[rounddigit] % 10);
	bigInt t("1"), add;
	t.digitshift(rounddigit);
	for (int i = 0; i < seed; ++i) {
		add = add + t;
	}

	ret = ret + add;
	//ret.zero_justify();
	return ret;
}

int T;
bigInt target;
bigInt f(bigInt x) {
	return custommult(x, custommult(x, x));
}

bigInt bisection(bigInt l, bigInt h) {
	bigInt lo, hi, mid;
	lo = l, hi = h;


	int loop = 1300;
	if (h.lastdigit < 303) loop = 300;
	if (h.lastdigit < 308) loop = 500;
	if (h.lastdigit < 313) loop = 800;

	bigInt fmid;
	for (int i = 0; i < loop; ++i) {
		mid = (lo + hi) / 2;
		fmid = f(mid);
		//fmid.print();
		//printf("\n");
		if (fmid < target) {
			lo = mid;
		}
		else if (fmid > target) {
			hi = mid;
		}
	}

	return mid;
}

void proc() {
	//ifstream cin;
	//cin.open("input.txt");

	cin >> T;
	while (T--) {
		string s, e;
		cin >> s;
		bigInt lo("0"), hi(s), ans;

		hi.digitshift(90);

		target = hi;
		bigInt mid, one("1");
		while (lo < hi || lo == hi) {
			mid = (lo + hi) / 2;
			if (mid * mid * mid > target)
				hi = mid - one;
			else
				lo = mid + one;
		}

		lo = lo - one;

		print10(lo);

		printf("\n");
	}
}



void test() {
	bigInt a("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
	bigInt b = a * a;
	b.print();
}

int main() {

	proc();

	return 0;
}
*/

/*
//https://github.com/mukel/ProgrammingContests/blob/master/OldStuff/SPOJ/new3/cubert.cpp
//Alfonso2 Peterssen
//SPOJ #291 "Cube Root"
//16 - 9 - 2008

#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define REP( i, n ) \
	for ( int i = 0; i < (n); i++ )
#define REPD( i, n ) \
	for ( int i = (n) - 1; i >= 0; i-- )

typedef long long int64;

const int
BASE = 10000000,
BASE_LOG = 7,
MAXLEN = 100;

int T;
struct bigint {
	int size;
	int64 T[MAXLEN];
	bigint(int64 x = 0, int size = 1) : size(size) {
		memset(T, 0, sizeof(T));
		T[0] = x;
	}
};

bool operator < (const bigint& a, const bigint& b) {
	if (a.size != b.size)
		return a.size < b.size;
	REPD(i, a.size)
		if (a.T[i] != b.T[i])
			return a.T[i] < b.T[i];
	return false;
}

bool operator <= (const bigint& a, const bigint& b) {
	return !(b < a);
}

bigint& normal(bigint& bn) {
	int64 r = 0, t;
	REP(i, bn.size) {
		while (bn.T[i] < 0) {
			bn.T[i + 1] -= 1;
			bn.T[i] += BASE;
		}
		t = bn.T[i] + r;
		bn.T[i] = t % BASE;
		r = t / BASE;
	}
	for (; r > 0; r /= BASE)
		bn.T[bn.size++] = r % BASE;
	while (bn.size > 1 && bn.T[bn.size - 1] == 0)
		bn.size--;
	return bn;
}

bigint operator + (bigint a, bigint& b) {
	a.size = max(a.size, b.size);
	REP(i, a.size)
		a.T[i] += b.T[i];
	return normal(a);
}

bigint operator + (bigint a, int64 x) {
	a.T[0] += x;
	return normal(a);
}

bigint operator - (bigint a, bigint& b) {
	a.size = max(a.size, b.size);
	REP(i, a.size)
		a.T[i] += b.T[i];
	return normal(a);
}

bigint operator - (bigint a, int64 x) {
	a.T[0] -= x;
	return normal(a);
}

bigint operator * (bigint a, bigint b) {
	bigint c(0, a.size + b.size);
	REP(i, a.size)
		REP(j, b.size)
		c.T[i + j] += a.T[i] * b.T[j];
	return normal(c);
}

bigint operator * (bigint a, int64 x) {
	REP(i, a.size)
		a.T[i] *= x;
	return normal(a);
}

pair< bigint, int64 > divmod(bigint bn, int64 x) {
	int64 r = 0, t;
	REPD(i, bn.size) {
		t = BASE * r + bn.T[i];
		bn.T[i] = t / x;
		r = t % x;
	}
	return make_pair(normal(bn), r);
}

bigint operator / (bigint bn, int64 x) {
	return divmod(bn, x).first;
}

int64 operator % (bigint bn, int64 x) {
	return divmod(bn, x).second;
}

void print(bigint bn) {
	printf("%lld", bn.T[bn.size - 1]);
	REPD(i, bn.size - 1)
		printf("%0*lld", BASE_LOG, bn.T[i]);
}

void read(bigint& bn) {
	static char line[200];
	scanf("%s", &line);
	int len = strlen(line);
	int i = len % BASE_LOG;
	if (i > 0) i -= BASE_LOG;
	for (; i < len; i += BASE_LOG) {
		int64 x = 0;
		REP(j, BASE_LOG)
			x = 10 * x + (i + j >= 0 ? line[i + j] - '0' : 0);
		bn.T[bn.size++] = x;
	}
	reverse(bn.T, bn.T + bn.size);
	normal(bn);
}

int main() {

	for (scanf("%d", &T); T--; ) {
		bigint X;
		read(X);

		REP(i, 15) X = X * 100;

		bigint lo(0);
		bigint hi = X;

		while (lo <= hi) {
			bigint mid = (lo + hi) / 2;
			if (mid * mid * mid <= X)
				lo = mid + 1;
			else
				hi = mid - 1;
		}

		lo = lo - 1;

		pair< bigint, int64 > R;
		R = divmod(lo, 100000);
		int p1 = R.second; lo = R.first;
		R = divmod(lo, 100000);
		int p2 = R.second; lo = R.first;

		int sum = 0;
		REP(i, lo.size)
			for (int x = lo.T[i]; x != 0; x /= 10)
				sum = (sum + x) % 10;

		for (int x = p1; x != 0; x /= 10)
			sum = (sum + x) % 10;

		for (int x = p2; x != 0; x /= 10)
			sum = (sum + x) % 10;

		printf("%d ", sum); print(lo); printf(".%05d%05d\n", p2, p1);
	}

	return 0;
}
*/

/*
//http://www.mianshigee.com/question/17321nwo
#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

const __int64 mod=10000000;
struct BigNum
{
	__int64 a[300];

	BigNum()
	{
		a[0]=1;
		a[1]=0;
	}

	BigNum(int x)
	{
		if(x>=mod) a[0]=2,a[1]=x/mod,a[2]=x%mod;
		else a[0]=1,a[1]=x;
	}

	BigNum(__int64 x)
	{
		stack<__int64> s;
		while(x)
		{
			s.push(x%mod);
			x/=mod;
		}
		a[0]=s.size();
		int k=0;
		while(!s.empty())
		{
			a[++k]=s.top();
			s.pop();
		}
	}

	BigNum(string str)
	{
		int i;
		for(i=0;i<str.length();i++) if(str[i]!='0') break;
		if(i==str.length())
		{
			a[0]=1;
			a[1]=0;
			return;
		}
		str=str.substr(i,str.length()-i);
		int p=str.length()%7,j;
		__int64 k;
		a[0]=0;
		if(p)
		{
			a[0]=1;
			k=0;
			for(i=0;i<p;i++) k=k*10+str[i]-'0';
			a[1]=k;
			str=str.substr(p,str.length()-p);
		}
		for(i=0;i<str.length();)
		{
			k=0;
			for(j=i;j<i+7;j++) k=k*10+str[j]-'0';
			a[++a[0]]=k;
			i=j;
		}
	}

	BigNum operator+(BigNum temp)
	{
		BigNum ans;
		__int64 i,j,k,p;
		if(a[0]>temp.a[0]) p=a[0];
		else p=temp.a[0];
		for(i=a[0],j=temp.a[0],k=p;j>=1&&i>=1;i--,j--,k--)
			ans.a[k]=a[i]+temp.a[j];
		if(j==0)
		{
			while(i>=1) ans.a[i]=a[i--];
		}
		else
		{
			while(j>=1) ans.a[j]=temp.a[j--];
		}
		ans.a[0]=0;
		for(i=p;i>=1;i--)
		{
			ans.a[i-1]+=ans.a[i]/mod;
			ans.a[i]%=mod;
		}
		if(ans.a[0])
		{
			for(i=p+1;i>=1;i--) ans.a[i]=ans.a[i-1];
			ans.a[0]=p+1;
		}
		else ans.a[0]=p;
		return ans;
	}

	BigNum operator-(BigNum temp)
	{
		BigNum ans;
		int i,j;
		for(i=0;i<=a[0];i++) ans.a[i]=a[i];
		for(i=ans.a[0],j=temp.a[0];i>=1&&j>=1;i--,j--)
			ans.a[i]-=temp.a[j];
		for(i=ans.a[0];i>=1;i--) if(ans.a[i]<0)
		{
			ans.a[i]+=mod;
			ans.a[i-1]--;
		}
		for(i=1;i<=a[0];i++) if(ans.a[i]) break;
		if(i>a[0])
		{
			ans.a[0]=1;
			ans.a[1]=0;
			return ans;
		}
		for(j=i;j<=a[0];j++) ans.a[j+1-i]=ans.a[j];
		ans.a[0]=a[0]-i+1;
		return ans;
	}

	BigNum operator*(BigNum temp)
	{
		BigNum ans;
		int i,j,p=a[0]+temp.a[0]-1;
		memset(ans.a,0,sizeof(ans.a));
		for(i=a[0];i>=1;i--) for(j=temp.a[0];j>=1;j--)
			ans.a[i+j-1]+=a[i]*temp.a[j];
		ans.a[0]=0;
		for(i=p;i>=1;i--)
		{
			ans.a[i-1]+=ans.a[i]/mod;
			ans.a[i]%=mod;
		}
		if(ans.a[0])
		{
			for(i=p;i>=0;i--) ans.a[i+1]=ans.a[i];
			ans.a[0]=p+1;
		}
		else ans.a[0]=p;
		return ans;
	}

	BigNum operator/(int x)
	{
		BigNum ans;
		int i,j;
		__int64 p;
		for(i=1;i<=a[0];i++)
		{
			if(i==1)
			{
				ans.a[i]=a[i]/x;
				p=a[i]%x;
			}
			else
			{
				ans.a[i]=(p*mod+a[i])/x;
				p=(p*mod+a[i])%x;
			}
		}
		for(i=1;i<=a[0];i++) if(ans.a[i]) break;
		if(i>a[0])
		{
			ans.a[0]=1;
			ans.a[1]=0;
			return ans;
		}
		for(j=i;j<=a[0];j++) ans.a[j+1-i]=ans.a[j];
		ans.a[0]=a[0]-i+1;
		return ans;
	}

	int operator==(BigNum temp)
	{
		if(a[0]!=temp.a[0]) return 0;
		for(int i=1;i<=a[0];i++) if(a[i]!=temp.a[i]) return 0;
		return 1;
	}

	int operator>(BigNum temp)
	{
		if(a[0]>temp.a[0]) return 1;
		if(a[0]<temp.a[0]) return 0;
		for(int i=1;i<=a[0];i++) if(a[i]!=temp.a[i]) return a[i]>temp.a[i];
		return 0;
	}

	int operator<(BigNum temp)
	{
		if(a[0]<temp.a[0]) return 1;
		if(a[0]>temp.a[0]) return 0;
		for(int i=1;i<=a[0];i++) if(a[i]!=temp.a[i]) return a[i]<temp.a[i];
		return 0;
	}

	int operator<=(BigNum temp)
	{
		BigNum p;
		for(int i=0;i<=a[0];i++) p.a[i]=a[i];
		return !(p>temp);
	}

	int operator>=(BigNum temp)
	{
		BigNum p;
		for(int i=0;i<=a[0];i++) p.a[i]=a[i];
		return !(p<temp);
	}

	void print()
	{
		printf("%I64d",a[1]);
		for(int i=2;i<=a[0];i++) printf("%07d",(int)a[i]);
	}
};

BigNum low,high,mid,ans,p,temp,temp1;
string str;

void print(BigNum a)
{
	vector<int> V;
	int i,j;
	for(i=a.a[0];i>=1;i--)
	{
		if(i>1)
		{
			for(j=1;j<=7;j++)
			{
				V.push_back((int)(a.a[i]%10));
				a.a[i]/=10;
			}
		}
		else
		{
			while(a.a[i])
			{
				V.push_back((int)(a.a[i]%10));
				a.a[i]/=10;
			}
		}
	}
	j=0;
	for(i=0;i<V.size();i++) j+=V[i];
	printf("%d ",j%10);
	for(i=V.size()-1;i>=10;i--) printf("%d",V[i]);putchar('.');
	for(i=9;i>=0;i--) printf("%d",V[i]);puts("");
}

int main()
{
	while(cin>>str)
	{
		p=BigNum(str);
		int i;
		for(i=1;i<=30;i++) p=p*BigNum(10);
		low=BigNum(1);
		high=p;
		while(low<=high)
		{
			mid=(low+high)/2;
			temp=mid*mid*mid;
			if(temp>=p) high=mid-BigNum(1);
			else low=mid+BigNum(1);
		}
		temp=low*low*low;
		temp1=high*high*high;
		if(temp==p) print(low);
		else if(temp1==p) print(high);
		else if(temp<p) print(low);
		else print(high);
	}
	return 0;
}
*/