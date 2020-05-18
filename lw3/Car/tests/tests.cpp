#include <iostream>
#define CATCH_CONFIG_MAIN

#include "../../../catch2/catch.hpp"
#include "../Car/Car.h"

SCENARIO("Car creation test")
{
	bool isOk = true;
	CCar car;
	if (car.IsEngineOn() || car.GetGear() != 0 || car.GetSpeed() != 0 || car.GetDirection() != CCar::Direction::None)
	{
		isOk = false;
	}

	REQUIRE(isOk);
}

SCENARIO("Check TurnOnEngine")
{
	CCar car;
	bool isOk = true;
	bool startSuccess;

	startSuccess = car.TurnOnEngine();

	if (!car.IsEngineOn() || !startSuccess)
	{
		isOk = false;
	}

	startSuccess = car.TurnOnEngine();

	if (startSuccess || !car.IsEngineOn())
	{
		isOk = false;
	}


	REQUIRE(isOk);
}

SCENARIO("Check TurnOffEngine")
{
	CCar car;
	bool isOk = true;
	bool trunOffSuccess;

	trunOffSuccess = car.TurnOffEngine();

	if (trunOffSuccess || car.IsEngineOn())
	{
		isOk = false;
	}

	car.TurnOnEngine();

	trunOffSuccess = car.TurnOffEngine();

	if (!trunOffSuccess || car.IsEngineOn())
	{
		isOk = false;
	}

	car.TurnOnEngine();

	car.SetGear(1);
	car.SetSpeed(20);

	trunOffSuccess = car.TurnOffEngine();

	if(trunOffSuccess || !car.IsEngineOn())
	{
		isOk = false;
	}



	REQUIRE(isOk);
}

SCENARIO("Check SetGear")
{
	CCar car;
	bool isOk = true;
	bool changeGearSuccess;

	changeGearSuccess = car.SetGear(1);

	if (!changeGearSuccess || car.GetGear() != 1)
	{
		isOk = false;
	}

	changeGearSuccess = car.SetGear(-1);

	if (!changeGearSuccess || car.GetGear() != -1)
	{
		isOk = false;
	}

	changeGearSuccess = car.SetGear(0);

	if (!changeGearSuccess || car.GetGear() != 0)
	{
		isOk = false;
	}


	changeGearSuccess = car.SetGear(5);

	if (changeGearSuccess || car.GetGear() == 5)
	{
		isOk = false;
	}

	changeGearSuccess = car.SetGear(6);

	if (changeGearSuccess || car.GetGear() == 6)
	{
		isOk = false;
	}

	changeGearSuccess = car.SetGear(-2);

	if (changeGearSuccess || car.GetGear() == -2)
	{
		isOk = false;
	}

	REQUIRE(isOk);
}

SCENARIO("Check SetSpeed")
{
	CCar car;
	bool isOk = true;
	bool changeSuccess;

	car.SetGear(1);
	changeSuccess = car.SetSpeed(20);

	if (!changeSuccess || car.GetSpeed() != 20)
	{
		isOk = false;
	}

	changeSuccess = car.SetSpeed(50);

	if (changeSuccess || car.GetSpeed() == 50)
	{
		isOk = false;
	}

	car.SetGear(2);
	changeSuccess = car.SetSpeed(50);

	if (!changeSuccess || car.GetSpeed() != 50)
	{
		isOk = false;
	}

	changeSuccess = car.SetSpeed(-1);

	if (changeSuccess || car.GetSpeed() == -1)
	{
		isOk = false;
	}

	REQUIRE(isOk);
}

SCENARIO("Check direction logic")
{
	CCar car;
	bool isOk = true;
	
	if (car.GetDirection() != CCar::Direction::None)
	{
		bool isOk = false;
	}

	car.SetGear(1);
	car.SetSpeed(20);

	if (car.GetDirection() != CCar::Direction::Ahead)
	{
		bool isOk = false;
	}

	car.SetSpeed(0);
	car.SetGear(-1);
	car.SetSpeed(10);

	if (car.GetDirection() != CCar::Direction::Back)
	{
		bool isOk = false;
	}

	car.SetSpeed(0);

	if (car.GetDirection() != CCar::Direction::None)
	{
		bool isOk = false;
	}


	REQUIRE(isOk);
}