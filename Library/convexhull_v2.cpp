//BOJ 7420
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>

using namespace std;

struct geovector {
	double x, y;
	const double PI = 2.0 * acos(0.0);
	explicit geovector(double x_ = 0, double y_ = 0) : x(x_), y(y_) {

	}

	geovector& operator = (const geovector& rhs) {
		x = rhs.x;
		y = rhs.y;
		return *this;
	}

	bool operator == (const geovector& rhs) const {
		return x == rhs.x && y == rhs.y;
	}

	bool operator < (const geovector& rhs) const {
		if (y * rhs.x != x * rhs.y) return y * rhs.x < x * rhs.y;
		if (y != rhs.y) return y < rhs.y;
		return x < rhs.x;
	}

	geovector operator + (const geovector& rhs) {
		return geovector(x + rhs.x, y + rhs.y);
	}

	geovector operator - (const geovector& rhs) {
		return geovector(x - rhs.x, y - rhs.y);
	}

	geovector operator * (double rhs) const {
		return geovector(x * rhs, y * rhs);
	}

	double norm() const {
		return hypot(x, y);
	}

	geovector normalize() const {
		if (norm() == 0) return geovector(0.0, 0.0);
		return geovector(x / norm(), y / norm());
	}

	double polarangle() const {
		//x 축의 양의 방향으로부터 이 벡터까지 반시계 방향으로 잰 각도
		return fmod(atan2(y, x) + 2 * PI, 2 * PI);
	}

	double dotproduct(const geovector& rhs) const {
		return x * rhs.x + y * rhs.y;
	}

	double crossproduct(const geovector& rhs) const {
		return x * rhs.y - y * rhs.x;
	}

	geovector projection(const geovector& rhs) const {
		//이 벡터를 rhs 에 사영한 결과
		geovector ret = rhs.normalize();
		return ret * ret.dotproduct(*this);
	}

};

//원점에서 벡터 b 가 벡터 a 의 반시계 방향이면 양수, 시계 방향 음수, 평행이면 0
double ccw(geovector a, geovector b) {
	return a.crossproduct(b);
}

double normalccw(geovector a, geovector b) {
	geovector x, y;
	x = a.normalize(), y = b.normalize();
	return ccw(x, y);
}


//벡터 p 기준으로 벡터 b 가 벡터 a 의 반시계 방향이면 양수, 시계 방향 음수, 평행이면 0
double ccw(geovector p, geovector a, geovector b) {
	return ccw(a - p, b - p);
}

bool comp( geovector& a, geovector& b) {
	return ((a.y != b.y) ? a.y < b.y : a.x < b.x);
}

bool problemcomp(geovector& a, geovector& b) {
	return ((a.y != b.y) ? a.y > b.y : a.x < b.x);
}

bool isInsidePolygon(geovector q, const vector<geovector>& p) {
	int crosscnt = 0;

	for (int i = 0; i < p.size(); ++i) {
		int j = (i + 1) % p.size();

		if ((p[i].y > q.y) != (p[j].y > q.y)) {
			double xcross = ((p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y)) + p[i].x;

			if (q.x < xcross) ++crosscnt;
		}
	}

	return (crosscnt % 2) > 0;
}

vector<geovector> grahamscan(vector<geovector> plist) {
	sort(plist.begin(), plist.end(), comp);

	for (int i = 1; i < plist.size(); ++i) {
		plist[i] = plist[i] - plist[0];
	}

	sort(plist.begin() + 1, plist.end());

	for (int i = 1; i < plist.size(); ++i) {
		plist[i] = plist[i] + plist[0];
	}

	stack<int> st;

	st.push(0);
	st.push(1);
	//st.push(2);
	for (int i = 2; i < plist.size(); ++i) {
		while (st.size() >= 2) {
			int first, second;
			first = st.top();
			st.pop();
			second = st.top();
			if (ccw(plist[second], plist[first], plist[i]) > 0) {
				st.push(first);
				break;
			}
		}

		st.push(i);
	}

	vector<geovector> ret;
	while (!st.empty()) {
		ret.push_back(plist[st.top()]);
		st.pop();
	}

	return ret;
}


bool pointonline(geovector p, geovector a, geovector b) {
	double pol = ccw(a, p, b);

	if (pol == 0) {
		if (p.x < min(a.x, b.x) || p.x > max(a.x, b.x) || p.y < min(a.y, b.y) || p.y > max(a.y, b.y)) return false;
		return true;
	}

	return false;
}

bool lineintersect(geovector a, geovector b, geovector c, geovector d) {
	double ab, cd;
	ab = ccw(a, b, c) * ccw(a, b, d);
	cd = ccw(c, d, a) * ccw(c, d, b);

	if (ab == 0 && cd == 0) {
		if (a == c || a == d) return true;
		if (b == c || b == d) return true;

		if (pointonline(c, a, b)) return true;
		if (pointonline(d, a, b)) return true;
		if (pointonline(a, c, d)) return true;
		if (pointonline(b, c, d)) return true;


		return false;
	}

	return (ab <= 0 && cd <= 0);
}

bool polygonintersect(vector<geovector>& h1, vector<geovector>& h2) {

	for (int i = 0; i < h1.size(); ++i) {
		for (int j = 0; j < h2.size(); ++j) {
			int p, q;
			p = (i + 1) % h1.size();
			q = (j + 1) % h2.size();

			//if (pointonline(h2[j], h1[i], h1[p])) return true;
			if (lineintersect(h1[i], h1[p], h2[j], h2[q])) return true;
		}
	}

	for (int i = 0; i < h1.size(); ++i) {
		if (isInsidePolygon(h1[i], h2)) return true;
	}
	for (int i = 0; i < h2.size(); ++i) {
		if (isInsidePolygon(h2[i], h1)) return true;
	}

	return false;
}

const double PI = 2.0 * acos(0.0);
