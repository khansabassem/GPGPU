#pragma once

#include <iostream>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*----------------------*\
 |*	public 		*|
 \*---------------------*/

//// Choose one of the two (either/either):
#define HEAT_FLOAT
//#define HEAT_DOUBLE
//#define HEAT_HALF

/*----------------------*\
 |*	private 	*|
 \*---------------------*/

// fp64 (float 64 bits)
#ifdef HEAT_FLOAT
#define real float
#endif

// fp32 (float 32 bits)
#ifdef HEAT_DOUBLE
#define real double
#endif

// fp16 (float 32 bits)
#ifdef HEAT_HALF
#define real half
#endif

static std::string realToString()
    {
    #ifdef HEAT_FLOAT
    return "float-fp32";
    #endif

    #ifdef HEAT_DOUBLE
    return "double-fp64";
    #endif

    #ifdef HEAT_HALF
    return "half-fp16";
    #endif
    }


/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

