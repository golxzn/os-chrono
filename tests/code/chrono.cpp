
#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>

#include <golxzn/os/chrono.hpp>

using namespace std::chrono_literals;

TEST_CASE("Test chrono clock", "[test][os][chrono][fast_clock]") {
	golxzn::os::chrono::fast_clock<> clock;
	std::this_thread::sleep_for(10ms);
	REQUIRE(clock.elapsed() >= 10ms);
}
