
// Informatica - Boletin 4 (11/XI/2013) - b4_1_fechas.cpp
// Marcos Vives Del Sol
// Licencia: WTFPL

#include <iostream>
using namespace std;

bool is_leap_year(int year)
{
	return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

int calculate_month_days(int year, int month)
{
	int days = -1;
	switch (month)
	{
		case 2:
			if (is_leap_year(year))
				days = 29;
			else
				days = 28;
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			days = 30;
			break;
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			days = 31;
	}

	return days;
}

bool is_date_valid(int year, int month, int day)
{
	bool valid = false;
	int monthDays;

	if (year >= 1582)
	{
		monthDays = calculate_month_days(year, month);
		if (monthDays > 0 && day >= 1 && day <= monthDays)
			valid = true;
	}

	return valid;
}

int main()
{
	int year, month, day;

	cout << "Este programa determina si una fecha introducida por teclado es o no valida." << endl << endl;

	cout << "Dime dia: ";
	cin >> day;
	
	cout << "Dime mes: ";
	cin >> month;
	
	cout << "Dime anyo: ";
	cin >> year;

	cout << "La fecha introducida (" << day << "/" << month << "/" << year << ") ";
	if (!is_date_valid(year, month, day))
		cout << "NO ";
	cout << "es valida en el calendario gregoriano" << endl;

	return 0;
}
