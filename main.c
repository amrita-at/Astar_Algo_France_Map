/**
    * Implementation of A star algorithm to compute the
    * shortest path between the two cities in the Map.
    * @AmritaTiwari
*/


#include <stdio.h>
#include "list.h"
#include "map.h"
#include "string.h"


 /**
    * two city names are passed as the program arguments
    * reads the map file as defined and returns the following:
    * @return 0 and the path if the arguments passed are correct
    * @return 1 if the cities or the city list does not exist or
    * @return 1 if the number of arguments is not two
    * @return 2 if the program failed to read or open the map file
    */


int main( int argc, char* argv[] )
{
    char* mapFilePath = mapFile;

    printf( "Reading from the given map file: %s\n", mapFilePath );
    printf( "\nResulting path from %s to %s is as follows: \n\n", argv[1], argv[2] );

    List* cityList = readMapFile( mapFilePath );

    if( !cityList ){
        return 2;
    }
    else
    {
        status solution = calculatePath( cityList, argv[1], argv[2] );

        if( solution == 1 ){
            return 1;
        }
    }

    delList(cityList);
    return 0;
}
