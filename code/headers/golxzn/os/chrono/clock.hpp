/**
 * @file golxzn/os/chrono/clock.hpp
 * @author Ruslan Golovinskii (golxzn@gmail.com)
 * @brief Clock classes to measure elapsed time
 * @date 2023-10-24
 *
 * @copyright Copyright (c) 2023
 */

#pragma once

#include "golxzn/os/chrono/utils.hpp"
#include "golxzn/os/chrono/time.hpp"

namespace golxzn::os::chrono {

/**
 * @brief Class that represents fast clock, which store only one time point.
 * @ingroup Chrono clocks
 * This class allows to measure time since last call of elapsed() or since construction.
 * It's fast because it doesn't store any information but last time point
 * This class provides measurement of elapsed time since last call of elapsed() or since construction.
 * > It doesn't store any information but last time point. When you call elapsed(), it stores new time point,
 * > and returns difference of old and new time points.
 * @tparam BaseClock clock that will be used for measurement. It has to be monotonic and STL compatible.
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
 * @see golxzn::os::chrono::clock
 */
template<class BaseClock = utils::default_base_clock>
class fast_clock {
	static_assert(BaseClock::is_steady,
		"[golxzn::os::chrono::fast_clock] BaseClock is not a monotonic clock");
	static_assert(utils::enough_resolution_v<BaseClock>,
		"[golxzn::os::chrono::fast_clock] BaseClock's resolution is less than microseconds!");

public:
	using base_clock = BaseClock;                       ///< Base clock type
	using time_point = typename base_clock::time_point; ///< Time point type from base clock
	static constexpr time_point zero{};                 ///< Zero time point

	/**
	 * @brief Returns elapsed time since last call of `elapsed()` or since construction.
	 * @return time
	 */
	[[nodiscard]] time elapsed() noexcept;

private:
	time_point m_last_time{ base_clock::now() };
};

/**
 * @brief Class that represents clock.
 * @ingroup Chrono clocks
 * In comparison with @ref golxzn::os::chrono::fast_clock, it provides more functionality but it's slower.
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
	 * @see time restart() noexcept;
	 * @see time reset() const noexcept;
	 * @see time elapsed() const noexcept;
	 */
	[[nodiscard]] bool running() const noexcept;

	/**
	 * @brief Returns elapsed time since last reset or construction.
	 * @return time
	 * @see time restart() noexcept;
	 * @see time reset() const noexcept;
	 * @see bool running() const noexcept
	 */
	[[nodiscard]] time elapsed() const noexcept;

	/**
	 * @brief Restarts clock
	 * @return elapsed time since last reset or construction.
	 * @see time reset() const noexcept;
	 * @see time elapsed() const noexcept;
	 * @see bool running() const noexcept
	 * @see void start() noexcept
	 * @see void stop() noexcept
	 */
	[[nodiscard]] time restart() noexcept;

	/**
	 * @brief Resets clock
	 * @return elapsed time since last reset or construction.
	 * @see time restart() const noexcept;
	 * @see time elapsed() const noexcept;
	 * @see bool running() const noexcept
	 * @see void start() noexcept
	 * @see void stop() noexcept
	 */
	[[nodiscard]] time reset() noexcept;

	/**
	 * @brief Starts clock
	 * @see stop()
	 * @see bool running() const noexcept
	 */
	void start() noexcept;

	/**
	 * @brief Stops clock
	 * @see start()
	 * @see bool running() const noexcept
	 */
	void stop() noexcept;

private:
	time_point m_last_reset_time{ base_clock::now() };
	time_point m_stop_time{ zero };
};

#include "golxzn/os/chrono/impl/clock.inl"

} // namespace golxzn::os::chrono

