#pragma once
#include <iostream>
#include <vector>
#include <stdio.h>
using namespace std;
typedef vector<vector<double>> Array;


class Matrix
{
private:
	Array matrix;
	int m = 0; //количество строк
	int n = 0; //количество столбцов

public:

	void set_M(int m);
	void set_N(int n);

	int get_M();
	int get_N();

	Matrix();
	Matrix(int m, int n);
	Matrix(const Matrix& other);


	void del();
	void Fill();
	void Display();


	friend std::ostream& operator << (std::ostream& out,const Matrix& other);
	friend std::istream& operator >> (std::istream& in,Matrix& other);
	Matrix& operator = (const Matrix& other);
	Matrix& operator + (double integer);
	Matrix& operator + (const Matrix& other);
	Matrix& operator -();
	Matrix& operator - (double integer);
	Matrix& operator - (const Matrix& other);
	Matrix& operator * (double integer);
	Matrix& operator * (const Matrix& other);
	Matrix& operator ++ ();
	Matrix& operator ++ (int);
	Matrix& operator -- ();
	Matrix& operator -- (int);
	Matrix& operator *= (double integer);
	Matrix& operator += (double integer);
	Matrix& operator += (const Matrix& other);
	Matrix& operator -= (double integer);
	Matrix& operator -= (const Matrix& other);
	double& operator () (const int rows,const int cols);
	bool operator == (const Matrix& other);
	bool operator != (const Matrix& other);
};

