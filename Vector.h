#pragma once
#include <iostream>
using namespace std;
class Vector
{
private:
	size_t m_size;
	int* m_arr;
public:
	// конструктор с параметрами
	Vector(size_t size): m_arr(new int[size]()), m_size(size) {};
	
	//конструктор копирования
	Vector(const Vector& vec): m_arr(new int[vec.m_size]), m_size(vec.m_size) {
		for (size_t i = 0; i < m_size;i++) {
			m_arr[i] = vec.m_arr[i];
		}
	};

	// конструктор перемещения
	Vector(Vector&& vec) noexcept : m_arr(vec.m_arr), m_size(vec.m_size) {
		vec.m_arr = nullptr;
		vec.m_size = 0;
	};


	//Оператор присваивания копированием
	Vector& operator = (Vector& vec) {
		if (this == &vec) return *this;
		delete[] m_arr;
		m_arr = new int[vec.m_size];
		m_size = vec.m_size;
		for (size_t i = 0; i < m_size; i++) {
			m_arr[i] = vec.m_arr[i];
		}
		return *this;
	};

	//Оператор присваивания перемещением
	Vector& operator = (Vector&& vec) noexcept {
		if (this == &vec) return *this;
		delete[] m_arr;
		m_arr = vec.m_arr;
		m_size = vec.m_size;
		vec.m_arr = nullptr;
		vec.m_size = 0;
		return *this;
	};

	//деструктор
	~Vector() {
		if (m_arr) {
			delete[] m_arr;
			m_arr = nullptr;
			m_size = 0;
		}
	};

	void set_val(int val,int index) {
		this->m_arr[index] = val;
	}
	int get_val(int index) {
		return this->m_arr[index];
	}

	int get_size() {return m_size;};

	int sum(){
		int summa = 0;
		for (size_t i = 0; i < m_size; i++){summa += m_arr[i];};
		return summa;
	}


	// Метод resize(size_t new_size)
	void resize(size_t new_size) {
		int* new_arr = new int[new_size]();
		if (new_size < 0) { throw "You cannot enter a negative number" ; };
		size_t min_size = (new_size < m_size) ? new_size : m_size;
		for (size_t i = 0; i < min_size; ++i) {
			new_arr[i] = m_arr[i];
		}
		delete[] m_arr;
		m_arr = new_arr;
		m_size = new_size;
	}

	// Метод slice(size_t start, size_t end)
	Vector slice(size_t start, size_t end) const {
		if (start > end || end >= m_size) {
			throw "Invalid indices for slice";
		}
		if (start < 0 || end<0) { throw "You cannot enter a negative number"; };
		Vector result(end - start + 1);
		for (size_t i = start; i <= end; ++i) {
			result.m_arr[i - start] = m_arr[i];
		}
		return result;
	}

	// Итераторы
	int* begin() { return m_arr; }
	int* end() { return m_arr + m_size; }
	const int* begin() const { return m_arr; }
	const int* end() const { return m_arr + m_size; }

	// Метод push_back(int value)
	void push_back(int value) {
		resize(m_size + 1);
		m_arr[m_size - 1] = value;
	}

	// Метод find(int value)
	int find(int value) const {
		for (size_t i = 0; i < m_size; ++i) {
			if (m_arr[i] == value) return static_cast<int>(i);
		}
		return -1; // Элемент не найден
	}

};

