#pragma once
#include <iostream>
#include <sstream>
#include <chrono>
#include <ctime>
using namespace std;

class Date
{
private:
	int Day;
	int Month;
	int Year;

	//Kiem tra nam nhuan
	bool IsLeapYear() const
	{
		return (Year % 400 == 0) || (Year % 4 == 0 && Year % 100 != 0);
	}

	// Ngay cuoi cung cua thang
	int LastDayOfMonth() const
	{
		if (Month > 0 && Month <= 12 && Year > 0)
		{
			if (Month == 2) {
				if (IsLeapYear())
					return 29;
				else
					return 28;
			}
			else if (Month == 4 || Month == 6 || Month == 9 || Month == 11)
			{
				return 30;
			}
			else
			{
				return 31;
			}
		}
		else
		{
			return 0;
		}
	}

public:
	//Constructor
	Date(int _day = 0, int _month = 0, int _year = 0) : Day(_day), Month(_month), Year(_year) {};

	//destructor
	~Date() {};

	//Getters
	int GetDay() const { return Day; }
	int GetMonth() const { return Month; }
	int GetYear() const { return Year; }

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

	// Xuat Date dinh dang day/month/year
	void Print() const
	{
		cout << Day << "/" << Month << "/" << Year;
	}

	string DateToString() const
	{
		return to_string(Day) + "/" + to_string(Month) + "/" + to_string(Year);
	}

	bool IsEmpty() const {
		return (Day == 0 && Month == 0 && Year == 0);
	}

	bool FromString(const string& str)
	{
		stringstream ss(str);
		char c1, c2;
		int d, m, y;

		if (!(ss >> d >> c1 >> m >> c2 >> y) || c1 != '/' || c2 != '/')
		{
			cout << "nhap cho dung ky tu va ngay thang nam (DD/MM/YYYY)";
			return false;
		}

		ss >> ws;// bỏ qua khoảng trắng
		if (!ss.eof())// dò những dòng đằng sau year nếu còn thừa chữ
		{
			cout << "khong chu cai hoac ky tu dang sau";
			return false;
		}

		Day = d;
		Month = m;
		Year = y;

		return true;
	}



	bool operator<(const Date& d)
	{
		if (Year < d.Year)
			return true;
		else
		{
			if (Year == d.Year)
			{
				if (Month < d.Month)
					return true;
				else
				{
					if (Month == d.Month) {
						if (Day < d.Day)
							return true;
					}
				}
			}
		}
		return false;
	}

	bool operator==(const Date& d)
	{
		return Year == d.Year && Month == d.Month && Day == d.Day;
	}

	bool operator>(const Date& d)
	{
		return !(*this < d) && !(*this == d);
	}

	int DemSoNgayDenSinhNhatTrongNam() const
	{
		Date now = Date::Now();
		int TongSoNgayHienTaiDenHetNam = 0;
		for (int i = now.GetMonth(); i <= 12; i++)
		{
			TongSoNgayHienTaiDenHetNam += Date::GetCountDayOfMonth(i, now.GetYear());
		}
		TongSoNgayHienTaiDenHetNam -= now.GetDay();

		int TongSoNgay = 0;
		for (int i = Month; i <= 12; i++)
		{
			TongSoNgay += Date::GetCountDayOfMonth(i, Year);
		}
		TongSoNgay -= Day;

		return TongSoNgayHienTaiDenHetNam - TongSoNgay;
	}

	static int GetCountDayOfMonth(int month, int year)
	{
		Date d(1, month, year);
		if (month > 0 && month <= 12 && year > 0)
		{
			if (month == 2) {
				if (d.IsLeapYear())
					return 29;
				else
					return 28;
			}
			else if (month == 4 || month == 6 || month == 9 || month == 11)
			{
				return 30;
			}
			else
			{
				return 31;
			}
		}
		else
		{
			return 0;
		}
	}

	static Date Now()
	{
		chrono::system_clock::time_point now = chrono::system_clock::now();
		time_t currentTime = chrono::system_clock::to_time_t(now);

		tm localTime;
		localtime_s(&localTime, &currentTime);

		int year = localTime.tm_year; //localTime.tm_year ket qua tinh tu nam 1900 tro di. vi du nhu 2026 thi ket qua cua localTime.tm_year la 126.
		int month = localTime.tm_mon; //localTime luu thang bat dau tu 0 den 11. tuong duong thang 1->12.
		int day = localTime.tm_mday;

		Date result(day, month + 1, year + 1900);

		return result;
	}
};