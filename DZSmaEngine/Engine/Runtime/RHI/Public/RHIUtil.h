#pragma 
#include "RHISources.h"
#include "RHICommandList.h"
class RHIUtil
{
public:
	template<typename T>
	static inline UniFormLayout* CreateLayout(T* pData)
	{
		UniFormLayout* mCBDrawLayout = new UniFormLayout();
		mCBDrawLayout->Resource = &pData;
		mCBDrawLayout->ConstantBufferSize = static_cast<uint32>(sizeof(T) + (16 - (sizeof(T) % 16)));
		return mCBDrawLayout;
	}
};