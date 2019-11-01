#pragma once
#include<iostream>
#include <vector>
#include<string>
#include<cstdlib>
#include<algorithm>
#include<time.h> //FOR SRAND()
#include "Elevator.h"

using namespace std;


//Display to see whats in that vector
void displayPeople(vector<Person> people)
{
	if (people.size() == 0)
	{
		cout << "\nempty\n";
	}
	for (int i = 0; i < people.size(); i++) {
		cout << "\nPerson # " << people[i].getPersonID() << " :   Starting Floor: " << people[i].getStartingFloor() << " Destination Floor: " << people[i].getDesiredFloor() << endl;
		cout << "\nStarting time" << people[i].getStartTime() << endl;
	}
}

void SceneCreator(int numElevtor, int numPeople, vector<Elevator>& elevators, vector<Person>& people)
{

	//vector<Elevator> elevators;
	Elevator newElevator;

	//vector<Person> people;
	Person newPerson;

	//Elevator(int elevatornumber, int currentfloor, bool direction)
	for (int i = 0; i < numElevtor; i++)
	{
		if (i == 0)
		{
			newElevator = Elevator((i + 1), 0, true);
		}
		else if (i == 1)
		{
			newElevator = Elevator((i + 1), 0, false);
		}
		else if (i % 2 == 0)
		{
			newElevator = Elevator((i + 1), 0, true);

		}
		else if (i % 2 == 1)
		{
			newElevator = Elevator((i + 1), 0, false);
		}
		elevators.push_back(newElevator);

	}



	




	//MAKES PEOPLE AND THEIR REQUESTS. INITALIZES IF THEY ARE GOING UP OR DOWN
	srand(time(NULL));
	for (int i = 0; i < numPeople; i++)
	{
		newPerson = Person((i + 1), (rand() % 29) + 1, ((rand() % 9) + 1), ((rand() % 9) + 1));
		while (newPerson.getStartingFloor() == newPerson.getDesiredFloor()) {                   // IF EXAMPLE REQUEST THE SAME FLOOR AS THEY ARE ON
			newPerson = Person((i + 1), (rand() % 29) + 1, ((rand() % 9) + 1), ((rand() % 9) + 1));// THIS WILL KEEP GOING UNTIL THEY GET A NEW ONE. 
		}
		if (newPerson.getDesiredFloor() > newPerson.getStartingFloor()) {  // LETS PROGRAM KNOW IF PERSON is GOING UP
			newPerson.setDirection(true);
		}
		else {
			newPerson.setDirection(false);

		}

		people.push_back(newPerson);
		//cout << "THE SIZE OF THIS IS\n" << people.size() << endl;
	}


}
void sortUp(vector<Person>&calls)
{
	//Selectin sort Ascending order
	if (calls[0].getDirection() == true)
	{
		for (int i = 0; i < calls.size(); i++) {

			int indexSmallest = i;
			for (int j = i + 1; j < (calls.size()); j++) {

				if (calls[j].getStartingFloor() < calls[indexSmallest].getStartingFloor()) {/// SELECTION SORT
					indexSmallest = j;

				}
			}

			// Swap numbers[i] and numbers[indexSmallest]
			Person temp2 = calls[i];
			calls[i] = calls[indexSmallest];
			calls[indexSmallest] = temp2;

		}
	}
}
void oragizedRequester(vector<Person>& people)
{
	
	if (people.size() > 1)
	{


		//Sorting
		for (int i = 0; i < people.size(); i++) {
			int indexSmallest = i;
			for (int j = i + 1; j < (people.size()); j++) {

				if (people[j].getStartingFloor() < people[indexSmallest].getStartingFloor()) {
					indexSmallest = j;

				}
			}

			// Swap numbers[i] and numbers[indexSmallest]
			Person temp = people[i];
			people[i] = people[indexSmallest];
			people[indexSmallest] = temp;

		}
	}
}

void oraganizeUpDown(vector<Person> people, vector<Person>& people_going_up, vector<Person>& people_going_down, int wheelTime)
{

	
	
	for (int i = 0; i < people.size(); i++) {
		if ((people[i].getDirection() == false) && (people[i].getbutton() == false) && (people[i].getStartTime() == wheelTime)) {//This doesn't allow people who have already been sorted to be sorted again
			
			people_going_down.push_back(people[i]); // THIS HERE SHOULD SORT THE UP CALLS AND DOWN CALLS

		}
		else if ((people[i].getDirection() == true) && (people[i].getbutton()== false) && (people[i].getStartTime() == wheelTime)) {//This doesn't allow people who have already been sorted to be sorted again
			people_going_up.push_back(people[i]); // THIS HERE SHOULD SORT THE UP CALLS AND DOWN CALLS

		}

	}
}

int checkProxU(vector<Elevator>elevators)
{
	//Return the index of the elevator that is closest to the people going up
	int size = elevators.size();
	int sizeup;
	vector<Elevator> ups;
	for (int i = 0; i < size; i++)
	{
		if (elevators[i].getUpDown() == true)//Puts all elevators picking up people going up in a vector
		{
			ups.push_back(elevators[i]);
		}
	}
	if (ups.empty())//There is no elevators picking up people going up
	{

		return -1; 
	}
	else
	{
		sizeup = ups.size();
	}
	int x = 0;
	if (sizeup == 1)//Only one elevator to choose from
	{
		return ups[0].getNumber() - 1;  //returning the 0 index
	}


	for (int i = 1; i < sizeup; i++)//Loop for multiple elevators
	{
		if ((ups[x].get_Response_Up() - ups[x].getFloor()) <= (ups[i].get_Response_Up() - ups[i].getFloor()))//This checks the people going up, who is closest
		{
			x = i - 1;
		}
		else
		{
			x = i;
		}

	}
	return x;

}

int checkProxD(vector<Elevator>elevators)
{
	//Return the index of the elevator that is closest to the people going down
	int size = elevators.size();
	int sizedown;
	vector<Elevator> downs;
	for (int i = 0; i < size; i++)
	{
		if (elevators[i].getUpDown() == false)//Puting all the elevators picking up downs in a vector
		{
			downs.push_back(elevators[i]);
		}
	}
	if (downs.empty())//There is no elevators picking up people going up
	{

		return -1;
	}
	else
	{

		sizedown = downs.size();
	}
	int x = 0;
	if (sizedown == 1)//Only one elevator to choose from
	{
		return downs[0].getNumber() - 1;
	}

	for (int i = 1; i < sizedown; i++)//Loop for multiple elevators
	{

		if ((downs[x].get_Response_Down() - downs[x].getFloor()) <= (downs[i].get_Response_Down() - downs[i].getFloor()))//This checks the people going up, who is closest
		{
			x = i - 1;
		}
		else
		{
			x = i;
		}

	}
	return x;

}

void oraganizeEmptyU(vector<Elevator>& elevators, vector<Person> people_going_dir)
{
	sortUp(people_going_dir);
	int person = people_going_dir.size();
	person--;
	
	int size = elevators.size();
	
	for (int i = 0; i < size; i++)
	{
		if (!people_going_dir.empty())
		{
			
			elevators[i].set_Response_Up(people_going_dir[0].getStartingFloor());//Set the lowest starting floor to compare
			
		}
	}
}

void oraganizeEmptyD(vector<Elevator>& elevators, vector<Person> people_going_dir)
{
	
	sortUp(people_going_dir);
	int size = elevators.size();
	int person = people_going_dir.size();
	person--;

	for (int i = 0; i < size; i++)
	{
		if (!people_going_dir.empty())
		{
			elevators[i].set_Response_Down(people_going_dir[person].getStartingFloor());//Set the highest starting floor to compare
			
		}
	}
}

void decidingU(vector<Elevator>&elevators, vector<Person>& people_going_up, vector<Person>& requesters)
{
	//Decides which elevator is closer
	int close = checkProxU(elevators);
	
	if ((close == -1))
	{
		
		

	}
	else
	{
		elevators[close].setdir(true);


		if (!people_going_up.empty())
		{

			cout << "Elevator " << elevators[close].getNumber();
			


			for (int i = 0; i < people_going_up.size(); i++)//Loop through people who have pressed button already and delete them
			{

				if (people_going_up[i].getbutton())
				{
					people_going_up.erase(people_going_up.begin() + i);
				}
			}
			if (!(people_going_up.empty()))
			{
				elevators[close].elevator_movingU(people_going_up); //Take the requests and put them into a pending for the elevator

				for (int i = 0; i < people_going_up.size(); i++) //Loop through people and say who has pressed button
				{
					if (!(elevators[close].getpendingidSize() == 0))
					{
						for (int j = 0; j < elevators[close].getpendingidSize(); j++)
						{

							if (people_going_up[i].getPersonID() == elevators[close].getpendingfloorId(j))//If your id matches the one in the pending elevator
							{
								people_going_up[i].setbutton(true);//Person pressed that button and will be deleted later

							}
						}
					}

					for (int j = 0; j < requesters.size(); j++)//Loop through requesters 
					{
						if (people_going_up[i].getPersonID() == requesters[j].getPersonID())//If the Id from requesters is same as people going up Id
						{
							requesters[j].setbutton(true);//Set button to true to be used later in elevators switching from up to down
						}
					}
				}
			}

			
			if (!(elevators[close].getPending() == elevators[close].getFloor()))//Display of where elevator is going
			{
				cout << " going to floor " << elevators[close].getPending() << "\n";
			}
			while (elevators[close].getPending() == elevators[close].getFloor())//Once Elevator gets to the floor to pick someone up
			{
				
				elevators[close].popPending(0);//delete pending once arrived
				cout << "\nPicked up Person " << elevators[close].getpendingfloorId(0) << "\nGoing to floor " << elevators[close].getPending() << endl;






				for (int j = 0; j < requesters.size(); j++) 
				{
					if (elevators[close].getpendingfloorId(0) == requesters[j].getPersonID())
					{
						requesters[j].setonE(true);//True this requester got on the elevator, used when getting off elevator
					}
				}

				elevators[close].poppendingfloorId(0);//delete the id of person
			}

			elevators[close].setuFloor();//going to the direction of the pending request

		}
		else if (!(elevators[close].getpendingSize() == 0))//if the people requesting is all deleted then use pending to finish moving elevator
		{
			cout << "Elevator " << elevators[close].getNumber();
			//cout << "ERROR D";
			if (!(elevators[close].getPending() == elevators[close].getFloor()))
			{
				cout << " going to floor " << elevators[close].getPending() << "\n";
			}
			while (elevators[close].getPending() == elevators[close].getFloor())//Once Elevator gets to the floor to pick someone up
			{
				//cout << "ERROR E";
				elevators[close].popPending(0);
				cout << "\nPicked up Person " << elevators[close].getpendingfloorId(0) << "\nGoingto floor " << elevators[close].getPending() << endl;

				for (int j = 0; j < requesters.size(); j++)
				{

					if (elevators[close].getpendingfloorId(0) == requesters[j].getPersonID())
					{
						requesters[j].setonE(true);//True this requester got on the elevator, used when getting off elevator
					}
				}

				elevators[close].poppendingfloorId(0);


			}

			elevators[close].setuFloor();//going to the direction of the pending request

		}
	}
	
	
}
void decidingD(vector<Elevator>&elevators,  vector<Person>& people_going_down, vector<Person>& requesters)
{
	int close = checkProxD(elevators);
	
	if ((close == -1))
	{
		
		
	}
	else
	{
		elevators[close].setdir(false);
		if (!people_going_down.empty())
		{
			cout <<"Elevator " << elevators[close].getNumber();
			//cout << "ERROR F";

			for (int i = 0; i < people_going_down.size(); i++)//Loop through people who have pressed button already and delete them
			{

				if (people_going_down[i].getbutton())
				{
					people_going_down.erase(people_going_down.begin() + i);
				}
			}
			if (!(people_going_down.empty()))
			{
				elevators[close].elevator_movingD(people_going_down);//Take the requests and put them into a pending for the elevator

				for (int i = 0; i < people_going_down.size(); i++)
				{
					if (!(elevators[close].getpendingidSize() == 0))
					{
						for (int j = 0; j < elevators[close].getpendingidSize(); j++)
						{

							if (people_going_down[i].getPersonID() == elevators[close].getpendingfloorId(j))//If your id matches the one in the pending elevator
							{
								people_going_down[i].setbutton(true);

							}
						}
					}

					for (int j = 0; j < requesters.size(); j++)
					{
						if (people_going_down[i].getPersonID() == requesters[j].getPersonID())
						{
							requesters[j].setbutton(true);//Set button to true to be used later in elevators switching from up to down
						}
					}
				}
			}


			if (!(elevators[close].getPending() == elevators[close].getFloor()))
				//cout << "ERROR G";
			{
				cout << " going to floor " << elevators[close].getPending() << "\n";
			}
			while (elevators[close].getPending() == elevators[close].getFloor())//Once Elevator gets to the floor to pick someone up
			{
				//cout << "ERROR H";
				elevators[close].popPending(0);
				cout << "\nPicked up Person " << elevators[close].getpendingfloorId(0) << "\nGoing to floor " << elevators[close].getPending() << endl;






				for (int j = 0; j < requesters.size(); j++)
				{
					if (elevators[close].getpendingfloorId(0) == requesters[j].getPersonID())
					{
						requesters[j].setonE(true);//True this requester got on the elevator, used when getting off elevator
					}
				}
				elevators[close].poppendingfloorId(0);
			}

			elevators[close].setdFloor();//going to the direction of the pending request

		}
		else if (!(elevators[close].getpendingSize() == 0))
		{
			cout  << "Elevator " << elevators[close].getNumber();
			//cout << "ERROR I";

			if (!(elevators[close].getPending() == elevators[close].getFloor()))
				//cout << "ERROR J";
			{
				cout << " going to floor " << elevators[close].getPending() << "\n";
			}
			while (elevators[close].getPending() == elevators[close].getFloor())//Once Elevator gets to the floor to pick someone up
			{
				//cout << "ERROR K";
				elevators[close].popPending(0);
				cout << "\nPicked up Person " << elevators[close].getpendingfloorId(0) << "\nGoingto floor " << elevators[close].getPending() << endl;





				for (int j = 0; j < requesters.size(); j++)
				{

					if (elevators[close].getpendingfloorId(0) == requesters[j].getPersonID())
					{
						requesters[j].setonE(true);//True this requester got on the elevator, used when getting off elevator
					}
				}

				elevators[close].poppendingfloorId(0);
			}

			elevators[close].setdFloor();//going to the direction of the pending request

		}
	}
}



void wheeloTime(vector<Elevator>&elevators, vector<Person> people, int& wheelTime, vector<Person>& requesters, vector<int>& waitTimes)
{
	wheelTime++;
	

	int numberElevators, numberPeople;
	numberElevators = elevators.size();
	numberPeople = people.size();

	cout << "\nTime: " << wheelTime;
	cout << "\n___________________________________________\n";
	//display elevator postion
	for (int i = 0; i < numberElevators; i++)
	{
		cout << endl << elevators[i].getNumber() << " Elevator at Floor " << elevators[i].getFloor();
	}
	//Display people requests by time

	bool itZero = true;
	cout << "\n\nRequests:     ";
	for (int i = 0; i < numberPeople; i++)
	{

		Person requester;

		if (people[i].getStartTime() == wheelTime)
		{
			requester = people[i];
			cout << "\nPerson " << requester.getPersonID() << " starts at floor " << requester.getStartingFloor();
			requesters.push_back(requester);
			itZero = false;
		}
		else if (itZero && (i == (numberPeople - 1)))
		{
			cout << "\nNo Requests at this time\n";
		}

	}
	
	//once Exited pop that person
	
	if (!(requesters.empty()))
	{
		
		for (int i = 0; i < elevators.size(); i++)
		{
			//cout << "\nERROR 1";
			if (!(elevators[i].getexitingSize() == 0))
			{
				//cout << "\nERROR 2";
				for (int j = 0; j < elevators[i].getexitingSize(); j++)
				{	
					//cout << "\nERROR 3";
					if ((elevators[i].getexitingSize() == 0))
					{

					}
					
					else if ((elevators[i].getExiting(j) == elevators[i].getFloor()) && !(elevators[i].getexitingSize() == 0))
					{
						//cout << "\nERROR 5";
						for (int x = 0; x < requesters.size(); x++)
						{
							//cout << "\nERROR 6" << x << j << endl;
							if (((requesters.empty()) || ((elevators[i].getexitingSize() == 0))) || (j < 0))
							{
								//cout << "liashdpof" << endl;
							}
							
							else if (((requesters[x].getPersonID() == elevators[i].getexitingId(j)) && (requesters[x].getonE() == true)) && !requesters.empty())//Make sure this perosn is on the elevator
							{
								//cout << "\nERROR 8";
								cout << "\nElevator " << elevators[i].getNumber() << " is letting Person " << requesters[x].getPersonID() << " off\n";
								waitTimes.push_back(wheelTime - requesters[x].getStartTime());
								requesters.erase(requesters.begin() + x);
								
								//cout << "NOT HERE";
								x = x - 1;
								elevators[i].popexitingId(j);
								elevators[i].popExiting(j);
								elevators[i].popPending(j);
								j = j - 1;
								

								
								
							}
							
						}
						
					}
					
				}
				
				
			}

			
		}


		
	}
	

	



}


void switcherO(vector<Elevator>& elevators, vector<Person> requesters)
{
	int x = 20;
	int z = -1;
	int t;
	
	for (int i = 0; i < elevators.size(); i++)
	{
		int y;
		if (elevators[i].getpendingidSize() == 0)//Wont choose elevators who are already moving
		{
			for (int j = 0; j < requesters.size(); j++)
			{
				if (!requesters[j].getbutton())//If the requester has already been picked up
				{
					y = abs(elevators[i].getFloor() - requesters[j].getStartingFloor());//which elevator is closer to the requester
					if (y < x)
					{
						x = y;
						z = i;
						t = j;
					}
				}
			}
		}
	}

	if (!(z == -1))
	{
		elevators[z].setdir(requesters[t].getDirection());//change the direction of elevator
		
	}
	
}

//Calculate Average wait times
int averagewaitTime(vector<int> waitTimes, int numberPeople)
{
	int add = 0;
	for (int i = 0; i < waitTimes.size(); i++)
	{
		add = waitTimes[i] + add;
	}

	add = (add / numberPeople);
	return add;
}
