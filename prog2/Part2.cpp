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
	int max_time = 50;
	int current_time = 0;
	int total_wait_time[4] = {0};
	int cars_passed[4] = {0};
	int IDnumber = 100;

	srand(time(NULL));
	ofstream output;
	output.open("output.txt");

	double arrival_rates[4] = {0.15, 0.45, 0.6, 0.30};
	cout << "Enter arrival rates";
	for (int i = 0; i < 4; i++)
	{
		cout << "\n" << i + 1 << ":";
		cin >> arrival_rates[i];
	}
	//cout << "test1" << endl;
	Queue<Car> arrivals[4];

	Car blank;
	//blank.Display(current_time, output);
	Car temp;
	/*Car temp(1,1,1,1);
	arrivals[0].enqueue(temp);
	arrivals[0].peekFront().Display(current_time, output);
	arrivals[0].dequeue();*/

	Car roundabouts[16];
	for (int i = 0; i < 16; i++)
		roundabouts[i] = blank;
	//cout << "test2" << endl;
	while (current_time < max_time)
	{
		for (int i = 0; i < 4; i++)
		{
			//cout << "test3." <<i<< endl;
			int randarrival=rand()%100;
			if (randarrival < (arrival_rates[i] * 100))
			{
				Car toqueue(IDnumber,(((i+rand()%3+1)*4)-1)%16, current_time,i*4);
				arrivals[i].enqueue(toqueue);
				IDnumber++;
				//cout << endl;
				toqueue.Display(current_time, output);                                                           //test
				//cout << endl;
			}
		}
		temp = roundabouts[0];
		for (int i = 0; i < 15; i++)
		{
			//cout << "test4." <<i<< endl;

			roundabouts[i] = roundabouts[i+1];
		}
		roundabouts[15] = temp;

		for (int i = 1; i <= 4; i++)
		{
			int index = i * 4-1;
			//cout << " " << roundabouts[index].GetExit();                                                          //test
			//cout << " " << roundabouts[index].GetID();
			if (roundabouts[index].GetExit()==index)
			{
				int current_wait = total_wait_time[roundabouts[index].GetEntrance()];
				//cout << current_wait<<endl;                                                                         //test
				roundabouts[index].Display(current_time, output);
				total_wait_time[roundabouts[index].GetEntrance()] = current_wait + (current_time - roundabouts[index].GetTime());
				cars_passed[roundabouts[index].GetEntrance()]++;
				roundabouts[index] = blank;
			}
		}

		for (int i = 1; i <= 4; i++)
		{
			int index = i * 4-1;
			if (roundabouts[index].GetID() == 0 && roundabouts[i*4].GetID() == 0)
			{
				if (!arrivals[i - 1].isEmpty())
				{
					roundabouts[(i - 1) * 4] = arrivals[i - 1].peekFront();
					arrivals[i - 1].dequeue();
				}
			}
		}
		current_time++;
	}

	for (int i = 0; i < 4; i++)
	{
		cout << "\n\n**********\n" << endl;
		cout << " Queue Number: " << i;
		cout << " Total Cars passed: " << cars_passed[i];
		cout << " Total Wait time at queue: " << total_wait_time[i];
		cout << endl;
	}

	for (int i = 0; i < 4; i++)
	{
		output << "\n\n**********\n" << endl;
		output << " Queue Number: " << i;
		output << " Total Cars passed: " << cars_passed[i];
		output << " Total Wait time at queue: " << total_wait_time[i];
		output << endl;
	}

	output.close();
	return 0;
}
