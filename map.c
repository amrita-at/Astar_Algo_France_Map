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


#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "map.h"
#include "list.h"


//creating the city
City* createCity( )
{
    City* nCity = ( City* )malloc( sizeof( City ) );
    nCity->name = ( char* )malloc( MAX_LENGTH  );
    nCity->backptr = 0;
    nCity->g = 0;
    nCity->h = 0;
    nCity->lat = 0;
    nCity->lon = 0;
    nCity->neighbour = 0;
    return nCity;
}

//creating neighbours
Neighbour* createNeighbour( )
{
    Neighbour* nNeighbour = ( Neighbour* )malloc( sizeof( Neighbour ) );
    nNeighbour->name = ( char* )malloc( MAX_LENGTH );
    nNeighbour->distance = 0;
    return nNeighbour;

}

//comparing the two given cities
static int compareCities(void * c1, void * c2)
{

    City* firstCity = ( City* )c1;
    City* secondCity = ( City* )c2;
    return strcasecmp( firstCity->name, secondCity->name  );
}

//comparing the cost of the cities
static int compareCityDistance(void * c1, void * c2)
{

    City* firstCity = ( City* )c1;
    City* secondCity = ( City* )c2;
    if ( firstCity->g == secondCity->g )
    {
        return 0;
    }
    else if ( firstCity->g < secondCity->g )
    {
        return -1;
    }

    return 2 ;
}

//returns the city name and it's g value for computation
static void getCity( void * c )
{
    printf(" %s :\n",( ( City* )c )->name );
    printf(" %d :\n",( ( City* )c )->g );
}

//compares the neighbour cities
static int compareNeighbours( void * c1, void * c2 )
{
    return strcmp( ( ( Neighbour* )c1 )->name, ( ( ( Neighbour* )c2 )->name ) );
}

//returns the neighbour name and the distance
static void getNeighbour( void * c )
{
    printf(" %s :\n",( ( Neighbour* )c )->name );
    printf(" %d:\n",( ( Neighbour* )c )->distance );
}

//checking if the city exists in the list or not
City* findCity( List* cityList, char* name )
{
    Node* currentNode = cityList->head;
    while( currentNode )
    {
        City* curCity = ( City* )currentNode->val;
        if( strcasecmp( curCity->name, name ) == 0)
        {
            return curCity;
        }
        currentNode = currentNode->next;
    }
    return 0;
}

//calculating the value of h with the given formula
static int calculate_heuristic_cost( City* startCity, City* endCity )
{
    return ( abs( startCity->lat - endCity->lat ) + abs( startCity->lon - endCity->lon ) ) / 4;
}


//calculating the city with smallest 'f' cost
static City* getSmallestFValueCity( List* openList )
{
    Node* currentNode = openList->head;
    if( !currentNode )
    {
        return 0;
    }

    City* smallestFCity = ( City* )currentNode->val;
    int smallestFvalue = smallestFCity->g + smallestFCity->h;
    currentNode = currentNode->next;

    while( currentNode )
    {
        City* currCity = ( City* )currentNode->val;
        if( smallestFvalue > ( currCity->g + currCity->h ) )
        {
            smallestFCity = currCity;
        }
        currentNode = currentNode->next;
    }
    return smallestFCity ;
}

//Displaying the final calculated path
static void displayResults( City* currentCity )
{
    List* distanceList = newList( compareCityDistance, getCity );
    while( currentCity )
    {
        addListAt( distanceList, 1, currentCity );
        currentCity = currentCity->backptr;
    }
    displayList(distanceList);
    delList(distanceList);
}

//reading from the text file of MAP, the cities and its neighbours
List* readMapFile( char*  filename )
{
    FILE* fileptr;

    // opening file in read mode
    fileptr = fopen( filename, "r" );

    if( !fileptr )
    {
        return 0;
    }

    List* cityList = newList( compareCities, getCity );
    char* cityName = ( char* )malloc(MAX_LENGTH);
    City* newCity = 0;

    // reading each line from FRANCE.MAP File
    while ( !feof ( fileptr ) )
    {

        int nLat=-1;
        int nLon=-1;
        fscanf( fileptr, "%s %d %d", cityName, &nLat, &nLon );
        if( -1 != nLon )
        {
            if( 0 != newCity )
            {
                addList( cityList, newCity );
            }
            newCity = createCity();
            newCity->neighbour = newList( compareNeighbours, getNeighbour );
            strncpy( newCity->name, cityName, MAX_LENGTH );
            newCity->lat = nLat;
            newCity->lon = nLon;
        }
        else if( 0 != newCity )
        {
            Neighbour* neighbour = 0;
            neighbour = createNeighbour();
            strncpy( neighbour->name, cityName, MAX_LENGTH );
            neighbour->distance = nLat;
            addList( newCity->neighbour, neighbour );
        }
    }
    if( 0 != newCity )
    {
        addList( cityList, newCity );
    }
    fclose( fileptr );
    return cityList;
}

status calculatePath( List* cityList, char* sourceCity, char* destCity )
{

    City* startCity = findCity( cityList, sourceCity );
    City* goalCity = findCity( cityList, destCity );

    /* returns 1 if the cityList or the cities in the list does not exist.*/
    if( !cityList || !startCity || !goalCity )
    {
        return 1;
    }

    List* closedList = newList( compareCities, getCity );

    List* openList = newList( compareCities, getCity );

    // the cost of travelling from start point to start is zero.
    startCity->g = 0;
    startCity->h = calculate_heuristic_cost( startCity, goalCity );

    // adding start city to open list
    addList( openList, startCity );

    //looping all the cities in open list
    while( lengthList( openList ) > 0 )
    {
        City* currentCity = getSmallestFValueCity( openList );
        remFromList( openList, currentCity );
        addList( closedList, currentCity );

        if( cityList->comp( currentCity, goalCity ) == 0  )
        {
            //displaying the final solution list
            displayResults( currentCity );
            break;
        }

        Node* neighbourNode = currentCity->neighbour->head;
        while( neighbourNode )
        {
            Neighbour* nextNeighbour = ( Neighbour* )neighbourNode->val;
            City* sucCity = findCity( cityList, nextNeighbour->name );
            int sucNodeCost = currentCity->g + nextNeighbour->distance;
            City* nodeSuc = findCity( openList, sucCity->name );
            if( nodeSuc!=0 )
            {
                if( sucNodeCost >= nodeSuc->g )
                {
                    neighbourNode = neighbourNode->next;
                    continue;
                }
                remFromList( openList, sucCity );
            }
            nodeSuc = findCity( closedList, sucCity->name );
            if( nodeSuc != 0 )
            {
                /* if successor city is on the CLOSED list but the existing
                successor is shorter or better then continue as it is */
                if( sucNodeCost >= nodeSuc->g )
                {
                    neighbourNode = neighbourNode->next;
                    continue;
                }
                remFromList( closedList, sucCity );
            }

            // Set the parent of successor city as current city
            sucCity->backptr = currentCity;

            // set g value of successor city  as a new successor Node Cost
            sucCity ->g = sucNodeCost;

            /* Set h to be the estimated distance to goal city applying the heuristic function */
            sucCity->h = calculate_heuristic_cost( sucCity, goalCity );
            addList( openList, sucCity );
            neighbourNode = neighbourNode->next;
        }

    }
    delList( openList );
    delList( closedList );
    return OK;
}


