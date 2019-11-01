#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<time.h>
#include "Header.h"




using namespace std;


int main()
{
	int wheelTime = 0;
	//Intro Choices
	int numberElevators;
	int numberPeople;
	
	

	cout << "Welcome to the elevator sim\n";
	cout << "How many elevators are in the building: ";
	cin >> numberElevators;
	cout << "\nHow many people will there be: ";
	cin >> numberPeople;

	vector<int> waitTimes;
	vector<Elevator> elevators;
	vector<Person> people;           //ALL THE PEOPLE 
	vector<Person> people_going_up;  // ALL THE PEOPLE GOING UP
	vector<Person> people_going_down;//ALL THE PEOPLE GOING Down
	vector<Person> requesters;       //People requesting

									
	SceneCreator(numberElevators, numberPeople, elevators, people); /// MAKES SCENE
	
	displayPeople(people);
	


	//Loops past time limit to finish getting people where there going
	cout << "\nStarting simulation\n";
	while (wheelTime < 60)
	{
		wheeloTime(elevators, people, wheelTime, requesters, waitTimes);
		



		

		//passrequester instead
		if (!requesters.empty())
		{
			//Sorting Requesters in ascending order
			oragizedRequester(requesters);
			

			//Separtes the up requesters from the down
			oraganizeUpDown(requesters, people_going_up, people_going_down, wheelTime);


			//Decides if the closer elevator needs to switch from picking up people going up or down
			switcherO(elevators, requesters);
			if (!people_going_up.empty())
			{
				//Sets the person with the lowest start floor as a comparing number 
				oraganizeEmptyU(elevators, people_going_up);
			}
			if (!people_going_down.empty())
			{
				//Sets the person with the highest start floor as a comparing number
				oraganizeEmptyD(elevators, people_going_down);
			}
			
			cout << "\n****************\n";
			//Decsion to make on which people to pick up first, who to pick up on the way , and who needs to wait
			decidingU(elevators, people_going_up, requesters);
			decidingD(elevators, people_going_down, requesters);
		}
		else
		{
			cout << "\nNo People at this time\n";
		}



		
		

	}

	cout << "\n\nSimulation Over\n\nAverage Wait time: " << averagewaitTime(waitTimes, numberPeople) <<"seconds\n\nThank You\n\n";
	
	return 0;
}