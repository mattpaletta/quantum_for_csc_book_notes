#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <cmath>

#include "complex.hpp"

TEST_CASE("example 1.1.2", "[chapter 1]") {
	std::complex<float> a{-3, 1};
	std::complex<float> b{2, -4};
	CHECK(quantum::add(a, b) == a + b);
}

TEST_CASE("example 1.1.3 c1 + c2", "[chapter 1]") {
	std::complex<float> c1{-3, 1};
	std::complex<float> c2{2, -4};
	CHECK(quantum::add(c1, c2) == c1 + c2);
}

TEST_CASE("example 1.1.3 c1 * c2", "[chapter 1]") {
	std::complex<float> c1{-3, 1};
	std::complex<float> c2{2, -4};
	CHECK(quantum::multiply(c1, c2) == c1 * c2);
}

TEST_CASE("example 1.2.1 c1 * c2", "[chapter 1]") {
	std::complex<float> c1{3, -2};
	std::complex<float> c2{1, 2};
	CHECK(quantum::multiply(c1, c2) == c1 * c2);
}

TEST_CASE("exercise 1.2.2 c1 * c2", "[chapter 1]") {
	std::complex<float> c1{3, -2};
	std::complex<float> c2{1, 2};
	CHECK(quantum::multiply(c1, c2) == c1 * c2);
	CHECK(quantum::multiply(c2, c1) == c1 * c2);
}

TEST_CASE("exercise 1.2.2 c1 * c2 == c2 * c1", "[chapter 1]") {
	float c1 = 5;
	std::complex<float> c2{1, 2};
	CHECK(quantum::multiply(c2, c1) == c2 * c1);
}

TEST_CASE("example 1.2.2 c1 / c2", "[chapter 1]") {
	std::complex<float> c1{-2, 1};
	std::complex<float> c2{1, 2};
	CHECK(quantum::divide(c1, c2) == c1 / c2);
}

TEST_CASE("example 1.2.3 modulus c1", "[chapter 1]") {
	std::complex<float> c1{1, -1};
	CHECK(quantum::modulus(c1) == Approx(sqrt(2)));
}

TEST_CASE("exercise 1.2.4 modulus c1", "[chapter 1]") {
	std::complex<float> c1{4, -3};
	CHECK(quantum::modulus(c1) == Approx(5.0f));
}

TEST_CASE("programming drill 1.2.1 conjugate c1", "[chapter 1]") {
	std::complex<float> c1{4, -3};
	std::complex<float> c2{1, -1};
	CHECK(quantum::conjugate(c1) + quantum::conjugate(c2) == quantum::conjugate(c1 + c2));
}

const double pi() { return std::atan(1)*4; }
const double to_radians(const double a) { return (pi() * a) / 180; }

TEST_CASE("programming drill 1.3.2 polar c1", "[chapter 1]") {
	std::complex<float> c1{1, -1};
	CHECK(quantum::polar(c1).real() == Approx(1.41421f));
	CHECK(std::abs(quantum::polar(c1).imag()) == Approx(to_radians(45)));
}

TEST_CASE("programming drill 1.3.2 complex c1", "[chapter 1]") {
	CHECK(quantum::to_complex<float>(std::sqrt(2), to_radians(45)).real() == Approx(1.0f));
	CHECK(quantum::to_complex<float>(std::sqrt(2), to_radians(45)).imag() == Approx(1.0f));
}
