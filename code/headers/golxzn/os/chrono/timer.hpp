#pragma once

#include <thread>

#include "golxzn/os/chrono/time.hpp"

namespace golxzn::os::chrono {

/**
 * @brief Class that represents timer.
 * @ingroup golxzn::os::chrono
 * @tparam OnTimerDone type of function that will be called when timer is done.
 * @tparam BaseClock clock that will be used for measurement. It has to be monotonic and STL compatible.
 */
template<class OnTimerDone, class BaseClock = utils::default_base_clock>
class timer {
	static_assert(BaseClock::is_steady,
		"[golxzn::os::chrono::timer] BaseClock is not a monotonic clock");
	static_assert(utils::enough_resolution_v<BaseClock>,
		"[golxzn::os::chrono::timer] BaseClock's resolution is less than microseconds!");

public:
	using base_clock = BaseClock;
	using time_point = typename base_clock::time_point;
	using timer_end_callback = OnTimerDone;

	static constexpr auto default_precision{ std::chrono::microseconds{ 1 } };
	static constexpr time_point zero{};

	/**
	 * @brief Timer constructor from timer interval and callback.
	 * @ingroup golxzn::os::chrono::construction
	 * @details Timer's callback will be called after timer_interval.
	 * @param timer_interval Timer interval.
	 * @param callback Function that will be called after timer_interval.
	 * @param precision Precision of timer. By default it's 1 microsecond (1us). Only if GOLXZN_MULTITHREADING is defined.
	 */
	template<class Rep, class Period>
	timer(const std::chrono::duration<Rep, Period> timer_interval, timer_end_callback &&callback
#if defined(GOLXZN_MULTITHREADING)
		, const std::chrono::microseconds precision = default_precision
#endif // defined(GOLXZN_MULTITHREADING)
	) noexcept;

	/**
	 * @brief Timer constructor from timer interval and callback.
	 * @ingroup golxzn::os::chrono::construction
	 * @details Timer's callback will be called after timer_interval.
	 * @param timer_interval Timer interval.
	 * @param callback Function that will be called after timer_interval.
	 * @param precision Precision of timer. By default it's 1 microsecond (1us). Only if GOLXZN_MULTITHREADING is defined.
	 */
	timer(const time timer_interval, timer_end_callback &&callback
#if defined(GOLXZN_MULTITHREADING)
		, const std::chrono::microseconds precision = default_precision
#endif // defined(GOLXZN_MULTITHREADING)
	) noexcept;

#if defined(GOLXZN_MULTITHREADING)
	~timer() noexcept;
#endif // defined(GOLXZN_MULTITHREADING)

#if !defined(GOLXZN_MULTITHREADING)
	/**
	 * @brief Updates timer.
	 * @warning Only if GOLXZN_MULTITHREADING is not defined.
	 * @details Should be called in main thread. It's not needed if GOLXZN_MULTITHREADING is defined.
	 */
	void update();
#endif // !defined(GOLXZN_MULTITHREADING)

	/**
	 * @brief Returns true if timer is done.
	 * @see is_running()
	 * @see time_left()
	 */
	[[nodiscard]] bool is_done() const noexcept;

	/**
	 * @brief Returns true if timer is running.
	 * @see is_done()
	 * @see time_left()
	 */
	[[nodiscard]] bool is_running() const noexcept;

	/**
	 * @brief Returns time left to the end of the timer.
	 * @see is_running()
	 * @see is_done()
	 */
	[[nodiscard]] time time_left() const noexcept;

private:
	const time_point m_start_time{ base_clock::now() };
	const time_point m_timer_interval;

#if defined(GOLXZN_MULTITHREADING)
	std::thread m_timer_thread;
#else // ^^^ defined(GOLXZN_MULTITHREADING) ^^^ / vvv !defined(GOLXZN_MULTITHREADING) vvv
	timer_end_callback m_callback;
#endif // !defined(GOLXZN_MULTITHREADING)
};

/**
 * @brief Class that represents fast_timer.
 * @details Compared to golxzn::os::chrono::timer it doesn't use a thread and callback.
 * @ingroup golxzn::os::chrono
 * @tparam BaseClock clock that will be used for measurement. It has to be monotonic and STL compatible.
 */
template<class BaseClock = utils::default_base_clock>
class fast_timer {
	static_assert(BaseClock::is_steady,
		"[golxzn::os::chrono::fast_timer] BaseClock is not a monotonic clock");
	static_assert(utils::enough_resolution_v<BaseClock>,
		"[golxzn::os::chrono::fast_timer] BaseClock's resolution is less than microseconds!");

public:
	using base_clock = BaseClock;
	using time_point = typename base_clock::time_point;
	static constexpr time_point zero{};

	/**
	 * @brief fast_timer constructor from timer interval.
	 * @ingroup golxzn::os::chrono::construction
	 * @param timer_interval Timer interval.
	 * @see fast_timer(const time timer_interval)
	 * @see fast_timer(const std::chrono::duration<Rep, Period> timer_interval)
	 */
	explicit constexpr fast_timer(const time timer_interval) noexcept;

	/**
	 * @brief fast_timer constructor from timer interval.
	 * @ingroup golxzn::os::chrono::construction
	 * @param timer_interval Timer interval.
	 * @see fast_timer(const time timer_interval)
	 * @see fast_timer(const std::chrono::duration<Rep, Period> timer_interval)
	 */
	explicit constexpr fast_timer(const time_point timer_interval) noexcept;

	/**
	 * @brief fast_timer constructor from timer interval.
	 * @ingroup golxzn::os::chrono::construction
	 * @param timer_interval Timer interval.
	 * @see fast_timer(const time timer_interval)
	 * @see fast_timer(const time_point timer_interval)
	 */
	template<class Rep, class Period>
	explicit constexpr fast_timer(const std::chrono::duration<Rep, Period> timer_interval) noexcept;

	/**
	 * @brief Returns true if timer is done.
	 * @see is_running()
	 * @see time_left()
	 */
	[[nodiscard]] constexpr bool is_done() const noexcept;

	/**
	 * @brief Returns true if timer is running.
	 * @see is_done()
	 * @see time_left()
	 */
	[[nodiscard]] constexpr bool is_running() const noexcept;

	/**
	 * @brief Returns time left to the end of the timer.
	 * @see is_running()
	 * @see is_done()
	 */
	[[nodiscard]] constexpr time time_left() const noexcept;

private:
	const time_point m_start_time{ base_clock::now() };
	const time_point m_timer_interval;
};

#include "golxzn/os/chrono/impl/timer.inl"

} // namespace golxzn::os::chrono

/**
 * @class golxzn::os::chrono::timer
 * @ingroup golxzn::os::chrono
 * @warning This class behaviour is undefined if GOLXZN_MULTITHREADING is not defined.
 *
 * This class is used to measure time. It calls callback when it's done.
 * If GOLXZN_MULTITHREADING __is not__ defined it doesn't use a thread.
 * So to call callback it has to be updated in main thread. It storing callback.
 * If GOLXZN_MULTITHREADING __is__ defined it uses a thread.
 * So to call callback it doesn't have to be updated. It doesn't storing callback, but std::thread
 *
 * Example of using:
 * @code{.cpp}
 * std::atomic_bool executed{ false };
 * golxzn::os::chrono::timer timer2{ 10ms,
 * 	std::function<void()>{ [&executed] { executed.store(true); } }
 * };
 * while(!timer2.is_done()) { std::this_thread::sleep_for(1ms); }
 * std::this_thread::sleep_for(1ms);
 * @endcode
 */

/**
 * @class golxzn::os::chrono::fast_timer
 * @ingroup golxzn::os::chrono
 *
 * This class is used to measure time. It doesn't use a thread and callback.
 * It stores only start time and timer interval, which is passing in constructor.
 * So it's very lightweight. It's just check if the creating time + interval is less than current time.
 *
 * Example of using:
 * @code{.cpp}
 * golxzn::os::chrono::fast_timer<> timer{ 100ms }
 * while (timer.is_running()) {
 * 	const auto left{ timer.time_left() };
 * 	// do something
 * }
 * @endcode
 */
