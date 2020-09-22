// geometric vector

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
//#include <cmath>
using namespace std;

struct geovector {
	double x, y;
	const double PI = 2.0 * acos(0.0);
	explicit geovector(double x_ = 0, double y_ = 0) {
		x = x_, y = y_;
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