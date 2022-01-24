#include"SptProject.h"
using namespace spt;
#include<math.h>
using namespace std;
int32 spt::Max(int32 a, int32 b)
{
	return a > b ? a : b;
}

int32 spt::Max(int32 a, int32 b, int32 c)
{
	return Max(Max(a, b), c);
}

int32 spt::Min(int32 a, int32 b)
{
	return a < b ? a : b;
}

int32 spt::Min(int32 a, int32 b, int32 c)
{
	return Min(Min(a, b), c);
}

uint32 spt::Max(uint32 a, uint32 b)
{
	return a > b ? a : b;
}

uint32 spt::Max(uint32 a, uint32 b, uint32 c)
{
	return Max(Max(a, b), c);
}

uint32 spt::Min(uint32 a, uint32 b)
{
	return a < b ? a : b;
}

uint32 spt::Min(uint32 a, uint32 b, uint32 c)
{
	return Min(Min(a, b), c);
}

float32 spt::Max(float32 a, float32 b)
{
	return a > b ? a : b;
}

float32 spt::Max(float32 a, float32 b, float32 c)
{
	return Max(Max(a, b), c);
}

float32 spt::Min(float32 a, float32 b)
{
	return a < b ? a : b;
}

float32 spt::Min(float32 a, float32 b, float32 c)
{
	return Min(Min(a, b), c);
}

float64 spt::Sqrt(float64 Value)
{
	return sqrt(Value);
}

float32 spt::Sqrt(float32 Value)
{
	return sqrtf(Value);
}

float32 spt::ATan2(int32 y, int32 x)
{
	float32 ang = (float32)atan2(y, x);
	if (ang < 0)
	{
		ang += 2 * 3.1415926f;
	}
	return (float32)ang * 180.0f / 3.1415926f;
}

float32 spt::ATan2(float32 y, float32 x)
{
	float32 ang = (float32)atan2(y, x);
	if (ang < 0)
	{
		ang += 2 * 3.1415926f;
	}
	return (float32)ang * 180.0f / 3.1415926f;
}
