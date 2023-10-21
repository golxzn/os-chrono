#include "golxzn/os/chrono/utils.hpp"
#include "golxzn/os/chrono/time.hpp"

namespace golxzn::os::chrono {

time time::now() noexcept {
	return time{ utils::default_base_clock::now() };
}

} // namespace golxzn::os::chrono

