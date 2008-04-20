/**
 * Routines that you'll need to write
 *
 */
#include <GLUT/glut.h>         /* glut.h includes gl.h and glu.h*/
//#include <stdlib.h>
//#include <stdio.h>
#include <iostream>
#include <vector>
#include <list>
#include <math.h>
#include "DrawStuff.h"

#include "SetPixel.h"


//void setPixel (int x, int y);



/* 
 * Draw line from x1, y1 to x2, y2 
 */
void DrawStuff::drawLine( int p1x, int p1y, int p2x, int p2y) 
{
	int dx; 
	int dy; 
	int incMajor; 
	int incMinor; 
	int d; 
	int x; 
	int y; 

	// If necessary, switch the points so we're 
	// always drawing from left to right. 
	if (p2x < p1x) { 
	   int t; 
	   t = p2x; 
	   p2x = p1x; 
	   p1x = t; 
	   t = p2y; 
	   p2y = p1y; 
	   p1y = t; 
	} 

	// The change in x
	dx = p2x - p1x; 

	// The change in y
	dy = p2y - p1y; 

	// If slope is 0
	if (dy == 0)
	{
		// No change in y ever, fill in for the same y
		for (int i = p1x; i < p2x; i++)
		{
			SetPixel::setPixel(i, p1y);
		}
	}
	// If slope is oo
	else if (dx == 0)
	{
		// make sure we're going from bottom to top
		if (p1y > p2y)
		{
			int t = p1y;
			p1y = p2y;
			p2y = t;
		}

		// Fill in all the ys for this x
		for (int i = p1y; i < p2y; i++)
		{
			SetPixel::setPixel(p1x, i);
		}
	}



	// Slope is between 0 and 1
	else if ((dy >= 0) && (dy <= dx)) 
	{ 
		// Initiate the decision variable and the increment variables
		d = 2 * dy - dx;	
		incMajor = 2 * dy;
		incMinor = 2 * (dy - dx); 

		x = p1x; 
		y = p1y; 

		SetPixel::setPixel(x, y); 
		
		// For all x,
		while (x < p2x) 
		{ 
		   // If d negative, choose same y, add incMajor
		   if (d <= 0) 
		   { 
			   d += incMajor; 
			   x++; 
		   } 
		   // Otherwise choose higher y, add incMinor
		   else 
		   { 
			   d += incMinor; 
			   x++; 
			   y++; 
		   } 
		   SetPixel::setPixel(x, y); 
	   } 
	} 

	//   if the slope is 0 to -1
	// dy is negative, invert
	else if ((dy <= 0) && (-dy <= dx)) 
	{
		d = 2 * dy - dx; 
		incMajor = 2 * dy; 
		incMinor = 2 * (dy + dx);  // This is + dx in this case, isntead of - dx
		
		x = p1x; 
		y = p1y; 
		
		SetPixel::setPixel(x, y); 
	   
		// for all x
		while (x < p2x) 
		{ 
			// choose lower y
			if (d <= 0) 
			{ 
				d += incMinor; 
				x++; 
				y--; 
			} 
			// choose same y
			else  
			{ //the line is above the midpoint, do
				d += incMajor; 
				x++; 
			} 
			SetPixel::setPixel(x, y); 
		}
	}

	//   if the slope is 1 to infinity
	else if ((dy >= 0) && (dy >= dx)) 
	{
		// Swap x and ys
		d = 2 * dx - dy; 
		incMajor = 2 * dx; 
		incMinor = 2 * (dx - dy); 

		x = p1x; 
		y = p1y; 

		SetPixel::setPixel(x,y);

		// for all ys
		while (y < p2y) 
		{ 
			// choose left point
			if (d <= 0) 
			{ 
			   d += incMajor; 
			   y++; 
			} 
			// choose the right point
			else 
			{
			   d += incMinor; 
			   y++; 
			   x++; 
			}
			SetPixel::setPixel(x,y);
		} 
	} 
	
	//   if the slope is -1 to negative infinity
	else if ((dy <= 0) && (-dy >= dx))
	{
		// Again x and y swapped
		d = 2 * dx - dy; 
		incMajor = 2 * dx; 
		incMinor = 2 * (dx + dy); // again adding dy instead of subtracting, because negative slope

		x = p1x; 
		y = p1y; 

		SetPixel::setPixel(x,y);
		   
		// for all y
		while (y > p2y)
		{
			// choose left point
			if (d <= 0)
			{
			   d += incMajor; 
			   y--; 
			} 
			// choose right point
			else 
			{ 
			   d += incMinor; 
			   y--; 
			   x++; 
			}
			SetPixel::setPixel(x,y);
		} 
	} 
}

using namespace std; // for list
/* 
 * Draw filled polygon 
 */
void DrawStuff::drawPolygon( int n, int x[], int y[] ) {
	
	int yMaxAll = INT_MIN;	// Hold the maximum y value
	list<Edge> edges;  // to hold the input edges

	// Take the points and make them into edges
	for (int i = 0; i < n; i++)
	{
		Edge tempEdge;
		
		if (y[i] > yMaxAll)
		{
			yMaxAll = y[i];
		}
		
		// last point goes back to the first
		if (i == n - 1)
		{
			tempEdge.x1 = x[i];
			tempEdge.y1 = y[i];
			tempEdge.x2 = x[0];
			tempEdge.y2 = y[0];
		}
		else
		{
			tempEdge.x1 = x[i];
			tempEdge.y1 = y[i];
			tempEdge.x2 = x[i+1];
			tempEdge.y2 = y[i+1];
		}
		
		// If horizontal slope don't include, don't need to process these
		if (tempEdge.y1 == tempEdge.y2)
		{
			continue;
		}
		else
		{	
			edges.push_back(tempEdge);
		}
			
	}
	
	// Test to verify that our edges are correct
//	glBegin(GL_LINE_LOOP);
//	for (list<Edge>::const_iterator i = edges.begin(); i != edges.end(); i++)
//	{
//		const Edge& e = *i;
//		glVertex2i(e.x1, e.y1);
//		glVertex2i(e.x2, e.y2);
//		
//	}
//	glEnd();

	// Edge table.  each entry in the vector holds a list of buckets that have a ymin 
	// Size of the vector is yMaxAll, the greatest Y value we have
	vector< list<Bucket> > edgeTable(yMaxAll);
	
	// For each edge, fill in the bucket info
	for (list<Edge>::const_iterator i = edges.begin(); i != edges.end(); i++)
	{
		const Edge& e = *i;
		Bucket tempBucket;
		
		int yMin;	// Store yMin, this is which list to add it to
		
		// Find yMax
		if (e.y1 > e.y2)
		{
			tempBucket.yMax = e.y1;
			tempBucket.x = e.x2;	// x is the x value at yMin, NOT yMax
			yMin = e.y2;
		}
		else
		{
			tempBucket.yMax = e.y2;
			tempBucket.x = e.x1;	// x is the x value at yMin, NOT yMax
			yMin = e.y1;
		}
		
		// Calculate dx and dy
		tempBucket.dx = e.x1 - e.x2;
		tempBucket.dy = e.y1 - e.y2;
		
		// store the inverse slope to increment x
		tempBucket.invSlope = (float)tempBucket.dx/(float)tempBucket.dy;
		
		// Add this to yMin pos in the edge table
		edgeTable[yMin].push_back(tempBucket);
		
	}
	
	// Sort the edge table (with our defined < operator)
	for (int i = 0; i < edgeTable.size(); i++)
	{
		if (!edgeTable[i].empty())
		{
			edgeTable[i].sort();
		}
	}
	
	// Active edge table
	list<Bucket> activeEdgeTable;
	
	// For each scan line
	for (int scanLine = 0; scanLine < edgeTable.size(); scanLine++)
	{
		// Delete Buckets from the AET where yMax = scanLine
		for (list<Bucket>::iterator i = activeEdgeTable.begin(); i != activeEdgeTable.end(); i++)
		{
			const Bucket& e = *i;
		
			if (e.yMax == scanLine)
			{
				activeEdgeTable.erase(i);
			}
			
		}

		// add the edges on this scan line to active list
		while(!edgeTable[scanLine].empty())
		{
			activeEdgeTable.push_back(edgeTable[scanLine].front());
			edgeTable[scanLine].pop_front();
		}
		
		// sort them according to our defined < operator
		activeEdgeTable.sort();
		
		// Figure out how many pairs of edges we have, we'll fill between them
		int numPairs = activeEdgeTable.size()/2;
		
		// For each pair of edges, draw a line between their current x
		list<Bucket>::iterator aeti = activeEdgeTable.begin();
		for (int i = 0; i < numPairs; i++)
		{
			const Bucket& bucketOne = *aeti;
			const Bucket& bucketTwo = *(++aeti);
			
			// use our draw line function, has a special case for 0 slope lines
			drawLine(bucketOne.x, scanLine, bucketTwo.x, scanLine);
			
			aeti++;
		}
		
		// Incrememnt x by the inverse slope for each edge
		for (list<Bucket>::iterator i = activeEdgeTable.begin(); i != activeEdgeTable.end(); i++)
		{
			Bucket& bucket = *i;
			bucket.x += bucket.invSlope;
		}
	}
}


/**
 * Clip the polygon with vertex count in and verticies inx and iny against
 * the rectangular clipping region specified by lower left corner (x0, y0) 
 * and upper right corner (x1, y1).  The resulting vertices are places in
 * outx, and outy with the vertex count places in out.
 */
void DrawStuff::clipPolygon (int in, int inx[], int iny[], int *out, int outx[],
                  int outy[], int x0, int y0, int x1, int y1)
{
	// ClipEdge for each edge
	ClipEdge bottom, left, top, right;
	
	// Calculate the points, slope, dx and dy for each clip edge
	bottom.x1 = x0;
	bottom.y1 = y0;
	bottom.x2 = x1;
	bottom.y2 = y0;
	bottom.dx = bottom.x2-bottom.x1;
	bottom.dy = bottom.y2-bottom.y1;
	bottom.slope = (float)bottom.dy/(float)bottom.dx;
	
	right.x1 = x1;
	right.y1 = y0;
	right.x2 = x1;
	right.y2 = y1;
	right.dx = right.x2-right.x1;
	right.dy = right.y2-right.y1;
	right.slope = (float)right.dy/(float)right.dx;
	
	top.x1 = x1;
	top.y1 = y1;
	top.x2 = x0;
	top.y2 = y1;
	top.dx = top.x2-top.x1;
	top.dy = top.y2-top.y1;
	top.slope = (float)top.dy/(float)top.dx;
	
	left.x1 = x0;
	left.y1 = y1;
	left.x2 = x0;
	left.y2 = y0;
	left.dx = left.x2-left.x1;
	left.dy = left.y2-left.y1;
	left.slope = (float)left.dy/(float)left.dx;
	
	// Debug for printing the clipping window
//	glColor3ub(0,0,0);
//	glBegin(GL_LINES);
//	
//		glVertex2i(bottom.x1, bottom.y1);
//		glVertex2i(bottom.x2, bottom.y2);
//		glVertex2i(right.x1, right.y1);
//		glVertex2i(right.x2, right.y2);
//		glVertex2i(top.x1, top.y1);
//		glVertex2i(top.x2, top.y2);
//		glVertex2i(left.x1, left.y1);
//		glVertex2i(left.x2, left.y2);
//	
//	glEnd();
	
	// Temporary arrays to hold the output at the different stages
	int outX1[50];
	int outX2[50];
	int outX3[50];
	
	int outY1[50];
	int outY2[50];
	int outY3[50];
	
	// Temporary length variables at the different stages
	int length1;
	int length2;
	int length3;
	
	// clip against each edge, results of current goes to next
	SHPC(inx, iny, outX1, outY1, in, &length1, right);
	SHPC(outX1, outY1, outX2, outY2, length1, &length2, top);
	SHPC(outX2, outY2, outX3, outY3, length2, &length3, left);
	SHPC(outX3, outY3, outx, outy, length3, out, bottom);
}

// Clips against one edge, using the ClipEdge struct
void DrawStuff::SHPC(int inX[], int inY[], int outX[], int outY[], int inLength, int *outLength, ClipEdge clipboundry)
{
	// outlength is initially zero
	*outLength = 0;
	
	// previous point for the first one is the last point in our list
	int px = inX[inLength-1];
	int py = inY[inLength-1];
	
	// for each point, check which case we are
	for (int i = 0; i < inLength; i++)
	{
		// Our current point
		int vx = inX[i];
		int vy = inY[i];
		
		// If this point is inside (Case 1 & 4)
		if (clipboundry.isInside(vx, vy))
		{
			// If both are inside (Case 1)
			if (clipboundry.isInside(px, py))
			{
				// Store the current point in our output
				outX[*outLength] = vx;
				outY[*outLength] = vy;
				(*outLength)++;
			}
			// If just current is inside (Case 4)
			else
			{
				int intx;	// New clipped point
				int inty;	// New clipped point
				
				// Clip against the edge
				clipboundry.intersect(px, py, vx, vy, &intx, &inty);
				
				// Add this new point
				outX[*outLength] = intx;
				outY[*outLength] = inty;
				(*outLength)++;
				
				// Then add our current point (it's still inside)
				outX[*outLength] = vx;
				outY[*outLength] = vy;
				(*outLength)++;
			}
		}
		// Current point is NOT inside (case 2 & 3)
		else
		{
			// If the previous point was
			if (clipboundry.isInside(px, py))
			{
				int intx;	// New clipped point
				int inty;	// New clipped point

				// Clip against the edge
				clipboundry.intersect(px, py, vx, vy, &intx, &inty);
				
				// Only store this new clipped point, omit the current point
				outX[*outLength] = intx;
				outY[*outLength] = inty;
				(*outLength)++;
			}
			
			// Case 3 has no output, both points are outside
		}
		
		// Next time the previous point is the current point
		px = vx;
		py = vy;
	}
}


