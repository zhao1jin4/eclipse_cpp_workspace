#include <stdio.h>
#include <stdlib.h>

namespace stl_search_sort
{
   int compareints (const void * a, const void * b)
   {
	 return ( *(int*)a - *(int*)b );
   }
   int values[] = {  90, 100 ,10, 20, 25, 40};



   void search()
   {
	  int * pItem;
	 int key = 40;
	 pItem = (int*) bsearch (&key, values, 6, sizeof (int), compareints);
	 if (pItem!=NULL)
	   printf ("%d is in the array.\n",*pItem);
	 else
	   printf ("%d is not in the array.\n",key);
   }

  void order()
  {
	  int n;
	  qsort (values, 6, sizeof(int), compareints);
	  for (n=0; n<6; n++)
		 printf ("%d ",values[n]);
  }
   int main(int argc, char* argv[])
   {
	   //search();
	   order();

	   return 0;
   }


}
