#pragma once

#include <iostream>
#include <complex>
#include <cassert>
#include <algorithm>

#include <chapter3/chapter3.hpp>

namespace quantum {
	template<class T, std::size_t N>
	T ket_length(const std::array<std::complex<T>, N>& ket) {
		T sum = 0;
		for (const auto& i : ket) {
			sum += std::norm(i);
		}
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
		return dot(
				normalize_ket(ket1),
				calculate_bra(ket1, normalize_ket(ket2)));
	}

	template<class T, std::size_t M, std::size_t N>
	auto commutator(const matrix<M, N, T>& a, const matrix<M, N, T>& b) {
		return subtraction<T, M, N>(
				multiply<T, M, N>(a, b),
				multiply<T, M, N>(b, a));
	}

	template<class T, std::size_t N>
	T calculate_mean(const matrix<N, N, T>& state, const std::array<T, N>& ket) {
		const auto bra = multiply(state, ket);
		return dot(conjugate( bra ), ket);
	}

	template<class T, std::size_t N>
	T calculate_variance(const matrix<N, N, T>& state, const std::array<T, N>& ket) {
		const T mean = calculate_mean(state, ket);
		const auto calculate_hermitian = subtraction(
				state,
				scalar(identity<T, N>(), mean));
		const matrix<N, N, T> expected_value = multiply<T>(
				calculate_hermitian,
				calculate_hermitian);

		T sum{0};
		const auto variance = multiply(
				conjugate(ket),
				multiply(expected_value, ket));

		for (int i = 0; i < N; ++i) {
			sum += variance[i];
		}

		return sum;
	}

	namespace spin {
		template<class T>
		constexpr T h = 2;

		template<class T>
		constexpr T reduced_planck_constant = h<T>;

		template<class T>
		const matrix<2, 2, std::complex<T>> Sx = scalar<std::complex<T>, 2, 2>({{{
				{std::complex<T>{0, 0}, std::complex<T>{1, 0}},
				{std::complex<T>{1, 0}, std::complex<T>{0, 0}}
			}}},
			std::complex<T>{h<T> / 2});

		template<class T>
		const matrix<2, 2, std::complex<T>> Sy = scalar<std::complex<T>, 2, 2>({{{
				{std::complex<T>{0, 0}, std::complex<T>{0, -1}},
				{std::complex<T>{0, 1}, std::complex<T>{0,  0}}
			}}},
			std::complex<T>{h<T> / 2});

		template<class T>
		const matrix<2, 2, std::complex<T>> Sz = scalar<std::complex<T>, 2, 2>({{{
				{std::complex<T>{1, 0}, std::complex<T>{0,  0}},
				{std::complex<T>{0, 0}, std::complex<T>{-1, 0}}
			}}},
			std::complex<T>{h<T> / 2});

		template<class T>
		const auto left_right = Sx<T>;

		template<class T>
		const auto in_out = Sy<T>;

		template<class T>
		const auto up_down = Sz<T>;
	}
}
