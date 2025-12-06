#include "acequia_manager.h"
#include <iostream>
using namespace std;

/*Instructions for this problem:

	The intend of this project is to simulate water management conservation principles in the context of New Mexico

	In this simulation, there exists several Regions (North, South, etc.). Each region class includes both:
	- a given water level
	- a given water need
	- a indicator boolean for if the region is flooded
	- an indicator boolean for if the region is in drought

	With each region, there are given waterSources provided (perhaps a .dat file list each waterSource to  a region) 
	and certain waterSources have canals connected to them to deliver water across regions.

	Given the current state of the region, students wil be asked to utlize the canals that connect regions to
	develop the logic and algorithm for finding a solution. The simulation has a fixed time



	The student solution will be evaluated on the criteria that each region meets the following:
	- a given region is NOT flooded
	- a given region is NOT in drought
	- the region waterNeed does not exceed the region waterLevel 
*/

/*This will be how the solveProblems function is set up. The student may enter their on  */
/*
void solveProblems(AcequiaManager& manager)
{
	//the student can call the members of the canals object such as name of canal. sourceRegion, and destinationRegion
	//This could be helpful in informing the students strategy to solve the problem
	auto canals = manager.getCanals();
	//students may call to get Region and WaterSource objects to inform decisions 


	while(!manager.isSolved && manager.hour!=manager.SimulationMax)
	{	
		//enter student code here


		manager.nexthour();
	}
}
*/


/*example 2 format*/
/*
void solveProblems(AcequiaManager& manager)
{
	auto canals = manager.getCanals();
	while(!manager.isSolved && manager.hour!=manager.SimulationMax)
	{
	//Students will implement this function to solve the probelms
	//Example: Adjust canal flow rates and directions
		if(manager.hour==0)
		{
			canals[0]->setFlowRate(1);
			canals[0]->toggleOpen(true);
		}
		else if(manager.hour==1)
		{
			canals[1]->setFlowRate(0.5);
			canals[1]->toggleOpen(true);
		}
		else if(manager.hour==82)
		{
			canals[0]->toggleOpen(false);
			canals[1]->toggleOpen(false);
		}
	//student may add any necessary functions or check on the progress of each region as the simulation moves forward. 
	//The manager takes care of updating the waterLevels of each region and waterSource while the student is just expected
	//to solve how to address the state of each region

		
		manager.nexthour();
	}
}
*/

/*example 2*/
/*
void solveProblems(AcequiaManager& manager)
{
	auto canals = manager.getCanals();
	while(!manager.isSolved && manager.hour!=manager.SimulationMax)
	{
	//Students will implement this function to solve the probelms
	//Example: Adjust canal flow rates and directions
		if(manager.hour==1)
		{
			canals[0]->setFlowRate(0.1);
			canals[0]->toggleOpen(true);
			canals[1]->setFlowRate(0.2);
			canals[1]->toggleOpen(true);
		}
		else if(manager.hour==3)
		{
			canals[0]->toggleOpen(false);
			canals[1]->toggleOpen(false);
		}
	//student may add any necessary functions or check on the progress of each region as the simulation moves forward. 
	//The manager takes care of updating the waterLevels of each region and waterSource while the student is just expected
	//to solve how to address the state of each region

		
		manager.nexthour();
	}
}
*/


//In this solution, students can make functions that aid in identifying the best course of action for moving
//water resources. They can set conditions that then work on the canal vectors based on the information reported

//This can help in optimizing solutions for dynamic constraints such as weather (rain, or dried up waterSources) and
//make the solution to the problem more abstract, allowing the logic and algorithm to be the sole priority of the student
//while the computation is left for the Acequia Manager

//This would be the perfect opportunity to identify the tools learned from ECE 231L such as:
//data structures (stacks, queues, trees(?)), templates, vector class functions, etc... to aid in the algorithm solution

//WATER LEVEL AND WATER CAPACITY IS IN THOUSAND OF GALLONS I.E: 36 is 36000 gallons flow rate of 1, is 3600 gallons per hour = 3.6

int findCanal(std::vector<Canal *> canals, std::string region)
{
	int match;
	for(int i = 0; i< canals.size();i++)
	{
		if(canals[i]->sourceRegion->name == region)
		{
			match = i;
		}
	}
	return match;
}

void release(std::vector<Canal *> canals, std::string region)
{
	int match = findCanal(canals, region);
	canals[match]->toggleOpen(true);
	canals[match]->setFlowRate(1);
	return;
}

void close(std::vector<Canal *> canals, std::string region)
{
	int match = findCanal(canals, region);
	canals[match]->toggleOpen(false);
}


void solveProblems(AcequiaManager& manager)
{

	bool check = false;
	auto canals = manager.getCanals();
	auto regions = manager.getRegions();

	while(!manager.isSolved && manager.hour!=manager.SimulationMax)
	{
		double northLevel = regions[0]->waterLevel;
		double northNeed = regions[0]->waterNeed;
		double northCapacity = regions[0]->waterCapacity;

		double southLevel = regions[1]->waterLevel;
		double southNeed = regions[1]->waterNeed;
		double southCapacity = regions[1]->waterCapacity;


		double eastLevel = regions[2]->waterLevel;
		double eastNeed = regions[2]->waterNeed;
		double eastCapacity = regions[2]->waterCapacity;

		double north_diff = northLevel - northNeed;
		double east_diff = eastLevel - eastNeed;
		double south_diff = southLevel - southNeed;
		
		canals[1]->toggleOpen(true);
		canals[1]->setFlowRate(1);

		cout << northLevel << endl;
		cout << southLevel << endl;
		cout << eastLevel << endl;

		if(regions[0]->isInDrought == true && east_diff < south_diff)
		{
			
		}
		else if(regions[0]->isInDrought == true && south_diff < east_diff)
		{
		
		}

		if(regions[1]->isInDrought == true && north_diff < east_diff)
		{

		}
		else if(regions[1]->isInDrought == true && east_diff < north_diff)
		{

		}

		if(regions[2]->isInDrought == true && north_diff < south_diff)
		{

		}
		else if(regions[2]->isInDrought == true && south_diff < north_diff)
		{
		
		}


		if(regions[0]->isFlooded == true && east_diff < south_diff)
		{
			
		}
		else if(regions[0]-> isFlooded == true && south_diff < east_diff)
		{
		
		}

		if(regions[1]-> isFlooded == true && north_diff < east_diff)
		{

		}
		else if(regions[1]-> isFlooded == true && east_diff < north_diff)
		{

		}

		if(regions[2]-> isFlooded == true && north_diff < south_diff)
		{

		}
		else if(regions[2]-> isFlooded == true && south_diff < north_diff)
		{
		
		}
		
			// Region Difference check for loop
		/*for (int i = 0; i < regions.size(); ++i){
			if(regions[i]->isInDrought == true)
			{
				
			} 
			else if (regions[i]->isFlooded == true)
			{
				regions[i]->name;	
			}
			
		}*/
		
		if(northLevel <= northNeed){
			
		}
		
		if(manager.hour == 0)
		{
			for(int i = 0; i<canals.size(); i++)
			{
				canals[i]->toggleOpen(true);
				canals[i]->setFlowRate(1);
			}
		}

		for(int i =0 ; i<regions.size(); i++)
		{
			if(regions[i]->isFlooded == true)
			{
				//release water from that region by a canal
				release(canals, regions[i]->name);
			}
			else if(regions[i]->isInDrought = true)
			{
				//find canal to move water
				
				// close();
			}

			else if(regions[i]->isFlooded == true && regions[i]->isInDrought == true)
			{
				close(canals, regions[i]->name);
			}
		}
		
		manager.nexthour();
	}
}


double findFlowRate(double waterLevel, double waterNeed)
{
	double flowRate;
	double waterDifference = abs(waterLevel-waterNeed);
	
	if(waterDifference <= 0)
	{
		flowRate = 0;
	}
}