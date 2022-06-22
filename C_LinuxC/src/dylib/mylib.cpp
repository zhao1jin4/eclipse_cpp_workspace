
#define ENDSTRING '\0'
int strLen(char *string)
{
  int len = 0;
  while(*string++ != ENDSTRING)
    len++;
  return len;
}

int mymax(int a,int b ){
	return a>b?a:b;
}
int add(int a,int b)
{
  return (a + b);
}
