#pragma once

template <typename T>
class MyRange
{
	//��� ���������� ��������������� ����� ������������� ������� numeric_limits. 
	//� ����������� ���������� �������� ������������� ��� ���� �������������� �����
	T min_r=std::numeric_limits<T>::min();
	T max_r=std::numeric_limits<T>::max();
public:
	constexpr MyRange(const T& min, const T& max):min_r(min),max_r(max){}
	constexpr T get_min() const { return min_r; }
	constexpr T get_max() const { return max_r; }
	constexpr bool is_entry(const T& t) const { return (!(t < min_r)) && (!(max_r < t)); }
	constexpr T ranged(const T&t) const
	{
		T res{};
		if (t < min_r) res = min_r;
		if (max_r < t) res = max_r;
		if (this->is_entry(t)) res = t;
		return res;
	}
};

