#ifndef GEOMETRY_H
#define GEOMETRY_H

class Point {
private:
	int x;
	int y;
public:
	Point();
	Point(int x1, int y1);
	Point(const Point& other);
	Point& operator=(const Point& other);

	int getX() const {
		return x;
	}
	int getY() const {
		return y;
	}
};

class PolygonalChain {
public:
	int n;
	Point* points;
	PolygonalChain(int n1, Point* points1);
	PolygonalChain(const PolygonalChain& other);
	PolygonalChain& operator=(const PolygonalChain& other);
	//fixed destructor
	//fixed destructor virtual
	virtual ~PolygonalChain();

	int getN() const {
		return n;
	}
	Point getPoint(int num) const {
		return points[num];
	}

	virtual double perimeter() const;
};

class ClosedPolygonalChain : public PolygonalChain {
public:
	ClosedPolygonalChain(
		int n,
		Point* points
	)
		: PolygonalChain(n, points)
	{}
	ClosedPolygonalChain(const ClosedPolygonalChain& other);
	ClosedPolygonalChain& operator=(const ClosedPolygonalChain& other);

	virtual double perimeter() const;
	int getN() const {
		return n;
	}
	Point getPoint(int num) const {
		return points[num];
	}
};

class Polygon : public ClosedPolygonalChain {
public:
	Polygon(
		int n,
		Point* points
	)
		: ClosedPolygonalChain(n, points)
	{}
	Polygon(const Polygon& other);
	Polygon& operator=(const Polygon& other);
	virtual double area() const;
};

class Triangle : public Polygon {
public:
	Triangle(
		int n,
		Point* points
	)
		: Polygon(n, points)
	{}
	Triangle(const Triangle& other);
	Triangle& operator=(const Triangle& other);
	bool hasRightAngle() const;
};

class Trapezoid : public Polygon {
public:
	Trapezoid(
		int n,
		Point* points
	)
		: Polygon(n, points)
	{}
	Trapezoid(const Trapezoid& other);
	Trapezoid& operator=(const Trapezoid& other);
	double height() const;
};

class RegularPolygon : public Polygon {
public:
	RegularPolygon(
		int n,
		Point* points
	)
		: Polygon(n, points)
	{}
	RegularPolygon(const RegularPolygon& other);
	RegularPolygon& operator=(const RegularPolygon& other);
	double area() const;
	double perimeter() const;
};

#endif
