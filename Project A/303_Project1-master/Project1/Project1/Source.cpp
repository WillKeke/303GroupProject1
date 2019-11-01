#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<time.h>
#include "Header.h"




using namespace std;


int main()
{
	//Intro Choices
	int numberElevators;
	int numberPeople;
	int floors;
	int choice;
	string enter;

	cout << "Welcome to the elevator sim\n";
	cout << "This utilizes a multi-elevator system with two elevators and turns into a single elevator system when warranted.\n";
	cout << "This is how it will operate:\n";
	cout << "1) Slected calls will be shown UNORGANIZED to simulate randomness\n";
	cout << "2) Using our algoritm we will organize the calls (in order) for the fastest delivery possible \n";
	cout << "3) Depening on proximity which ever elevator is close to pick up will move first and data on each passenger will be shown\n";
	cout << " \nPRESS ENTER TO CONTINUE";
	cin.ignore();


	numberElevators = 2;
	numberPeople = (rand() % 9);
	
	
	vector<Elevator> elevators;
	vector<Person> people;           //ALL THE PEOPLE 
	vector<Person> people_going_up;  // ALL THE PEOPLE GOING UP
	vector<Person> people_going_down;//ALL THE PEOPLE GOING Down

	//cout << "\nHere is your scene: \n";
	SceneCreator(numberElevators, numberPeople, elevators, people); /// MAKES SCENE

	

	/// SELECTION SORT FUNCTION LOW TO HIGH.
	cout << "\nThese are the list of calls UNORGANIZED that the elevators will handle" << endl;
	for (int i = 0; i < people.size(); i++) {
		cout <<"\nPerson # "<<people[i].getPersonID()<< " :   Starting Floor: "<< people[i].getStartingFloor() <<" Destination Floor: "<< people[i].getDesiredFloor()<< endl;
	}
	
	//cout << "\nSize of vector The PEOPLE VECTOR is : " << people.size()<< endl;


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

	/*cout << "******\n" << people.size() << endl << "This is the PEOPLE VECTOR calls organized" << endl;
	//people.erase(people.end());

	for (int i = 0; i < people.size(); i++) {
		cout << "\nPerson # " << people[i].getPersonID() << " :   Starting Floor: " << people[i].getStartingFloor() << " Destination Floor: " << people[i].getDesiredFloor() << endl;
	}
	cout << "*******\n" << people.size() << endl;*/

	for (int i = 0; i < people.size(); i++) {
		if (people[i].getDirection() == false) {
			people_going_down.push_back(people[i]); // THIS HERE SHOULD SORT THE UP CALLS AND DOWN CALLS
			
		}
		else if (people[i].getDirection() == true) {
			people_going_up.push_back(people[i]); // THIS HERE SHOULD SORT THE UP CALLS AND DOWN CALLS

		}
	}
	
	//cout << "\nTHIS IS THE NEW DOWN VECTOR SIZE: " << people_going_down.size() << endl;
	cout << "\nAfter processing these calls through our organizing algorithm,\nwe have seperated all the people who are going down,\nand those who are going up:\n" ;
	cout << "\nHERE ARE THE GOING DOWN ENTRIES:\n" << endl;

	for (int i = 0; i < people_going_down.size(); i++) {
		cout << "\nPerson # " << people_going_down[i].getPersonID()  << " :   Starting floor: " << people_going_down[i].getStartingFloor() << " Destination Floor: " << people_going_down[i].getDesiredFloor()<< endl;
	}
	//cout << "stop \n THE PEOPLE GOING UP VECTOR SIZE IS NOW " << people_going_up.size() <<"\n"<< endl;
	cout << "\nHERE ARE THE GOING UP ENTRIES:\n" << endl;
	
	//reverse(people_going_down.begin(), people_going_down.end()); //REVERSES THE GOING DOWN VECTOR FOR PROCESSING

	///cout << "stop \n LARGE TO SMALLEST" << people.size() << endl;

	for (int i = 0; i < people_going_up.size(); i++) {
		cout << "\nPerson # " << people_going_up[i].getPersonID() << " :   Starting floor: " << people_going_up[i].getStartingFloor() << " Destination Floor: " << people_going_up[i].getDesiredFloor() << endl;
	}

	//calculates responses for proximity
	
	if (!people_going_up.empty()) {
		elevators[0].set_Response_Up(people_going_up[0].getStartingFloor());
		elevators[1].set_Response_Up(people_going_up[0].getStartingFloor());
	}
	if (!people_going_down.empty()) {
		elevators[0].set_Response_Down(people_going_down[0].getStartingFloor());

		elevators[1].set_Response_Down(people_going_down[0].getStartingFloor());
	}
	

	/// WILL DECIDE WHAT ELEVATOR GOES TO WHAT AND DOES FINAL PROCESS.  
	/// This gets the proximity for each elevator
	 //cout << elevators[0].get_Response_Up() << endl;
	 //cout << elevators[1].get_Response_Up() << endl;

	//IF PEOPLE ARE GOING UP AND ELEVATOR 1 PROXIMITY IS LOWER THAN ELEVATOR 2,ELEVATOR 1 WILL GO FIRST AND TAKE UP CALLS
	if (!people_going_up.empty() && ( elevators[0].get_Response_Up() < elevators[1].get_Response_Up())) {
		cout << "Elevator 1 on floor " << elevators[0].getFloor()<< " is closer and will handle the up calls.\n\n" << endl;
		elevators[0].elevator_moving(people_going_up);
		//IF THE  PEOPLE GOING DOWN VECTOR IS FILLED
		if (!people_going_down.empty()) {
			cout << "Elevator 2 on floor " << elevators[1].getFloor() << " is  will handle the down calls.\n\n" << endl;
			elevators[1].elevator_moving(people_going_down);
		}
	}
	//IF PEOPLE ARE GOING UP AND ELEVATOR 1 PROXIMITY IS LOWER THAN ELEVATOR 1,ELEVATOR 2 WILL GO FIRST AND TAKE UP CALLS
	else if (!people_going_up.empty() && (elevators[1].get_Response_Up() < elevators[0].get_Response_Up())) {
		cout << "Elevator 2 on floor " << elevators[1].getFloor() << " is closer and will handle the up calls.\n\n" << endl;
		elevators[1].elevator_moving(people_going_up);
		//IF THE  PEOPLE GOING DOWN VECTOR IS FILLED
		if (!people_going_down.empty()) {
			cout << "Elevator 1 on floor " << elevators[0].getFloor() << " is  will handle the down calls.\n\n" << endl;
			elevators[0].elevator_moving(people_going_down);
		}
	}
	//IF ELEVATOR 1 AND 2 ARE ON THE SAME FLOOR
	else if (!people_going_up.empty() && (elevators[0].get_Response_Up() == elevators[1].get_Response_Up())){
		cout << "Elevators are on the same floor. Elevator 1 will move first and will handle the up calls.\n\n" << endl;
		elevators[0].elevator_moving(people_going_up);

		if (!people_going_down.empty()) {
			cout << "Elevator 2 on floor " << elevators[1].getFloor() << " is will handle the down calls.\n\n" << endl;
			elevators[1].elevator_moving(people_going_down);
		}
	}
	//IF THERE ARE  ONLY DOWN CALLS AND ELEVATOR 1 IS CLOSER
	else if (people_going_up.empty() && (elevators[0].get_Response_Down() < elevators[1].get_Response_Down())) {
		cout << "Elevator 1 on floor " << elevators[0].getFloor() << " is closer and will handle the down calls.\n\n" << endl;
		elevators[0].elevator_moving(people_going_down);
		
	}
	//IF THERE ARE  ONLY DOWN CALLS AND ELEVATOR 2 IS CLOSER
	else if (people_going_up.empty() && (elevators[1].get_Response_Down() < elevators[0].get_Response_Down())) {
		cout << "Elevator 2 on floor " << elevators[1].getFloor() << " is closer and will handle the down calls.\n\n" << endl;
		elevators[1].elevator_moving(people_going_down);
		
		
	}
	//IF THERE ARE  ONLY DOWN CALLS AND BOTH ARE ONE THE SAME FLOOR
	else if (people_going_up.empty() && (elevators[0].get_Response_Down() == elevators[1].get_Response_Down())) {
		cout << "Elevators are on the same floor. Elevator 1 will move first and will handle the down calls.\n\n" << endl;
		elevators[0].elevator_moving(people_going_down);

		
	}
	return 0;
}