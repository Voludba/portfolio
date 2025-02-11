#include "Matrix.h"
#include <math.h>
#include <stdexcept>
#include <vector>

//конструктор по умолчанию
Matrix::Matrix()
{
	set_M(0);
	set_N(0);
	Array matrix;
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			matrix[i][j]=0;
		}
	}
} 

//конструктор
Matrix::Matrix(int m, int n)
{
	set_M(m);
	set_N(n);
	Array matrix;
}

//конструктор копирования
Matrix::Matrix(const Matrix& other)
{
	set_M(other.m);
	set_N(other.n);
	Array matrix;
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			this->matrix[i][j] = other.matrix[i][j];
		}
	}
}

//функция заполнения матрицы
void Matrix::Fill()
{
	double temp = 0;	
	vector<double> buffer;
	for (int i = 0; i < m; ++i)
	{
		
		for (int j = 0; j < n; ++j)
		{
			cout << "matrix[" << i+1 << "][" << j+1 << "] = ";
			cin >> temp;
			buffer.push_back(temp);
		}
		matrix.push_back(buffer);
		buffer.clear();
	}
}

//функция вывода матрицы на экран
void Matrix::Display()
{
	if (!this->matrix.empty())
	{
		for (int i = 0; i < m; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				cout << this->matrix[i][j] << " ";
			}
			cout << endl;
		}
	}
	else
	{
		throw runtime_error{ "Матрица пустая" };
	}
}

//деструктор
void Matrix::del()
{
	Array::iterator ib = matrix.begin(),ie = matrix.end();
	this->matrix.erase(ib, ie);
}

//оператор вывода матрицы
std::ostream& operator<< (std::ostream& out,const Matrix& other) 
{
	if (other.matrix.empty()) 
	{
		out << "Matrix is empty";
	}
	for (int i = 0; i < other.m; ++i) 
	{
		for (int j = 0; j <other.n; ++j) 
		{
			out << other.matrix[i][j] << " ";
		}
		out << endl;
	}
	return out;
}

//оператор ввода матрицы
std::istream& operator>> (std::istream& in,Matrix& other) 
{
	double temp = 0;
	vector<double> buffer;
	for (int i = 0; i < other.m; ++i) 
	{
		for (int j = 0; j < other.n; ++j) 
		{
			cout << "matrix[" << i + 1 << "][" << j + 1 << "] = ";
			cin >> temp;
			buffer.push_back(temp);
		}
		other.matrix.push_back(buffer);
		buffer.clear();
	}
	return in;
}

//Оператор присваивания
Matrix& Matrix::operator = (const Matrix& other)
{
	this->del();
	Array matrix;
	double temp = 0;
	vector<double> buffer;
	if (!other.matrix.empty())
	{
		for (int i = 0; i < other.m; ++i)
		{
			for (int j = 0; j < other.n; ++j)
			{
				buffer.push_back(other.matrix[i][j]);
			}
			this->matrix.push_back(buffer);
			buffer.clear();
			cout << endl;
		}
	}
	else
	{
		throw runtime_error{ "Матрица пустая" };
	}
	

	return *this;
}

/////////////////////////////////////////////////////////////////////Сложение матриц

//Оператор сложения матрицы с числом
Matrix& Matrix::operator + (double integer)
{
	Matrix* L = new Matrix(this->get_M(), this->get_N());
	double temp = 0;
	vector<double> buffer;
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			temp = this->matrix[i][j] + integer;
			buffer.push_back(temp);
		}
		L->matrix.push_back(buffer);
		buffer.clear();
	}
	return *L;
	L->del();
}

//Оператор сложения матрицы с матрицей
Matrix& Matrix::operator + (const Matrix& other)
{
	Matrix* L = new Matrix(this->get_M(), this->get_N());
	if (this->get_M() == other.m && this->get_N() == other.n)
	{
		double temp = 0;
		vector<double> buffer;
		for (int i = 0; i < m; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				temp = this->matrix[i][j] + other.matrix[i][j];
				buffer.push_back(temp);
			}
			L->matrix.push_back(buffer);
			buffer.clear();
		}
	}
	else
	{
		throw runtime_error{ "Матрицы не равны" };
	}
	return *L;
	L->del();
}

//Оператор сложения матрицы с числом(с накоплением)
Matrix& Matrix::operator += (double integer)
{
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			this->matrix[i][j] += integer;
		}
	}
	return *this;
}

//Оператор сложения матрицы с матрицей(с накоплением)
Matrix& Matrix::operator += (const Matrix& other)
{
	if (this->get_M() == other.m && this->get_N() == other.n)
	{
		for (int i = 0; i < m; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				this->matrix[i][j] += other.matrix[i][j];
			}
		}
	}
	else
	{
		throw runtime_error{ "Матрицы не равны" };
	}
	return *this;
}

/////////////////////////////////////////////////////////////////////Унарные операторы

//префиксный инкремент 
Matrix& Matrix::operator ++ () 
{
	for (int i = 0; i < m; ++i) 
	{
		for (int j = 0; j < n; ++j) 
		{
			matrix[i][j] = matrix[i][j] + 1;
		}
	}
	return *this;
}

//постфиксный инкремент 
Matrix& Matrix::operator ++ (int) 
{
	Matrix* L = new Matrix(this->m, this->n);
	double temp = 0;
	vector<double> buffer;
	for (int i = 0; i < m; ++i) 
	{
		for (int j = 0; j < n; ++j) 
		{
			temp = this->matrix[i][j];
			buffer.push_back(temp);
			this->matrix[i][j] = this->matrix[i][j] + 1;
		}
		L->matrix.push_back(buffer);
		buffer.clear();
	}
	return *L;
	L->del();
}

//префиксный декремент 
Matrix& Matrix::operator -- () 
{
	for (int i = 0; i < m; ++i) 
	{
		for (int j = 0; j < n; ++j) 
		{
			matrix[i][j] = matrix[i][j] - 1;
		}
	}
	return *this;
}

//постфиксный декремент 
Matrix& Matrix::operator -- (int) 
{
	Matrix* L = new Matrix(this->m, this->n);
	double temp = 0;
	vector<double> buffer;
	for (int i = 0; i < m; ++i) 
	{
		for (int j = 0; j < n; ++j) 
		{
			temp = this->matrix[i][j];
			buffer.push_back(temp);
			this->matrix[i][j] = this->matrix[i][j] - 1;
		}
		L->matrix.push_back(buffer);
		buffer.clear();
	}
	return *L;
	L->del();
}

/////////////////////////////////////////////////////////////////////Разность матриц

//Разность матрицы и числа
Matrix& Matrix::operator - (double integer)
{
	Matrix* L = new Matrix(this->get_M(), this->get_N());
	double temp = 0;
	vector<double> buffer;
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			temp = this->matrix[i][j] - integer;
			buffer.push_back(temp);
		}
		L->matrix.push_back(buffer);
		buffer.clear();
	}
	return *L;
	L->del();
}

//Разность матрицы и матрицы
Matrix& Matrix::operator - (const Matrix& other)
{
	Matrix* L = new Matrix(this->get_M(), this->get_N());
	if (this->get_M() == other.m && this->get_N() == other.n)
	{
		double temp = 0;
		vector<double> buffer;
		for (int i = 0; i < m; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				temp = this->matrix[i][j] - other.matrix[i][j];
				buffer.push_back(temp);
			}
			L->matrix.push_back(buffer);
			buffer.clear();
		}
	}
	return *L;
	L->del();
}

//Разность матрицы и числа(с накоплением)
Matrix& Matrix::operator -= (double integer)
{
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			this->matrix[i][j] -= integer;
		}
	}
	return *this;
}

//Разность матрицы и матрицы(с накоплением)
Matrix& Matrix::operator -= (const Matrix& other)
{
	if (this->get_M() == other.m && this->get_N() == other.n)
	{
		for (int i = 0; i < m; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				this->matrix[i][j] -= other.matrix[i][j];
			}
		}
	}
	else
	{
		throw runtime_error{ "Матрицы не равны" };
	}
	return *this;
}

/////////////////////////////////////////////////////////////////////Умножение матриц

//Умножение всех элементов матрицы на -1
Matrix& Matrix::operator-()
{
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			this->matrix[i][j] *= (-1);
		}
	}
	return *this;
}

//Умножение матрицы на число(с накоплением)
Matrix& Matrix::operator *= (double integer)
{
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			this->matrix[i][j] *= integer;
		}
	}
	return *this;
}

//Умножение матрицы на число
Matrix& Matrix::operator * (double integer)
{
	Matrix* L = new Matrix(this->get_M(), this->get_N());
	double temp = 0;
	vector<double> buffer;
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			temp = this->matrix[i][j]* integer;
			buffer.push_back(temp);
		}
		L->matrix.push_back(buffer);
		buffer.clear();
	}
	return *L;
	L->del();
}

//Умножение матрицы на матрицу
Matrix& Matrix::operator * (const Matrix& other)
{
	Matrix* L = new Matrix(this->get_M(), this->get_N());
	if (this->get_M() == other.n)
	{
		int temp = 0;
		vector<double> buffer;
		for (int i = 0; i < m; ++i)
		{
			for (int j = 0; j < m; ++j)
			{
				temp = 0;
				for (int k = 0; k < m; ++k)
				{
					temp+= this->matrix[i][k] * other.matrix[k][j];
				}
				buffer.push_back(temp);
			}
			L->matrix.push_back(buffer);
			buffer.clear();
		}
	}
	return *L;
	L->del();
}

/////////////////////////////////////////////////////////////////////

//Оператор взятия элемента матрицы
double& Matrix::operator () (int m,int n)
{
	if (m+1 > this->get_M() || n+1 > this->get_N() || m < 0 && n <0)
	{
		throw runtime_error{ "Неправильные значения" };
		exit;
	}
	else return matrix[m][n];
}

//Оператор сравнения
bool Matrix::operator==(const Matrix& other)
{
	if (this->get_M() == other.m && this->get_N() == other.n)
	{
		for (int i = 0; i < m; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				if (this->matrix[i][j] == other.matrix[i][j])
				{
					continue;
				}	
				else
				{
					return 0;
				}

			}
		}
		return 1;
	}
	else
	{
		throw runtime_error{ "Maтрицы нельзя сравнить" };
		return 0;
	}
}

//Оператор сравнения
bool Matrix::operator!=(const Matrix& other)
{
	if (this->get_M() == other.m && this->get_N() == other.n)
	{
		for (int i = 0; i < m; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				if (this->matrix[i][j] == other.matrix[i][j])
				{
					continue;
				}
				else
				{
					return 1;
				}

			}
		}
		return 0;
	}
	else
	{
		throw runtime_error{ "Maтрицы нельзя сравнить" };
		return 1;
	}
}

//Сеттер М
void Matrix::set_M(int m)
{
	if(m>=0)
	{
		this->m = m;
	}
	else
	{
		throw runtime_error{ "M должно быть больше нуля" };
		return;
	}
}
//Геттер М
int Matrix::get_M() { return m; }
//Сеттер N
void Matrix::set_N(int n) 
{ 
	if (n >= 0)
	{
		this->n = n;
	}
	else
	{
		throw runtime_error{ "N должно быть больше нуля" };
		return;
	}
}
//Геттер N
int Matrix::get_N() { return n; }
