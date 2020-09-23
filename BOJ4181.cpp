//BOJ 4181
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
//#include <cmath>
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
		if (x != rhs.x) return x < rhs.x;
		return y < rhs.y;
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
	return ((a.x != b.x) ? a.x < b.x : a.y < b.y);
}

int N;
vector<geovector> input;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//ifstream cin;
	//cin.open("input.txt");

	cin >> N;

	for (int i = 0; i < N; ++i) {
		int s, e;
		char F;

		cin >> s >> e >> F;
		if(F == 'Y') input.push_back(geovector(s, e));
	}

	sort(input.begin(), input.end(), comp);

	for (int i = 1; i < input.size(); ++i) {
		input[i] = input[i] - input[0];
	}

	sort(input.begin() + 1, input.end());

	int idx = 0;
	for (int i = input.size() - 1; i > 0; --i) {
		if (ccw(input[i], input[i - 1]) != 0) {
			idx = i;
			break;
		}
	}

	reverse(input.begin() + idx, input.end());

	printf("%d\n", input.size());

	for (int i = 0; i < input.size(); ++i) {
		if(i>0) input[i] = input[i] + input[0];
		printf("%.0lf %.0lf\n", input[i].x, input[i].y);
	}

	return 0;
}

/*
//BOJ4181
//1st attempt. TLE
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
//#include <cmath>
using namespace std;

struct geovector {
	double x, y;
	const double PI = 2.0 * acos(0.0);
	explicit geovector(double x_ = 0, double y_ = 0) : x(x_), y(y_) {

	}

	geovector& operator = (const geovector & rhs) {
		x = rhs.x;
		y = rhs.y;
		return *this;
	}

	bool operator == (const geovector& rhs) const {
		return x == rhs.x && y == rhs.y;
	}

	bool operator < (const geovector& rhs) const {
		return ((x != rhs.x) ? x < rhs.x : y < rhs.y);
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

// convex hull gift wrap

#define polygon vector<geovector>

polygon giftwrap(vector<geovector>& points) {
	int n = points.size();
	polygon hull;

	geovector pivot = *min_element(points.begin(), points.end());
	//가장 왼쪽, 아래에 있는 점을 찾는다.

	map<pair<double, double>, int> mp;

	hull.push_back(pivot);
	mp[{pivot.x, pivot.y}] = 1;
	int tt = 0;
	while (1) {
		//printf("%d\n", ++tt);
		geovector last = hull.back(), next = points[0];
		double cross, dist;
		//last 는 마지막으로 hull 에 포함된 점

		for (int i = 1; i < n; ++i) {
			double tcross = ccw(last, next, points[i]);
			double tdist = (next - last).norm() - (points[i] - last).norm();

			if ( ( tcross > 0 || (tcross == 0 && tdist < 0))  && mp.count({ points[i].x, points[i].y }) == 0 ) next = points[i];
		}

		int cnt = 0;

		for (int i = 0; i < n; ++i) {
			double tcross = ccw(last, next, points[i]);
			if (mp.count({ points[i].x, points[i].y })) {
				++cnt;
				continue;
			}
			if (tcross != 0) continue;
			if ((next - last).norm() > (points[i] - last).norm()) {
				next = points[i];
			}
		}

		//한바퀴를 다 돌아서 처음으로 돌아오면 break.
		if (pivot == next) break;
		if (cnt == n) break;

		hull.push_back(next);
		mp[{next.x, next.y}] = 1;
	}

	return hull;
}

int N;
vector<geovector> input, ans;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//ifstream cin;
	//cin.open("input.txt");

	cin >> N;

	for (int i = 0; i < N; ++i) {
		int s, e;
		char F;
		cin >> s >> e >> F;
		if(F == 'Y') input.push_back(geovector(s, e));
	}

	ans = giftwrap(input);

	//FILE* pfile;
	//pfile = fopen("output.txt", "w");

	printf("%d\n", ans.size());

	printf("%0.lf %0.lf\n", ans[0].x, ans[0].y);

	for (int i = ans.size() - 1; i > 0; --i) {
		printf("%0.lf %0.lf\n", ans[i].x, ans[i].y);
	}

	return 0;
}

*/