#pragma once

#include <iostream>
#include <complex>
#include <cassert>
#include <algorithm>

#include <chapter4/chapter4.hpp>

namespace quantum {
	namespace gate {
		template<class T>
		const matrix<2, 2, T> qnot {{{
			{0, 1},
			{1, 0}
		}}};

		template <class T>
		const matrix<2, 4, T> qand {{{
			{1, 1, 1, 0},
			{0, 0, 0, 1}
		}}};

		template<class T>
		const matrix<2, 4, T> qor {{{
			{1, 0, 0, 0},
			{0, 1, 1, 1}
		}}};

		template <class T>
		const auto qnand = multiply(qnot<T>, qand<T>);
	}
}
