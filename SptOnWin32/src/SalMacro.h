#ifndef SALMACRO_H
#define SALMACRO_H

namespace spt
{
#ifndef M_ArrLen
#define M_ArrLen(arr)	((sizeof(arr))/(sizeof(arr[0])))
#endif
#define M_Singleton(className)	static className& Instance(){static className inst;return inst;}


}


#endif // !SALMACRO_H

