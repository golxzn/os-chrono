#pragma once

#include <thread>
#include "golxzn/os/chrono/utils.hpp"
#include "golxzn/os/chrono/time.hpp"

namespace golxzn::os::chrono {

template<std::invocable OnTimerDone, utils::base_clock BaseClock = utils::default_base_clock>
class timer {
	static_assert(BaseClock::is_steady,
		"[golxzn::os::chrono::timer] BaseClock is not a monotonic clock");
	static_assert(utils::enough_resolution_v<BaseClock>,
		"[golxzn::os::chrono::timer] BaseClock's resolution is less than microseconds!");

public:
	using base_clock = BaseClock;
	using time_point = base_clock::time_point;
	using timer_end_callback = OnTimerDone;

	static constexpr auto default_precision{ std::chrono::microseconds{ 1 } };
	static constexpr time_point zero{};

	template<class Rep, class Period>
	timer(const std::chrono::duration<Rep, Period> timer_interval, timer_end_callback &&callback
#if defined(GOLXZN_MULTITHREADING)
		, const std::chrono::microseconds precision = default_precision
#endif // defined(GOLXZN_MULTITHREADING)
	) noexcept;

	timer(const time timer_interval, timer_end_callback &&callback
#if defined(GOLXZN_MULTITHREADING)
		, const std::chrono::microseconds precision = default_precision
#endif // defined(GOLXZN_MULTITHREADING)
	) noexcept;



#if !defined(GOLXZN_MULTITHREADING)
	void update();
#endif // !defined(GOLXZN_MULTITHREADING)

	[[nodiscard]] bool is_done() const noexcept;
	[[nodiscard]] bool is_running() const noexcept;
	[[nodiscard]] time time_left() const noexcept;

private:
	const time_point m_start_time{ base_clock::now() };
	const time_point m_timer_interval;

#if defined(GOLXZN_MULTITHREADING)
	std::jthread m_timer_thread;
#else // ^^^ defined(GOLXZN_MULTITHREADING) ^^^ / vvv !defined(GOLXZN_MULTITHREADING) vvv
	timer_end_callback m_callback;
#endif // !defined(GOLXZN_MULTITHREADING)
};

template<utils::base_clock BaseClock>
class timer<void, BaseClock> {
	static_assert(BaseClock::is_steady,
		"[golxzn::os::chrono::timer] BaseClock is not a monotonic clock");
	static_assert(utils::enough_resolution_v<BaseClock>,
		"[golxzn::os::chrono::timer] BaseClock's resolution is less than microseconds!");

public:
	using base_clock = BaseClock;
	using time_point = base_clock::time_point;
	static constexpr time_point zero{};

	explicit constexpr timer(const std::convertible_to<time_point> auto timer_interval) noexcept;

	[[nodiscard]] constexpr bool is_done() const noexcept;
	[[nodiscard]] constexpr bool is_running() const noexcept;
	[[nodiscard]] constexpr time time_left() const noexcept;

private:
	const time_point m_start_time{ base_clock::now() };
	const time_point m_timer_interval;
};

template<utils::base_clock BaseClock = utils::default_base_clock>
using fast_timer = timer<void, BaseClock>;

#include "golxzn/os/chrono/impl/timer.inl"

} // namespace golxzn::os::chrono
