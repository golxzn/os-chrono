#pragma once

#include <chrono>
#include <utility>
#include <concepts>
#include <type_traits>

namespace golxzn::os::chrono::utils {

template<class T>
concept base_clock = requires {
	typename T::time_point;
	{ T::now() } -> std::convertible_to<typename T::time_point>;
};

/**
 * @brief Default clock type
 * @see std::chrono::steady_clock
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
 *
 * @tparam T return type
 * @param current current time (usually std::chrono::time_point)
 * @param last last time (usually std::chrono::time_point)
 * @return constexpr T
 * @see golxzn::os::chrono::utils::base_clock
 */
template<std::constructible_from<std::chrono::microseconds> T>
[[nodiscard]] constexpr T difference(const auto current, const auto last) noexcept {
	return T{ std::chrono::duration_cast<std::chrono::microseconds>(current - last) };
}


} // namespace golxzn::os::chrono::utils
