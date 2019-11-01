#include<algorithm>
class Person    //People requesting and getting on elevator
{
private:
	int personID;
	int startTime;
	int startingFloor;
	int desiredFloor;
	bool goingUp;
	int waitTime;
	



public: // setters and getters for variables
	Person()//Default constructor
	{
		personID = 0;
		 startTime = 0;
		 startingFloor = 0;
		 desiredFloor = 0;
		 goingUp = false;
		 waitTime = 0;
		

	}
	Person(int personid,int starttime, int startfloor, int desiredfloor )
	{
		personID = personid;
		startTime = starttime;
		startingFloor = startfloor;
		desiredFloor = desiredfloor;
		
		
		
	}
	void setDirection(bool direction)
	{
		goingUp = direction;
	}

	bool getDirection()
	{
		return goingUp ;
	}

	int getPersonID()
	{
		return personID;
	}

	int getStartTime()
	{
		return startTime;

	}

	int getStartingFloor()
	{
		return startingFloor;

	}

	int getDesiredFloor()
	{
		return desiredFloor;
	}


	int getTime()  // Figure out Wait times there has to be a way to explain efficiency
	{
		return waitTime;
	}

};