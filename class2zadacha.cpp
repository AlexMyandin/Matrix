
#include <iostream>
#include "Vector.h"
#include "Matrix.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "");
	// проверка вектора
	Vector v1(10);
	v1.set_val(10, 3);
	cout << v1.get_val(3)<<"\n";


	//проверка матрицы
	Matrix m1(5, 5);
	m1.set_val(3, 4, 45);
	cout << m1.get_val(3, 4)<<"\n";
	m1.transporse();
	cout << m1.get_val(3, 4) << "\n";
	cout << m1.get_val(4, 3) << "\n";

	Matrix m2(m1);
	m1.set_val(4, 3, 30);
	cout << m2.get_val(4, 3) << "\n";
	m2.set_val(4, 3, 122);
	cout << m1.get_val(4, 3) << "\n";
	Matrix m3 = move(m1);
	cout << m3.get_val(4, 3) << "\n";
	// cout << m1.get_val(4, 3) << "\n";// вызывает исключение, т. к. был использован оператор присваиваиния перемещением 
	Matrix m4(move(m3));
	cout << m4.get_val(4, 3) << "\n";
	//cout << m3.get_val(4, 3) << "\n";// вызывает исключение, т. к. был использован конструктор с перемещением 
	Matrix m5 = m4;
	cout << m4.get_val(4, 3) << "\n";
	cout << m5.get_val(4, 3) << "\n";
	cout << "row = " << m5.find(30).first << " , col = " << m5.find(30).second << "\n";
	Matrix m6 = m5.slice(2, 4, 2, 4);
	cout << "row_count = " << m6.get_row() << ", col_count = " << m6.get_col()<<"\n";
	cout << m6.get_val(2, 1) << "\n";
}