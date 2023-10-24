/**
 * @file golxzn/os/chrono.hpp
 * @author Ruslan Golovinskii (golxzn@gmail.com)
 * @brief Main header for golxzn::os::chrono
 * @date 2023-10-24
 *
 * @copyright Copyright (c) 2023
 *
 * @defgroup golxzn::os::chrono Chrono
 *
 * Description
 * -------------
 *
 * This file is the common header to include all the functionality of golxzn::os::chrono.
 * It includes the following classes:
 * - [golxzn::os::chrono::time](@ref golxzn::os::chrono::time)
 * - [golxzn::os::chrono::fast_clock](@ref golxzn::os::chrono::fast_clock)
 * - [golxzn::os::chrono::clock](@ref golxzn::os::chrono::clock)
 * - [golxzn::os::chrono::fast_timer](@ref golxzn::os::chrono::fast_timer)
 * - [golxzn::os::chrono::timer](@ref golxzn::os::chrono::timer)
 *
 * Diagram
 * -------------
 *
 * ```plantuml
 * @startuml
 * !theme crt-amber
 * title golxzn chrono classes
 *
 * namespace golxzn::os::chrono {
 *     class time {
 *         + seconds() const noexcept : float|double
 *         + milliseconds() const noexcept : i32
 *         + microseconds() const noexcept : i64
 *         + duration() const noexcept : std::chrono::microseconds
 *         {static} + zero() noexcept : time
 *         {static} + now() noexcept : time
 *     }
 *
 *     class fast_clock {
 *         + elapsed() noexcept : time
 *     }
 *     class clock {
 *         + running() const noexcept : bool
 *         + elapsed() noexcept : time
 *         + restart() noexcept : time
 *         + reset() noexcept : time
 *         + start() noexcept : void
 *         + stop() noexcept : void
 *     }
 *
 *     class fast_timer {
 *         + constructor(interval)
 *         + is_done() const noexcept : bool
 *         + is_running() const noexcept : bool
 *         + time_left() const noexcept : time
 *     }
 *     class timer {
 *         + constructor(interval, callback)
 *         + is_done() const noexcept : bool
 *         + is_running() const noexcept : bool
 *         + time_left() const noexcept : time
 *     }
 *
 *     time <.. fast_clock
 *     time <.. clock
 *     time <.. fast_timer
 *     time <.. timer:now
 * }
 *
 * @enduml
 * ```
 */

#pragma once

#include <golxzn/os/chrono/time.hpp>
#include <golxzn/os/chrono/clock.hpp>
#include <golxzn/os/chrono/timer.hpp>

namespace gxzn = golxzn;

#if defined(GOLXZN_USE_GLOBAL_NAMES)
namespace golxzn { using namespace os; } // namespace golxzn
#endif // defined(GOLXZN_USE_GLOBAL_NAMES)
