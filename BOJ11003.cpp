#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long

deque<pair<int, int>> deq;
int N, L;

int main() {
	scanf("%d %d", &N, &L);

	for (int i = 1; i <= N; ++i) {
		while(!deq.empty() && deq.front().second < i - L + 1) {
			deq.pop_front();
		}
		int t;
		scanf("%d", &t);

		while (!deq.empty() && deq.back().first >= t) {
			deq.pop_back();
		}

		deq.push_back({ t,i });
		printf("%d ", deq.front().first);
	}
}

/*
//cubelover's solution. 고인물 ㄷㄷ
#pragma GCC optimize("O3")
#pragma GCC target("arch=skylake")
#include <cstring>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

char *p;

inline int readInt() {
	int t, r;
	if ((t = *p++) == 45) {
		for (r = *p++ - 48; (t = *p++ - 48) >= 0; r = r * 10 + t);
		return -r;
	}
	for (r = t - 48; (t = *p++ - 48) >= 0; r = r * 10 + t);
	return r;
}

int a[5000000], b[5000000];

int main() {
	struct stat st;
	fstat(0, &st);
	p = (char *)mmap(0, st.st_size, PROT_READ, MAP_SHARED, 0, 0);

	char buf[1048576], *p = buf;
	char x[100000][5], y[100000][5], z[100000];
	int i, j, t, s = 1, e = 0, n, m;
	for (i = 0; i < 100000; i++) {
		x[i][0] = i / 10000 + 48;
		x[i][1] = i / 1000 % 10 + 48;
		x[i][2] = i / 100 % 10 + 48;
		x[i][3] = i / 10 % 10 + 48;
		x[i][4] = i % 10 + 48;
		for (j = 10; j <= i; j *= 10);
		while (j /= 10) y[i][z[i]++] = i / j % 10 + 48;
	}
	n = readInt(); m = readInt();
	b[0] = -2e9;
	for (i = 0; i < n; i++) {
		a[i] = t = readInt();
		if (i >= m && a[i - m] == b[s]) b[s++] = -2e9;
		while (b[e] > t) e--;
		b[++e] = a[i];
		if (buf + sizeof(buf) - p < 12) {
			write(1, buf, p - buf);
			p = buf;
		}
		t = b[s];
		if (t < 0) {
			*p++ = 45;
			t = -t;
		}
		if (t < 100000) {
			memcpy(p, y[t], z[t]);
			p += z[t];
			*p++ = 32;
		}
		else {
			memcpy(p, y[t / 100000], z[t / 100000]);
			p += z[t / 100000];
			memcpy(p, x[t % 100000], 5);
			p += 5;
			*p++ = 32;
		}
	}
	write(1, buf, p - buf);
}
*/


/*
//ntopia's soltuion. Fast IO
#include <cstdio>
using namespace std;

namespace FIO {
	const size_t BUFFER_SIZE = 524288;
	char buffer[BUFFER_SIZE];
	char* ptr = buffer;

	inline char readByte() {
		if (ptr == buffer + BUFFER_SIZE) {
			fread(buffer, 1, BUFFER_SIZE, stdin);
			ptr = buffer;
		}
		return *(ptr++);
	}

	int readInt() {
		int ret = 0;
		char c = readByte();
		while (!('0' <= c && c <= '9') && c != '-') {
			c = readByte();
		}
		bool neg = false;
		if (c == '-') {
			neg = true;
			c = readByte();
		}
		while ('0' <= c && c <= '9') {
			ret = ret * 10 + (c - '0');
			c = readByte();
		}
		return neg ? -ret : ret;
	}
};

int q[5000001], qi[5000001];
int f, r;

void proc() {
	int n = FIO::readInt();
	int l = FIO::readInt();

	f = 0;  r = 0;
	for (int i = 0; i < n; ++i) {
		int v = FIO::readInt();

		while (r - f > 0 && q[r - 1] >= v) {
			--r;
		}
		q[r] = v;  qi[r] = i;
		++r;

		while (r - f > 0 && qi[f] < i - l + 1) {
			++f;
		}
		printf("%d ", q[f]);
	}
}

int main() {
	proc();
	return 0;
}


*/
//TC
/*
100 15
84 87 78 16 94 36 87 93 50 22 63 28 91 60 64 27 41 27 73 37 12 69 68 30 83 31 63 24 68 36 30 3 23 59 70 68 94 57 12 43 30 74 22 20 85 38 99 25 16 71 14 27 92 81 57 74 63 71 97 82 6 26 85 28 37 6 47 30 14 58 25 96 83 46 15 68 35 65 44 51 88 9 77 79 89 85 4 52 55 100 33 61 77 69 40 13 27 87 95 40
*/

/*
//segtree TLE
struct segtree {
	int n;
	vector<ll> seg;

	segtree(const vector<ll>& a) {
		n = a.size();
		seg.resize(4 * n);
		init(a, 0, n - 1, 1);
	}

	ll init(const vector<ll>& a, ll left, ll right, ll node) {

		if (left == right) {
			seg[node] = a[left];
			return seg[node];
		}

		ll mid = (left + right) / 2;
		ll linit = init(a, left, mid, node * 2);
		ll rinit = init(a, mid + 1, right, (node * 2) + 1);
		seg[node] = min(linit, rinit);
		return seg[node];
	}


	ll query(ll left, ll right, ll node, ll nodeLeft, ll nodeRight) {
		if (left > nodeRight || right < nodeLeft) {
			return INT_MAX - 10000;
		}

		if (left <= nodeLeft && right >= nodeRight) {
			return seg[node];
		}

		ll nodeMid = (nodeLeft + nodeRight) / 2;
		ll lquery = query(left, right, node * 2, nodeLeft, nodeMid);
		ll rquery = query(left, right, node * 2 + 1, nodeMid + 1, nodeRight);
		return min(lquery, rquery);
	}

	ll querycall(ll left, ll right) {
		return query(left, right, 1, 0, n - 1);
	}
};

int main() {
	int N, L;
	scanf("%d %d", &N, &L);

	vector<ll> input;

	for (int i = 0; i < N; ++i) {
		ll t;
		scanf("%lld", &t);
		input.push_back(t);
	}

	segtree S(input);

	for (int i = 1; i <= N; ++i) {
		int s = ((i - L + 1) > 0 ? i - L + 1 : 1);
		int e = i;

		printf("%d ", S.querycall(s - 1, e - 1));
	}

	return 0;
}
*/