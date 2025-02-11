#pragma once
#include <iostream>
#include <vector>
using namespace std;



class Date
{
private:
	int second = 0;
	int minute = 0;
	int hour = 0;

public:

	void set_second(int second);
	void set_minute(int minute);
	void set_hour(int hour);

	int get_second();
	int get_minute();
	int get_hour();

	Date();
	Date(int second, int minute, int hour);
	Date(const Date& other);


	~Date(void);
	void Fill();
	void Display();


	Date& operator = (const Date& other);
	Date& operator + (int seconds);
	int operator - (const Date& other);
	Date& operator -(int seconds);
	bool operator == (const Date& other);
	bool operator != (const Date& other);
	bool operator >(const Date& other);
	bool operator <(const Date& other);
	void NormPlus();
	int NormMinus(const Date& other);
};

