#pragma once

#include <complex>
#include <array>
#include <iostream>

namespace quantum {
	template<std::size_t M, std::size_t N, class T>
	using matrix = std::array<std::array<T, N>, M>;

	template<class T, std::size_t M, std::size_t N>
	void fill(matrix<M, N, T>& a, const T& b) {
		for (int i = 0; i < M; ++i) {
			for (int j = 0; j < N; ++j) {
				a[i][j] = b;
			}
		}
	}

	template<class T, std::size_t N>
	void to_string(const std::array<T, N>& a) {
		std::cout << "[";
		for (int j = 0; j < N; ++j) {
			std::cout << a[j];
			if (j != N - 1) {
			std::cout << " ";
			}
		}
		std::cout << "]" << std::endl;
	}

	template<class T, std::size_t M, std::size_t N>
	void to_string(const matrix<M, N, T>& a) {
		for (int i = 0; i < M; ++i) {
			to_string(a[i]);
		}
	}

	template<class T, std::size_t N>
	std::array<T, N> addition(const std::array<T, N>& a, const std::array<T, N>& b) {
		std::array<T, N> out;
		for (std::size_t i = 0; i < N; ++i) {
			out[i] = a[i] + b[i];
		}
		return out;
	}

	template<class T, std::size_t M, std::size_t N>
	matrix<M, N, T> addition(const matrix<M, N, T>& a, const matrix<M, N, T>& b) {
		matrix<M, N, T> out;
		for (std::size_t i = 0; i < M; ++i) {
			out[i] = addition(a[i], b[i]);
		}
		return out;
	}

	template<class T, std::size_t N>
	std::array<T, N> scalar(const std::array<T, N>& a, const T& b) {
		std::array<T, N> out;
		for (std::size_t i = 0; i < N; ++i) {
			out[i] = b * a[i];
		}
		return out;
	}

	template<class T, std::size_t M, std::size_t N>
	matrix<M, N, T> scalar(const matrix<M, N, T>& a, const T& b) {
		matrix<M, N, T> out;
		for (std::size_t i = 0; i < M; ++i) {
			out[i] = scalar(a[i], b);
		}
		return out;
	}

	template<class T, std::size_t M, std::size_t N>
	matrix<M, N, T> subtraction(const matrix<M, N, T>& a, const matrix<M, N, T>& b) {
		matrix<M, N, T> out;
		for (std::size_t i = 0; i < M; ++i) {
			// Add -b, equivalent of addition
			out[i] = addition(a[i], scalar(b[i], T{-1}));
		}
		return out;
	}

	template<class T>
	std::complex<T> conjugate(const std::complex<T>& a) {
		return {a.real(),  a.imag() * -1.0f};
	}

	template<class T, std::size_t N>
	std::array<std::complex<T>, N> conjugate(const std::array<std::complex<T>, N>& a) {
		std::array<std::complex<T>, N> out;
		for (std::size_t i = 0; i < N; ++i) {
			out[i] = conjugate(a[i]);
		}
		return out;
	}

	template<class T, std::size_t M, std::size_t N>
	matrix<M, N, T> conjugate(const matrix<M, N, T>& a) {
		matrix<M, N, T> out;
		for (std::size_t i = 0; i < M; ++i) {
			for (std::size_t j = 0; j < N; ++j) {
				// Conjugate except for the diagonal
				//out[i][j] = (i == j) ? a[i][j] : conjugate(a[i][j]);
				out[i][j] = conjugate(a[i][j]);
			}
		}
		return out;
	}

	template<class T, std::size_t N>
	matrix<N, N, T> identity() {
		matrix<N, N, T> out;
		for (std::size_t i = 0; i < N; ++i) {
			for (std::size_t j = 0; j < N; ++j) {
				out[i][j] = (i == j) ? 1 : 0;
			}
		}
		return out;
	}

	template<class T, std::size_t N>
	std::array<T, N> inverse(const std::array<T, N>& a) {
		std::array<T, N> out;
		for (std::size_t i = 0; i < N; ++i) {
			out[i] = a[i] * -1.0f;
		}
		return out;
	}

	template<class T, std::size_t M, std::size_t N>
	matrix<M, N, T> inverse(const matrix<M, N, T>& a) {
		matrix<M, N, T> out;
		for (std::size_t i = 0; i < M; ++i) {
			out[i] = inverse(a[i]);
		}
		return out;
	}

	template<class T, std::size_t M, std::size_t N>
	matrix<N, M, T> transpose(const matrix<M, N, T>& a) {
		matrix<N, M, T> out;
		for (int i = 0; i < M; ++i) {
			for (int j = 0; j < N; ++j) {
				out[i][j] = a[j][i];
			}
		}
		return out;
	}

	template<class T, std::size_t M, std::size_t N, std::size_t P>
	matrix<M, P, T> multiply(const matrix<M, N, T>& a, const matrix<N, P, T>& b) {
		auto get_element = [&a, &b](std::size_t j, std::size_t k) {
			T out = 0;
			for (std::size_t x = 0; x < N; ++x) {
				out += (a[j][x] * b[x][k]);
			}
			return out;
		};
		matrix<M, P, T> out;
		for (std::size_t j = 0; j < M; ++j) {
			for (std::size_t k = 0; k < P; ++k) {
				out[j][k] = get_element(j, k);
			}
		}
		return out;
	}

	template<class T, std::size_t M>
	matrix<M, 1, T> vector_to_matrix(const std::array<T, M>& b) {
		matrix<M, 1, T> out;
		for (std::size_t j = 0; j < M; ++j) {
			out[j][0] = b[j];
		}
		return out;
	}

	template<class T, std::size_t M, std::size_t N>
	std::array<T, M> multiply(const matrix<M, N, T>& a, const std::array<T, N>& b) {
		auto get_element = [&a, &b](std::size_t j) {
			T out = 0;
			for (std::size_t x = 0; x < N; ++x) {
				out += (a[j][x] * b[x]);
			}
			return out;
		};
		std::array<T, M> out;
		for (std::size_t j = 0; j < M; ++j) {
			out[j] = get_element(j);
		}
		return out;
	}

	template<class T, std::size_t N>
	std::array<T, N> multiply(const std::array<T, N>& a, const std::array<T, N>& b) {
		std::array<T, N> out;
		for (std::size_t j = 0; j < N; ++j) {
			out[j] = a[j] * b[j];
		}
		return out;
	}

	template<class T, std::size_t N>
	T dot(const std::array<T, N>& a, const std::array<T, N>& b) {
		T out;
		for (std::size_t i = 0; i < N; ++i) {
			out += a[i] * b[i];
		}
		return out;
	}

	template<class T, std::size_t M, std::size_t N, std::size_t P>
	matrix<M, P, T> dot(const matrix<M, N, T>& a, const matrix<N, P, T>& b) {
		const auto b_trans = transpose(b);
		matrix<M, P, T> out;
		for (int i = 0; i < M; ++i) {
			for (int j = 0; j < P; ++j) {
				// First row a, dot first column of b
				out[i][j] = dot(a[i], b_trans[j]);
			}
		}

		return out;
	}


	template<class T, std::size_t N>
	std::complex<T> norm(const std::array<std::complex<T>, N>& a) {
		std::complex<T> out;
		for (std::size_t i = 0; i < N; ++i) {
			out += std::norm(a[i]);
		}
		return std::sqrt(out);
	}

	template<class T, std::size_t N>
	std::complex<T> distance(const std::array<std::complex<T>, N>& a, const std::array<std::complex<T>, N>& b) {
		// Calculate a - b
		return norm(addition(a, inverse(b)));
	}

	template<class T>
	bool approximatelyEqual(T a, T b, T epsilon = 0.0001f) {
    	return fabs(a - b) <= ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
	}

	template<class T>
	bool essentiallyEqual(T a, T b, T epsilon = 0.0001f) {
		return fabs(a - b) <= ( (fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * epsilon);
	}

	template<class T, std::size_t M, std::size_t N>
	bool is_equal(const matrix<M, N, std::complex<T>>& a, const matrix<M, N, std::complex<T>>& b) {
		for (int i = 0; i < M; ++i) {
			for (int j = 0; j < N; ++j) {
				if (!approximatelyEqual(a[i][j].real(), b[i][j].real()) || !approximatelyEqual(a[i][j].imag(), b[i][j].imag())) {
					return false;
				}
			}
		}
		return true;
	}

	template<class T, std::size_t M, std::size_t N>
	bool is_equal(const matrix<M, N, T>& a, const matrix<M, N, T>& b) {
		for (int i = 0; i < M; ++i) {
			for (int j = 0; j < N; ++j) {
				if (!approximatelyEqual(a[i][j], b[i][j])) {
					return false;
				}
			}
		}
		return true;
	}


	template<class T, std::size_t N>
	bool is_symmetric(const matrix<N, N, T>& a) {
		return is_equal( transpose(a), a);
	}

	template<class T, std::size_t M, std::size_t N>
	matrix<M, N, T> hermitian(const matrix<M, N, T>& a) {
		return transpose( conjugate( a ) );
	}

	template<class T, std::size_t N>
	bool is_hermitian(const matrix<N, N, T>& a) {
		return is_equal( a, hermitian(a));
	}

	template<class T, std::size_t N>
	bool is_unitary(const matrix<N, N, T>& a) {
		// A * H(A) == H(A) * A == I
		return is_equal(multiply(hermitian(a), a), identity<T, N>());
	}

	template<class T, std::size_t M0, std::size_t M1, std::size_t N0, std::size_t N1>
	matrix<M0 * N0, M1 * N1, T> tensor_product(const matrix<M0, M1, T>& a, const matrix<N0, N1, T>& b) {
		matrix<M0 * N0, M1 * N1, T> out;

		for (std::size_t j = 0; j < M0; ++j) {
			for (std::size_t k = 0; k < M1; ++k) {
				// Do matrix multiplication, and copy results
				matrix<N0, N1, T> multB = scalar(b, T(a[j][k]));

				for (std::size_t a = 0; a < N0; ++a) {
					for (std::size_t b = 0; b < N1; ++b) {
						const std::size_t x = (j * (M0 + 1) + a);
						const std::size_t y = (k * (M1 + 1) + b);

						out[x][y] = multB[a][b];
					}
				}
			}
		}
		return out;
	}
}
