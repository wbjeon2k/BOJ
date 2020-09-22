// BOJ1708

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

	hull.push_back(pivot);
	while (1) {
		geovector last = hull.back(), next = points[0];
		//last 는 마지막으로 hull 에 포함된 점

		for (int i = 1; i < n; ++i) {
			double cross = ccw(last, next, points[i]);
			double dist = (next - last).norm() - (points[i] - last).norm();

			//last 기준으로 모든 점들 중 가장 왼쪽에 있는 점을 찾는다.
			//평행한 경우 거리가 더 먼 점을 선택.
			if (cross > 0 || cross == 0 && dist < 0) {
				next = points[i];
			}
		}

		//한바퀴를 다 돌아서 처음으로 돌아오면 break.
		if (next == pivot) break;

		hull.push_back(next);
	}
	
	return hull;
}

int N;
vector<geovector> input, ans;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;

	for (int i = 0; i < N; ++i) {
		int s, e;
		cin >> s >> e;
		input.push_back(geovector(s, e));
	}

	ans = giftwrap(input);

	printf("%d\n", ans.size());

	return 0;
}