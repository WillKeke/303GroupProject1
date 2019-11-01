#pragma once
#include<iostream>
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
	bool button;
	bool onE;



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
	Person(int personid, int starttime, int startfloor, int desiredfloor)
	{
		personID = personid;
		startTime = starttime;
		startingFloor = startfloor;
		desiredFloor = desiredfloor;
		button = false;
		onE = false;


	}

	//All Setters and getters for person
	void setDirection(bool direction)
	{
		goingUp = direction;
	}
	
	bool getDirection()
	{
		return goingUp;
	}

	int getPersonID()
	{
		return personID;
	}

	int getStartTime()
	{
		return startTime;

	}
	void setonE(bool but)
	{
		onE = but;
	}
	bool getonE()
	{
		return onE;
	}
	int getStartingFloor()
	{
		return startingFloor;

	}

	int getDesiredFloor()
	{
		return desiredFloor;
	}


	int getTime()   
	{
		return waitTime;
	}
	bool getbutton()
	{
		return button;
	}
	void setbutton(bool but)
	{
		button = but;
	}

};