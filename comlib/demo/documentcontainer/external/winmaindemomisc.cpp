#include <windows.h>
#include <iostream.h>
#include <stdio.h>

extern "C" 
{
void myprint(HRESULT hr)
{	
	printf("hr: %x \n", hr);
}
}