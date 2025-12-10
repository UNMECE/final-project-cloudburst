#include "acequia_manager.h"
#include <iostream>
#include <cmath>
using namespace std;

//WATER LEVEL AND WATER CAPACITY IS IN THOUSAND OF GALLONS I.E: 36 is 36000 gallons flow rate of 1, is 3600 gallons per hour = 3.6

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
        // cout << "\n" << "FLOWRATE: " << flowRate << "\n" << endl;
        return flowRate;
}

/*When the simulation has the exact even amount of water need to water level, it says the simulation was not solved,
* even though the water needs are met. Meaning the water levels are at the exact water need.*/

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

                                /*SOME LOGIC TO LOOK INTO:
                * Have a beginning if statement to test which region has the lowest water difference(need-level)
                * This means that the region with the most water will have the most positive water diff.
                * Based off of this send it into a general if statement to send water to the region with the least amount of water.
                * This will basically run through a loop always sending water to the lowest, and it'll eventually even out all of their differences between their need. */

                // water_diff[0] = north
                // water_diff[1] = south
                // water_diff[2] = east

                int a = 0;

                for(int i = 1; i < 3; ++i) {

                        if (water_diff[i] > water_diff[a]) {
                                a = i;
                        }
                }
                double tempFlowRate = 0, tempDiff = 0, beforeFlowRate = 0;
                double mainDiff = 0, finalFlow = 0, preSet = 0;

                switch (a){
                        case 0: // NORTH HAS MOST WATER OR IS CLOSEST TO ITS NEED
                        {
                                if(water_diff[1] < water_diff[2])  // South Has Least Amount
                                {
                                        // North to South
                                        canals[0]->setFlowRate(findFlowRate(water_diff[0],water_diff[1]));

                                        // cout << " Case 0 NS" << endl;
                                }
                                else if(water_diff[2] < water_diff[1]) // East Has Least Amount
                                {
                                        // North to East
                                        canals[2]->setFlowRate(findFlowRate(water_diff[0],water_diff[2]));

                                        // cout << " Case 0 NE" << endl;
                                }
                                else if(water_diff[1]==water_diff[2]) //East and South Equal Differences
                                {
                                        mainDiff = abs(water_diff[0] - water_diff[1]);

                                        finalFlow = mainDiff/3;

                                        if(finalFlow == 0)
                                        {
                                                finalFlow = 0;
                                        }
                                        else if(finalFlow >= 3.6)
                                        {
                                                finalFlow = 1;
                                        }
                                        else
                                        {
                                                finalFlow = finalFlow/3.6;
                                        }

                                        // North to South and East
                                        canals[0]->setFlowRate(finalFlow);
                                        canals[2]->setFlowRate(finalFlow);
                                        // cout << " Case 0 NSE" << endl;
                                }
                                break;
                        }
                        case 1: // OUTH HAS MOST WATER OR IS CLOSEST TO ITS NEED
                        {
                                if(water_diff[0] < water_diff[2])  //North Has Least Amount
                                {
                                        // South To North
                                        canals[1]->setFlowRate(findFlowRate(water_diff[1], water_diff[0]));
                                        canals[3]->setFlowRate(findFlowRate(water_diff[1], water_diff[0]));
                                    
                                        // cout << " Case 1 SN" << endl;
                                }
                                else if(water_diff[2] < water_diff[0]) //East Has Least Amount
                                {
                                        //South To East
                                        canals[1]->setFlowRate(findFlowRate(water_diff[1], water_diff[2]));

                                        // cout << " Case 1 SE" << endl;
                                }
                                else if(water_diff[2] == water_diff[0])
                                {

                                        // IF COMMENTED OUT CODE WORKS REMOVE ELSE IF ^ AND USE THIS: mainDiff = abs(water_diff[1] - beforeFlowRate);
                                        // AND CODE IN THIS ELSE IF

                                        mainDiff = abs(water_diff[1] - water_diff[0]);

                                        finalFlow = mainDiff/3;

                                        if(finalFlow == 0)
                                        {
                                                finalFlow = 0;
                                        }
                                        else if(finalFlow >= 3.6)
                                        {
                                                finalFlow = 1;
                                        }
                                        else
                                        {
                                                finalFlow = finalFlow/3.6;
                                        }

                                        preSet = finalFlow * 2;

                                        if(preSet > 1)
                                        {
                                                preSet = 1;
                                        }

                                        // South to North and East
                                        canals[1]->setFlowRate(preSet);
                                        canals[3]->setFlowRate(finalFlow);
                                        // cout << " Case 1 SNE" << endl;
                                }
                                break;
                        }
                        case 2: // EAST HAS MOST WATER OR IS CLOSEST TO ITS NEED
                        {
                                if(water_diff[1] < water_diff[0])  // South Has Least Amount
                                {
                                        // East to South
                                        canals[3]->setFlowRate(findFlowRate(water_diff[2], water_diff[1]));
                                        canals[0]->setFlowRate(findFlowRate(water_diff[2], water_diff[1]));

                                        // cout << " Case 2 ES" << endl;
                                }
                                else if(water_diff[0] < water_diff[1]) //North Has Least Amount
                                {

                                        // East to North
                                        canals[3]->setFlowRate(findFlowRate(water_diff[2], water_diff[0]));

                                        // cout << " Case 2 EN" << endl;
                                }
                                else if(water_diff[0] == water_diff[1])
                                {

                                        // IF COMMENTED OUT CODE WORKS REMOVE ELSE IF ^ AND USE THIS: mainDiff = abs(water_diff[2] - beforeFlowRate);
                                        // AND CODE IN THIS ELSE IF

                                        mainDiff = abs(water_diff[2] - water_diff[0]);

                                        finalFlow = mainDiff/3;

                                        if(finalFlow == 0)
                                        {
                                                finalFlow = 0;
                                        }
                                        else if(finalFlow >= 3.6)
                                        {
                                                finalFlow = 1;
                                        }
                                        else
                                        {
                                                finalFlow = finalFlow/3.6;
                                        }

                                        preSet = 2 * finalFlow;

                                        if(preSet > 1)
                                        {
                                                preSet = 1;
                                        }

                                        // East to North and South
                                        canals[0]->setFlowRate(finalFlow);
                                        canals[3]->setFlowRate(preSet);
                                        //cout << " Case 2 ENS" << endl;
                                }
                                break;
                        }
                }
                
                /*
                cout << "\n" << endl;
                cout << "North: " << water_diff[0] << endl;
                cout << "South: " << water_diff[1] << endl;
                cout << "East: " << water_diff[2] << endl;
                */
                
                manager.nexthour();
                canals[0]->setFlowRate(0);
                canals[1]->setFlowRate(0);
                canals[2]->setFlowRate(0);
                canals[3]->setFlowRate(0);
                cout << "\n" << endl;
        }

        for (int i = 0; i < 4; i++){
                canals[i]->toggleOpen(false);
        }
}
