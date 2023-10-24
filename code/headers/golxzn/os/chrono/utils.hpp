/**
 * @file golxzn/os/chrono/utils.hpp
 * @author Ruslan Golovinskii (golxzn@gmail.com)
 * @brief Useful functions and aliases for golxzn::os::chrono
 * @date 2023-10-24
 *
 * @copyright Copyright (c) 2023
 */

#pragma once

#include <chrono>
#include <utility>
#include <type_traits>

namespace golxzn::os::chrono::utils {

template<class T>
using floating_point_t = std::enable_if_t<std::is_floating_point_v<T>, T>;

/**
 * @brief Default clock type
 */
using default_base_clock = std::conditional_t<std::chrono::high_resolution_clock::is_steady,
	std::chrono::high_resolution_clock,
	std::chrono::steady_clock
>;

template<class Clock, class Minimum = std::micro>
struct enough_resolution : std::bool_constant<std::ratio_less_equal_v<typename Clock::period, Minimum>> {};

template<class Clock>
static constexpr bool enough_resolution_v{ enough_resolution<Clock>::value };

/**
 * @brief Time difference between two time points
 * @ingroup Chrono utilities
 * @tparam T return type
 * @param current current time (usually std::chrono::time_point)
 * @param last last time (usually std::chrono::time_point)
 * @return constexpr T
 * @see golxzn::os::chrono::utils::base_clock
 */
template<class T, class Other>
[[nodiscard]] constexpr auto difference(const Other &current, const Other &last) noexcept
	-> std::conditional_t<std::is_constructible_v<T, std::chrono::microseconds>, T, void> {
	return T{ std::chrono::duration_cast<std::chrono::microseconds>(current - last) };
}

} // namespace golxzn::os::chrono::utils
