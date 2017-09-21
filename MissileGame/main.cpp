/// <summary>
/// Author: Eoin Abbey-Maher
/// Date: 14/09/17
/// Game to launch a missile
/// Known Bugs:
///  Can enter coordinates larger than the Maximum generated,
///  If User inputs a Letter Program crahses
/// </summary>

#include <iostream>
#include <ctime>
#include "missile.h"

//Setting use for the standard Library Namespace
using namespace std;

//Finctions to be run within the program
void mainMenu(); //Main Menu FOr Choices
void launchSequence(); //Input of main menu selection and Switch statement to deal with main menu
void missileSelect(); //Selecting the warhead
void randomiseTarget(); //Get random coordinates for the target 
void InputCode(); //Input missile launch code
void armMissile(); //Arm the missile for launch
void collision(); //Launch the missile and see if it hits

Missile missile; //Create Missile Object

//Number to keep track of which step user is on
int processNum{ 0 };

//Entry point
int main()
{
	srand((unsigned)time(0));

	mainMenu();
	system("pause");
	return 1;
}

//Main Menu Shown in Console Window
void mainMenu()
{
	cout << "1. Select Warhead" << endl;
	cout << "2. Aqcuire Target" << endl;
	cout << "3. Insert the Launch Code" << endl;
	cout << "4. Arm the Missile" << endl;
	cout << "5. Launch The Missile" << endl;
	cout << endl;
	cout << "Input The step your on" << endl;
	launchSequence();
}

//Input selection number and Switch statement to control the users choices
void launchSequence()
{
	int choiceNum{ 0 };
	cin >> choiceNum;

	switch (choiceNum)
	{
	//Step to select the warhead
	case 1: 
		if (processNum == 0)
		{
			system("cls");
			missileSelect();
		}
		else if (processNum != 0)
		{
			cout << "This is not an available option Please select again" << endl;
			system("cls");
			mainMenu();
			launchSequence();
		}
		break;
	//Step to Acquire the target
	case 2:
		if (processNum == 1)
		{
			randomiseTarget();
		}
		else
		{
			cout << "This is not an available option Please select again" << endl;
			system("cls");
			mainMenu();
			launchSequence();
		}
		break;
	//Step to insert the Launch Code
	case 3:
		if (processNum == 2)
		{
			InputCode();
		}
		else
		{
			cout << "This is not an available option Please select again" << endl;
			system("cls");
			mainMenu();
			launchSequence();
		}
		break;
	//Step to arm the Missile
	case 4:
		if (processNum == 3)
		{
			armMissile();
		}
		else
		{
			cout << "This is not an available option Please select again" << endl;
			system("cls");
			mainMenu();
			launchSequence();
		}
		break;
	//Step to check the collision of the Missile and the Target
	case 5:
		if (processNum == 4)
		{
			collision();
		}
		else
		{
			cout << "This is not an available option Please select again" << endl;
			system("cls");
			mainMenu();
			launchSequence();
		}
		break;
	//If any number other than 1-5  is selected This is the step carried out
	default:
		cout << "This is not an available option Please select again" << endl;
		system("cls");
		mainMenu();
		launchSequence();
	}
}


void missileSelect()
{
	int missileNum{ 0 };
	cout << "Select your Warhead" << endl;
	cout << "1) Explosive (4 Digit Launch Code)" << endl << "2) Nuclear (6 Digit Launch Code)" << endl;

	cin >> missileNum;

	//Sets wether missile is Explosive or Nuclear
	switch (missileNum)
	{
		case 1: 
			//Set the missile to be explosive if the player inputs 1
			missile.payload = EXPLOSIVE;
			processNum += 1;
			cout << "Explosive Warhead has been selected" << endl;
			system("pause");
			system("cls");
			mainMenu();
			break;
		//Set the missile to be nuclear if player inputs 2
		case 2:
			missile.payload = NUCLEAR;
			processNum += 1;
			cout << "Nuclear Warhead has been selected" << endl;
			system("pause");
			system("cls");
			mainMenu();
			break;

	default:
		break;
	}
}


void randomiseTarget()
{
	cout << "Enter Coordinates (x = 0 - 300, Y = 0 - 100) " << endl;
	cin >> missile.coordinates.x >> missile.coordinates.y; //Let User input there coordinates to aim at 

	cout << "Aquiring Target..." << endl;

	missile.target.coordinates.x = (rand() % 300) + 1; //Get a random Coordinate for Target X & Y 
	missile.target.coordinates.y = (rand() % 100) + 1;

	cout << "Target has been Aquired, Coordinates Locked in" << endl;

	system("pause");
	processNum += 1;
	system("cls");
	mainMenu();
}

//Input the launch code for the missiles
void InputCode()
{
	float launchcode{ 0 };
	if (missile.payload == WarHead::EXPLOSIVE)
	{
		cout << "Input the 4 digit Launch Code" << endl;
		cin >> launchcode;

		if (launchcode == missile.LAUNCHCODE1)
		{
			cout << "You have entered the correct launch code, Missile ready to Arm" << endl;
			system("pause");
			processNum += 1;
			system("cls");
			mainMenu();
		}
		else
		{
			cout << "You have entered An incorrect launch code, Please Try Again" << endl;
			system("pause");
			InputCode();
		}
	}
	if (missile.payload == WarHead::NUCLEAR)
	{
		cout << "Input the 6 digit Launch Code" << endl;
		cin >> launchcode;
		//if the code is right
		if (launchcode == missile.LAUNCHCODE2)
		{
			cout << "You have entered the correct launch code, Missile ready to Arm" << endl;
			system("pause");
			processNum += 1;
			system("cls");
			mainMenu();
		}
		//otherwise do this
		else
		{
			cout << "You have entered An incorrect launch code, Please Try Again" << endl;
			system("pause");
			InputCode();
		}
	}

}

void armMissile()
{
	missile.armed = false;
	
	cout << "Missile Preparing to be armed ... " << endl;

	missile.arm();

	cout << "Missile has been armed and is ready for launch" << endl;
	system("Pause");
	processNum += 1;
	system("cls");
	mainMenu();
}

void collision()
{
	cout << "Missile Launching" << endl;

	//If the Missile is Explosive
	if (missile.payload == WarHead::EXPLOSIVE)
	{
		//If the Coordinates are within 10 of the target then its a succesful hit
		if (missile.coordinates.x <= missile.target.coordinates.x + 10 || missile.coordinates.x >= missile.target.coordinates.x - 10
			&& missile.coordinates.y <= missile.target.coordinates.y + 10 || missile.coordinates.y >= missile.target.coordinates.y - 10)
		{
			cout << "You succesfully Hit the Target" << endl;
			cout << "Target was located at " << missile.target.coordinates.x << " , " << missile.target.coordinates.y << endl;
			system("Pause");
		}
		else
		{
			cout << "You missed The Target Hard Luck" << endl;
			cout << "Target was located at " << missile.target.coordinates.x << " , " << missile.target.coordinates.y << endl;
			system("Pause");
		}
	}
	
	//If the Missile coordingates are within 25 of the target Coordinates It is a succesful hit
	else if (missile.payload == WarHead::NUCLEAR)
	{
		if (missile.coordinates.x <= missile.target.coordinates.x + 25 || missile.coordinates.x >= missile.target.coordinates.x - 25
			&& missile.coordinates.y <= missile.target.coordinates.y + 25 || missile.coordinates.y >= missile.target.coordinates.y - 25)
		{
			cout << "You succesfully Hit the Target" << endl;
			cout << "Target was located at " << missile.target.coordinates.x << " , " << missile.target.coordinates.y << endl;
			system("Pause");
		}
		else
		{
			cout << "You missed The Target Hard Luck" << endl;
			cout << "Target was located at " << missile.target.coordinates.x << " , " << missile.target.coordinates.y << endl;
			system("Pause");
		}
	}
}



