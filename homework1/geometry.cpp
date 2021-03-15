#include "geometry.h"
#include <cmath>
#define PI 3.14159265359

Point::Point() {
	x = 0;
	y = 0;
}

Point::Point(int x1, int y1) {
	x = x1;
	y = y1;
}

Point::Point(const Point& other) {
	x = other.x;
	y = other.y;
}

Point& Point::operator=(const Point& other) {
	if (&other == this)
		return *this;

	x = other.x;
	y = other.y;

	return *this;
}

PolygonalChain::PolygonalChain(int n1, Point* points1) {
	n = n1;
	points = new Point[n];
	for (int i = 0; i < n; i++) {
		points[i] = points1[i];
	}
}

PolygonalChain::PolygonalChain(const PolygonalChain& other) {
	n = other.n;
	points = new Point[n];
	for (int i = 0; i < n; i++) {
		points[i] = other.points[i];
	}
}

PolygonalChain& PolygonalChain::operator=(const PolygonalChain& other) {
	if (&other == this)
		return *this;

	n = other.n;
	delete[] points;
	points = new Point[n];
	for (int i = 0; i < n; i++) {
		points[i] = other.points[i];
	}
	return *this;
}

double segment(Point point1, Point point2) {
	return sqrt(pow((point1.getX() - point2.getX()), 2) + pow((point1.getY() - point2.getY()), 2));
}

double PolygonalChain::perimeter() const {
	double per = 0;
	double piece;
	for (int i = 1; i < n; i++) {
		piece = segment(points[i], points[i - 1]);
		per = per + piece;
	}
	return per;
};

PolygonalChain::~PolygonalChain() {
	delete[] points;
}

ClosedPolygonalChain::ClosedPolygonalChain(const ClosedPolygonalChain& other) : PolygonalChain(other) {}

ClosedPolygonalChain& ClosedPolygonalChain::operator=(const ClosedPolygonalChain& other) {
	PolygonalChain::operator=(other);
	return *this;
}

double ClosedPolygonalChain::perimeter() const {
	double per;
	double piece;
	per = PolygonalChain::perimeter();
	piece = segment(points[0], points[n - 1]);
	per = per + piece;
	return per;
}

Polygon::Polygon(const Polygon& other) : ClosedPolygonalChain(other) {}

Polygon& Polygon::operator=(const Polygon& other) {
	ClosedPolygonalChain::operator=(other);
	return *this;
}

double Polygon::area() const {
	int res = 0;
	for (int i = 1; i < n; i++) {
		res = res + points[i - 1].getX() * points[i].getY() - points[i].getX() * points[i - 1].getY();
	}
	res = res + points[n - 1].getX() * points[0].getY() - points[0].getX() * points[n - 1].getY();
	//fixed mb you need abs function
	return 0.5 * abs(res);
}

Triangle::Triangle(const Triangle& other) : Polygon(other) {}

Triangle& Triangle::operator=(const Triangle& other) {
	Polygon::operator=(other);
	return *this;
}

bool Triangle::hasRightAngle() const {
	double side1, side2, side3;
	side1 = pow((points[0].getX() - points[1].getX()), 2) + pow((points[0].getY() - points[1].getY()), 2);
	side2 = pow((points[2].getX() - points[1].getX()), 2) + pow((points[2].getY() - points[1].getY()), 2);
	side3 = pow((points[2].getX() - points[0].getX()), 2) + pow((points[2].getY() - points[0].getY()), 2);
	return side1 + side2 == side3 || side1 + side3 == side2 || side2 + side3 == side1;
}

Trapezoid::Trapezoid(const Trapezoid& other) : Polygon(other) {}

Trapezoid& Trapezoid::operator=(const Trapezoid& other) {
	Polygon::operator=(other);
	return *this;
}

//fixed area from base class
double Trapezoid::height() const {
	double a = segment(points[1], points[2]);
	double b = segment(points[0], points[3]);
	double res = Polygon::area();
	//fixed dont use capital letters for variables
	return 2 * res / (a + b);
}

RegularPolygon::RegularPolygon(const RegularPolygon& other) : Polygon(other) {}

RegularPolygon& RegularPolygon::operator=(const RegularPolygon& other) {
	Polygon::operator=(other);
	return *this;
}

double RegularPolygon::perimeter() const {
	//fixed i think you need function for it
	return segment(points[1], points[0]) * n;
}


double RegularPolygon::area() const {
	double piece;
	piece = segment(points[1], points[0]);
	return 0.25 * piece * piece * n * (cos(PI / n) / sin(PI / n));
}
