

template<class CB, class Base>
template<class Rep, class Period>
timer<CB, Base>::timer(const std::chrono::duration<Rep, Period> timer_interval, timer_end_callback &&callback
#if defined(GOLXZN_MULTITHREADING)
		, const std::chrono::microseconds precision
#endif // defined(GOLXZN_MULTITHREADING)
)
	: m_timer_interval{ timer_interval }
#if !defined(GOLXZN_MULTITHREADING)
	, m_callback{ std::move(callback) }
#endif // defined(GOLXZN_MULTITHREADING)
{

#if defined(GOLXZN_MULTITHREADING)

	m_timer_thread = std::thread([this, cb = callback, precision] {
		while (is_running()) [[likely]] { std::this_thread::sleep_for(precision); }
		cb();
	});

#endif // defined(GOLXZN_MULTITHREADING)
}

template<class CB, class Base>
timer<CB, Base>::timer(const time timer_interval, timer_end_callback &&callback
#if defined(GOLXZN_MULTITHREADING)
		, const std::chrono::microseconds precision
#endif // defined(GOLXZN_MULTITHREADING)
)
	: timer{ timer_interval.duration(), std::move(callback)
#if defined(GOLXZN_MULTITHREADING)
	, precision
#endif // defined(GOLXZN_MULTITHREADING)
} { }

#if defined(GOLXZN_MULTITHREADING)
template<class CB, class Base>
timer<CB, Base>::~timer() noexcept {
	if (m_timer_thread.joinable()) {
		m_timer_thread.join();
	} else {
		m_timer_thread.detach();
	}
}
#endif // defined(GOLXZN_MULTITHREADING)

#if !defined(GOLXZN_MULTITHREADING)
template<class CB, class Base>
void timer<CB, Base>::update() {
	if (is_done()) [[unlikely]] {
		m_callback();
	}
}
#endif // !defined(GOLXZN_MULTITHREADING)

template<class CB, class Base>
bool timer<CB, Base>::is_done() const noexcept {
	return utils::difference<time_point>(base_clock::now(), m_start_time) >= m_timer_interval;
}

template<class CB, class Base>
bool timer<CB, Base>::is_running() const noexcept {
	return !is_done();
}

template<class CB, class Base>
time timer<CB, Base>::time_left() const noexcept {
	const auto diff{ utils::difference<time_point>(base_clock::now(), m_start_time) };
	return diff < m_timer_interval ? utils::difference<time>(m_timer_interval, diff) : time{};
}

template<class Base>
constexpr fast_timer<Base>::fast_timer(const time timer_interval) noexcept
	: fast_timer{ static_cast<time_point>(timer_interval) } {
}

template<class Base>
constexpr fast_timer<Base>::fast_timer(const time_point timer_interval) noexcept
	: m_timer_interval{ timer_interval }
{}

template<class Base>
template<class Rep, class Period>
constexpr fast_timer<Base>::fast_timer(const std::chrono::duration<Rep, Period> timer_interval) noexcept
	: m_timer_interval{ timer_interval } {
}

template<class Base>
constexpr bool fast_timer<Base>::is_done() const noexcept {
	return utils::difference<time_point>(base_clock::now(), m_start_time) >= m_timer_interval;
}

template<class Base>
constexpr bool fast_timer<Base>::is_running() const noexcept {
	return !is_done();
}

template<class Base>
constexpr time fast_timer<Base>::time_left() const noexcept {
	const auto diff{ utils::difference<time_point>(base_clock::now(), m_start_time) };
	return diff < m_timer_interval ? utils::difference<time>(m_timer_interval, diff) : time{};
}

