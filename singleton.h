#pragma once

template <typename T>
class singleton
{
public:
	static T* getInstance()
	{
		static T instance;
		return &instance;
	}
};
