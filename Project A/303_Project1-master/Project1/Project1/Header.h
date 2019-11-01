#include <iostream>
#include <vector>
#include<string>
#include<cstdlib>
#include<algorithm>
#include<time.h> //FOR SRAND()
#include "Elevator.h"

using namespace std;





void SceneCreator(int numElevtor, int numPeople, vector<Elevator>& elevators, vector<Person>& people)
{

	//vector<Elevator> elevators;
	Elevator newElevator;

	//vector<Person> people;
	Person newPerson;

	//Elevator(int elevatornumber, int currentfloor, bool direction)
	for (int i = 0; i < numElevtor; i++)
	{
		newElevator = Elevator((i+1), 0, true);
		elevators.push_back(newElevator);

	}
	


	//Person(int personid,int starttime, int startfloor, int desiredfloor, bool direction)

	


	//MAKES PEOPLE AND THEIR REQUESTS. INITALIZES IF THEY ARE GOING UP OR DOWN
	srand(time(NULL));
		for (int i = 0; i < numPeople; i++)
		{
			newPerson = Person((i+1), (rand() % 60), ((rand() %9)+1), ((rand() % 9) + 1));           
			while (newPerson.getStartingFloor() == newPerson.getDesiredFloor()) {                   // IF EXAMPLE REQUEST THE SAME FLOOR AS THEY ARE ON
				newPerson = Person((i + 1), (rand() % 60), ((rand() % 9) + 1), ((rand() % 9) + 1));// THIS WILL KEEP GOING UNTIL THEY GET A NEW ONE. 
			}
			if (newPerson.getDesiredFloor() > newPerson.getStartingFloor()) {  // LETS PROGRAM KNOW IF PERSON is GOING UP
				newPerson.setDirection(true);
			}
			else {
				newPerson.setDirection(false);
			
			}

			people.push_back(newPerson);
			//cout << "THE SIZE OF THIS IS\n" << people.size() << endl; CHECKS HOW BIG ORIGINAL VECTOR IS
		}

	
}