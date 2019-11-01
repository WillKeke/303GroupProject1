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
	int pendingFloor;
	bool goingUp;
	int up_Response_Num;
	int down_Response_Num;
	int Two_Seconds = 2;
	int Three_Seconds = 3;
	int Grand_Total=0;
	
	//For elevator processing
	int get_to_time; // time to get from elevator destination to floor (ex. elevator is on floor 1 and going to 4) TAKES 2 SECONDS PER FLOOR
	int simple_travel_time;// time to get from start floor to destination (ex. floor 3 to 4) TAKES 2 SECONDS PER FLOOR
	int loading_time=0; // this is how long it takes to load onto the elevator on each floor TAKES 3 SECONDS
	






public:
	Elevator() {
		elevatorNumber = 0; 
		currentFloor= 0;
		pendingFloor = 0;
		goingUp = false;

	}
	
	Elevator(int elevatornumber, int currentfloor, bool direction)
	{
		elevatorNumber = elevatornumber;
		currentFloor = currentfloor;
		goingUp = direction;
		pendingFloor = 0; //Fix this almost there
	}

	int getNumber()
	{
		return elevatorNumber;
	}

	int getFloor()
	{
		return currentFloor;
	}

	int getPending()
	{
		return pendingFloor;
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

	void setPendingFloor(int floorNumber)
	{
		pendingFloor = floorNumber;
	}
	/// GETTERS AND SETTERS FOR RESPONSE UP
	void set_Response_Up(int num) {
		up_Response_Num = abs(num - currentFloor);
	}

	int get_Response_Up() {
		return up_Response_Num;
	}
	/// GETTERS AND SETTERS FOR RESPONSE down.             //// This here will give back a number that will be used to calculate which
	void set_Response_Down(int num) {                      //// elevator goes to which floor on a proximity basis.
		down_Response_Num = abs(num - currentFloor);     
	}

	int get_Response_Down() {
		return down_Response_Num;
	}
	void elevator_moving(vector<Person>calls) {
		
		///SWITCHES TO PUT IN ASCENDING ORDER (FOR GOING UP ONLY)
		if (calls[0].getDirection() == true) {
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
			if (calls[0].getDirection() != true) {
				reverse(calls.begin(), calls.end()); /// REVERSES VECTOR FOR GOING DOWN
			}
		
		get_to_time = abs(currentFloor - calls[0].getStartingFloor()) * Two_Seconds;
		
		
		// ANOTHER SORTING TO PUT THE DOWARD IN ORDER MIGHT NEED TO REDO THIS AGAIN

		if (calls[0].getDirection() == false) {
			for (int i = 0; i < calls.size(); i++) {

				int indexSmallest = i;
				for (int j = i + 1; j < (calls.size()); j++) {

					if (calls[j].getDesiredFloor() < calls[indexSmallest].getDesiredFloor()) {
						indexSmallest = j;

					}
				}

				// Swap numbers[i] and numbers[indexSmallest]
				Person temp2 = calls[i];
				calls[i] = calls[indexSmallest];
				calls[indexSmallest] = temp2;

			}
		}

		if (calls[0].getDirection() != true) {
			reverse(calls.begin(), calls.end()); /// REVERSES VECTOR FOR GOING DOWN
		}

		for (int i = 0; i < calls.size(); i++) {

			

			simple_travel_time = abs(calls[i].getDesiredFloor() - calls[i].getStartingFloor()) * Two_Seconds;

			if (calls[i].getDirection() == true) {
				for (int j = 0; j < calls.size(); j++) {
					if (calls[j].getStartingFloor() < calls[0].getDesiredFloor()) { ///
						loading_time++;                                         ///THIS HERE PROCESS THE LOADING/UNLOADING TIME
					}                                                           ///BETWEEN PASSANGERS
					if (calls[j].getDesiredFloor() < calls[0].getDesiredFloor()) {
						loading_time++;
					}

				}
			}
			else if (calls[i].getDirection() != true ) {
				for (int j = 0; j < calls.size(); j++) {
					if (calls[j].getStartingFloor() < calls[0].getDesiredFloor()) { /// FOR THE DOWNWARD LOADING TIME CALCULAION
						loading_time++;                                         ///THIS HERE PROCESS THE LOADING/UNLOADING TIME
					}                                                           ///BETWEEN PASSANGERS
					if (calls[j].getDesiredFloor() > calls[0].getDesiredFloor()) {
						loading_time++;
					}

				}
			}
			loading_time = loading_time * Three_Seconds;
			cout << "Person " << calls[i].getPersonID() << " will be number " << i + 1 << "\nto get exit elevator going " ;
			if (calls[i].getDirection() == true) {
				cout << "UP.\n";
			}
			else {
				cout << "DOWN.\n";
			}
			cout << "Starting at floor: " << calls[i].getStartingFloor() << "\nWaiting time will be: " << loading_time + simple_travel_time + get_to_time
				<< " seconds to get to floor: " << calls[i].getDesiredFloor() << " including a loading time of " << loading_time << " seconds.\n\n" << endl;
			Grand_Total += loading_time + simple_travel_time + get_to_time;
			loading_time = 0;
			simple_travel_time = 0; // RESETS TIMES FOR NEXT CALL IN ORDER
			currentFloor = calls[(calls.size()-1)].getDesiredFloor();///WILL THE ELEVATOR AT THIS FLOOR WHEN DONE
			
		}
		cout << "Elevator " << elevatorNumber << " is now on floor: " << currentFloor << "\n" << endl;
	}
};