#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <sstream>


class Polynomial {
private:
	int mindeg;
	int maxdeg;
	int n;
	int* factors;
public:
	Polynomial();
	Polynomial(int mind, int maxd, int* factors1);
	Polynomial(const Polynomial& other);
	virtual ~Polynomial();
	Polynomial& operator=(const Polynomial& other);
	
	friend bool operator==(const Polynomial& pol1, const Polynomial& pol2);
	friend bool operator!=(const Polynomial& pol1, const Polynomial& pol2);

	int operator[](int num) const;
	int& operator[](int num);

	friend Polynomial operator+(const Polynomial& pol1, const Polynomial& pol2);
	friend Polynomial operator-(const Polynomial& pol1, const Polynomial& pol2);
	friend Polynomial operator-(const Polynomial& other);
	friend Polynomial operator/(const Polynomial& other, int num);
	friend Polynomial operator*(int num, const Polynomial& other);
	friend Polynomial operator*(const Polynomial& other, int num);
	friend Polynomial operator*(const Polynomial& pol1, const Polynomial& pol2);

	double get(int num);
	Polynomial zerocheck();

	Polynomial& operator-=(const Polynomial& other);
	Polynomial& operator+=(const Polynomial& other);
	Polynomial& operator*=(const Polynomial& other);
	Polynomial& operator*=(int num);
	Polynomial& operator/=(int num);

	friend std::ostream& operator<<(std::ostream& stream, const Polynomial& other);
	friend std::istream& operator>>(std::istream& stream, Polynomial& other);
};

#endif
