#pragma once

#include <chrono>
#include <compare>
#include <concepts>
#include <golxzn/os/aliases.hpp>

namespace golxzn::os::chrono {

class time {
public:
	constexpr time() = default;
	constexpr time(const time &) = default;
	constexpr time(time &&) noexcept = default;
	constexpr time &operator=(const time &) = default;
	constexpr time &operator=(time &&) noexcept = default;

	explicit constexpr time(const std::chrono::microseconds duration) noexcept;

	template<class Rep, class Period>
	explicit constexpr time(const std::chrono::duration<Rep, Period> duration) noexcept;

	template<class Clock, class Duration = typename Clock::duration>
	explicit constexpr time(const std::chrono::time_point<Clock, Duration> time_point) noexcept;

	explicit constexpr time(const std::floating_point auto seconds) noexcept;
	explicit constexpr time(const i32 milliseconds) noexcept;
	explicit constexpr time(const i64 microseconds) noexcept;

	template<std::floating_point FloatType = f64>
	[[nodiscard]] constexpr FloatType seconds() const noexcept;
	[[nodiscard]] constexpr i32 milliseconds() const noexcept;
	[[nodiscard]] constexpr i64 microseconds() const noexcept;

	[[nodiscard]] constexpr std::chrono::microseconds duration() const noexcept;

	template<class Rep, class Period>
	[[nodiscard]] explicit constexpr operator std::chrono::duration<Rep, Period>() const noexcept;

	[[nodiscard]] constexpr time &operator+=(const time &rhs) noexcept;
	[[nodiscard]] constexpr time &operator-=(const time &rhs) noexcept;

	[[nodiscard]] friend constexpr auto operator<=>(const time&, const time&) noexcept = default;

	[[nodiscard]] static constexpr time zero() noexcept;
	[[nodiscard]] static time now() noexcept;

private:
	std::chrono::microseconds m_microseconds{};
};

[[nodiscard]] constexpr time seconds(const std::floating_point auto value) noexcept;
[[nodiscard]] constexpr time milliseconds(const i32 value) noexcept;
[[nodiscard]] constexpr time microseconds(const i64 value) noexcept;

template<class Rep, class Period>
[[nodiscard]] constexpr std::strong_ordering operator<=>(const time &lhs, const std::chrono::duration<Rep, Period> &rhs) noexcept;

template<class Clock, class Duration = typename Clock::duration>
[[nodiscard]] constexpr std::strong_ordering operator<=>(const time &lhs, const std::chrono::time_point<Clock, Duration> &rhs) noexcept;

[[nodiscard]] constexpr std::strong_ordering operator<=>(const time &lhs, const std::floating_point auto rhs) noexcept;
[[nodiscard]] constexpr std::strong_ordering operator<=>(const time &lhs, const i32 rhs) noexcept;
[[nodiscard]] constexpr std::strong_ordering operator<=>(const time &lhs, const i64 rhs) noexcept;

[[nodiscard]] constexpr std::strong_ordering operator<=>(const std::floating_point auto lhs, const time &rhs) noexcept;
[[nodiscard]] constexpr std::strong_ordering operator<=>(const i32 lhs, const time &rhs) noexcept;
[[nodiscard]] constexpr std::strong_ordering operator<=>(const i64 lhs, const time &rhs) noexcept;

[[nodiscard]] constexpr time operator-(const time &rhs) noexcept;
[[nodiscard]] constexpr time operator-(const time &lhs, const time &rhs) noexcept;
[[nodiscard]] constexpr time operator+(const time &lhs, const time &rhs) noexcept;

#include "golxzn/os/chrono/impl/time.inl"

} // namespace golxzn::os::chrono
