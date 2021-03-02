#include "geometry.h"
#include <cmath>

Point::Point() {
	x = 0;
	y = 0;
}

Point::Point(int x1, int y1) {
	setPoint(x1, y1);
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

void Point::setPoint(int x1, int y1) {
	x = x1;
	y = y1;
}

PolygonalChain::PolygonalChain(int n1, Point* points1) {
	setPolygonalChain(n1, points1);
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
	//todo memory leak
	points = new Point[n];
	for (int i = 0; i < n; i++) {
		points[i] = other.points[i];
	}
	return *this;
}

//todo move to constructor
void PolygonalChain::setPolygonalChain(int n1, Point* points1) {
	n = n1;
	points = new Point[n];
	for (int i = 0; i < n; i++) {
		points[i] = points1[i];
	}
}

double PolygonalChain::perimeter() const {
	double per = 0;
	double piece;
	for (int i = 1; i < n; i++) {
		piece = sqrt(pow((points[i].getX() - points[i - 1].getX()), 2) + pow((points[i].getY() - points[i - 1].getY()), 2));
		per = per + piece;
	}
	return per;
};

ClosedPolygonalChain::ClosedPolygonalChain(const ClosedPolygonalChain& other) : PolygonalChain(other) {}

ClosedPolygonalChain& ClosedPolygonalChain::operator=(const ClosedPolygonalChain& other) {
	PolygonalChain::operator=(other);
	return *this;
}

double ClosedPolygonalChain::perimeter() const {
	//todo copy-paste, use from base class
	double per = 0;
	double piece;
	for (int i = 1; i < n; i++) {
		piece = sqrt(pow((points[i].getX() - points[i - 1].getX()), 2) + pow((points[i].getY() - points[i - 1].getY()), 2));
		per = per + piece;
	}
	piece = sqrt(pow((points[0].getX() - points[n - 1].getX()), 2) + pow((points[0].getY() - points[n - 1].getY()), 2));
	per = per + piece;
	return per;
}

Polygon::Polygon(const Polygon& other) : ClosedPolygonalChain(other) {}

Polygon& Polygon::operator=(const Polygon& other) {
	ClosedPolygonalChain::operator=(other);
	return *this;
}

double Polygon::area() const {
	//todo remove doubles
	double res = 0;
	double mult;
	for (int i = 1; i < n; i++) {
		mult = (double)points[i - 1].getX() * (double)points[i].getY();
		res = res + mult;
		mult = (double)points[i].getX() * (double)points[i - 1].getY();
		res = res - mult;
	}
	mult = (double)points[n - 1].getX() * (double)points[0].getY();
	res = res + mult;
	mult = (double)points[0].getX() * (double)points[n - 1].getY();
	res = res - mult;
	if (res > 0) {
		return 0.5 * res;
	}
	else return -0.5 * res;
}

Triangle::Triangle(const Triangle& other) : Polygon(other) {}

Triangle& Triangle::operator=(const Triangle& other) {
	Polygon::operator=(other);
	return *this;
}
//todo without sqrt
int Triangle::hasRightAngle() const {
	double side1, side2, side3;
	side1 = pow((sqrt(pow((points[0].getX() - points[1].getX()), 2) + pow((points[0].getY() - points[1].getY()), 2))), 2);
	side2 = pow((sqrt(pow((points[2].getX() - points[1].getX()), 2) + pow((points[2].getY() - points[1].getY()), 2))), 2);
	side3 = pow((sqrt(pow((points[2].getX() - points[0].getX()), 2) + pow((points[2].getY() - points[0].getY()), 2))), 2);
	if (side1 + side2 == side3 || side1 + side3 == side2 || side2 + side3 == side1) {
		return 1;
	}
	else return 0;
}

Trapezoid::Trapezoid(const Trapezoid& other) : Polygon(other) {}

Trapezoid& Trapezoid::operator=(const Trapezoid& other) {
	Polygon::operator=(other);
	return *this;
}

double Trapezoid::height() const {
	double a = sqrt(pow((points[1].getX() - points[2].getX()), 2) + pow((points[1].getY() - points[2].getY()), 2));
	double b = sqrt(pow((points[0].getX() - points[3].getX()), 2) + pow((points[0].getY() - points[3].getY()), 2));
	double res = 0;
	double mult;
	for (int i = 1; i < n; i++) {
		mult = (double)points[i - 1].getX() * (double)points[i].getY();
		res = res + mult;
		mult = (double)points[i].getX() * (double)points[i - 1].getY();
		res = res - mult;
	}
	mult = (double)points[n - 1].getX() * (double)points[0].getY();
	res = res + mult;
	mult = (double)points[0].getX() * (double)points[n - 1].getY();
	res = res - mult;
	if (res > 0) {
		res = 0.5 * res;
	}
	else res = -0.5 * res;
	double H = 2 * res / (a + b);
	return H;
}

//todo area and perimeter
RegularPolygon::RegularPolygon(const RegularPolygon& other) : Polygon(other) {}

RegularPolygon& RegularPolygon::operator=(const RegularPolygon& other) {
	Polygon::operator=(other);
	return *this;
}