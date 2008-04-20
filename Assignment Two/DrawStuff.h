#ifndef INCLUDED_DrawStuff
#define INCLUDED_DrawStuff



class DrawStuff
{
// Edge struct
struct Edge{
	int x1;
	int y1;
	int x2;
	int y2;
};
// Buckets used in polygon filling
struct Bucket{
	int yMax;	// yMax of the edge
	float x;	// current x value (initially x of ymin point)
	int dx;		// Change in x
	int dy;		// Change in y
	float invSlope;		// Inverse slope (1/m) or 1/(dy/dx)
	
	// Define the < operator so we can use the sort() function on a list of buckets
	bool operator<(const Bucket& bucketTwo)
	{
		// Compare on x value first
		if (x < bucketTwo.x)
		{
			return true;
		}
		else if (x > bucketTwo.x)
		{
			return false;
		}
		// The same x, sort on inverse slope
		else
		{
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

// ClipEdge used to clip polygons against
struct ClipEdge
{
	int x1;		// 
	int y1;		// 
	int x2;		// 
	int y2;		// 
	int dx;		// Change in x
	int dy;		// Change in y
	float slope;// Slope of the line
	
	// Whether or not a point is inside (to the left since we're going CCW around the edges)
	bool isInside(int x, int y)
	{
		// infinite slope
		if (dx == 0)
		{
			// Pointing up
			if (dy > 0)
			{
				// if less than my x, inside
				if (x < x1)
				{
					return true;
				}
			}
			// Pointing down
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
	
	// Get the y value from the equation of this line for a given x
	float yFromX(int x)
	{
		// b = y - m*x
		float yInt = y1 - (slope * x);
		
		// y= mx + b
		float y = slope * x + yInt;
		
		return y;
	}
	
	// Calculate the intersection point using determinants
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
	
	// Calculate the determinant
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
				  
// Clip a polygon against a given ClipEdge object
static void SHPC(int inX[], int inY[], int outX[], int outY[], int inLength, int *outLength, ClipEdge clipboundry);
};

#endif