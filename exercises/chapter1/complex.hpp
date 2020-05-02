#include <complex>

namespace quantum {
	template<typename T>
	std::complex<T> add(const std::complex<T>& a, const std::complex<T>& b) {
		return {a.real() + b.real(), a.imag() + b.imag()};
	}

	template<typename T>
	std::complex<T> subtract(const std::complex<T>& a, const std::complex<T>& b) {
		return {a.real() - b.real(), a.imag() - b.imag()};
	}

	template<typename T>
	std::complex<T> multiply(const std::complex<T>& a, const std::complex<T>& b) {
		return {(a.real() * b.real()) - (a.imag() * b.imag()), (a.real() * b.imag()) + (a.imag() * b.real())};
	}

	template<typename T>
	std::complex<T> multiply(const std::complex<T>& a, const T& b) {
		return {a.real() * b, a.imag() * b};
	}

	template<typename T>
	std::complex<T> divide(const std::complex<T>& a, const std::complex<T>& b) {
		/*
		 * (x, y) = (a1, b1) / (a2, b2)
		 *      x  = (a1a2 + b1b2) / (a2^2 + b2^2)
		 *      y  = (a2b1 - a1b2) / (a2^2 + b2^2)
		 * 		   = x / yi
		 */
		const T a1 = a.real();
		const T b1 = a.imag();
		const T a2 = b.real();
		const T b2 = b.imag();
		const T x = (a1 * a2 + b1 * b2) / (a2 * a2 + b2 * b2);
		const T y = (a2 * b1 - a1 * b2) / (a2 * a2 + b2 * b2);
		return {x, y};
	}

	template<typename T>
	T modulus(const std::complex<T>& a) {
		return sqrt((a.real() * a.real()) + (a.imag() * a.imag()));
	}

	template<typename T>
	std::complex<T> conjugate(const std::complex<T>& a) {
		return multiply<T>(a, -1);
	}

	template<typename T>
	std::complex<T> polar(const std::complex<T>& a) {
		const T p = modulus(a);
		const T theta = std::atan(T(a.real() / a.imag()));
		return {p, theta};
	}
	
	template<typename T>
	std::complex<T> to_complex(const T p, const T theta) {
		return {p * std::cos(theta), p * std::sin(theta)};
	}
}
