#include <iostream>
#include "Matrix.h"
#include <stdexcept>
#include <Windows.h>
#include <stdio.h>
using namespace std;


int main()
{
	setlocale(LC_ALL, "ru");
	int m = 0, n = 0;
	try
	{
		cout << "Для матрицы M: " << endl;

		cout << "Введите количество строк: ";
		cin >> m;
		cout << "Введите количество столбцов: ";
		cin >> n;

		Matrix M(m, n);
		M.Fill();
		M.Display();


		cout << "Для матрицы N: " << endl;

		cout << "Введите количество строк: ";
		cin >> m;
		cout << "Введите количество столбцов: ";
		cin >> n;

		Matrix N(m, n);
		N.Fill();
		N.Display();



		//Разность матриц

		cout << "Разность матриц: " << endl;
		Matrix L = Matrix(m, n);
		L = (M - N);
		L.Display();

		cout << "Разность матрицы и числа: " << endl;
		L = M - 1;
		L.Display();

		cout << "Разность матриц(с накоплением): " << endl;
		L -= M;
		L.Display();

		cout << "Разность матрицы и числа(с накоплением): " << endl;
		L -= 1;
		L.Display();

		L.del();

		cout << "\n\n" << endl;



		//Сумма матриц

		cout << "Сложение матриц:" << endl;
		Matrix S = Matrix(m, n);
		S = M + N;
		M.Display();

		cout << "Сложение матрицы и числа:" << endl;
		S = M + 1;

		cout << "Сложение матриц(с накоплением):" << endl;
		S += M;

		cout << "Сложение матрицы и числа(с накоплением):" << endl;
		S += 1;
		S.del();

		cout << "\n\n" << endl;
		


		//Умножение матриц

		cout << "Умножение матриц:" << endl;
		Matrix U = Matrix(m, n);
		U = (M * N);
		U.Display();

		cout << "Умножение матрицы на число:" << endl;
		U = M * 2;
		U.Display();

		cout << "Умножение матрицы на число(с накоплением):" << endl;
		U *= 2;
		U.Display();

		cout << "Умножение матрицы на -1:" << endl;
		-U;
		U.Display();

		cout << "\n\n" << endl;



		//Унарные операторы

		cout << "Вывод префиксного инкремента:" << endl;
		cout << ++M << endl;
		cout << "Вывод постфиксного инкремента:" << endl;
		cout << M++ << endl;
		cout << "Вывод префиксного декремента:" << endl;
		cout << --M << endl;
		cout << "Вывод постфиксного декремента:" << endl;
		cout << M-- << endl;

		

		cout << "Вызов элемента матрицы по индексу:" << endl;

		int k, l;
		cout << "Введите номер строки: ";
		cin >> k;
		cout << "Введите номер столбца: ";
		cin >> l;
		cout << U(k,l) << endl;
		U.del();

		cout << "\n\n" << endl;



		cout << "Сравнение матриц:" << endl;
		if (M != N) { cout << "Матрицы не равны" << endl; }
		else { cout << "Матрицы равны" << endl; }



		N.del();

		M.del();


	}
	catch (exception& exc)
	{
		cerr << exc.what() << endl;
		exit(0);
	}
	return 0;
}
