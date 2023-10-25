#include <functional>
#include <atomic>
#include <thread>

#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>

#include <golxzn/os/chrono.hpp>

using namespace std::chrono_literals;

TEST_CASE("Test chrono timer", "[test][os][chrono][fast_timer]") {
	golxzn::os::chrono::fast_timer<> timer{ 10ms };
	while(!timer.is_done()) { std::this_thread::sleep_for(1ms); }
	REQUIRE(timer.is_done());
	REQUIRE(timer.is_running() == false);
	REQUIRE(timer.time_left() == golxzn::os::chrono::time::zero());
}

TEST_CASE("Test chrono timer", "[test][os][chrono][timer]") {
	std::atomic_bool executed{ false };
	golxzn::os::chrono::timer timer{ 10ms, [&executed] { executed.store(true); } };
	while (timer.is_running()) {
		std::this_thread::sleep_for(1ms);  // Wait until timer is done
#if !defined(GOLXZN_MULTITHREADING)
		timer.update(); // Manually update to execute callback
#endif // !defined(GOLXZN_MULTITHREADING)
	}
	std::this_thread::sleep_for(1ms); // to ensure that callback executed

	REQUIRE(executed == true);
}
