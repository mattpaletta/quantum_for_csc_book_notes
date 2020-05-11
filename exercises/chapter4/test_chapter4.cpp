#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <cmath>

#include <iostream>
#include <complex>

#include <chapter4/chapter4.hpp>

TEST_CASE("programming drill 4.1.1 find probability of state", "[chapter4]") {
	// The particle can be in 4 positions
	constexpr std::array<std::complex<double>, 4> state = {{
				{-3, -1},
				{0, -2},
				{0, 1},
				{2, 0}}};
	// simulate the first quantum system described in this section
	CHECK(quantum::prob_of_particle_at_pos(2, state) == Approx(0.052631 /* 0.052624 */));

	// user specify how many points the particle can occupy
	// user specify a ket vector state vector by assigning amplitudes
	// perform calculation in example 4.1.1 to find probabilities
}

TEST_CASE("programming drill 4.1.1 describe probability of transition", "[chapter4]") {
	// Provide second ket vector, find probability of transitioning from the first ket to the second after an observation has been made
	const std::complex<double> constant{std::sqrt(2) / 2};
	const auto start_state = quantum::scalar<std::complex<double>, 2>({{
			{1, 0},
			{0, 1}
		}},
		constant);

	const auto end_state = quantum::scalar<std::complex<double>, 2>({{
			{0, 1},
			{-1, 0}
		}},
		constant);

	const auto bra = quantum::calculate_bra(start_state, end_state);
	const std::array<std::complex<double>, 2> bra_values{{
		{0, -1},
		{-1, 0}}};
	// Check we calculated the `bra` correctly
	CHECK(bra[0] == constant * bra_values[0]);

	// Verify the transition
	CHECK(quantum::prob_of_particle_from_transition(start_state, end_state).real() == Approx(0));
	CHECK(quantum::prob_of_particle_from_transition(start_state, end_state).imag() == Approx(-1));
}

template<class T, std::size_t M, std::size_t N>
void check_matrix(const quantum::matrix<M, N, std::complex<T>>& Sa, const quantum::matrix<M, N, std::complex<T>>& Sb) {
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < N; ++j) {
			CHECK(Sa[i][j].real() == Approx(Sb[i][j].real()));
			CHECK(Sa[i][j].imag() == Approx(Sb[i][j].imag()));
		}
	}
}

TEST_CASE("example 4.2.3", "[chapter4]") {
	const std::complex<float> constant{0, 2};

	// [Sx, Sy] = 2iSz
	check_matrix(
		quantum::commutator(quantum::spin::Sx<float>, quantum::spin::Sy<float>),
		quantum::scalar(quantum::spin::Sz<float>, constant));

	// [Sy, Sz] = 2iSx
	check_matrix(
		quantum::commutator(quantum::spin::Sy<float>, quantum::spin::Sz<float>),
		quantum::scalar(quantum::spin::Sx<float>, constant));

	// [Sz, Sx] = 2iSy
	check_matrix(
		quantum::commutator(quantum::spin::Sz<float>, quantum::spin::Sx<float>),
		quantum::scalar(quantum::spin::Sy<float>, constant));
}


TEST_CASE("programming drill 4.2.1 calculate mean", "[chapter4]") {
	const quantum::matrix<2, 2, std::complex<float>> state {{
		{{ {1, 0}, {0, -1} }},
		{{ {0, 1}, {2, 0} }}
	}};

	const std::array<std::complex<float>, 2> ket = {{
		{std::sqrt(2.f) / 2.f, 0},
		{0, std::sqrt(2.f) / 2.f}
	}};

	CHECK(quantum::calculate_mean(state, ket).real() == Approx(2.5));
}

TEST_CASE("programming drill 4.2.1 calculate variance", "[chapter4]") {
	const quantum::matrix<2, 2, std::complex<float>> state {{
		{{ {1, 0}, {0, -1} }},
		{{ {0, 1}, {2, 0} }}
	}};

	const std::array<std::complex<float>, 2> ket = {{
		{std::sqrt(2.f) / 2.f, 0},
		{0, std::sqrt(2.f) / 2.f}
	}};

	CHECK(quantum::calculate_variance(state, ket).real() == Approx(0.25));
}
