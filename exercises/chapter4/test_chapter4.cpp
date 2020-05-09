#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <cmath>

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
	CHECK(bra[0] == constant * bra_values[0]);

	CHECK(quantum::prob_of_particle_from_transition(start_state, end_state) == std::complex<double>{0, 1});
}
