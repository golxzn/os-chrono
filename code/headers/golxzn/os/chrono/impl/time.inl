
constexpr time::time(const std::chrono::microseconds duration) noexcept
	: m_microseconds{ duration } {}

template<class Rep, class Period>
constexpr time::time(const std::chrono::duration<Rep, Period> duration) noexcept
	: m_microseconds{ std::chrono::duration_cast<decltype(m_microseconds)>(duration) } {}

template<class Clock, class Duration>
constexpr time::time(const std::chrono::time_point<Clock, Duration> time_point) noexcept
	: time{ time_point.time_since_epoch() } {}

template<class T>
constexpr time::time(const utils::floating_point_t<T> seconds) noexcept
	: time{ std::chrono::duration<decltype(seconds)>{ seconds } } { }

constexpr time::time(const i32 milliseconds) noexcept
	: time{ std::chrono::milliseconds{ milliseconds } } { }

constexpr time::time(const i64 microseconds) noexcept
	: time{ std::chrono::microseconds{ microseconds } } { }

template<class T>
constexpr utils::floating_point_t<T> time::seconds() const noexcept {
	return std::chrono::duration<T>{ m_microseconds }.count();
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

template<class T>
constexpr time &time::operator+=(const utils::floating_point_t<T> rhs) noexcept {
	return *this += golxzn::os::chrono::seconds(rhs);
}

constexpr time &time::operator+=(const i32 rhs) noexcept {
	return *this += golxzn::os::chrono::milliseconds(rhs);
}

constexpr time &time::operator+=(const i64 rhs) noexcept {
	return *this += golxzn::os::chrono::microseconds(rhs);
}


constexpr time &time::operator-=(const time &rhs) noexcept {
	m_microseconds -= rhs.m_microseconds;
	return *this;
}

template<class T>
constexpr time &time::operator-=(const utils::floating_point_t<T> rhs) noexcept {
	return *this -= golxzn::os::chrono::seconds(rhs);
}

constexpr time &time::operator-=(const i32 rhs) noexcept {
	return *this -= golxzn::os::chrono::milliseconds(rhs);
}

constexpr time &time::operator-=(const i64 rhs) noexcept {
	return *this -= golxzn::os::chrono::microseconds(rhs);
}

constexpr bool time::operator==(const time &rhs) const noexcept{
	return m_microseconds == rhs.m_microseconds;
}
constexpr bool time::operator!=(const time &rhs) const noexcept{
	return m_microseconds != rhs.m_microseconds;
}
constexpr bool time::operator>=(const time &rhs) const noexcept{
	return m_microseconds >= rhs.m_microseconds;
}
constexpr bool time::operator<=(const time &rhs) const noexcept{
	return m_microseconds <= rhs.m_microseconds;
}
constexpr bool time::operator> (const time &rhs) const noexcept{
	return m_microseconds > rhs.m_microseconds;
}
constexpr bool time::operator< (const time &rhs) const noexcept{
	return m_microseconds < rhs.m_microseconds;
}



constexpr time time::zero() noexcept { return time{}; }

template<class T>
constexpr time seconds(const utils::floating_point_t<T> value) noexcept { return time{ value }; }
constexpr time milliseconds(const i32 value) noexcept { return time{ std::chrono::milliseconds{ value } }; }
constexpr time microseconds(const i64 value) noexcept { return time{ std::chrono::microseconds{ value } }; }
