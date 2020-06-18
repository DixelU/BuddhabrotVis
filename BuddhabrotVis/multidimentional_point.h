#pragma once
#include <array>
#include <ostream>
#include <initializer_list>

template<size_t dims>
struct Point {
	std::array<double, dims> pt;
	Point() {
		for (int i = 0; i < dims; i++)
			pt[i] = 0;
	}
	Point(const Point<dims> &P) {
		for (int i = 0; i < dims; i++)
			pt[i] = P.pt[i];
	}
	Point(std::initializer_list<double> il_d) {
		std::initializer_list<double>::iterator y = il_d.begin();
		for (size_t i = 0; i < dims && y != il_d.end(); i++, y++)
			pt[i] = *y;
	}
	Point(std::initializer_list<int> il) {
		std::initializer_list<int>::iterator y = il.begin();
		for (size_t i = 0; i < dims && y != il.end(); i++, y++)
			pt[i] = *y;
	}
	double get_norm() {
		double sum = 0;
		for (int i = 0; i < dims; i++)
			sum += pt[i] * pt[i];
		return sqrt(sum);
	}
	inline size_t get_dims() const {
		return dims;
	}
	inline double& operator[](size_t D) {
		return pt[D];
	}
	inline double operator[](size_t D) const {
		return pt[D];
	}
	inline Point<dims> operator+(const Point<dims> &P) const {
		Point<dims> N;
		for (size_t i = 0; i < dims; i++)
			N[i] = pt[i] + P[i];
		return N;
	}
	inline Point<dims> operator-(const Point<dims> &P) const {
		Point<dims> N;
		for (size_t i = 0; i < dims; i++)
			N[i] = pt[i] - P[i];
		return N;
	}
	inline Point<dims> operator*(double M) const {
		Point<dims> N;
		for (size_t i = 0; i < dims; i++)
			N[i] = pt[i] * M;
		return N;
	}
	inline double operator*(const Point<dims> &P) const {
		double S;
		for (size_t i = 0; i < dims; i++)
			S += pt[i] * P[i];
		return S;
	}
	inline Point<dims>& operator-() {
		for (size_t i = 0; i < dims; i++)
			pt[i] = 0 - pt[i];
		return *this;
	}
};

template<size_t dims>
std::ostream& operator<<(std::ostream& os, const Point<dims> &P) {
	os << "(";
	for (size_t i = 0; i < dims; i++) {
		os << P[i];
		if (i != dims - 1)
			os << ",";
	}
	os << ")";
	return os;
}

template<size_t dims>
inline Point<dims> operator*(double M, Point<dims> P) {
	Point<dims> N;
	for (size_t i = 0; i < dims; i++)
		N[i] = P[i] * M;
	return N;
}