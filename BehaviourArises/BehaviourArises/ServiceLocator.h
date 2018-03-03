#pragma once

template <typename T>
class ServiceLocator
{
public:
	static T* GetService() {
		assert(m_service != nullptr);
		return m_service;
	}
	static void ProvideService(T* p_service)
	{
		m_service = p_service;
	}
private:
	static T* m_service;
};
template <typename T>
T* ServiceLocator<T>::m_service = nullptr;