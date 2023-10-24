#pragma once

#include <chrono>
#include <type_traits>
#include <golxzn/os/aliases.hpp>

#include "golxzn/os/chrono/utils.hpp"

namespace golxzn::os::chrono {

/**
 * @brief Class that represents time.
 * @ingroup Chrono time
 * @details It's a wrapper around std::chrono::microseconds.
 * This time representation is based on std::chrono::microseconds and is used in golxzn::os::chrono.
 * @see golxzn::os::chrono::clock
 * @see golxzn::os::chrono::fast_clock
 * @see golxzn::os::chrono::timer
 * @see golxzn::os::chrono::fast_timer
 */
class time {
public:
	constexpr time() = default;
	constexpr time(const time &) = default;
	constexpr time(time &&) noexcept = default;
	constexpr time &operator=(const time &) = default;
	constexpr time &operator=(time &&) noexcept = default;

	/**
	 * @brief Constructor that creates time from std::chrono::microseconds.
	 * @ingroup Chrono time construction
	 * @param duration - duration in microseconds.
	 * @see time(const std::chrono::duration<Rep, Period> duration)
	 * @see time(const std::chrono::time_point<Clock, Duration> time_point)
	 * @see time(const utils::floating_point_t<T> seconds)
	 * @see seconds(const utils::floating_point_t<T> value)
	 * @see milliseconds(const i32 value)
	 * @see microseconds(const i64 value)
	 */
	explicit constexpr time(const std::chrono::microseconds duration) noexcept;

	/**
	 * @brief Constructor that creates time from std::chrono::duration.
	 * @ingroup Chrono time construction
	 * @tparam Rep Duration rep
	 * @tparam Period Duration period
	 * @see time(const std::chrono::microseconds duration)
	 * @see time(const std::chrono::time_point<Clock, Duration> time_point)
	 * @see time(const utils::floating_point_t<T> seconds)
	 * @see seconds(const utils::floating_point_t<T> value)
	 * @see milliseconds(const i32 value)
	 * @see microseconds(const i64 value)
	 */
	template<class Rep, class Period>
	explicit constexpr time(const std::chrono::duration<Rep, Period> duration) noexcept;

	/**
	 * @brief Constructor that creates time from std::chrono::time_point.
	 * @ingroup Chrono time construction
	 * @tparam Clock time_point clock
	 * @tparam Clock::duration time_point duration
	 * @see time(const std::chrono::microseconds duration)
	 * @see time(const std::chrono::duration<Rep, Period> duration)
	 * @see time(const utils::floating_point_t<T> seconds)
	 * @see seconds(const utils::floating_point_t<T> value)
	 * @see milliseconds(const i32 value)
	 * @see microseconds(const i64 value)
	 */
	template<class Clock, class Duration = typename Clock::duration>
	explicit constexpr time(const std::chrono::time_point<Clock, Duration> time_point) noexcept;

	/**
	 * @brief Constructor that creates time from seconds floating point value
	 * @ingroup Chrono time construction
	 * @tparam T floating point type (e.g. float, double)
	 * @see time(const i32 milliseconds)
	 * @see time(const i64 microseconds)
	 * @see seconds(const utils::floating_point_t<T> value)
	 * @see milliseconds(const i32 value)
	 * @see microseconds(const i64 value)
	 */
	template<class T>
	explicit constexpr time(const utils::floating_point_t<T> seconds) noexcept;

	/**
	 * @brief Constructor that creates time from milliseconds value
	 * @ingroup Chrono time construction
	 * @see time(const utils::floating_point_t<T> seconds)
	 * @see time(const i64 microseconds)
	 * @see seconds(const utils::floating_point_t<T> value)
	 * @see milliseconds(const i32 value)
	 * @see microseconds(const i64 value)
	 */
	explicit constexpr time(const i32 milliseconds) noexcept;

	/**
	 * @brief Constructor that creates time from microseconds value
	 * @ingroup Chrono time construction
	 * @see time(const utils::floating_point_t<T> seconds)
	 * @see time(const i32 milliseconds)
	 * @see seconds(const utils::floating_point_t<T> value)
	 * @see milliseconds(const i32 value)
	 * @see microseconds(const i64 value)
	 */
	explicit constexpr time(const i64 microseconds) noexcept;

	/**
	 * @brief Returns duration in seconds
	 * @ingroup Chrono time conversion
	 * @tparam T floating point type (e.g. float, double). Default is f64 aka double.
	 * @return Seconds as floating point type T
	 * @see milliseconds()
	 * @see microseconds()
	 */
	template<class T = f64>
	[[nodiscard]] constexpr utils::floating_point_t<T> seconds() const noexcept;

	/**
	 * @brief Returns duration in milliseconds
	 * @ingroup Chrono time conversion
	 * @return Milliseconds as i32
	 * @see seconds()
	 * @see microseconds()
	 */
	[[nodiscard]] constexpr i32 milliseconds() const noexcept;

	/**
	 * @brief Returns duration in microseconds
	 * @ingroup Chrono time conversion
	 * @return Microseconds as i64
	 * @see seconds()
	 * @see milliseconds()
	 */
	[[nodiscard]] constexpr i64 microseconds() const noexcept;

	/**
	 * @brief Converts time to std::chrono::duration
	 * @ingroup Chrono time conversion
	 * @tparam Rep Duration rep
	 * @tparam Period Duration period
	 * @return std::chrono::duration
	 * @see operator std::chrono::duration<Rep, Period>()
	 */
	[[nodiscard]] constexpr std::chrono::microseconds duration() const noexcept;

	/**
	 * @brief Converts time to std::chrono::duration
	 * @ingroup Chrono time conversion
	 * @tparam Rep Duration rep
	 * @tparam Period Duration period
	 * @return std::chrono::duration<Rep, Period> with casted microseconds
	 * @see duration()
	 */
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

	/**
	 * @brief Zero time.
	 * @ingroup Chrono time constants
	 * @return Well, zero, I guess.
	 */
	[[nodiscard]] static constexpr time zero() noexcept;

	/**
	 * @brief Now time.
	 * @return Current time.
	 */
	[[nodiscard]] static time now() noexcept;

private:
	std::chrono::microseconds m_microseconds{};
};

/**
 * @brief Make time from floating point value (seconds).
 * @ingroup Chrono time construction
 * @tparam T floating point type
 * @param value floating point value
 * @return time
 * @see milliseconds(const i32 value)
 * @see microseconds(const i64 value)
 */
template<class T>
[[nodiscard]] constexpr time seconds(const utils::floating_point_t<T> value) noexcept;

/**
 * @brief Make time from integer value (milliseconds).
 * @ingroup Chrono time construction
 * @param value Integer value (milliseconds)
 * @return time
 * @see seconds(const utils::floating_point_t<T> value)
 * @see microseconds(const i64 value)
 */
[[nodiscard]] constexpr time milliseconds(const i32 value) noexcept;

/**
 * @brief Make time from integer value (microseconds).
 * @ingroup Chrono time construction
 * @param value Integer value (microseconds)
 * @return time
 * @see seconds(const utils::floating_point_t<T> value)
 * @see milliseconds(const i32 value)
 */
[[nodiscard]] constexpr time microseconds(const i64 value) noexcept;

#include "golxzn/os/chrono/impl/time.inl"

} // namespace golxzn::os::chrono
