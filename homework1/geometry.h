#ifndef GEOMETRY_H
#define GEOMETRY_H

//Точка
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

//Ломаная
class PolygonalChain {
public:
	int n;
	Point* points;
	PolygonalChain(int n1, Point* points1);
	PolygonalChain(const PolygonalChain& other);
	PolygonalChain& operator=(const PolygonalChain& other);
//fixed destructor
	~PolygonalChain();

	int getN() const {
		return n;
	}
	Point getPoint(int num) const {
		return points[num];
	}

	virtual double perimeter() const;
};

//Замкнутая ломаная
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
	~ClosedPolygonalChain();

	virtual double perimeter() const;
	int getN() const {
		return n;
	}
	Point getPoint(int num) const {
		return points[num];
	}
};

//Многоугольник
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
	~Polygon();
	virtual double area() const;
};

//Треугольник
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
	~Triangle();
	int hasRightAngle() const;
};

//Трапеция
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
	~Trapezoid();
	double height() const;
};

//Правильный многоугольник
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
	~RegularPolygon();
	double area() const;
	double perimeter() const;
};

#endif
