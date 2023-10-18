
constexpr time::time(const std::chrono::microseconds duration) noexcept
	: m_microseconds{ duration } {}

template<class Rep, class Period>
constexpr time::time(const std::chrono::duration<Rep, Period> duration) noexcept
	: m_microseconds{ std::chrono::duration_cast<decltype(m_microseconds)>(duration) } {}

template<class Clock, class Duration>
constexpr time::time(const std::chrono::time_point<Clock, Duration> time_point) noexcept
	: time{ time_point.time_since_epoch() } {}

constexpr time::time(const std::floating_point auto seconds) noexcept
	: time{ std::chrono::duration<decltype(seconds)>{ seconds } } { }

constexpr time::time(const i32 milliseconds) noexcept
	: time{ std::chrono::milliseconds{ milliseconds } } { }

constexpr time::time(const i64 microseconds) noexcept
	: time{ std::chrono::microseconds{ microseconds } } { }

template<std::floating_point FloatType>
constexpr FloatType time::seconds() const noexcept {
	return std::chrono::duration<FloatType>{ m_microseconds }.count();
}

constexpr i32 time::milliseconds() const noexcept {
	return std::chrono::duration_cast<std::chrono::duration<i32, std::milli>>(m_microseconds).count();
}

constexpr i64 time::microseconds() const noexcept {
	return m_microseconds.count();
}

constexpr std::chrono::microseconds time::duration() const noexcept {
	return m_microseconds;
}

template<class Rep, class Period>
constexpr time::operator std::chrono::duration<Rep, Period>() const noexcept {
	return std::chrono::duration_cast<std::chrono::duration<Rep, Period>>(m_microseconds);
}

constexpr time &time::operator+=(const time &rhs) noexcept {
	m_microseconds += rhs.m_microseconds;
	return *this;
}

constexpr time &time::operator-=(const time &rhs) noexcept {
	m_microseconds -= rhs.m_microseconds;
	return *this;
}

constexpr time time::zero() noexcept { return time{}; }

constexpr time seconds(const std::floating_point auto value) noexcept { return time{ value }; }
constexpr time milliseconds(const i32 value) noexcept { return time{ std::chrono::milliseconds{ value } }; }
constexpr time microseconds(const i64 value) noexcept { return time{ std::chrono::microseconds{ value } }; }

constexpr auto operator<=>(const time &lhs, const std::floating_point auto rhs) noexcept {
	return lhs <=> seconds(rhs);
}
constexpr auto operator<=>(const time &lhs, const i32 rhs) noexcept -> std::strong_ordering {
	return lhs <=> milliseconds(rhs);
}
constexpr auto operator<=>(const time &lhs, const i64 rhs) noexcept -> std::strong_ordering {
	return lhs <=> microseconds(rhs);
}

constexpr auto operator<=>(const std::floating_point auto lhs, const time &rhs) noexcept -> std::strong_ordering {
	return seconds(lhs) <=> rhs;
}
constexpr auto operator<=>(const i32 lhs, const time &rhs) noexcept -> std::strong_ordering {
	return milliseconds(lhs) <=> rhs;
}
constexpr auto operator<=>(const i64 lhs, const time &rhs) noexcept -> std::strong_ordering {
	return microseconds(lhs) <=> rhs;
}

constexpr time operator-(const time &rhs) noexcept { return microseconds(-rhs.microseconds()); }
constexpr time operator-(const time &lhs, const time &rhs) noexcept { return time{ lhs } -= rhs; }
constexpr time operator+(const time &lhs, const time &rhs) noexcept { return time{ lhs } += rhs; }
