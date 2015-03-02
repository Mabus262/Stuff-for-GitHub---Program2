#if !defined CAR_H
#define CAR_H

#include <cassert>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Car
{
public:
	Car();
	Car(int id, int exn, int qtime, int enn);
	Car(const Car & orig);

	Car & operator=(const Car & right);

	virtual ~Car();
	int GetID() const;
	int GetExit() const;
	int GetTime() const;
	int GetEntrance() const;
	void Display(int timenow, ostream & out) const;

private:
	int IDNum;
	int ExitNum;
	int timeinQ;
	int EnterNum;

};

Car::Car()
{
	IDNum = 0;
	ExitNum = -1;
	EnterNum = -1;
	timeinQ = 0;
}

Car::Car(int id, int exn, int qtime,int enn)
{
	IDNum = id;
	ExitNum = exn;
	EnterNum = enn;
	timeinQ = qtime;
}

Car::Car(const Car & orig)
{
	IDNum = orig.IDNum;
	ExitNum = orig.ExitNum;
	timeinQ = orig.timeinQ;
	EnterNum = orig.EnterNum;
}

Car & Car::operator=(const Car & right)
{
	IDNum = right.IDNum;
	ExitNum = right.ExitNum;
	timeinQ = right.timeinQ;
	EnterNum = right.EnterNum;
	return *this;
}

Car::~Car()
{

}

int Car::GetID() const
{
	return IDNum;
}

int Car::GetExit() const
{
	return ExitNum;
}

int Car::GetEntrance() const
{
	return EnterNum;
}

int Car::GetTime() const
{
	return timeinQ;
}

void Car::Display(int timenow, ostream & out) const
{

	int id = GetID();
	int exit = GetExit();
	int entrance = GetEntrance();
	int timein = GetTime();

	out << "*****" << endl;
	out << "ID: " << id << endl;
	out << "Exit#: " << exit << endl;
	out << "Entrance#: " << entrance << endl;
	out << "Time entered Queue: " << timein << endl;
	out << "Time exited: " << timenow << endl;
	out << "Total Time Waiting: " << timenow - timein << endl;
	out << "*****\n" << endl;
	
	return;
}

#endif