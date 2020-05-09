#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <cmath>

#include <chapter2/chapter2.hpp>

TEST_CASE("programming drill 2.1.1 addition", "[chapter 2]") {
	using comp = std::complex<float>;
	const comp x1{5, 13};
	const comp x2{6, 2};
	const comp x3{0.53, -6};
	const comp x4{12, 0};

	const std::array<comp, 4> x{x1, x2, x3, x4};

	const comp y1{7, -8};
	const comp y2{0, 4};
	const comp y3{2, 0};
	const comp y4{9.4, 3};

	const std::array<comp, 4> y{y1, y2, y3, y4};
	const auto result = quantum::addition(x, y);

	CHECK(result[0].real() == Approx(12));
	CHECK(result[0].imag() == Approx(5));

	CHECK(result[1].real() == Approx(6));
	CHECK(result[1].imag() == Approx(6));

	CHECK(result[2].real() == Approx(2.53));
	CHECK(result[2].imag() == Approx(-6));

	CHECK(result[3].real() == Approx(21.4));
	CHECK(result[3].imag() == Approx(3));
}

TEST_CASE("programming drill 2.1.1 inverse", "[chapter 2]") {
	using comp = std::complex<float>;
	const comp x1{5, 13};
	const comp x2{6, 2};
	const comp x3{0.53, -6};
	const comp x4{12, 0};

	const std::array<comp, 4> x{x1, x2, x3, x4};
	for (int i = 0; i < 4; ++i) {
		CHECK(quantum::inverse(x)[i] + x[i] == std::complex<float>{0, 0});
	}
}

TEST_CASE("programming drill 2.1.1 scalar", "[chapter 2]") {
	using comp = std::complex<float>;
	const comp x1{5, 13};
	const comp x2{6, 2};
	const comp x3{0.53, -6};
	const comp x4{12, 0};

	const std::array<comp, 4> x{x1, x2, x3, x4};
	const auto result = quantum::scalar(x, x1);

	CHECK(result[0].real() == Approx(-144.0f));
	CHECK(result[0].imag() == Approx(130.0f));

	CHECK(result[1].real() == Approx(4.0f));
	CHECK(result[1].imag() == Approx(88.0f));

	CHECK(result[2].real() == Approx(80.65f));
	CHECK(result[2].imag() == Approx(-23.11f));

	CHECK(result[3].real() == Approx(60.0f));
	CHECK(result[3].imag() == Approx(156.0f));
}

TEST_CASE("programming drill 2.2.1 addition", "[chapter 2]") {
	using comp = std::complex<float>;
	const comp x1{5, 13};
	const comp x2{6, 2};
	const comp x3{0.53, -6};

	const comp y1{5, 13};
	const comp y2{6, 2};
	const comp y3{0.53, -6};

	const comp z1{5, 13};
	const comp z2{6, 2};
	const comp z3{0.53, -6};

	const std::array<comp, 3> x{x1, x2, x3};
	const std::array<comp, 3> y{y1, y2, y3};
	const std::array<comp, 3> z{z1, z2, z3};

	const quantum::matrix<3, 3, comp> mat{x, y, z};

	const auto result = quantum::addition(mat, mat);
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			CHECK(quantum::inverse(mat)[i][j] + mat[i][j] == std::complex<float>{0, 0});
		}
	}
}

TEST_CASE("programming drill 2.2.1 inverse", "[chapter 2]") {
	using comp = std::complex<float>;
	const comp x1{5, 13};
	const comp x2{6, 2};
	const comp x3{0.53, -6};

	const comp y1{5, 13};
	const comp y2{6, 2};
	const comp y3{0.53, -6};

	const comp z1{5, 13};
	const comp z2{6, 2};
	const comp z3{0.53, -6};

	const std::array<comp, 3> x{x1, x2, x3};
	const std::array<comp, 3> y{y1, y2, y3};
	const std::array<comp, 3> z{z1, z2, z3};

	const quantum::matrix<3, 3, comp> mat{x, y, z};

	const auto result = quantum::inverse(mat);
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			CHECK(result[i][j] + mat[i][j] == std::complex<float>{0, 0});
		}
	}
}

TEST_CASE("programming drill 2.2.1 scalar", "[chapter 2]") {
	using comp = std::complex<float>;
	const comp x1{5, 13};
	const comp x2{6, 2};
	const comp x3{0.53, -6};

	const comp y1{5, 13};
	const comp y2{6, 2};
	const comp y3{0.53, -6};

	const comp z1{5, 13};
	const comp z2{6, 2};
	const comp z3{0.53, -6};

	const std::array<comp, 3> x{x1, x2, x3};
	const std::array<comp, 3> y{y1, y2, y3};
	const std::array<comp, 3> z{z1, z2, z3};

	const quantum::matrix<3, 3, comp> mat{x, y, z};

	const auto result = quantum::scalar(mat, std::complex<float>{0, 0});
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			CHECK(result[i][j] == std::complex<float>{0, 0});
		}
	}
}

TEST_CASE("programming drill 2.2.2", "[chapter 2]") {
	using comp = std::complex<float>;
	const comp Ax1{3, 2};
	const comp Ax2{0, 0};
	const comp Ax3{5, -6};

	const comp Ay1{1, 0};
	const comp Ay2{4, 2};
	const comp Ay3{0, 1};

	const comp Az1{4, -1};
	const comp Az2{0, 0};
	const comp Az3{4, 0};

	const std::array<comp, 3> Ax{Ax1, Ax2, Ax3};
	const std::array<comp, 3> Ay{Ay1, Ay2, Ay3};
	const std::array<comp, 3> Az{Az1, Az2, Az3};

	const quantum::matrix<3, 3, comp> matA{Ax, Ay, Az};

	const comp Bx1{5, 0};
	const comp Bx2{2, -1};
	const comp Bx3{6, -4};

	const comp By1{0, 0};
	const comp By2{4, 5};
	const comp By3{2, 0};

	const comp Bz1{7, -4};
	const comp Bz2{2, 7};
	const comp Bz3{0, 0};

	const std::array<comp, 3> Bx{Bx1, Bx2, Bx3};
	const std::array<comp, 3> By{By1, By2, By3};
	const std::array<comp, 3> Bz{Bz1, Bz2, Bz3};

	const quantum::matrix<3, 3, comp> matB{Bx, By, Bz};

	const comp Cx1{26, -52};
	const comp Cx2{60, 24};
	const comp Cx3{26, 0};

	const comp Cy1{9, 7};
	const comp Cy2{1, 29};
	const comp Cy3{14, 0};

	const comp Cz1{48, -21};
	const comp Cz2{15, 22};
	const comp Cz3{20, -22};

	const std::array<comp, 3> Cx{Cx1, Cx2, Cx3};
	const std::array<comp, 3> Cy{Cy1, Cy2, Cy3};
	const std::array<comp, 3> Cz{Cz1, Cz2, Cz3};

	const quantum::matrix<3, 3, comp> matC{Cx, Cy, Cz};

	const auto result = quantum::multiply(matA, matB);
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			CHECK(result[i][j] == matC[i][j]);
		}
	}
}

TEST_CASE("programming drill 2.4.1 inner product", "[chapter 2]") {
	using comp = std::complex<float>;
	const comp x1{5, 0};
	const comp x2{3, 0};
	const comp x3{-7, 0};
	const std::array<comp, 3> x{x1, x2, x3};

	const comp y1{6, 0};
	const comp y2{2, 0};
	const comp y3{0, 0};
	const std::array<comp, 3> y{y1, y2, y3};

	CHECK(quantum::dot(x, y) == std::complex<float>{36, 0});
}

TEST_CASE("programming drill 2.4.2 norm", "[chapter 2]") {
	using comp = std::complex<float>;
	const comp x1{3, 0};
	const comp x2{-6, 0};
	const comp x3{2, 0};
	const std::array<comp, 3> x{x1, x2, x3};

	CHECK(quantum::norm(x) == std::complex<float>{7, 0});
}

TEST_CASE("programming drill 2.4.3 norm", "[chapter 2]") {
	using comp = std::complex<float>;
	const comp x1{3, 0};
	const comp x2{1, 0};
	const comp x3{2, 0};
	const std::array<comp, 3> x{x1, x2, x3};

	const comp y1{2, 0};
	const comp y2{2, 0};
	const comp y3{-1, 0};
	const std::array<comp, 3> y{y1, y2, y3};

	CHECK(quantum::distance(x, y).real() == Approx(3.31662));
	CHECK(quantum::distance(x, y).imag() == Approx(0));
}

TEST_CASE("programming drill 2.6.1 equal", "[chapter 2]") {
	using comp = std::complex<float>;
	const comp x1{5, 0};
	const comp x2{4, 5};
	const comp x3{6, -16};
	const std::array<comp, 3> x{x1, x2, x3};

	const comp y1{4, -5};
	const comp y2{13, 0};
	const comp y3{7, 0};
	const std::array<comp, 3> y{y1, y2, y3};

	const comp z1{6, 16};
	const comp z2{7, 0};
	const comp z3{-2.1, 0};
	const std::array<comp, 3> z{z1, z2, z3};

	const quantum::matrix<3, 3, comp> A{x, y, z};
	CHECK(quantum::is_equal(A, A));
	CHECK(!quantum::is_equal(A, quantum::inverse(A)));
}

TEST_CASE("programming drill 2.6.1 transpose", "[chapter 2]") {
	using comp = std::complex<float>;
	const comp x1{5, 0};
	const comp x2{4, 5};
	const comp x3{6, -16};
	const std::array<comp, 3> x{x1, x2, x3};

	const comp y1{4, -5};
	const comp y2{13, 0};
	const comp y3{7, 0};
	const std::array<comp, 3> y{y1, y2, y3};

	const comp z1{6, 16};
	const comp z2{7, 0};
	const comp z3{-2.1, 0};
	const std::array<comp, 3> z{z1, z2, z3};

	const quantum::matrix<3, 3, comp> A{x, y, z};
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			CHECK(quantum::transpose(A)[i][j] == A[j][i]);
		}
	}
}

TEST_CASE("programming drill 2.6.1 hermitian", "[chapter 2]") {
	using comp = std::complex<float>;
	const comp x1{5, 0};
	const comp x2{4, 5};
	const comp x3{6, -16};
	const std::array<comp, 3> x{x1, x2, x3};

	const comp y1{4, -5};
	const comp y2{13, 0};
	const comp y3{7, 0};
	const std::array<comp, 3> y{y1, y2, y3};

	const comp z1{6, 16};
	const comp z2{7, 0};
	const comp z3{-2.1, 0};
	const std::array<comp, 3> z{z1, z2, z3};

	const quantum::matrix<3, 3, comp> A{x, y, z};
	CHECK(quantum::is_hermitian(A) == true);
}

TEST_CASE("programming drill 2.6.2 unitary", "[chapter 2]") {
	using comp = std::complex<double>;
	const comp x1{1.0f/sqrt(2), 0};
	const comp x2{1.0f/sqrt(2), 0};
	const comp x3{0, 0};
	const std::array<comp, 3> x{x1, x2, x3};

	const comp y1{0, -1/sqrt(2)};
	const comp y2{0, 1/sqrt(2)};
	const comp y3{0, 0};
	const std::array<comp, 3> y{y1, y2, y3};

	const comp z1{0, 0};
	const comp z2{0, 0};
	const comp z3{0, 1};
	const std::array<comp, 3> z{z1, z2, z3};

	const quantum::matrix<3, 3, comp> A{x, y, z};
	CHECK(quantum::is_unitary(A) == true);
}

TEST_CASE("programming drill 2.7.1 small tensor product", "[chapter 2]") {
	using comp = std::complex<float>;
	const comp x{1};
	const comp y{2};

	const comp a{3};
	const comp b{4};
	const comp c{5};

	const quantum::matrix<2, 1, comp> A = {{
		{x},
		{y}
	}};
	const quantum::matrix<3, 1, comp> B = {{
		{a},
		{b},
		{c}
	}};
	const auto result = quantum::tensor_product(A, B);

	const std::array<comp, 6> values{
		x * a,
		x * b,
		x * c,
		y * a,
		y * b,
		y * c};

	for (std::size_t i = 0; i < 6; ++i) {
		CHECK(result[i][0] == values[i]);
	}
}

TEST_CASE("programming drill 2.7.1 large tensor product", "[chapter 2]") {
	using comp = std::complex<float>;

	const comp a00{3, 2};
	const comp a01{5, -1};
	const comp a10{0, 2};
	const comp a11{0, 2};


	const comp b00{1, 0};
	const comp b01{3, 4};
	const comp b02{5, -7};
	const comp b10{10, 2};
	const comp b11{6, 0};
	const comp b12{2, 5};
	const comp b20{0, 0};
	const comp b21{0, 1};
	const comp b22{2, 9};

	const quantum::matrix<2, 2, comp> A = {{
		{a00, a01},
		{a10, a11},
	}};
	const quantum::matrix<3, 3, comp> B = {{
		{b00, b01, b02},
		{b10, b11, b12},
		{b20, b21, b22}
	}};
	const auto result = quantum::tensor_product(A, B);

	const quantum::matrix<6, 6, comp> values = {{
		{a00 * b00, a00 * b01, a00 * b02, a01 * b00, a01 * b01, a01 * b02},
		{a00 * b10, a00 * b11, a00 * b12, a01 * b10, a01 * b11, a01 * b12},
		{a00 * b20, a00 * b21, a00 * b22, a01 * b20, a01 * b21, a01 * b22},
		{a10 * b00, a10 * b01, a10 * b02, a11 * b00, a11 * b01, a11 * b02},
		{a10 * b10, a10 * b11, a10 * b12, a11 * b10, a11 * b11, a11 * b12},
		{a10 * b20, a10 * b21, a10 * b22, a11 * b20, a11 * b21, a11 * b22},
	}};

	for (std::size_t i = 0; i < 6; ++i) {
		for (std::size_t j = 0; j < 6; ++j) {
			CHECK(result[i][j] == values[i][j]);
		}
	}
}
