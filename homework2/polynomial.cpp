#include "polynomial.h"
#include <iostream>
#include <cmath>

Polynomial::Polynomial() {
	mindeg = 0;
	maxdeg = 0;
	n = 0;
	factors = new int[1];
	factors[0] = 0;
}

Polynomial::Polynomial(int mind, int maxd, int* factors1) {
	mindeg = mind;
	maxdeg = maxd;
	n = maxd - mind + 1;
	// if (maxdeg == mindeg && mindeg == 0) n = 0;
	factors = new int[n];
	for (int i = 0; i < n; i++) {
		factors[i] = factors1[i];
	}
}

Polynomial::Polynomial(const Polynomial& other) {
	mindeg = other.mindeg;
	maxdeg = other.maxdeg;
	n = maxdeg - mindeg + 1;
	// if (maxdeg == mindeg && mindeg == 0) n = 0;
	factors = new int[n];
	for (int i = 0; i < n; i++) {
		factors[i] = other.factors[i];
	}
}

Polynomial::~Polynomial() {
	delete[]factors;
}

Polynomial& Polynomial::operator=(const Polynomial& other) {
	if (&other == this)
		return *this;

	mindeg = other.mindeg;
	maxdeg = other.maxdeg;
	delete[] factors;
	n = maxdeg - mindeg + 1;
	// if (maxdeg == mindeg && mindeg == 0) n = 0;
	factors = new int[n];
	for (int i = 0; i < n; i++) {
		factors[i] = other.factors[i];
	}
	return *this;
}

std::ostream& operator<<(std::ostream& stream, const Polynomial& other) {
	if (other.n == 0) {
		stream << '0';
	}
	else {
		for (int i = other.n - 1; i >= 0; i--) {
			if (other.factors[i] != 0) {
				if (i == other.n - 1) {
					if (other.factors[i] == -1) {
						if (i + other.mindeg == 0) {
							stream << "-1";
						}
						else stream << '-';
					}
					else {
						if (other.factors[i] == 1 && i + other.mindeg == 0) {
							stream << '1';
						}
						else {
							if (other.factors[i] != 1) {
								stream << other.factors[i];
							}
						}
					} 
				}
				else {
					if (other.factors[i] < 0) {
						if (other.factors[i] == -1) {
							if (i + other.mindeg == 0) {
								stream << "-1";
							}
							else stream << '-';
						}
						else stream << other.factors[i];
					}
					else {
						if (other.factors[i] == 1) {
							if (other.mindeg + i == 0) {
								stream << "+1";
							}
							else stream << '+';
						}
						else {
							if (other.factors[i] != 0) {
								stream << '+' << other.factors[i];
							}
						}
					}
				}
				if (other.mindeg + i == 1) {
					stream << 'x';
				}
				else if (other.mindeg + i != 0) {
					stream << "x^" << other.mindeg + i;
				}
			}
		}
	}
	return stream;
}

std::istream& operator>>(std::istream& stream, Polynomial& other) {
	stream >> other.mindeg >> other.maxdeg;
	for (int i = 0; i < other.mindeg - other.maxdeg + 1; i++) {
		stream >> other.factors[i];
	}
	return stream;
}

bool operator==(const Polynomial& pol1, const Polynomial& pol2) {
	Polynomial res1(pol1.mindeg, pol1.maxdeg, pol1.factors);
	Polynomial res2(pol2.mindeg, pol2.maxdeg, pol2.factors);
	res1 = res1.zerocheck();
	res2 = res2.zerocheck();
	if (res1.mindeg != res2.mindeg || res1.maxdeg != res2.maxdeg) {
		return false;
	}
	for (int i = 0; i < res1.n; i++) {
		if (res1.factors[i] != res2.factors[i]) {
			return false;
		}
	}
	return true;
}

bool operator!=(const Polynomial& pol1, const Polynomial& pol2) {
	return !(pol1 == pol2);
}

Polynomial operator+(const Polynomial& pol1, const Polynomial& pol2) {
	if (pol1.n == 0) {
		return pol2;
	}
	if (pol2.n == 0) {
		return pol1;
	}
	Polynomial res = Polynomial();
	if (pol1.mindeg < pol2.mindeg) {
		res.mindeg = pol1.mindeg;
	}
	else res.mindeg = pol2.mindeg;
	if (pol2.maxdeg < pol1.maxdeg) {
		res.maxdeg = pol1.maxdeg;
	}
	else res.maxdeg = pol2.maxdeg;

	res.n = res.maxdeg - res.mindeg + 1;

	delete[] res.factors;
	res.factors = new int[res.n];
	for (int i = 0; i < res.n; i++) {
		res.factors[i] = 0;
	}

	for (int i = 0; i < pol1.n; i++) {
		res.factors[pol1.mindeg - res.mindeg + i] += pol1.factors[i];
	}
	for (int i = 0; i < pol2.n; i++) {
		res.factors[pol2.mindeg - res.mindeg + i] += pol2.factors[i];
	}
	return res;
}

Polynomial operator-(const Polynomial& pol1, const Polynomial& pol2) {
	return pol1 + (-1 * pol2);
}

Polynomial operator-(const Polynomial& other) {
	return -1 * other;
}

Polynomial operator/(const Polynomial& other, int value) {
	Polynomial res(other.mindeg, other.maxdeg, other.factors);
	for (int i = 0; i < res.n; i++) {
		res.factors[i] /= value;
	}
	res = res.zerocheck();
	return res;
}

Polynomial operator*(int value, const Polynomial& other) {
	Polynomial res(other.mindeg, other.maxdeg, other.factors);
	for (int i = 0; i < other.n; i++)
	{
		res.factors[i] *= value;
	}
	return res;
}

Polynomial operator*(const Polynomial& other, int value) {
	return value * other;
}

Polynomial operator*(const Polynomial& pol1, const Polynomial& pol2) {
	if (pol1.n == 0 || pol2.n == 0) {
		return Polynomial();
	}

	Polynomial res = Polynomial();
	res.mindeg = pol1.mindeg + pol2.mindeg;
	res.maxdeg = pol1.maxdeg + pol2.maxdeg;
	res.n = res.maxdeg - res.mindeg + 1;
	delete[] res.factors;
	res.factors = new int[res.n];
	for (int i = 0; i < res.n; i++) {
		res.factors[i] = 0;
	}
	for (int i = 0; i < pol1.n; i++) {
		for (int j = 0; j < pol2.n; j++) {
			res.factors[i + j] += pol2.factors[j] * pol1.factors[i];
		}
	}
	return res;
}

Polynomial operator-=(const Polynomial& pol1, const Polynomial& pol2) {
	return pol1 - pol2;
}

Polynomial operator+=(const Polynomial& pol1, const Polynomial& pol2) {
	return pol1 + pol2;
}

Polynomial operator*=(const Polynomial& pol1, const Polynomial& pol2) {
	return pol1 * pol2;
}

Polynomial operator/=(const Polynomial& other, int value) {
	return other / value;
}

double Polynomial::get(int value) {
	double res = 0;
	int j = mindeg;
	for (int i = 0; i < n; i++) {
		res += factors[i] * pow(value, j);
		j++;
	}
	return res;
}

int& Polynomial::operator[](int index) const {
	int temp = 0;
	if ((index > maxdeg) || (index < mindeg))
		return temp;
	else
		return factors[index - mindeg];
}

int& Polynomial::operator[](int index) {
	if (index > maxdeg) {
		int* temp = new int[n];
		for (int i = 0; i < n; i++)
			temp[i] = factors[i];
		delete[] factors;
		factors = new int[index - mindeg + 1];
		for (int i = 0; i < index - mindeg + 1; i++)
			factors[i] = 0;
		for (int i = 0; i < n; i++)
			factors[i] = temp[i];
		maxdeg = index;
		n = maxdeg - mindeg + 1;
		return factors[maxdeg - mindeg];
	}
	if (index < mindeg) {
		int* temp = new int[n];
		for (int i = 0; i < n; i++)
			temp[i] = factors[i];
		delete[] factors;
		factors = new int[maxdeg - index + 1];
		for (int i = 0; i < maxdeg - index + 1; i++)
			factors[i] = 0;
		for (int i = mindeg - index, j = 0; i < maxdeg - index + 1; i++, j++)
			factors[i] = temp[j];
		mindeg = index;
		return factors[0];
	}
	return factors[index - mindeg];
}

Polynomial Polynomial::zerocheck() {
	Polynomial res(mindeg, maxdeg, factors);
	int i = res.n - 1;
	while (res.factors[i] == 0 && i > -1) {
		i--;
	}
	if (i == -1) {
		res.mindeg = 0;
		res.maxdeg = 0;
		res.n = 1;
		delete[]res.factors;
		res.factors = new int[res.n];
		res.factors[0] = 0;
	}
	else {
		res.maxdeg = i + res.mindeg;
		int i = 0;
		while (res.factors[i] == 0) {
			i++;
		}
		res.mindeg += i;
		res.n = res.maxdeg - res.mindeg + 1;
		int* help = new int[res.n];
		for (int j = 0; j < res.n; j++) {
			help[j] = res.factors[j + i];
		}
		delete[]res.factors;
		res.factors = new int[res.n];
		for (i = 0; i < res.n; i++) {
			res.factors[i] = help[i];
		}
		delete[]help;
	}
	return res;
}
