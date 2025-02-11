#include "Date.h"
#include <math.h>
#include <vector>
#include <math.h>
#include <stdexcept>

Date::Date()
{
	set_second(0);
	set_minute(0);
	set_hour(0);
}

Date::Date(int second, int minute, int hour)
{
	set_second(second);
	set_minute(minute);
	set_hour(hour);

}

Date::Date(const Date& other)
{
	set_second(other.second);
	set_minute(other.minute);
	set_hour(other.hour);
}

void Date::Fill()
{
	cout << "Input second: ";
	cin >> this->second;
	cout << "Input minute: ";
	cin >> this->minute;
	cout << "Input hour: ";
	cin >> this->hour;
	this->NormPlus();
}

void Date::Display()
{
	cout << "second:   " << this->get_second() << endl;
	cout << "minute: " << this->get_minute() << endl;
	cout << "hour:  " << this->get_hour() << endl;
}

Date::~Date(void)
{

}

Date& Date::operator = (const Date& other)
{
	this->second = other.second;
	this->minute = other.minute;
	this->hour = other.hour;
	return *this;
}

/////////////////////////////////////////////////////////////////////

void Date::NormPlus()
{
	if (this->second >= 60)
	{
		this->minute += this->second / 60;
		this->second = this->second % 60;
	}
	if (this->minute >= 60)
	{
		this->hour += this->minute / 60;
		this->minute = this->minute % 60;
	}
	if (this->hour > 24)
	{
		cout << "Больше одного дня" << endl;
		this->hour = this->hour % 24;
	}
}

/////////////////////////////////////////////////////////////////////

Date& Date::operator + (int seconds)
{
	Date* Temp = new Date();
	int secondtemp = 0, minutetemp = 0, hourtemp = 0;
	if (seconds < 0)
	{
		throw runtime_error{ "Неарвильное значение" };
	}
	else 
	{
		if (seconds >= 60)
		{
			minutetemp += seconds / 60;
			secondtemp = seconds % 60;
		}
		else if (seconds < 60)
		{
			secondtemp = seconds % 60;
		}
		if (minutetemp > 60)
		{
			hourtemp += minutetemp / 60;
			minutetemp = minutetemp % 60;
		}
		Temp->minute = this->minute + minutetemp;
		Temp->second = this->second + secondtemp;
		Temp->hour = this->hour + hourtemp;
		Temp->NormPlus();
		return *Temp;
	}
	
}

/////////////////////////////////////////////////////////////////////

int Date::operator - (const Date& other)
{
	int seconds = 0;
	int time1 = this->hour * 3600 + this->minute * 60 + this->second;
	int time2 = other.hour * 3600 + other.minute * 60 + other.second;
	seconds = abs(time1 - time2);
	return seconds;
}

/////////////////////////////////////////////////////////////////////

Date& Date::operator -(int seconds)
{
	Date* Temp = new Date();
	int secondtemp = 0, minutetemp = 0, hourtemp = 0;
	if (seconds < 0)
	{
		throw runtime_error{ "Неарвильное значение" };
	}
	else
	{
		if (this->second>seconds)
		{
			Temp->second = this->second - seconds;
		}
		else if (this->second < seconds)
		{
			if (seconds < 60)
			{
				Temp->minute = this->minute - 1;
				if (Temp->minute < 0)
				{
					Temp->minute = 59;
					Temp->hour = this->hour - 1;
				}
				Temp->second = this->second - seconds + 60;
			}
			else if (seconds >= 60)
			{
				Temp->minute = this->minute - seconds / 60;
				if (Temp->minute < 0)
				{
					Temp->hour = this->hour - abs(seconds) / 3600;
					Temp->minute = Temp->minute+60;
					if (Temp->hour < 0)
					{
						Temp->hour = Temp->hour + 24;
					}
				}
				seconds = seconds % 60;
				if (this->second > seconds)
				{
					Temp->second = this->second - seconds;
				}
				else if (this->second > seconds)
				{
					Temp->minute = this->minute - 1;
					Temp->second = this->second - seconds + 60;
				}
			}
		}
		Temp->NormPlus();
		return *Temp;
	}
}

/////////////////////////////////////////////////////////////////////

bool Date::operator >(const Date& other)
{
	if (this->hour > other.hour)
	{
		return 1;
	}
	else if (this->hour < other.hour)
	{
		return 0;
	}
	else
	{
		if (this->minute > other.minute)
		{
			return 1;
		}
		else if (this->minute < other.minute)
		{
			return 0;
		}
		else
		{
			if (this->second > other.second)
			{
				return 1;
			}
			else if (this->second < other.second)
			{
				return 0;
			}
			else
			{
				cout << "Даты равны" << endl;
			}
		}
	}
}

bool Date::operator <(const Date& other)
{
	if (this->hour < other.hour)
	{
		return 1;
	}
	else if (this->hour > other.hour)
	{
		return 0;
	}
	else
	{
		if (this->minute < other.minute)
		{
			return 1;
		}
		else if (this->minute > other.minute)
		{
			return 0;
		}
		else
		{
			if (this->second < other.second)
			{
				return 1;
			}
			else if (this->second > other.second)
			{
				return 0;
			}
			else
			{
				cout << "Даты равны" << endl;
			}
		}
	}
}

bool Date::operator==(const Date& other)
{
	if (this->get_second() == other.second && this->get_minute() == other.minute && this->get_hour() == other.hour)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool Date::operator!=(const Date& other)
{
	if (this->get_second() == other.second && this->get_minute() == other.minute && this->get_hour() == other.hour)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void Date::set_second(int second)
{
	if (second >= 0)
	{
		this->second = second;
	}
	else
	{
		throw runtime_error{ "second должно быть больше нуля" };
		return;
	}
}
int Date::get_second() { return second; }
void Date::set_minute(int minute)
{
	if (minute >= 0)
	{
		this->minute = minute;
	}
	else
	{
		throw runtime_error{ "minute должно быть больше нуля" };
		return;
	}
}
int Date::get_minute() { return minute; }
void Date::set_hour(int hour)
{
	if (hour >= 0)
	{
		this->hour = hour;
	}
	else
	{
		throw runtime_error{ "hour должно быть больше нуля" };
		return;
	}
}
int Date::get_hour() { return hour; }