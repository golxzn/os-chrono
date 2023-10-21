#pragma once

#include "golxzn/os/chrono/utils.hpp"
#include "golxzn/os/chrono/time.hpp"

namespace golxzn::os::chrono {

template<utils::base_clock BaseClock = utils::default_base_clock>
class fast_clock {
	static_assert(BaseClock::is_steady,
		"[golxzn::os::chrono::fast_clock] BaseClock is not a monotonic clock");
	static_assert(utils::enough_resolution_v<BaseClock>,
		"[golxzn::os::chrono::fast_clock] BaseClock's resolution is less than microseconds!");

public:
	using base_clock = BaseClock;
	using time_point = base_clock::time_point;
	static constexpr time_point zero{};

	[[nodiscard]] time elapsed() noexcept;

private:
	time_point m_last_time{ base_clock::now() };
};

template<utils::base_clock BaseClock = utils::default_base_clock>
class clock {
	static_assert(BaseClock::is_steady,
		"[golxzn::os::chrono::clock] BaseClock is not a monotonic clock");
	static_assert(utils::enough_resolution_v<BaseClock>,
		"[golxzn::os::chrono::clock] BaseClock's resolution is less than microseconds!");

public:
	using base_clock = BaseClock;
	using time_point = base_clock::time_point;
	static constexpr time_point zero{};

	[[nodiscard]] bool running() const noexcept;
	[[nodiscard]] time elapsed() const noexcept;
	[[nodiscard]] time restart() noexcept;
	[[nodiscard]] time reset() noexcept;

	void start() noexcept;
	void stop() noexcept;

private:
	time_point m_last_reset_time{ base_clock::now() };
	time_point m_stop_time{ zero };
};

#include "golxzn/os/chrono/impl/clock.inl"

} // namespace golxzn::os::chrono
