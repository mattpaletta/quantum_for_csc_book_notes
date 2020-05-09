#pragma once

#include <iostream>
#include <complex>
#include <numeric>
#include <cassert>

#include <chapter3/chapter3.hpp>

namespace quantum {
	template<class T, std::size_t N>
	T ket_length(const std::array<std::complex<T>, N>& ket) {
		const auto sum = std::transform_reduce(
				ket.begin(),
				ket.end(),
				0,
				[](const T& a, const T& b) {
					return a + b;
				},
				[](const std::complex<T>& a) {
					// This is the squared magnitude
					return std::norm(a);
				});
		return sum;
	}

	template<class T, std::size_t N>
	std::array<std::complex<T>, N> normalize_ket(const std::array<std::complex<T>, N>& vector) {
		std::array<std::complex<T>, N> out;
		const auto sum = ket_length(vector);
		std::transform(
				vector.begin(),
				vector.end(),
				out.begin(),
				[&sum](const std::complex<T>& a) {
					return a / sum;
				});
		return out;
	}

	template<class T, std::size_t N>
	T prob_of_particle_at_pos(const std::size_t& i, const std::array<std::complex<T>, N>& state) {
		assert(i < N && i >= 0);
		const auto sum = ket_length(state);
		return std::norm(state[i]) / sum;
	}

	template<class T, std::size_t N>
	std::array<std::complex<T>, N> calculate_bra(const std::array<std::complex<T>, N>& ket1, const std::array<std::complex<T>, N>& ket2) {
		return conjugate(ket2);
	}

	template<class T, std::size_t N>
	std::complex<T> prob_of_particle_from_transition(const std::array<std::complex<T>, N>& ket1, const std::array<std::complex<T>, N>& ket2) {
		to_string(normalize_ket(ket1));
		to_string(ket1);
		return dot(
				normalize_ket(ket1),
				calculate_bra(ket1, normalize_ket(ket2)));
	}
}
