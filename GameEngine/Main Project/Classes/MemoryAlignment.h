//
//  MemoryAlignment.h
//  GameEngine
//
//  Created by Joseph Conley on 7/31/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef GameEngine_MemoryAlignment_h
#define GameEngine_MemoryAlignment_h

#include "Log.h"
#include "MathHelper.h"

namespace Helper 
{
	struct MemoryAlignment
	{
		// Align the specified memory address to the specified alignment in bytes
		static u32 alignAddress(const u32 rawAddress, const u32 alignment)
		{
			if (alignment == 0)
			{
				LOG("Aligning to 0");
				return rawAddress;
			}
			
			// This math only works for powers of two
			ASSERT(Math::isPowerOf2(alignment), "Alignment is not a power of 2!");
			
			u32 mask = (alignment - 1);
			u32 misalignment = (rawAddress & mask);
			u32 adjustment = alignment - misalignment;
			
			u32 alignedAddress = rawAddress + adjustment;
			return alignedAddress;
		}
	};
}

#endif
