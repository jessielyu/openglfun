#ifndef INCLUDED_DrawStuff
#define INCLUDED_DrawStuff



class DrawStuff
{
struct Bucket{
	int yMax;
	float x;
	int dx;
	int dy;
	float invSlope;
	
	bool operator<(const Bucket& bucketTwo)
	{
		if (x < bucketTwo.x)
		{
			return true;
		}
		else if (x > bucketTwo.x)
		{
			return false;
		}
		// The same x, sort on 1/m
		else
		{
	//		float recipSlopeOne = 1.0f / (bucketOne.dy/bucketOne.dx);
	//		float recipSlopeTwo = 1.0f / (bucketTwo.dy/bucketTwo.dx);
	//		
	//		if (recipSlopeOne < recipSlopeTwo)
	//		{
	//			return true;
	//		}
	//		else
	//		{
	//			return false;
	//		}
			if (invSlope < bucketTwo.invSlope)
			{
				return true;
			}
			else
			{
				return false;
			}


		}
	}
};

struct ClipEdge
{
	int x1;
	int y1;
	int x2;
	int y2;
	int dx;
	int dy;
	float slope;
	
	bool isInside(int x, int y)
	{
		//float dx = x2 - x1;
		//float dy = y2 - y1;
		
		//float slope = dy/dx;
		
		// no slope
//		if (slope == 0)
//		{
//			if (dx < 0)
//			{
//				if (y < yFromX(x))
//				{
//					return true;
//				}
//			}
//			else
//			{
//				if (y >= yFromX(x))
//				{
//					return true;
//				}
//			}
//		}
		// infinite slope
		//else 
		if (dx == 0)
		{
			if (dy > 0)
			{
				// if less than my x, inside
				if (x < x1)
				{
					return true;
				}
			}
			else
			{
				// if less than my x, inside
				if (x > x1)
				{
					return true;
				}
			}			
		}
		// Quadrants 1 & 4
		else if (dx > 0)
		{
			// if y greater than my y
			if (y > yFromX(x))
			{
				return true;
			}
		}
		// Quadrants 2 & 3
		else if (dx < 0)
		{
			// if y less than my y
			if (y < yFromX(x))
			{
				return true;
			}
		}
		
		return false;
	}
	
	float yFromX(int x)
	{
		float yInt = y1 - (slope * x);
		
		float y = slope * x + yInt;
		
		return y;
	}
	
	void intersect(int edgeX1, int edgeY1, int edgeX2, int edgeY2, int* xOut, int* yOut)
	{
			
		double  _x1 = x1, _y1 = y1,
				_x2 = x2, _y2 = y2,
				_x3 = edgeX1, _y3 = edgeY1,
				_x4 = edgeX2, _y4 = edgeY2;
		
		*xOut = det(det(_x1, _y1, _x2, _y2), _x1 - _x2,
							 det(_x3, _y3, _x4, _y4), _x3 - _x4)/
						 det(_x1 - _x2, _y1 - _y2, _x3 - _x4, _y3 - _y4);
		*yOut = det(det(_x1, _y1, _x2, _y2), _y1 - _y2,
							 det(_x3, _y3, _x4, _y4), _y3 - _y4)/
						 det(_x1 - _x2, _y1 - _y2, _x3 - _x4, _y3 - _y4);
	}

	static double det(double a, double b, double c, double d)
	{
		return a * d - b * c;
	}
	
};

public:
/* 
 * Draw line from x1, y1 to x2, y2 
 */
static void drawLine( int x1, int y1, int x2, int y2);

/* 
 * Draw filled polygon 
 */

static void drawPolygon( int n, int x[], int y[] );

/**
 * Clip the polygon with vertex count in and verticies inx and iny against
 * the rectangular clipping region specified by lower left corner (x0, y0) 
 * and upper right corner (x1, y1).  The resulting vertices are places in
 * outx, and outy with the vertex count places in out.
 */
static void clipPolygon (int in, int inx[], int iny[], int *out, int outx[],
                  int outy[], int x0, int y0, int xq, int y1);
				  
bool sortBuckets(Bucket bucketOne, Bucket bucketTwo);

static void SHPC(int inX[], int inY[], int outX[], int outY[], int inLength, int *outLength, ClipEdge clipboundry);
};

#endif