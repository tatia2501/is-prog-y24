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
	factors = new int[n];
	for (int i = 0; i < n; i++) {
		factors[i] = factors1[i];
	}
}

Polynomial::Polynomial(const Polynomial& other) {
	mindeg = other.mindeg;
	maxdeg = other.maxdeg;
	n = maxdeg - mindeg + 1;
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
	factors = new int[n];
	for (int i = 0; i < n; i++) {
		factors[i] = other.factors[i];
	}
	return *this;
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

int& Polynomial::operator[](int num) const {
	if ((num > maxdeg) || (num < mindeg)) {
		int help = 0;
		return help;
	}
	else return factors[num - mindeg];
}

int& Polynomial::operator[](int num) {
	if (num > maxdeg) {
		int* help = new int[n];
		for (int i = 0; i < n; i++) {
			help[i] = factors[i];
		}
		delete[]factors;
		factors = new int[num - mindeg + 1];
		for (int i = n; i < num - mindeg + 1; i++) {
			factors[i] = 0;
		}
		for (int i = 0; i < n; i++) {
			factors[i] = help[i];
		}
		delete[]help;
		maxdeg = num;
		n = maxdeg - mindeg + 1;
		return factors[maxdeg - mindeg];
	} 
	else if (num < mindeg) {
		int* help = new int[n];
		for (int i = 0; i < n; i++) {
			help[i] = factors[i];
		}
		delete[]factors;
		factors = new int[maxdeg - num + 1];
		for (int i = 0; i < maxdeg - num + 1; i++) {
			factors[i] = 0;
		}
		int j = 0;
		for (int i = mindeg - num; i < maxdeg - num + 1; i++) {
			factors[i] = help[j];
			j++;
		}
		delete[]help;
		mindeg = num;
		return factors[0];
	}
	return factors[num - mindeg];
}

Polynomial operator+(const Polynomial& pol1, const Polynomial& pol2) {
	Polynomial res(pol1.mindeg, pol1.maxdeg, pol1.factors);
	res += pol2;
	return res;
}

Polynomial operator-(const Polynomial& pol1, const Polynomial& pol2) {
	return pol1 + (-1 * pol2);
}

Polynomial operator-(const Polynomial& other) {
	return -1 * other;
}

Polynomial operator/(const Polynomial& other, int num) {
	Polynomial res(other.mindeg, other.maxdeg, other.factors);
	for (int i = 0; i < res.n; i++) {
		res.factors[i] /= num;
	}
	return res.zerocheck();
}

Polynomial operator*(int num, const Polynomial& other) {
	if (num != 0) {
		Polynomial res(other.mindeg, other.maxdeg, other.factors);
		for (int i = 0; i < other.n; i++) {
			res.factors[i] *= num;
		}
		return res;
	} else return Polynomial();
}

Polynomial operator*(const Polynomial& other, int num) {
	return num * other;
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

Polynomial& Polynomial::operator+=(const Polynomial& other) {
	if (n == 0) {
		*this = other;
		return *this;
	}
	if (other.n == 0) {
		return *this;
	}
	int min, max;
	if (mindeg < other.mindeg) {
		min = mindeg;
	} else min = other.mindeg;
	if (other.maxdeg < maxdeg) {
		max = maxdeg;
	} else max = other.maxdeg;

	int size = max - min + 1;
	int* help = new int[size];
	for (int i = 0; i < size; i++) {
		help[i] = 0;
	}
	for (int i = 0; i < n; i++) {
		help[mindeg - min + i] += factors[i];
	}
	for (int i = 0; i < other.n; i++) {
		help[other.mindeg - min + i] += other.factors[i];
	}
	delete[]factors;
	factors = new int[size];
	for (int i = 0; i < size; i++) {
		factors[i] = help[i];
	}
	delete[]help;
	mindeg = min;
	maxdeg = max;
	n = size;
	return *this;
}

Polynomial& Polynomial::operator-=(const Polynomial& other) {
	*this = *this - other;
	return *this;
}

Polynomial& Polynomial::operator*=(const Polynomial& other) {
	*this = *this * other;
	return *this;
}

Polynomial& Polynomial::operator*=(int num) {
	*this = *this * num;
	return *this;
}

Polynomial& Polynomial::operator/=(int num) {
	*this = *this / num;
	return *this;
}

double Polynomial::get(int num) {
	double res = 0;
	int j = mindeg;
	for (int i = 0; i < n; i++) {
		res += factors[i] * pow(num, j);
		j++;
	}
	return res;
}

Polynomial Polynomial::zerocheck() {
	int i = n - 1;
	while (factors[i] == 0 && i > -1) i--;

	if (i == -1) {
		*this = Polynomial();
	}
	else {
		maxdeg = i + mindeg;
		i = 0;
		while (factors[i] == 0) i++;
		mindeg += i;
		n = maxdeg - mindeg + 1;
		int* help = new int[n];
		for (int j = 0; j < n; j++) {
			help[j] = factors[j + i];
		}
		delete[]factors;
		factors = new int[n];
		for (i = 0; i < n; i++) {
			factors[i] = help[i];
		}
		delete[]help;
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
				if (other.mindeg + i != 0) {
					stream << 'x';
					if (other.mindeg + i != 1) {
						stream << '^' << other.mindeg + i;
					}
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
