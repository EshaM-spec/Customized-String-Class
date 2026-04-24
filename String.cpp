#include "String.h"
#include<iostream>
using namespace std;
String::String()
{
	data = nullptr;
	size = 0;
}
String::String(const long long int n)
{
	String temp;
	temp=n;
	data = temp.data;
	size = temp.size;
	temp.data = nullptr;
	temp.size = 0;
}
String::String(const String& newStr) :String()
{
	if (newStr.data == nullptr)
		return;
	size = newStr.size;
	data = new char[size];
	for (int i = 0; i < size; i++)
	{
		data[i] = newStr.data[i];
	}
}
String::String(String&& temp)
{
	data = temp.data;
	size = temp.size;
	temp.data = nullptr;
	temp.size = 0;
}
String::String(const char c)
{
	data = new char[2];
	data[0] = c;
	data[1] = '\0';
	size = 2;

}
int String::getLength(const char* c)const
{
	if (c == nullptr)
		return 0;
	int count = 0, i = 0;

	while (c[i] != '\0')
	{
		count++;
		i++;
	}
	return count;
}
int String::getSize()
{
	return size;
}
String::String(const char* c) :String()
{
	if (c == nullptr || getLength(c) == 0)
		return;
	int n = getLength(c) + 1;
	data = new char[n];
	int i;
	for (i = 0; i < n - 1; i++)
	{
		data[i] = c[i];
	}
	data[i] = '\0';
	size = n;
}
String& String::operator =(String&& newStr)
{
	this->~String();
	if (newStr.data == nullptr)
		return *this;
	data = newStr.data;
	size = newStr.size;
	newStr.data = nullptr;
	newStr.size = 0;
	return *this;
}
String& String::operator =(const String& newStr)
{
	if (this == &(newStr))
		return *this;
	this->~String();
	if (newStr.data == nullptr)
		return *this;
	String s(newStr);
	data = s.data;
	size = s.size;
	s.data = nullptr;
	s.size = 0;
	return *this;
}
void String::input()
{
	this->~String();
	data = new char[2];
	size = 2;
	int count = 0;
	char ch;
	while (((ch = cin.get()) != '\n'))
	{
		data[count] = ch;
		if (count + 1 == size)
			resize(size * 2);
		count++;
	}
	data[count] = '\0';

}
void String::resize(int newSize)
{
	if (newSize <= 0)
	{
		data = nullptr;
		size = 0;
		return;
	}
	char* temp = new char[newSize];
	temp[0] = '\0';
	int i;
	for (i = 0; i < size && i < newSize; i++)
	{
		temp[i] = data[i];
	}
	temp[i] = '\0';
	this->~String();
	data = temp;
	size = newSize;

}
void String::shrink()
{
	if (data == nullptr)
		return;
	int n = getLength();
	resize(n);
}
int String::getLength()const
{
	return getLength(data);
}

char& String::operator[](const int index)
{
	if (data == nullptr)
	{
		cout << "Index does not exist";
		exit(0);
	}
	if (index <getSize() && index >= 0)
		return data[index];
	cout << "Index does not exist";
	exit(0);
}
const char& String::operator[](const int index)const
{
	if (data == nullptr)
	{
		cout << "Index does not exist";
		exit(0);
	}
	if (index <getLength() && index >= 0)
		return data[index];
	cout << "Index does not exist";
	exit(0);
}
bool String::operator !()const
{
	if (data == nullptr || data[0] == '\0')
		return true;
	return false;
}
int String::find(const String& subStr, const int start)const
{
	if (start < getLength() && start>-1)
	{
		int j = 0;
		int n = getLength(subStr.data);
		int oldStrLen = getLength();
		int count = 0;
		for (int i = start; i < oldStrLen; i++)
		{
			if (data[i] == subStr.data[j])
			{
				for (j = 0; j < n; j++)
				{
					if (data[i] != subStr.data[j])
						j = n + 1;
					else
						i++;
				}
				if (j == n)
				{
					return i - n;
				}
				j = 0;
				i--;
			}

		}
	}
	return -1;

}
int String::replace(const String& old, const String& newSubStr)
{
	if (old.data == nullptr || newSubStr.data == nullptr)
		return 0;
	int j = 0;
	int newStrLen = getLength(newSubStr.data);
	int oldStrLen = getLength(old.data);
	int strLen = getLength();
	int count = 0;
	int i;
	for (i = 0; i < (strLen + newStrLen - oldStrLen); i++)
	{
		if (data[i] == old.data[j])
		{

			for (j = 0; j < oldStrLen; j++)
			{
				if (data[i + j] != old.data[j])
					j = oldStrLen + 1;

			}
			if (j == oldStrLen)
			{

				remove(i, oldStrLen);
				insert(i, newSubStr);
				count++;

				i = i + (newStrLen - 1);
			}
			j = 0;
		}

	}
	return count;

}
void String::insert(const int index, const String& str)
{
	if (str.data == nullptr || str.data[0] == '\0')
	{
		return;
	}
	if (index <= getSize() && index >= 0)
	{
		int strLen = getLength();
		int newStrLen = getLength(str.data);
		int newLen = strLen + newStrLen;
		char* temp = new char[newLen + 1];
		int i = 0, j = 0, k = 0;
		for (i = 0; i < newLen; i++)
		{
			if (i == index)
			{

				for (int j = 0; j < newStrLen; j++)
				{
					temp[i] = str.data[j];
					i++;
				}
				i--;
			}
			else
			{
				temp[i] = data[k];
				k++;
			}
		}
		temp[newLen] = '\0';
		this->~String();
		data = temp;
		size = newLen + 1;
	}
	else
	{
		cout << "Index does not exist";
	}

}
void String::remove(const int index, const int count)
{
	if (index <getLength() && index>-1)
	{
		int len = getLength();
		int i;
		for (i = 0; count + i + index < len; i++)
		{
			data[index + i] = data[count + i + index];
		}

		data[index + i] = '\0';
		size = index + i + 1;
	}
	else
	{
		cout << "Index does not exist";
	}
}
void String::makeUpper()
{
	if (operator!())
		return;
	for (int i = 0; i < getLength(); i++)
	{
		if (data[i] >= 97 && data[i] <= 123)
		{
			data[i] = data[i] - 32;
		}
	}
}
void String::makeLower()
{
	if (operator!())
		return;
	for (int i = 0; i < getLength(); i++)
	{
		if (data[i] >= 65 && data[i] <= 91)
		{
			data[i] = data[i] + 32;
		}
	}
}
void String::reverse()
{
	if (data == nullptr || data[0] == '\0')
		return;
	int n = getLength();
	char* temp = new char[n + 1];
	int k = n - 1;
	for (int i = 0; i < n; i++)
	{
		temp[i] = data[k];
		k--;
	}
	temp[n] = '\0';
	this->~String();
	data = temp;
	size = n + 1;
}
void String::trimLeft()
{
	if (operator!())
		return;
	int i = 0;
	while (data[i] == '\n' || data[i] == ' ' || data[i] == '\t')
	{
		remove(i);
	}
}
void String::trimRight()
{

	if (operator!())
		return;
	int i = getLength() - 1;
	while (data[i] == '\n' || data[i] == ' ' || data[i] == '\t')
	{
		remove(i);
		i--;
	}
}
void String::trim()
{
	trimLeft();
	trimRight();
}
int String::operator==(const String& s2)const
{
	if (data == nullptr || s2.data == nullptr)
	{
		cout << "invalid string";
		exit(0);
	}
	int str1Len = getLength();
	int str2Len = getLength(s2.data);
	for (int i = 0; i < str1Len && i < str2Len; i++)
	{
		if (data[i] > s2.data[i])
			return 0;
		if (data[i] < s2.data[i])
			return -1;
	}
	if (str1Len == str2Len)
		return 1;
	return str1Len > str2Len ? 0 : -1;
}
String String::left(const int count)
{
	String newStr;
	if (data == nullptr)
		return newStr;
	if (data[0] == '\0')
	{
		newStr.data = new char[1];
		newStr[0] = '\0';
		return newStr;
	}
	if (count >= getLength())
	{
		newStr = *this;
		data[0] = '\0';
		size = 1;
		return newStr;
	}
	char* temp = new char[count + 1];
	for (int i = 0; i < count; i++)
	{
		temp[i] = data[i];
	}
	temp[count] = '\0';
	remove(0, count);
	newStr = temp;
	return newStr;
}
String String::right(const int count)
{
	String newStr;
	if (data == nullptr)
		return newStr;
	if (data[0] == '\0')
	{
		newStr.data = new char[1];
		newStr[0] = '\0';
		return newStr;
	}
	if (count >= getLength())
	{
		newStr = *this;
		newStr.reverse();
		data[0] = '\0';
		size = 1;
		return newStr;
	}
	char* temp = new char[count + 1];
	int n = getLength();
	int c = 0;
	for (int i = n - count; i < n; i++)
	{
		temp[c] = data[i];
		c++;
	}
	temp[count] = '\0';
	remove(0, count);
	newStr = temp;
	return newStr;
}
String String::operator +(const String& s2)
{
	if (data == nullptr || s2.data == nullptr)
	{
		cout << "Program ended with exit code.";
		exit(0);
	}
	int str2Len = getLength(s2.data);
	int strLen = getLength();
	char* temp = new char[strLen + str2Len + 1];
	String newStrng{ data };
	newStrng.insert(strLen, s2.data);
	newStrng.data[strLen + str2Len] = '\0';
	newStrng.size = strLen + str2Len + 1;
	return newStrng;
}
void String::operator +=(const String& s2)
{
	if (s2.data == nullptr || s2.data[0] == '\0')
		return;
	int strLen = getLength();
	int str2Len = getLength(s2.data);
	insert(strLen, s2);

}
int String::getNumberLength(long long int n)
{
	if (n == 0)
		return 1;
	int count = 0;
	while ((n % 10) != 0)
	{
		n = n / 10;
		count++;
	}

	return count;
}
String& String::operator=(const long long int num)
{
	int count = getNumberLength(num);
	long long int n = num;
	if (n < 0)
		n = -n;
	int c;
	char* temp = new char[count + 1];
	for (c = count - 1; c >= 0; c--)
	{
		temp[c] = (n % 10) + 48;
		n = n / 10;

	}
	temp[count] = '\0';
	this->~String();
	data = temp;
	size = count + 1;
	if (num < 0)
		insert(0, "-");
	return *this;
}

String& String::operator=(const double  num)
{
	this->~String();
	long long int n = num;
	double k = num;
	if (num < 0)
	{
		n = -n;
		k = -k;
	}
	float r = k - n;
	*this = n;
	int count = getLength();
	insert(count, String("."));
	count++;
	float c = 10;
	int t = 0;
	float y = 8;
	while (y != 0)
	{
		r = r * c;
		t = r;
		y = r - (float)t;
	}
	n = r;
	String temp2;
	temp2 = n;
	insert(count, temp2);
	if (num < 0)
		insert(0, "-");
	return *this;
}
String::operator long long int()const
{
	int i = 0;
	long long int num = 0;
	int c = 10;
	for (i = 0; i < getLength() && data[i] != '.'; i++)
	{
		if (data[i] >= '0' && data[i] <= '9')
		{
			num = (num * c) + (data[i] - 48);

		}
	}
	if (data[0] == '-')
		num = num * -1;
	return num;
}
String::operator double()const
{
	long long int integralPart = (long long int) * this;
	if (integralPart < 0)
		integralPart = integralPart * -1;
	double decimalPart = integralPart;
	double c = 10;

	for (int i = 1; i < getLength(); i++)
	{
		if (data[i - 1] == '.')
		{

			for (; i < getLength(); i++)
			{
				decimalPart = decimalPart + (data[i] - 48) / c;
				c = c * 10;
			}
		}
	}
	if (data[0] == '-')
		decimalPart = decimalPart * -1;
	return decimalPart;
}
String::operator bool()const
{
	if (data == nullptr || data[0] == '\0')
		return false;
	return true;
}

String String::operator()(const String& delim)
{
	String temp;
	if (delim.data == nullptr || data == nullptr)
	{
		return temp;
	}
	temp.resize(getLength() + 1);
	int k = 0;
	int i;
	for (i = 0; i < getLength(); i++)
	{

		for (int j = 0; j < delim.getLength(); j++)
		{
			if ((data[i] == delim[j]))
			{

				temp[k] = '\0';
				remove(0, i + 1);
				return temp;
			}
		}
		temp[k] = data[i];
		k++;
	}
	temp[k] = '\0';
	this->~String();
	return temp;
}String::~String()
{
	delete[]data;
	data = nullptr;
	size = 0;
}
void String::display()const
{
	if (data == nullptr || data[0] == '\0')
		return;
	int n = getLength();
	for (int i = 0; i < n; i++)
	{
		cout << data[i];
	}
}
ostream& operator<<(ostream&, const String& s)
{
	s.display();
	return cout;
}
istream& operator>>(istream& i, String& s)
{
	s.~String();
	s.resize(2);
	int count = 0;
	char ch;
	while (((ch = i.get()) != '\n'))
	{
		s[count] = ch;
		if (count + 1 == s.getSize())
			s.resize(s.getSize() * 2);
		count++;
	}
	s[count] = '\0';
	return i;
}
