#pragma once
//------  Utility.h  ------
//------  QÆ  ------
#include <basetsd.h>

//@brief	------  IDæ“¾—p–¼‘O‹óŠÔ  ------
namespace ID {
	//@brief	---  IDæ“¾ŠÖ”  ---
	template <class T>
	UINT64 Get() noexcept{
		static char value{};
		return reinterpret_cast<UINT64>(&value);
	}
}//namespace ID