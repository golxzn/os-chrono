<h1 align="center">⏱️ golxzn::os::chrono ⏱️</h1>

<div align="center">

[![Windows](https://github.com/golxzn/os-chrono/actions/workflows/ci-static-lib-windows.yml/badge.svg)][ci-windows]
[![Ubuntu](https://github.com/golxzn/os-chrono/actions/workflows/ci-static-lib-ubuntu.yml/badge.svg)][ci-ubuntu]
[![MacOS](https://github.com/golxzn/os-chrono/actions/workflows/ci-static-lib-macos.yml/badge.svg)][ci-macos]
</div>


<h2><b><i>Description</i></b></h2>

The time utilities for [golxzn::os](https://github.com/golxzn/os).

`golxzn::os::chrono` contains of:

- [golxzn::os::chrono::time](code/include/golxzn/os/chrono/time.hpp) - The time class which represents time points.
- [golxzn::os::chrono::fast_clock](code/include/golxzn/os/chrono/clock.hpp) - So simple and fast clock type to measure elapsed time.
- [golxzn::os::chrono::clock](code/include/golxzn/os/chrono/clock.hpp) - The same clock type as `fast_clock`, but with possibility to stop and resume.
- [golxzn::os::chrono::timer](code/include/golxzn/os/chrono/timer.hpp) - The timer class which could help you with calling functions by timeout or just measure intervals.

Each clock and timer has a template argument `BaseClock` which has to have static method `now()` returning `time_point`.
You could provide your own base clock to make clocks and timers work with your time point type. But ensure that your time point type has enough resolution to measure time. It has to be at least `std::micro`.

<h2><b><i>Dependencies</i></b></h2>

This library requires [golxzn::os::aliases](https://github.com/golxzn/os-aliases.git) and C++17 compatible compiler.

<h2><b><i>Usage</i></b></h2>

<h3><i><code>golxzh::os::chrono::clock</code> examples</i></h3>

```cpp
#include <iostream>
#include <golxzn/os/chrono.hpp>

int main() {
	static const auto test_clock = [] (auto clock) {
		size_t counter{};
		while (counter != 1'000'000'000) ++counter;
		return clock.elapsed();
	};

	using namespace golxzn::os::chrono;

	const auto fast_elapsed{     test_clock(fast_clock{}) };
	const auto fast_sys_elapsed{ test_clock(fast_clock<std::chrono::system_clock>{}) };
	const auto just_elapsed{     test_clock(clock{}) };
	const auto just_sys_elapsed{ test_clock(clock<std::chrono::system_clock>{}) };

	std::cout << "Fast elapsed: " << fast_elapsed.milliseconds() << " milliseconds\n";
	std::cout << "Just elapsed: " << just_elapsed.milliseconds() << " milliseconds\n";
	std::cout << "Fast elapsed (sys): " << fast_sys_elapsed.milliseconds() << " milliseconds\n";
	std::cout << "Just elapsed (sys): " << just_sys_elapsed.milliseconds() << " milliseconds\n";
}
```

<h3><i><code>golxzh::os::chrono::timer</code> examples</i></h3>

```cpp
#include <iostream>
#include <golxzn/os/chrono.hpp>

int main() {
	using namespace std::chrono_literals;

	std::cout << "[" << std::this_thread::get_id() << "]: Starting timer for 2 sec\n";
	golxzn::chrono::timer timer{ 1s, [] {
		std::cout << "[" << std::this_thread::get_id() << "]: Timer done\n";
	} };

	while (timer.is_running()) {
		std::cout << "[" << std::this_thread::get_id() << "]: Time left: " << timer.time_left().milliseconds() << " milliseconds\n";
		std::this_thread::sleep_for(100ms);
	}

	std::cout << "[" << std::this_thread::get_id() << "] Exiting\n";

}
```

<hr>

<h2>Thanks</h2>

Documentations is powered by:

- [💪 Doxygen][doxygen-link]
- [💘 doxygen-awesome-css][doxygen-awesome-css-link].

[ci-windows]: https://github.com/golxzn/os-chrono/actions/workflows/ci-static-lib-windows.yml
[ci-ubuntu]: https://github.com/golxzn/os-chrono/actions/workflows/ci-static-lib-ubuntu.yml
[ci-macos]: https://github.com/golxzn/os-chrono/actions/workflows/ci-static-lib-macos.yml

[doxygen-link]: https://www.doxygen.nl/
[doxygen-awesome-css-link]: https://github.com/jothepro/doxygen-awesome-css

