#include <stdio.h>
#include <stdlib.h>

char *g;

void Retrive ()
{
    g = getenv("CASE1");
}

char* Getpasswd ()
{
	Retrive ();
	
	printf ("Value = %s\r\n", g);
	return g;
	
}



