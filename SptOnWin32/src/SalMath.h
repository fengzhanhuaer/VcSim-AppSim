#ifndef SALMATH_H
#define SALMATH_H

namespace spt
{
	int32 Max(int32 a, int32 b);
	int32 Max(int32 a, int32 b, int32 c);
	int32 Min(int32 a, int32 b);
	int32 Min(int32 a, int32 b, int32 c);
	uint32 Max(uint32 a, uint32 b);
	uint32 Max(uint32 a, uint32 b, uint32 c);
	uint32 Min(uint32 a, uint32 b);
	uint32 Min(uint32 a, uint32 b, uint32 c);
	float32 Max(float32 a, float32 b);
	float32 Max(float32 a, float32 b, float32 c);
	float32 Min(float32 a, float32 b);
	float32 Min(float32 a, float32 b, float32 c);
	float64 Sqrt(float64 Value);
	float32 Sqrt(float32 Value);
	/// <summary>
	/// ·´ÕıÇĞ
	/// </summary>
	/// <param name="y"></param>
	/// <param name="x"></param>
	/// <returns>0~360¶È</returns>
	float32 ATan2(int32 y, int32 x);
	float32 ATan2(float32 y, float32 x);
}


#endif // !SALMATH_H
