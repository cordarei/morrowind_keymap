#pragma once
#include <algorithm>

template <class T>
class com_ptr {
public:
	com_ptr(T* p) : _p(p) {
		if (_p) _p->AddRef();
	}
	com_ptr(com_ptr const& other) : _p(other._p) {
		if (_p) _p->AddRef();
	}

	virtual ~com_ptr() {
		if (_p) _p->Release();
		_p = 0;
	}

	void swap(com_ptr & other) {
		std::swap(_p, other._p);
	}

	void reset() {
		com_ptr t(0);
		this->swap(t);
	}

	com_ptr& operator=(com_ptr const& other) {
		com_ptr t(other);
		this->swap(t);
		return *this;
	}

	T* get() { return _p; }
	T const * get() const { return _p; }

	T* operator->() { return _p; }
	T const * operator->() const { return _p; }

private:
	T* _p;
};