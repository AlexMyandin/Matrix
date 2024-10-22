#pragma once
using namespace std;
#include "Vector.h"
#include <iostream>
class Matrix
{
private:
	Vector** m_arr;
	int m_row;
	int m_col;
public:
	// конструктор с переменными
	Matrix(int row,int col):m_arr(new Vector* [row]), m_row(row), m_col(col) {
		for (size_t i = 0; i < row; i++)
		{
			m_arr[i] = new Vector(col);
		}
	};

	// конструктор копирования
	Matrix(Matrix& mat):m_arr(new Vector* [mat.m_row]), m_row(mat.m_row), m_col(mat.m_col) {
		for (size_t i = 0; i < mat.m_row; i++)
		{
			m_arr[i] = new Vector(mat.m_col);
			for (size_t k = 0; k < mat.m_col; k++) {
				m_arr[i][0].set_val(mat.m_arr[i][0].get_val(k), k); // заполняем вектор данными из другого вектора
			}
		}
	};

	// конструктор перемещения
	Matrix(Matrix&& mat) noexcept : m_arr(mat.m_arr), m_row(mat.m_row), m_col(mat.m_col) {
		mat.m_arr = nullptr;
		mat.m_row = 0;
		mat.m_col = 0;
	};

	// оператор присванивания копированием
	Matrix& operator = (Matrix& mat) {
		if (this == &mat) { return *this; };
		for (size_t i = 0; i < m_row; i++) {
			delete m_arr[i];
			m_arr[i] = nullptr;
		}
		delete[] m_arr;
		m_arr = new Vector * [mat.m_row];
		m_row = mat.m_row;
		m_col = mat.m_col;
		for (size_t i = 0; i < mat.m_row; i++)
		{
			m_arr[i] = new Vector(mat.m_col);
			for (size_t k = 0; k < mat.m_col; k++) {
				m_arr[i][0].set_val(mat.m_arr[i][0].get_val(k), k); // заполняем вектор данными из другого вектора
			}
		}
		return *this;

	};

	// оператор присванивания перемещением
	Matrix& operator = (Matrix&& mat) {
		if (this == &mat) { return *this; };
		for (size_t i = 0; i < m_row; i++) {
			delete m_arr[i];
			m_arr[i] = nullptr;
		}
		delete[] m_arr;
		m_arr = mat.m_arr;
		m_row = mat.m_row;
		m_col = mat.m_col;
		mat.m_arr = nullptr;
		return *this;

	};

	//деструктор
	~Matrix() {
		if (m_arr) {
			for (size_t i = 0; i < m_row; i++) {
				delete m_arr[i];
				m_arr[i] = nullptr;
			}
			delete[] m_arr;
			m_arr = nullptr;
			m_row = 0;
			m_col = 0;
		}
	};

	int get_row() {
		return m_row;
	}
	int get_col() {
		return m_col;
	}

	void set_val(int i, int k, int val) {
		m_arr[i][0].set_val(val, k);
	}
	int get_val(int i, int k) {
		return m_arr[i][0].get_val(k);
;	}
	void transporse() {
		Matrix newmat(m_col,m_row);
		for (size_t i = 0; i < m_row; i++)
		{
			for (size_t k = 0; k < m_col; k++) {
				newmat.m_arr[k][0].set_val(m_arr[i][0].get_val(k), i);
			}
		}
		*this = move(newmat); // Перемещаем обратно
	}

	pair<int, int> find(int value) const {
		for (size_t i = 0; i < m_row; ++i) {
			int index = m_arr[i][0].find(value);
			if (index != -1) {
				return { static_cast<int>(i), index };
			}
		}
		return { -1, -1 }; // Не найдено
	}

	// Метод slice(size_t start, size_t end)
	Matrix slice(size_t row_start, size_t row_end, size_t col_start, size_t col_end) {
		if (row_start > row_end ||col_start>col_end || row_end >= m_row || col_end>=m_col) {
			throw "Invalid indices for slice";
		}
		if (row_start < 0 || row_end < 0 || col_start<0|| col_end < 0) { throw "You cannot enter a negative number"; };
		Matrix result(row_end - row_start + 1, col_end - col_start + 1);
		for (size_t i = row_start; i <= row_end; ++i) {
			for (size_t k = col_start; k <= col_end; ++k)
			{
				result.m_arr[i - row_start][0].set_val(m_arr[i][0].get_val(k), k-col_start);
			}
		}
		return result;
	}

};

