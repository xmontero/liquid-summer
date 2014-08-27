#include <iostream>
#include "LiquidSummer.h"

int main( int /* argc */, char ** /* argv */ )
{
	int result = 1;
	
	try
	{
		LiquidSummer liquidSummer;
		
		liquidSummer.run();
		result = 0;
	}
	catch( char * message )
	{
		std::cout << "Exception. " << message;
	}
	
	return result;
}
