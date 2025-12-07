#include "acequia_manager.h"
#include <iostream>
#include <cmath>
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

void release(std::vector<Canal *> canals, std::string region, double flowRate)
{
	int match = findCanal(canals, region);
	canals[match]->toggleOpen(true);
	canals[match]->setFlowRate(flowRate);
	return;
}

void close(std::vector<Canal *> canals, std::string region)
{
	int match = findCanal(canals, region);
	canals[match]->toggleOpen(false);
}

double findFlowRate(double waterDiff1, double waterDiff2)
{
	double flowRate;
	double waterDifference = abs(waterDiff1-waterDiff2);
	
	flowRate = waterDifference/2;

	if(flowRate==0)
	{
		flowRate = 0;
	}
	else if(flowRate >= 3.6)
	{
		flowRate = 1;
	}
	else
	{
		flowRate = flowRate/3.6;
	}

	return flowRate;
}

void floodResponse(vector<Canal *> canals, int region_index, vector<double> water_diff){

	/*  
	North Diff = 0 
	South Diff = 1 
	East Diff = 2
	*/
	
	if(region_index == 0 && water_diff[2] < water_diff[1]) //  East < South
	{
		canals[0]->setFlowRate(findFlowRate(water_diff[0], water_diff[1])); // Canal: N to S
		canals[2]->setFlowRate(0);
	}
	else if(region_index == 0 && water_diff[1] < water_diff[2]) // South < East
	{
		canals[2]->setFlowRate(findFlowRate(water_diff[0], water_diff[2])); // Canal: N to E
		canals[0]->setFlowRate(0);
	}

	if(region_index == 1 && water_diff[0] < water_diff[2]) // North < East
	{
		canals[1]->setFlowRate(findFlowRate(water_diff[1], water_diff[2])); // Canal: S to E
		canals[3]->setFlowRate(0);
		
	}
	else if(region_index == 1 && water_diff[2] < water_diff[0]) // East < North
	{
		canals[1]->setFlowRate(findFlowRate(water_diff[1], water_diff[2])); // Canal: S to E
		canals[3]->setFlowRate(findFlowRate(water_diff[1], water_diff[2])); // Canal: E to N
	}

	if(region_index == 2 && water_diff[0] < water_diff[1]) // North < South
	{
		canals[3]->setFlowRate(findFlowRate(water_diff[2], water_diff[0])); // Canal: E to N
		canals[0]->setFlowRate(findFlowRate(water_diff[2], water_diff[0])); // Canal: N to S
	}
	else if(region_index == 2 && water_diff[1] < water_diff[0]) // South < North
	{
		canals[3]->setFlowRate(findFlowRate(water_diff[2], water_diff[0])); // Canal: E to N
		canals[0]->setFlowRate(0);
	}
}

// droughtResponce(): Similar to floodResponce(), but wth each region, checks if it's in drought.
// If true, check which region has the most water and requests water from that region.

// Need a way to lock in setting made to certain canals so they are not changed again by future functions.

void solveProblems(AcequiaManager& manager)
{

	bool check = false;
	auto canals = manager.getCanals();
	auto regions = manager.getRegions();

	double northNeed = regions[0]->waterNeed;
	double northCapacity = regions[0]->waterCapacity;

	double southNeed = regions[1]->waterNeed;
	double southCapacity = regions[1]->waterCapacity;

	double eastNeed = regions[2]->waterNeed;
	double eastCapacity = regions[2]->waterCapacity;


	for (int i = 0; i < 4; i++){
		canals[i]->toggleOpen(true);
	}

	while(!manager.isSolved && manager.hour!=manager.SimulationMax)
	{
		double northLevel = regions[0]->waterLevel;

		double southLevel = regions[1]->waterLevel;

		double eastLevel = regions[2]->waterLevel;

		/*  North Diff = 0 
			South Diff = 1 
			East Diff = 2
		*/
		
		vector<double> water_diff;
		water_diff.push_back(northLevel - northNeed);
		water_diff.push_back(southLevel - southNeed);
		water_diff.push_back(eastLevel - eastNeed);

		// If South has more water than needed, and North AND East need water,
		// send South's excess water to East
		if (water_diff[1] >= 3.6 && water_diff[0] < 0 && water_diff[2] < 0) {
			canals[1]->setFlowRate(1);
		}
		else if (water_diff[1] < 3.6 && water_diff[1] > 0 && water_diff[0] < 0 && water_diff[2] < 0) {
			canals[1]->setFlowRate(water_diff[1] / 3.6); // Canal: S to E
		}
		// Else, if South has less water than needed AND North and water to spare,
		// send North's excess water to South
		else if (water_diff[1] < 0 && water_diff[0] > 0) {
			canals[0]->setFlowRate(findFlowRate(water_diff[1], water_diff[0])); // Canal: N to S
		}
		// Else, if South's water is at water needed or North has no water to spare,
		// set flow rates and canals 0 and 1 to 0
		else {
			canals[0]->setFlowRate(0);
			canals[1]->setFlowRate(0);
		}

		// If North has more water than needed, and East need water,
		// send North's excess water to East
		if (water_diff[0]>= 3.6 && water_diff[2] < 0) {
			canals[2]->setFlowRate(1);
		}
		else if (water_diff[0] < 3.6 && water_diff[0] > 0 && water_diff[2] < 0) {
			canals[2]->setFlowRate(water_diff[0] / 3.6); // N to E
		}
		// Else, if North has less water than needed AND East has and water to spare,
		// send East's excess water to North
		else if (water_diff[0] < 0 && water_diff[2] > 0) {
			canals[3]->setFlowRate(findFlowRate(water_diff[1], water_diff[0])); // Canal: N to S
		}
		// Else, if North's water is at water needed or East has no water to spare,
		// set flow rates and canals 2 and 3 to 0
		else {
			canals[2]->setFlowRate(0);
			canals[3]->setFlowRate(0);
		}
		
		// For loop: If region is in drought,
		// find the region with the most water, regardless of whether it has excess water to spare,
		// and give water to region in drought.
		double mostWater = water_diff[0]; 
		if (water_diff[0] < 0 && water_diff[1] < 0 && water_diff[2] < 0){
			
			for (int i = 0; i < 3; i++){
				if(mostWater < water_diff[i]){
					mostWater = water_diff[i];
				}
			}
			
			if (mostWater == water_diff[0]){
				canals[0]->setFlowRate(1);
			}
			else if (mostWater == water_diff[1]){
				canals[1]->setFlowRate(1);
			}
			else if (mostWater == water_diff[2]){
				canals[3]->setFlowRate(1);	
			}
			
		}


		// Flow Rate Debug
		/*
		canals[1]->toggleOpen(true);
		canals[1]->setFlowRate(1);

		cout << northLevel << endl;
		cout << southLevel << endl;
		cout << eastLevel << endl;
		*/

		/*
		if(water_diff[2] < water_diff[1])
		{
			
		}
		else if(water_diff[1] < water_diff[2])
		{
		
		}

		if(water_diff[0] < water_diff[2])
		{

		}
		else if(water_diff[2] < water_diff[0])
		{

		}

		if(water_diff[0] < water_diff[1])
		{

		}
		else if(water_diff[1] < water_diff[0])
		{
		
		}
		*/
		
		/*for(int i = 0; i < regions.size(); i++){
			if(regions[i]->isFlooded){
				floodResponse(canals, i, water_diff);
			}
		}*/

		
		
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
		/*
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
		*/
		manager.nexthour();
	}

	for (int i = 0; i < 4; i++){
		canals[i]->toggleOpen(false);
	}
}


