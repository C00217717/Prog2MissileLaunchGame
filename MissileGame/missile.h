
using namespace std;

//Enum to select Missile Type
enum WarHead
{
	EXPLOSIVE,
	NUCLEAR
};

//Coordinates For where the missile Is being launched at
typedef struct Position
{
	int x;
	int y;

	void print()
	{
		cout << x << y << endl;
	}
}Coordinates;


//Target location for where the enemy is 
typedef struct Enemy
{
	Coordinates coordinates;
}Target;


struct Missile {
	WarHead payload;
	Coordinates coordinates;
	Target target;

	//Preset Launch codes for 
	float LAUNCHCODE1{1337};
	float LAUNCHCODE2{123456};

	//If the missile is armed or not
	bool armed{ false };

	//Function to set the missile to be armed
	void arm()
	{
		if (armed)
		{
			armed = false;
		}
		else
		{
			armed = true;
		}
	}
	void update()
	{
		coordinates.x += 1;
		coordinates.y += 2;
	}

};


