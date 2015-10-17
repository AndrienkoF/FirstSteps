#include <math.h>


double long2double(long long LongNum)
{
	double S [1];    
	double E [11];     
	double F [52];     
	
	int i, Num[64];    
	
	double E2 = 0; 
	double F2 = 0;
	double S2 = 0;

	for (i = 0; i <= 63; i++)
	{
		Num[i] = (LongNum & (1LL << 63 - i)) ? 1 : 0;     
	}

	S2 = Num[0];

	for (i = 0; i < 11; i++)
	{
		E[i] = Num[i + 1];
	}
	for (i = 0; i < 52; i++)
	{
		F[i] = Num[i + 12];
	}
	for (i = 0; i <= 10; i++)
	{
		E2 += E[i] * pow(2, i);
	}
	for (i = 0; i < 52; i++)
	{
		F2 += F[i] * pow(2, -i - 1);
	}


	if (E2 == 2048 && F2 != 0)
	{
		return NAN;
	}

	if (E2 == 2047 && F2 == 0 && S2 == 1)
	{
		return -INFINITY;
	}

	if (E2 == 2047 && F2 == 0 && S2 == 0)
	{
		return INFINITY;
	}

	if (E2 > 0 && E2 < 2047)
	{
		return pow(-1, S2) * pow(2, E2 - 1023) * (1 + F2);
	}
	if (E2 == 0 && F2 != 0) 
	{
		return pow(-1, S2) * pow(2, -126) * (1 + F2);
	}
	if (E2 == 0 && F2 == 0 && S2 == 1) 
	{
		return -0;
	}
	if (E2 == 0 && F2 == 0 && E2 == 0)  
	{
		return 0;
	}
}

