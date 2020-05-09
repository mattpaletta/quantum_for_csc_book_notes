#pragma once

#include <iostream>

#include <chapter2/chapter2.hpp>

namespace classical {
	template<std::size_t N, class T>
	std::array<T, N> process_timesteps(const quantum::matrix<N, N, T>& M, const std::array<T, N> initial_state, std::size_t num_timesteps = 1) {
		if (num_timesteps == 0) {
			return initial_state;
		} else if (num_timesteps == 1) {
			return quantum::multiply(M, initial_state);
		} else {
			// Recursively process timesteps
			const auto next_state = process_timesteps(M, initial_state, 1);
			return process_timesteps(M, next_state, num_timesteps - 1);
		}
	}
}

namespace quantum {
	template<std::size_t num_slits, std::size_t num_targets>
	auto run_double_slit_experiment() {
		constexpr auto N = num_slits + num_slits * (num_slits - 1) * num_targets;
		// Setup the matrix
		quantum::matrix<N, N, float> out;
		quantum::fill(out, 0.f);

		// Setup the bullet going through each slit
		constexpr auto slit_offset = 1;
		for (std::size_t i = slit_offset; i < num_slits + slit_offset; ++i) {
			// Bullet starts at index 0
			out[i][0] = 1.f / num_slits;
		}

		// Setup the bullet from each slit going through each target
		for (std::size_t i = slit_offset; i < num_slits + slit_offset; ++i) {
			auto start_vertex = 2 * i + 1;
			for (int j = 0; j < num_targets; ++j) {
				out[j + start_vertex][i] = 1.f / (float) num_targets;
			}
		}

		// Once the bullet hits a target, it stays there
		constexpr auto start_index = num_slits + slit_offset;
		for (std::size_t i = 0; i <= N / num_slits; ++i) {
			out[i + start_index][i + start_index] = 1;
		}

		// Multiply it by itself, showing what will happen after 2 'timesteps'
		return multiply(out, out);
	}

	template<std::size_t num_slits, std::size_t num_targets>
	auto get_double_slit_prob(const std::array<float, num_slits + num_slits * (num_slits -1) * num_targets>& state) {
		return multiply( run_double_slit_experiment<num_slits, num_targets>(), state);
	}
}
