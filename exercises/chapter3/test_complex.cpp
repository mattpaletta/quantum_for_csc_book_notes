#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <cmath>

#include <chapter3/chapter3.hpp>

TEST_CASE("programming drill 3.1.1 marble dynamics", "[chapter3]") {
	quantum::matrix<6, 6, int> M = {{
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0},
		{0, 1, 0, 0, 0, 1},
		{0, 0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0, 0},
		{1, 0, 0, 0, 1, 0}
	}};

	std::array<int, 6> state =   {6, 2, 1, 5, 3, 10};
	std::array<int, 6> values = {0, 0, 12, 5, 1, 9};

	// Graph adj mat, initial marble count per vertex, # timesteps
	const auto results = classical::process_timesteps(M, state, 1);
	for (std::size_t i = 0; i < 6; ++i) {
		CHECK(results[i] == values[i]);
	}
}

TEST_CASE("programming drill 3.1.1 marble dynamics sixth timestep", "[chapter3]") {
	quantum::matrix<6, 6, int> M = {{
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0},
		{0, 1, 0, 0, 0, 1},
		{0, 0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0, 0},
		{1, 0, 0, 0, 1, 0}
	}};

	std::array<int, 6> state =   {6, 2, 1, 5, 3, 10};
	std::array<int, 6> values = {0, 0, 1, 5, 9, 12};

	// Graph adj mat, initial marble count per vertex, # timesteps
	const auto results = classical::process_timesteps(M, state, 6);
	for (std::size_t i = 0; i < 6; ++i) {
		CHECK(results[i] == values[i]);
	}
}

TEST_CASE("programming drill 3.2.1 marble dynamics", "[chapter3]") {
	quantum::matrix<3, 3, float> M = {{
		{0,     1.f/6, 5.f/6},
		{1.f/3, 1.f/2, 1.f/6},
		{2.f/3, 1.f/3, 	   0},
	}};

	std::array<float, 3> state =   {1.f/6, 1.f/6, 2.f/3};
	std::array<float, 3> values = {21.f/36, 9.f/36, 6.f/36};

	// Graph adj mat, initial marble count per vertex, # timesteps
	const auto results = classical::process_timesteps(M, state, 1);
	for (std::size_t i = 0; i < M.size(); ++i) {
		CHECK(results[i] == Approx(values[i]));
	}
}

TEST_CASE("programming drill 3.2.2 double slit", "[chapter3]") {
	quantum::matrix<8, 8, float> M = {{
		{0,     0,     0,     0, 0, 0, 0, 0},
		{0,     0,     0,     0, 0, 0, 0, 0},
		{0,     0,     0,     0, 0, 0, 0, 0},
		{1.f/6, 1.f/3, 0,     1, 0, 0, 0, 0},
		{1.f/6, 1.f/3, 0,     0, 1, 0, 0, 0},
		{1.f/3, 1.f/3, 1.f/3, 0, 0, 1, 0, 0},
		{1.f/6, 0,     1.f/3, 0, 0, 0, 1, 0},
		{1.f/6, 0,     1.f/3, 0, 0, 0, 0, 1}
	}};

	// Graph adj mat, initial marble count per vertex, # timesteps
	constexpr auto num_slits = 2;
	constexpr auto num_targets = 3;
	const auto results = quantum::run_double_slit_experiment<num_slits, num_targets>();
	CHECK(quantum::is_equal(M, results));

	const auto final_state = quantum::get_double_slit_prob<num_slits, num_targets>({1, 0, 0, 0, 0, 0, 0, 0});
	CHECK(
		quantum::is_equal(
			quantum::vector_to_matrix(final_state),
			quantum::vector_to_matrix<float, 8>(
				{0, 0, 0, 1.f/6, 1.f/6, 1.f/3, 1.f/6, 1.f/6}
	)));
}
