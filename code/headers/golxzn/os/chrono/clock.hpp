#pragma once

#include "golxzn/os/chrono/utils.hpp"
#include "golxzn/os/chrono/time.hpp"

namespace golxzn::os::chrono {

/**
 * @brief Class that represents fast clock, which store only one time point.
 * @ingroup golxzn::os::chrono
 * @include golxzn/os/chrono/time.hpp
 * This class allows to measure time since last call of elapsed() or since construction.
 * It's fast because it doesn't store any information but last time point
 * @tparam BaseClock clock that will be used for measurement. It has to be monotonic and STL compatible.
 * @see golxzn::os::chrono::clock
 */
template<class BaseClock = utils::default_base_clock>
class fast_clock {
	static_assert(BaseClock::is_steady,
		"[golxzn::os::chrono::fast_clock] BaseClock is not a monotonic clock");
	static_assert(utils::enough_resolution_v<BaseClock>,
		"[golxzn::os::chrono::fast_clock] BaseClock's resolution is less than microseconds!");

public:
	using base_clock = BaseClock;
	using time_point = typename base_clock::time_point;
	static constexpr time_point zero{};

	/**
	 * @brief Returns elapsed time since last call of elapsed() or since construction.
	 * @return time
	 */
	[[nodiscard]] time elapsed() noexcept;

private:
	time_point m_last_time{ base_clock::now() };
};

/**
 * @brief Class that represents clock.
 * @ingroup golxzn::os::chrono
 * @include golxzn/os/chrono/time.hpp
 * In comparison with golxzn::os::chrono::fast_clock, it provides more functionality but it's slower.
 * @tparam BaseClock clock that will be used for measurement. It has to be monotonic and STL compatible.
 * @see golxzn::os::chrono::fast_clock
 */
template<class BaseClock = utils::default_base_clock>
class clock {
	static_assert(BaseClock::is_steady,
		"[golxzn::os::chrono::clock] BaseClock is not a monotonic clock");
	static_assert(utils::enough_resolution_v<BaseClock>,
		"[golxzn::os::chrono::clock] BaseClock's resolution is less than microseconds!");

public:
	using base_clock = BaseClock;
	using time_point = typename base_clock::time_point;
	static constexpr time_point zero{};

	/**
	 * @brief Returns true if clock is running.
	 * @return clock running state
	 * @see restart()
	 * @see reset()
	 * @see elapsed()
	 */
	[[nodiscard]] bool running() const noexcept;

	/**
	 * @brief Returns elapsed time since last reset or construction.
	 * @return time
	 * @see restart()
	 * @see reset()
	 * @see running()
	 */
	[[nodiscard]] time elapsed() const noexcept;

	/**
	 * @brief Restarts clock
	 * @return elapsed time since last reset or construction.
	 * @see reset()
	 * @see elapsed()
	 * @see running()
	 * @see start()
	 * @see stop()
	 */
	[[nodiscard]] time restart() noexcept;

	/**
	 * @brief Resets clock
	 * @return elapsed time since last reset or construction.
	 * @see restart()
	 * @see elapsed()
	 * @see running()
	 * @see start()
	 * @see stop()
	 */
	[[nodiscard]] time reset() noexcept;

	/**
	 * @brief Starts clock
	 * @see stop()
	 * @see running()
	 */
	void start() noexcept;

	/**
	 * @brief Stops clock
	 * @see start()
	 * @see running()
	 */
	void stop() noexcept;

private:
	time_point m_last_reset_time{ base_clock::now() };
	time_point m_stop_time{ zero };
};

#include "golxzn/os/chrono/impl/clock.inl"

} // namespace golxzn::os::chrono

/**
 * @class golxzn::os::chrono::fast_clock
 * @ingroup golxzn::os::chrono
 * This class provides measurement of elapsed time since last call of elapsed() or since construction.
 * It doesn't store any information but last time point. When you call elapsed(), it stores new time point,
 * and returns difference of old and new time points.
 *
 * Usage:
 * @code{.cpp}
 * golxzn::os::chrono::fast_clock<> clock;
 * while (game_running) {
 * 	const auto elapsed{ clock.elapsed() };
 * 	Game::Update(elapsed.seconds<double>());
 * 	...
 * }
 * @endcode
 */
