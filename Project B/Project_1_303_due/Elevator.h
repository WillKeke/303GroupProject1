#pragma once
#include<iostream>
#include<vector>
#include<time.h>

#include"Person.h"

using namespace std;
// elevator  is storing current floor



class Elevator
{
private:
	int elevatorNumber;
	int currentFloor;
	vector<int> pendingFloor;
	vector<int> exitingFloor;
	vector<int> exitingId;
	vector<int> pendingfloorId;
	bool goingUp;
	int up_Response_Num;
	int down_Response_Num;
	int Two_Seconds = 2;
	int Three_Seconds = 3;
	int Grand_Total = 0;

	//For elevator processing
	int get_to_time; // time to get from elevator destination to floor (ex. elevator is on floor 1 and going to 4) TAKES 2 SECONDS PER FLOOR
	int simple_travel_time;// time to get from start floor to destination (ex. floor 3 to 4) TAKES 2 SECONDS PER FLOOR
	int loading_time = 0; // this is how long it takes to load onto the elevator on each floor TAKES 3 SECONDS







public:
	Elevator() {
		elevatorNumber = 0;
		currentFloor = 0;

		goingUp = false;

	}

	Elevator(int elevatornumber, int currentfloor, bool direction)
	{
		elevatorNumber = elevatornumber;
		currentFloor = currentfloor;
		goingUp = direction;

	}

	int getNumber()
	{
		return elevatorNumber;
		
	}

	int getFloor()
	{
		return currentFloor;
	}
	int getExiting(int n)
	{
		return exitingFloor[n];
	}
	void popExiting(int n)
	{
		exitingFloor.erase(exitingFloor.begin() + n);
	}
	int getPending()
	{
		return pendingFloor[0];
	}
	void popPending(int n)
	{
		pendingFloor.erase(pendingFloor.begin() + n);
	}
	int getpendingfloorId(int n)
	{
		return pendingfloorId[n];
	}
	void poppendingfloorId(int n)
	{
		pendingfloorId.erase(pendingfloorId.begin() + n);
	}
	int getpendingSize()
	{
		return pendingFloor.size();
	}
	int getexitingId(int n)
	{
		return exitingId[n];
	}
	void popexitingId(int n)
	{
		exitingId.erase(exitingId.begin() + n);
	}
	int getexitingSize()
	{
		return exitingFloor.size();
	}
	int getpendingidSize()
	{
		return pendingfloorId.size();
	}
	void setuFloor()
	{
		if (currentFloor < pendingFloor[0])
		{
			currentFloor++;
		}
		else
		{
			currentFloor--;
		}
	}
	void setdFloor()
	{
		if (currentFloor < pendingFloor[0])
		{
			currentFloor++;
		}
		else
		{
			currentFloor--;
		}
	}
	bool getUpDown()
	{
		return goingUp;
	}
	string getDirection()
	{
		if (goingUp)
		{
			return "Up";
		}
		else
		{
			return "Down";
		}
	}

	void setdir(bool dir)
	{
		goingUp = dir;
	}
	void setPendingFloor(int floorNumber)
	{
		pendingFloor.push_back(floorNumber);
	}
	/// GETTERS AND SETTERS FOR RESPONSE UP
	void set_Response_Up(int num) {
		up_Response_Num = num;
	}

	int get_Response_Up() {
		return up_Response_Num;
	}
	/// GETTERS AND SETTERS FOR RESPONSE down.             //// This here will give back a number that will be used to calculate which
	void set_Response_Down(int num) {                      //// elevator goes to which floor on a proximity basis.
		down_Response_Num = num;
	}

	int get_Response_Down() {
		return down_Response_Num;
	}

	//Puts Requesters into this elevators pending going up
	void elevator_movingU(vector<Person>calls)
	{
		
		int sizeC = calls.size();
		sizeC--;
		int sizeP = pendingFloor.size();
		sizeP--;
		///SWITCHES TO PUT IN ASCENDING ORDER (FOR GOING UP ONLY)


		for (int i = 0; i < calls.size(); i++) {

			int indexSmallest = i;
			for (int j = i + 1; j < (calls.size()); j++) {

				if (calls[j].getDesiredFloor() < calls[indexSmallest].getDesiredFloor()) {/// SELECTION SORT
					indexSmallest = j;

				}
			}

			// Swap numbers[i] and numbers[indexSmallest]
			Person temp2 = calls[i];
			calls[i] = calls[indexSmallest];
			calls[indexSmallest] = temp2;

		}
		
		if (pendingFloor.empty())//If no pending then just put the person in pending
		{
			for (int i = 0; i < calls.size(); i++)
			{
				
				if (calls.size() == 1)
				{
					pendingFloor.push_back(calls[i].getStartingFloor());
					pendingfloorId.push_back(calls[i].getPersonID());
					exitingFloor.push_back(calls[i].getDesiredFloor());
					exitingId.push_back(calls[i].getPersonID());

					pendingFloor.push_back(calls[i].getDesiredFloor());
				}
				else if (calls[i].getStartingFloor() <= calls[sizeC].getDesiredFloor())
				{
					pendingFloor.push_back(calls[i].getStartingFloor());
					pendingfloorId.push_back(calls[i].getPersonID());
					exitingFloor.push_back(calls[i].getDesiredFloor());
					exitingId.push_back(calls[i].getPersonID());

					pendingFloor.push_back(calls[i].getDesiredFloor());
				}


			}
		}
		else
		{
			for (int i = 0; i < calls.size(); i++)
			{
				
				if ((calls[i].getStartingFloor() <= pendingFloor[sizeP]) && (calls[i].getStartingFloor() >= currentFloor))//Will pick up people on the way of dropping off someone else
				{
					pendingFloor.push_back(calls[i].getStartingFloor());
					pendingfloorId.push_back(calls[i].getPersonID());
					exitingFloor.push_back(calls[i].getDesiredFloor());
					exitingId.push_back(calls[i].getPersonID());

					pendingFloor.push_back(calls[i].getDesiredFloor());
				}
				


			}
		}
		//Sort it
		for (int i = 0; i < pendingFloor.size(); i++) {

			int indexSmallest = i;
			for (int j = i + 1; j < (pendingFloor.size()); j++) {

				if (pendingFloor[j] < pendingFloor[indexSmallest]) {/// SELECTION SORT
					indexSmallest = j;

				}
			}

			// Swap numbers[i] and numbers[indexSmallest]
			int temp2 = pendingFloor[i];
			pendingFloor[i] = pendingFloor[indexSmallest];
			pendingFloor[indexSmallest] = temp2;

		}


	}

	//Puts Requesters into this elevators pending going up
	void elevator_movingD(vector<Person>calls)
	{
		
		int sizeC = calls.size();
		int sizeP = pendingFloor.size();
		sizeP--;
		sizeC--;
		///SWITCHES TO PUT IN ASCENDING ORDER (FOR GOING UP ONLY)
		if (calls[0].getDirection() == false)
		{
			for (int i = 0; i < calls.size(); i++) {

				int indexSmallest = i;
				for (int j = i + 1; j < (calls.size()); j++) {

					if (calls[j].getDesiredFloor() < calls[indexSmallest].getDesiredFloor()) {/// SELECTION SORT
						indexSmallest = j;

					}
				}

				// Swap numbers[i] and numbers[indexSmallest]
				Person temp2 = calls[i];
				calls[i] = calls[indexSmallest];
				calls[indexSmallest] = temp2;

			}
		}
		reverse(calls.begin(), calls.end());//reverse it for going down

		
		if (pendingFloor.empty())
		{
			for (int i = 0; i < calls.size(); i++)
			{

				if (calls.size() == 1)
				{
					pendingFloor.push_back(calls[i].getStartingFloor());
					pendingfloorId.push_back(calls[i].getPersonID());
					exitingFloor.push_back(calls[i].getDesiredFloor());
					exitingId.push_back(calls[i].getPersonID());

					pendingFloor.push_back(calls[i].getDesiredFloor());
				}
				else if (calls[i].getStartingFloor() >= calls[sizeC].getDesiredFloor())
				{
					pendingFloor.push_back(calls[i].getStartingFloor());
					pendingfloorId.push_back(calls[i].getPersonID());
					exitingFloor.push_back(calls[i].getDesiredFloor());
					exitingId.push_back(calls[i].getPersonID());

					pendingFloor.push_back(calls[i].getDesiredFloor());
				}


			}
		}
		//put thing into pending both starting floor and desired floor
		else
		{
			for (int i = 0; i < calls.size(); i++)
			{

				if (((calls[i].getStartingFloor() >= pendingFloor[sizeP]) && (calls[i].getStartingFloor() <= currentFloor)))//Picking people up on the way down
				{
					pendingFloor.push_back(calls[i].getStartingFloor());
					pendingfloorId.push_back(calls[i].getPersonID());
					exitingFloor.push_back(calls[i].getDesiredFloor());
					exitingId.push_back(calls[i].getPersonID());

					pendingFloor.push_back(calls[i].getDesiredFloor());
				}
				

			}
		}
		//Sort it
		for (int i = 0; i < pendingFloor.size(); i++) {

			int indexSmallest = i;
			for (int j = i + 1; j < (pendingFloor.size()); j++) {

				if (pendingFloor[j] < pendingFloor[indexSmallest]) {/// SELECTION SORT
					indexSmallest = j;

				}
			}

			// Swap numbers[i] and numbers[indexSmallest]
			int temp2 = pendingFloor[i];
			pendingFloor[i] = pendingFloor[indexSmallest];
			pendingFloor[indexSmallest] = temp2;

		}

		reverse(pendingFloor.begin(), pendingFloor.end());
	}



};