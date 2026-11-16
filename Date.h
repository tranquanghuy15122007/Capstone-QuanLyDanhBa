#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
using namespace std;

class Date
{
private:
	int Day;
	int Month;
	int Year;

	// ngay cuoi cung cua thang nay (dung lai ham static ben duoi)
	int LastDayOfMonth() const
	{
		return GetCountDayOfMonth(Month, Year);
	}

	// dem xem ngay nay la ngay thu may trong nam (1/1 la ngay 1)
	int NgayThuMayTrongNam(int day, int month, int year) const
	{
		int tong = day;
		for (int i = 1; i < month; i++)
		{
			tong += GetCountDayOfMonth(i, year);
		}
		return tong;
	}

public:
	// Constructor
	Date(int _day = 0, int _month = 0, int _year = 0) : Day(_day), Month(_month), Year(_year) {}

	// Getters
	int GetDay() const { return Day; }
	int GetMonth() const { return Month; }
	int GetYear() const { return Year; }

	// Setters
	void SetDay(int day) { Day = day; }
	void SetMonth(int month) { Month = month; }
	void SetYear(int year) { Year = year; }

	// Kiem tra nam nhuan
	static bool IsLeapYear(int year)
	{
		return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
	}

	// So ngay cua 1 thang (tra ve 0 neu thang hoac nam sai)
	static int GetCountDayOfMonth(int month, int year)
	{
		if (month < 1 || month > 12 || year <= 0)
		{
			return 0;
		}
		if (month == 2)
		{
			if (IsLeapYear(year))
				return 29;
			return 28;
		}
		if (month == 4 || month == 6 || month == 9 || month == 11)
		{
			return 30;
		}
		return 31;
	}

	// Kiem tra Date hop le
	bool IsValidDate() const
	{
		if (Month < 1 || Month > 12) {
			cout << "Month phai >= 1 va <= 12" << endl;
			return false;
		}
		if (Day < 1 || Day > LastDayOfMonth()) {
			cout << "so ngay khong hop le dua vao thang" << endl;
			return false;
		}
		if (Year < 1000 || Year > 9999) {
			cout << "Year phai nhap 4 so" << endl;
			return false;
		}
		return true;
	}

	bool IsValidDateNoWarning() const
	{
		if (Month < 1 || Month > 12) {
			return false;
		}
		if (Day < 1 || Day > LastDayOfMonth()) {
			return false;
		}
		if (Year < 1000 || Year > 9999) {
			return false;
		}
		return true;
	}

	// Xuat Date dinh dang day/month/year
	void Print() const
	{
		cout << DateToString();
	}

	string DateToString() const
	{
		return to_string(Day) + "/" + to_string(Month) + "/" + to_string(Year);
	}

	bool IsEmpty() const
	{
		return (Day == 0 && Month == 0 && Year == 0);
	}

	bool FromString(const string& str)
	{
		stringstream ss(str);
		char c1, c2;
		int d, m, y;
		if (!(ss >> d >> c1 >> m >> c2 >> y) || c1 != '/' || c2 != '/')
		{
			return false;
		}

		ss >> ws; // bo qua khoang trang
		if (!ss.eof()) // con chu thua phia sau year
		{
			cout << "khong chu cai hoac ky tu dang sau" << endl;
			return false;
		}

		Day = d;
		Month = m;
		Year = y;
		return true;
	}

	bool FromStringNoWarning(const string& str)
	{
		stringstream ss(str);
		char c1, c2;
		int d, m, y;
		if (!(ss >> d >> c1 >> m >> c2 >> y) || c1 != '/' || c2 != '/')
		{
			return false;
		}

		ss >> ws; // bo qua khoang trang
		if (!ss.eof()) // con chu thua phia sau year
		{
			return false;
		}

		Day = d;
		Month = m;
		Year = y;
		return true;
	}

	bool operator<(const Date& d) const
	{
		if (Year != d.Year)
			return Year < d.Year;
		if (Month != d.Month)
			return Month < d.Month;
		return Day < d.Day;
	}

	bool operator==(const Date& d) const
	{
		return Year == d.Year && Month == d.Month && Day == d.Day;
	}

	bool operator>(const Date& d) const
	{
		return d < *this;
	}

	// So ngay tu hom nay den sinh nhat nam nay (am nghia la da qua sinh nhat)
	int DemSoNgayDenSinhNhatTrongNam() const
	{
		Date now = Date::Now();
		int ngayHomNay = NgayThuMayTrongNam(now.Day, now.Month, now.Year);
		int ngaySinhNhat = NgayThuMayTrongNam(Day, Month, now.Year); // dung nam hien tai
		return ngaySinhNhat - ngayHomNay;
	}

	// Lay ngay hien tai
	static Date Now()
	{
		time_t t = time(0);
		tm localTime;
		localtime_s(&localTime, &t); // tm_year tinh tu 1900, tm_mon tu 0 den 11
		return Date(localTime.tm_mday, localTime.tm_mon + 1, localTime.tm_year + 1900);
	}
};