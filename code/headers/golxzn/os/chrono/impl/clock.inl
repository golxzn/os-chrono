
template<class Base>
time fast_clock<Base>::elapsed() noexcept {
	const auto current{ base_clock::now() };
	return utils::difference<time>(current, std::exchange(m_last_time, current));
}

template<class Base>
bool clock<Base>::running() const noexcept {
	return m_stop_time == zero;
}

template<class Base>
time clock<Base>::elapsed() const noexcept {
	if (running()) [[unlikely]] {
		return utils::difference<time>(base_clock::now(), m_last_reset_time);
	}
	return utils::difference<time>(m_stop_time, m_last_reset_time);
}

template<class Base>
time clock<Base>::restart() noexcept {
	const auto elapsed_time{ elapsed() };
	m_stop_time = zero;
	m_last_reset_time = base_clock::now();
	return elapsed_time;
}

template<class Base>
time clock<Base>::reset() noexcept {
	const auto elapsed_time{ elapsed() };
	m_last_reset_time = base_clock::now();
	m_stop_time = m_last_reset_time;
	return elapsed_time;
}

