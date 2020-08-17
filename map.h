/**
    * all the operations related to the map and the graph is performed
    * creation of cities and its neighbours
    * comparing the cost of cities from one to another
    * reading from the map file i.e. FRANCE.MAP, user must pass 2 of the city names
    * calculation of h value with the provided formula for the cities
    * calculating the final path from source to destination
    * displaying the resultant path with the shortest cost between the cities
    * @AmritaTiwari
*/

#ifndef _Map_H
#define _Map_H

#include <stdlib.h>
#include "status.h"
#include "list.h"


#define MAX_LENGTH 1024

// Default file path defined
static char* mapFile = "FRANCE.MAP";

/* The struct contains the city name and its details from a Map file. */
typedef struct City
{
    char* name;
    int lon;
    int lat;
    int g;
    int h;
    List* neighbour;
    struct Cities* backptr;
} City;

// neighbours and its details.
typedef struct Neighbour
{
    char* name;
    int distance;
} Neighbour;

/**
    * function to read the map file line by line and create the list for cities and neighbours
    * @param file name for the map
    * @return the city list after reading the file line by line
    */
List* readMapFile( char* );

/**creating a new city*/
City* createCity( );

/**
    * function to check the city in the list
    * @param city list with all the city details in it
    * @param city name to be found on the list
    * @return 0 if the city is present in the list
    */
City* findCity( List*, char* );

/**creating the new neighbour*/
Neighbour* createNeighbour( );

/**
    * calculating the city with smallest f value
    * @param open list containing the source city and its neighbours
    * @return the city name with the least f value
    */
static City* getSmallestFValueCity( List* openList );

/**
    * calculating the h value of two cities with the formula
    * @param start city
    * @param the destination city
    * @return the h value calculated for the two given cities
    */
static int calculate_heuristic_cost( City* startCity, City* endCity );

/**
    * function to calculate the shortest cost path between the two cities
    * @param the list of cities from the map file
    * @param source city that is starting point
    * @param destination city that is the ending point
    * @return the displayResults function with the current city param
    */
status CalculatePath( List*, char*, char* );

/**
    * display function to display the final resultant path
    * @param the current travelling city with least cost
    * @result the result list with the route trough cities and its cost
    */
static void displayResults( City* currentCity );

#endif // _Map_H






