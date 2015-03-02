#include <cassert>
#include <iostream>
#include <string>
#include "queue.h"
#include "Car.h"
#include <ctime>
#include <fstream>

using namespace std;

int main()
{
	int MaxTime = 8;
	int CurrentTime = 0;
	int totalWaitTime[4] = { 0 };
	int Carspassed[4] = {0};
	int IDnumber = 100;

	srand(time(NULL));
	ofstream output;
	output.open("output.txt");

	double ArrivalRates[4] = {0.15, 0.45, 0.6, 0.30};
	cout << "Enter arrival rates";
	for (int i = 0; i < 4; i++)
	{
		cout << "\n" << i + 1 << ":";
		cin >> ArrivalRates[i];
	}
	//cout << "test1" << endl;
	Queue<Car> Arrivals[4];

	Car blank;
	Car temp;
	Car Roundabout[16];
	for (int i = 0; i < 16; i++)
		Roundabout[i] = blank;
	//cout << "test2" << endl;
	while (CurrentTime < MaxTime)
	{
		for (int i = 0; i < 4; i++)
		{
			//cout << "test3." <<i<< endl;
			int randarrival=rand()%100;
			if (randarrival < (ArrivalRates[i] * 100))
			{
				Car toqueue(IDnumber,((i+rand()%3+1)*4)%16-1, CurrentTime,i*4);
				Arrivals[i].enqueue(toqueue);
				IDnumber++;
			}
		}
		temp = Roundabout[0];
		for (int i = 1; i < 16; i++)
		{
			//cout << "test4." <<i<< endl;
			Roundabout[i] = temp;
			temp = Roundabout[i];
		}
		Roundabout[0] = temp;

		for (int i = 1; i <= 4; i++)
		{
			if (Roundabout[i * 4-1].GetExit()==i*4-1)
			{
				Roundabout[i * 4 - 1].Display(CurrentTime, output);
				totalWaitTime[Roundabout[i - 1].GetEntrance()] = totalWaitTime[Roundabout[i - 1].GetEntrance()] + (CurrentTime - Roundabout[i * 4 - 1].GetTime());
				Carspassed[Roundabout[i * 4 - 1].GetEntrance()]++;
				Roundabout[i * 4 - 1] = blank;
			}
		}

		for (int i = 1; i <= 4; i++)
		{
			if (Roundabout[i*4-1].GetID()!=0)
			{
				Roundabout[i-1] = Arrivals[i-1].peekFront();
				Arrivals[i-1].dequeue();
			}
		}
		CurrentTime++;
	}

	for (int i = 0; i < 4; i++)
	{
		cout << "\n\n**********\n" << endl;
		cout << " Queue Number: " << i;
		cout << " Total Cars passed: " << Carspassed[i];
		cout << " Total Wait time at queue: " << totalWaitTime[i];
		cout << endl;
	}

	for (int i = 0; i < 4; i++)
	{
		output << "\n\n**********\n" << endl;
		output << " Queue Number: " << i;
		output << " Total Cars passed: " << Carspassed[i];
		output << " Total Wait time at queue: " << totalWaitTime[i];
		output << endl;
	}

	output.close();
	return 0;
}