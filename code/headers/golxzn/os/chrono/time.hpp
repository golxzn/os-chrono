#pragma once

#include <chrono>
#include <type_traits>
#include <golxzn/os/aliases.hpp>

#include "golxzn/os/chrono/utils.hpp"

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

	template<class T>
	explicit constexpr time(const utils::floating_point_t<T> seconds) noexcept;

	explicit constexpr time(const i32 milliseconds) noexcept;
	explicit constexpr time(const i64 microseconds) noexcept;

	template<class T = f64>
	[[nodiscard]] constexpr utils::floating_point_t<T> seconds() const noexcept;
	[[nodiscard]] constexpr i32 milliseconds() const noexcept;
	[[nodiscard]] constexpr i64 microseconds() const noexcept;

	[[nodiscard]] constexpr std::chrono::microseconds duration() const noexcept;

	template<class Rep, class Period>
	[[nodiscard]] explicit constexpr operator std::chrono::duration<Rep, Period>() const noexcept;

	[[nodiscard]] constexpr time &operator+=(const time &rhs) noexcept;
	template<class T>
	[[nodiscard]] constexpr time &operator+=(const utils::floating_point_t<T> seconds) noexcept;
	[[nodiscard]] constexpr time &operator+=(const i32 milliseconds) noexcept;
	[[nodiscard]] constexpr time &operator+=(const i64 microseconds) noexcept;

	[[nodiscard]] constexpr time &operator-=(const time &rhs) noexcept;
	template<class T>
	[[nodiscard]] constexpr time &operator-=(const utils::floating_point_t<T> seconds) noexcept;
	[[nodiscard]] constexpr time &operator-=(const i32 milliseconds) noexcept;
	[[nodiscard]] constexpr time &operator-=(const i64 microseconds) noexcept;


	[[nodiscard]] constexpr bool operator==(const time &rhs) const noexcept;
	[[nodiscard]] constexpr bool operator!=(const time &rhs) const noexcept;
	[[nodiscard]] constexpr bool operator>=(const time &rhs) const noexcept;
	[[nodiscard]] constexpr bool operator<=(const time &rhs) const noexcept;
	[[nodiscard]] constexpr bool operator> (const time &rhs) const noexcept;
	[[nodiscard]] constexpr bool operator< (const time &rhs) const noexcept;

	[[nodiscard]] static constexpr time zero() noexcept;
	[[nodiscard]] static time now() noexcept;

private:
	std::chrono::microseconds m_microseconds{};
};

template<class T>
[[nodiscard]] constexpr time seconds(const utils::floating_point_t<T> value) noexcept;
[[nodiscard]] constexpr time milliseconds(const i32 value) noexcept;
[[nodiscard]] constexpr time microseconds(const i64 value) noexcept;

#include "golxzn/os/chrono/impl/time.inl"

} // namespace golxzn::os::chrono
