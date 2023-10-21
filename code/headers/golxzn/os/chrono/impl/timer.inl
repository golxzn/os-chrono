

template<std::invocable CB, utils::base_clock Base>
template<class Rep, class Period>
timer<CB, Base>::timer(const std::chrono::duration<Rep, Period> timer_interval, timer_end_callback &&callback
#if defined(GOLXZN_MULTITHREADING)
		, const std::chrono::microseconds precision
#endif // defined(GOLXZN_MULTITHREADING)
) noexcept
	: m_timer_interval{ timer_interval }
#if !defined(GOLXZN_MULTITHREADING)
	, m_callback{ std::move(callback) }
#endif // defined(GOLXZN_MULTITHREADING)
{

#if defined(GOLXZN_MULTITHREADING)

	/// @todo Replace C assert to GOLXZN_ASSERT(condition, "message")
	assert(callback != nullptr && "Callback can't be nullptr when using multithreading!");
	if (callback == nullptr) return;

	m_timer_thread = std::jthread([this, cb = std::move(callback), precision] {
		while (is_running()) [[likely]] { std::this_thread::sleep_for(precision); }
		cb();
	});

#else

	/// @todo Replace C assert to GOLXZN_ASSERT(condition, "message")
	assert(m_callback != nullptr && "Callback can't be nullptr when using multithreading!");

#endif // defined(GOLXZN_MULTITHREADING)
}

template<std::invocable CB, utils::base_clock Base>
timer<CB, Base>::timer(const time timer_interval, timer_end_callback &&callback
#if defined(GOLXZN_MULTITHREADING)
		, const std::chrono::microseconds precision
#endif // defined(GOLXZN_MULTITHREADING)
) noexcept : timer{ timer_interval.duration(), std::move(callback)
#if defined(GOLXZN_MULTITHREADING)
	, precision
#endif // defined(GOLXZN_MULTITHREADING)
} { }


#if !defined(GOLXZN_MULTITHREADING)
template<std::invocable CB, utils::base_clock Base>
void timer<CB, Base>::update() {
	if (is_done() && m_callback != nullptr) [[unlikely]] {
		m_callback();
	}
}
#endif // !defined(GOLXZN_MULTITHREADING)

template<std::invocable CB, utils::base_clock Base>
bool timer<CB, Base>::is_done() const noexcept {
	return utils::difference<time_point>(base_clock::now(), m_start_time) >= m_timer_interval;
}

template<std::invocable CB, utils::base_clock Base>
bool timer<CB, Base>::is_running() const noexcept {
	return !is_done();
}

template<std::invocable CB, utils::base_clock Base>
time timer<CB, Base>::time_left() const noexcept {
	const auto diff{ utils::difference<time_point>(base_clock::now(), m_start_time) };
	return diff < m_timer_interval ? utils::difference<time>(m_timer_interval, diff) : time{};
}


template<utils::base_clock Base>
constexpr timer<void, Base>::timer(const std::convertible_to<time_point> auto timer_interval) noexcept
	: m_timer_interval{ timer_interval } {
}

template<utils::base_clock Base>
constexpr bool timer<void, Base>::is_done() const noexcept {
	return utils::difference<time_point>(base_clock::now(), m_start_time) >= m_timer_interval;
}

template<utils::base_clock Base>
constexpr bool timer<void, Base>::is_running() const noexcept {
	return !is_done();
}

template<utils::base_clock Base>
constexpr time timer<void, Base>::time_left() const noexcept {
	const auto diff{ utils::difference<time_point>(base_clock::now(), m_start_time) };
	return diff < m_timer_interval ? utils::difference<time>(m_timer_interval, diff) : time{};
}

