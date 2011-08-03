//
//  MathHelper.h
//  GameEngine
//
//  Created by Joseph Conley on 7/31/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef GameEngine_MathHelper_h
#define GameEngine_MathHelper_h

#include "Assert.h"
#include "Types.h"

namespace Helper 
{
	struct Math
	{
		static bool isPowerOf2(const int value)
		{
			ASSERT(value, "This function not intended to work for 0.");
			
			// Example: value = 8, 0x1000 & 0x0111 = 0
			return !(value & (value - 1));
		}
	};
}

#endif
