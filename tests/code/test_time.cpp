#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>

#include <golxzn/os/chrono.hpp>


TEST_CASE("Test chrono time", "[test][os][chrono][time]") {
	using namespace std::chrono_literals;
	constexpr golxzn::os::chrono::time t1{ 42s };
	REQUIRE(t1.seconds() == 42.0);
	REQUIRE(t1.milliseconds() == 42000);
	REQUIRE(t1.microseconds() == 42000000);
	REQUIRE(static_cast<std::chrono::seconds>(t1) == 42s);
}

