#ifndef STRING_H
#define STRING_H
#include<iostream>
using namespace std;
class String
{
	char* data;
	int size;
	int getLength(const char* c)const;
	int getNumberLength(long long int n);
public:
	String(const String&);
	String(const long long int n);
	String();
	~String();
	String(const char c);
	String(const char* c);
	String(String&&);
	void input();
	String& operator =(const String& newStr);
	String& operator =(String&& newStr);
	int getSize();
	void resize(int newSize);
	void shrink();
	char& operator[](const int index);
	int getLength()const;
	const char& operator[](const int index)const;
	bool operator !()const;
	int find(const String& subStr, const int start = 0)const;
	int replace(const String& old, const String& newSubStr);
	void insert(const int index, const String& str);
	void remove(const int index, const int count = 1);
	void makeUpper();
	void makeLower();
	void reverse();
	void trimLeft();
	void trimRight();
	void trim();
	void display()const;
	int operator==(const String& s2)const;
	String left(const int count);
	String right(const int count);
	String operator+ (const String& s2);
	void operator +=(const String& s2);
	String& operator=(const long long int num);
	String& operator=(const double  num);
	explicit operator long long int()const;
	explicit operator double()const;
	explicit operator bool()const;
	String operator()(const String& delim);

};
istream& operator>>(istream&, String&);
ostream& operator<<(ostream&, const String&);

#endif