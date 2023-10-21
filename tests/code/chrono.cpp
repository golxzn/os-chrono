#include <functional>
#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>

#include <golxzn/os/chrono.hpp>

using namespace std::chrono_literals;

TEST_CASE("Test chrono time", "[test][os][chrono][time]") {
	constexpr golxzn::os::chrono::time t1{ 42s };
	REQUIRE(t1.seconds() == 42.0);
	REQUIRE(t1.milliseconds() == 42000);
	REQUIRE(t1.microseconds() == 42000000);
	REQUIRE(static_cast<std::chrono::seconds>(t1) == 42s);
}

TEST_CASE("Test chrono clock", "[test][os][chrono][fast_clock]") {
	golxzn::os::chrono::fast_clock<> clock;
	std::this_thread::sleep_for(10ms);
	REQUIRE(clock.elapsed() >= 10ms);
}

TEST_CASE("Test chrono clock", "[test][os][chrono][clock]") {
	golxzn::os::chrono::clock<> clock;
	std::this_thread::sleep_for(10ms);
	REQUIRE(clock.elapsed() >= 10ms);
}

TEST_CASE("Test chrono timer", "[test][os][chrono][fast_timer]") {
	golxzn::os::chrono::fast_timer<> timer{ 10ms };
	while(!timer.is_done()) { std::this_thread::sleep_for(1ms); }
	REQUIRE(timer.is_done());
	REQUIRE(timer.is_running() == false);
	REQUIRE(timer.time_left() == golxzn::os::chrono::time::zero());

	std::atomic_bool executed{ false };
	golxzn::os::chrono::timer timer2{ 10ms, std::function<void()>{ [&executed] { executed.store(true); } } };
	while(!timer2.is_done()) { std::this_thread::sleep_for(1ms); }
	std::this_thread::sleep_for(1ms); // to ensure that callback executed
	REQUIRE(executed == true);
}