#include <iostream>
using namespace std;

class Time
{
private:
	int seconds;
	int minutes;
	int hours;

	Time(int s);
	Time(int s, int m);

public:
	Time();
	Time(const Time& t);
	Time(int s, int m, int h);

	void Print()const;
	void Init();

	Time& operator++(); // ++a
	Time& operator--(); // --a
	Time operator++(int); // a++
	Time operator--(int); // a--

	Time operator+(int n); // a + 10
	Time operator-(const Time& t); // a - b
	Time operator-(int n); // a - 10

	Time& operator+=(int n); // a += 10
	Time& operator-=(int n); // a -= 10
	Time& operator-=(const Time& t); // a -= b

	bool operator > (const Time& t); // a > b
	bool operator < (const Time& t); // a < b
	bool operator >= (const Time& t); // a >= b
	bool operator <= (const Time& t); // a <= b
	bool operator == (const Time& t); // a == b
	bool operator != (const Time& t); // a != b

	int GetSeconds()const;
	int GetMinutes()const;
	int GetHours()const;

	void SetSeconds(int s);
	void SetMinutes(int m);
	void SetHours(int h);

	bool checkTime();

	int operator[](int index);

	friend ostream& operator << (ostream& o, const Time& t);
	friend istream& operator >> (istream& i, Time& t);
};

Time::Time(int s)
{
	seconds = s;
}

Time::Time(int s, int m) :Time(s)
{
	minutes = m;
}


Time::Time()
{
	seconds = 0;
	minutes = 0;
	hours = 0;
}

Time::Time(const Time& t)
{
	seconds = t.seconds;
	minutes = t.minutes;
	hours = t.hours;
}

Time::Time(int h, int m, int s) :Time(s, m)
{
	hours = h;
}

void Time::Print()const
{
	if (hours < 10)
		cout << '0';
	cout << hours << ":";

	if (minutes < 10)
		cout << '0';
	cout << minutes << ":";

	if (seconds < 10)
		cout << '0';
	cout << seconds << "\n";
}

void Time::Init()
{
	cout << "Enter a time (hours mins secs):\n\n";

	cout << ">>> ";
	cin >> hours >> minutes >> seconds;
}

Time& Time::operator ++()
{
	seconds++;
	if (seconds > 59)
	{
		minutes++;
		seconds = 0;
		if (minutes > 59)
		{
			hours++;
			minutes = 0;
			if (hours > 23)
			{
				hours = 0;
			}
		}
	}
	return *this;
}

Time& Time::operator --() // --a
{
	seconds--;
	if (seconds < 0)
	{
		seconds = 59;
		minutes--;
		if (minutes < 0)
		{
			minutes = 59;
			hours--;
			if (hours < 0)
			{
				hours = 23;
			}
		}
	}
	return *this;
}

Time Time::operator ++(int) // a++
{
	Time tmp(hours, minutes, seconds);

	seconds++;
	if (seconds > 59)
	{
		minutes++;
		seconds = 0;
		if (minutes > 59)
		{
			hours++;
			minutes = 0;
			if (hours > 23)
			{
				hours = 0;
			}
		}
	}

	return tmp;
}

Time Time::operator --(int) // a--
{
	Time tmp(hours, minutes, seconds);

	seconds--;
	if (seconds < 0)
	{
		seconds = 59;
		minutes--;
		if (minutes < 0)
		{
			minutes = 59;
			hours--;
			if (hours < 0)
			{
				hours = 23;
			}
		}
	}

	return tmp;
}

Time Time::operator +(int n)
{
	Time tmp(hours, minutes, seconds);
	tmp.seconds += n;

	while (tmp.seconds > 59)
	{
		tmp.seconds -= 60;
		tmp.minutes++;
		while (tmp.minutes > 59)
		{
			tmp.minutes -= 60;
			tmp.hours++;
			if (tmp.hours > 23)
			{
				tmp.hours = 0;
			}
		}
	}
	return tmp;
}

Time Time::operator -(const Time& t)
{
	Time tmp;

	int allTimeL = hours * 3600 + minutes * 60 + seconds;
	int allTimeR = t.hours * 3600 + t.minutes * 60 + t.seconds;

	if (allTimeL < allTimeR)
		throw "Invalid time :(";

	int allTime = allTimeL - allTimeR;

	tmp.hours = allTime / 3600;
	tmp.minutes = (allTime % 3600) / 60;
	tmp.seconds = allTime % 60;

	return tmp;
}

Time Time::operator -(int n)
{
	Time tmp(hours, minutes, seconds);
	
	int allTime = hours * 3600 + minutes * 60 + seconds;

	if (allTime < n)
		throw "Invalid time :(";

	allTime -= n;

	tmp.hours = allTime / 3600;
	tmp.minutes = (allTime % 3600) / 60;
	tmp.seconds = allTime % 60;

	return tmp;
}

Time& Time::operator+=(int n)
{
	seconds += n;
	while (seconds > 59)
	{
		seconds -= 60;
		minutes++;
		while (minutes > 59)
		{
			minutes -= 60;
			hours++;
			if (hours > 23)
			{
				hours = 0;
			}
		}
	}
	return *this;
}

Time& Time::operator-=(int n)
{
	int allTime = hours * 3600 + minutes * 60 + seconds;

	if (allTime < n)
		throw "Invalid time :(";

	allTime -= n;

	hours = allTime / 3600;
	minutes = (allTime % 3600) / 60;
	seconds = allTime % 60;

	return *this;
}

Time& Time::operator-=(const Time& t)
{
	int allTimeL = hours * 3600 + minutes * 60 + seconds;
	int allTimeR = t.hours * 3600 + t.minutes * 60 + t.seconds;

	if (allTimeL < allTimeR)
		throw "Invalid time :(";

	int allTime = allTimeL - allTimeR;

	hours = allTime / 3600;
	minutes = (allTime % 3600) / 60;
	seconds = allTime % 60;

	return *this;
}

bool Time::operator > (const Time& t)
{
	if (hours > t.hours)
	{
		return true;
	}
	else if (hours == t.hours)
	{
		if (minutes > t.minutes)
		{
			return true;
		}
		else if (minutes == t.minutes)
		{
			if (seconds > t.seconds)
			{
				return true;
			}
		}
	}
	return false;
}

bool Time::operator < (const Time& t)
{
	if (hours < t.hours)
	{
		return true;
	}
	else if (hours == t.hours)
	{
		if (minutes < t.minutes)
		{
			return true;
		}
		else if (minutes == t.minutes)
		{
			if (seconds < t.seconds)
			{
				return true;
			}
		}
	}
	return false;
}

bool Time::operator >= (const Time& t)
{
	if (hours > t.hours)
	{
		return true;
	}
	else if (hours == t.hours)
	{
		if (minutes > t.minutes)
		{
			return true;
		}
		else if (minutes == t.minutes)
		{
			if (seconds >= t.seconds)
			{
				return true;
			}
		}
	}
	return false;
}

bool Time::operator <= (const Time& t)
{
	if (hours < t.hours)
	{
		return true;
	}
	else if (hours == t.hours)
	{
		if (minutes < t.minutes)
		{
			return true;
		}
		else if (minutes == t.minutes)
		{
			if (seconds <= t.seconds)
			{
				return true;
			}
		}
	}
	return false;
}

bool Time::operator == (const Time& t)
{
	if (hours == t.hours 
		&& minutes == t.minutes 
		&& seconds == t.seconds) 
		return true;
	return false;
}

bool Time::operator != (const Time& t)
{
	if (hours == t.hours
		&& minutes == t.minutes
		&& seconds == t.seconds)
		return false;
	return true;
}

ostream& operator << (ostream& o, const Time& t)
{
	if (t.GetHours() < 10)
		o << '0';
	o << t.GetHours() << ":";
	
	if (t.GetMinutes() < 10)
		o << '0';
	o << t.GetMinutes() << ":";

	if (t.GetSeconds() < 10)
		o << '0';
	o << t.GetSeconds();

	return o;
}

istream& operator >> (istream& i, Time& t)
{
	cout << "Enter a time (hours mins secs): ";
	i >> t.hours >> t.minutes >> t.seconds;
	return i;
}

int Time::GetSeconds()const
{
	return seconds;
}

int Time::GetMinutes()const
{
	return minutes;
}

int Time::GetHours()const
{
	return hours;
}

void Time::SetSeconds(int s)
{
	seconds = s;
}

void Time::SetMinutes(int m)
{
	minutes = m;
}

void Time::SetHours(int h)
{
	hours = h;
}

int Time::operator[](int index)
{
	switch (index)
	{
	case 0:
		return hours;
	case 1:
		return minutes;
	case 2:
		return seconds;
	default:
		throw "Incorrect index :(\n";
	}
}

int main()
{
	Time obj1(12, 29, 21);
	Time obj2(5, 23, 38);

	cout << "Time:\t";
	cout << obj1 << "\n";

	cout << "++Time:\t";
	++obj1;
	cout << obj1 << "\n";

	cout << "Time++:\t";
	obj1++;
	cout << obj1 << "\n";

	cout << "--Time:\t";
	--obj1;
	cout << obj1 << "\n";

	cout << "Time--:\t";
	obj1--;
	cout << obj1 << "\n\n";

	cout << obj1 << " + 15:\t\t";
	obj1 = obj1 + 15;
	cout << obj1 << "\n";

	cout << obj1 << " - " << obj2 << ":\t" << obj1 - obj2 << "\n";

	cout << obj1 << " - 10:\t\t" << obj1 - 10 << "\n";

	cout << obj1 << " += 26:\t\t";
	obj1 += 26;
	cout << obj1 << "\n";

	cout << obj1 << " -= 6:\t\t";
	obj1 -= 6;
	cout << obj1 << "\n\n";

	cout << boolalpha << "03:12:20 > 04:05:43 : "
		<< (Time(3, 12, 20) > Time(4, 5, 43)) << "\n";

	cout << boolalpha << "05:07:21 < 04:05:43 : "
		<< (Time(5, 7, 21) < Time(4, 5, 43)) << "\n";

	cout << boolalpha << "03:12:20 >= 04:05:43 : "
		<< (Time(3, 12, 20) >= Time(4, 5, 43)) << "\n";

	cout << boolalpha << "05:07:21 <= 05:07:21 : "
		<< (Time(5, 7, 21) <= Time(5, 7, 21)) << "\n";

	cout << boolalpha << "03:12:20 == 04:05:43 : "
		<< (Time(3, 12, 20) == Time(4, 5, 43)) << "\n";

	cout << boolalpha << "03:12:20 != 04:05:43 : "
		<< (Time(3, 12, 20) != Time(4, 5, 43)) << "\n\n";

	cout << obj1 << "\nTime[0]: " << obj1[0]
		<< "\nTime[1]: " << obj1[1]
		<< "\nTime[2]: " << obj1[2] << "\n";
}
