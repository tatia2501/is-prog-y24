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

	int& operator[](int index) const;
	int& operator[](int index);

	Polynomial zerocheck();

	friend Polynomial operator+(const Polynomial& pol1, const Polynomial& pol2);
	friend Polynomial operator-(const Polynomial& pol1, const Polynomial& pol2);
	friend Polynomial operator-(const Polynomial& other);
	friend Polynomial operator/(const Polynomial& other, int value);
	friend Polynomial operator*(int value, const Polynomial& other);
	friend Polynomial operator*(const Polynomial& other, int value);
	friend Polynomial operator*(const Polynomial& pol1, const Polynomial& pol2);

	friend Polynomial operator-=(const Polynomial& pol1, const Polynomial& pol2);
	friend Polynomial operator+=(const Polynomial& pol1, const Polynomial& pol2);
	friend Polynomial operator*=(const Polynomial& pol1, const Polynomial& pol2);
	friend Polynomial operator/=(const Polynomial& other, int value);

	double get(int value);

	friend std::ostream& operator<<(std::ostream& stream, const Polynomial& other);
	friend std::istream& operator>>(std::istream& stream, Polynomial& other);
};

#endif 
