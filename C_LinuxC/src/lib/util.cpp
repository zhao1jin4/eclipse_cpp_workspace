#include <stdlib.h>
#include <stdio.h>

#include <assert.h>

namespace lib_util
{

	int main (int argc, char *argv[])
	{

		printf("Compiled: " __DATE__ " at " __TIME__ "\n");
		printf("This is line %d of file %s\n", __LINE__, __FILE__);
		printf("function is: %s \n", __FUNCTION__ );

		assert(1+1==2); //<assert.h>
		assert(1+1==3);

		 return 0;
	}
};



