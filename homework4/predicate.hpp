#ifndef PREDICATE_HPP
#define PREDICATE_HPP
#include <functional>

template <class InputIterator, class UnaryPredicate>
bool allOf(InputIterator begin, InputIterator end, const UnaryPredicate& func){
	while (begin != end) {
		if (!func(*begin)) {
			return false;
		}
		++begin;
	}
	return true;
};

template <class InputIterator, class UnaryPredicate>
bool anyOf(InputIterator begin, InputIterator end, const UnaryPredicate& func) {
	while (begin != end) {
		if (func(*begin)) {
			return true;
		}
		++begin;
	}
	return false;
};

template <class InputIterator, class UnaryPredicate>
bool noneOf(InputIterator begin, InputIterator end, const UnaryPredicate& func) {
	return !anyOf(begin, end, func);
};

template <class InputIterator, class UnaryPredicate>
bool oneOf(InputIterator begin, InputIterator end, const UnaryPredicate& func) {
	int check = 0;
	while (begin != end) {
		if (func(*begin)) {
			++check;
		}
		++begin;
	}
	if (check == 1) {
		return true;
	}
	else return false;
};

template <class BidirectionalIterator, class BinaryPredicate = std::less<>>
bool isSorted(BidirectionalIterator begin, BidirectionalIterator end, const  BinaryPredicate func = BinaryPredicate()) {
	if (begin == end) {
		return true;
	}
	while (begin != end - 1) {
		if (!func(*begin, *(begin + 1))) {
			return false;
		}
		++begin;
	}
	return true;
};

template <class ForwardIterator, class UnaryPredicate>
bool isPartitioned(ForwardIterator begin, ForwardIterator end, const UnaryPredicate& func) {
	while (begin != end && func(*begin)) {
		++begin;
	}
	while (begin != end) {
		if (func(*begin)) {
			return false;
		}
		++begin;
	}
	return true;
};

template <class InputIterator, class T>
InputIterator findNot(InputIterator begin, InputIterator end, const T& value) {
	while (begin != end) {
		if (*begin != value) {
			return begin;
		}
		++begin;
	}
	return end;
};

template <class InputIterator, class T>
InputIterator findBackward(InputIterator begin, InputIterator end, const T& value) {
	InputIterator ans = end;
	while (begin != end) {
		if (*begin == value) {
			ans = begin;
		}
		++begin;
	}
	return ans;
};

template <class BidirectionalIterator, class BinaryPredicate>
bool isPalindrome(BidirectionalIterator begin, BidirectionalIterator end, const BinaryPredicate& func) {
	--end;
	while (begin != end) {
		if (!func(*begin, *end)) {
			return false;
		}
		++begin;
		if (begin == end) return true;
		--end;
	}
	return true;
};

#endif
