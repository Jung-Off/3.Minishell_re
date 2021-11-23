#include <stdio.h>
#include <unistd.h>

#ifndef _MAX_PATH
#define _MAX_PATH 260
#endif

int main( )
{
	char strBuffer[_MAX_PATH] = { 0, };
	char strChangeDir[_MAX_PATH] = { "/Users/jji" };

	int nResult = chdir( strChangeDir );

	if( nResult == 0 )
	{
		printf( "이동 성공" );
	}
	else if( nResult == -1 )
	{
		perror( "이동 실패 - " );
	}

	return 0;
}