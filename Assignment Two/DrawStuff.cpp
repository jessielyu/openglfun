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


/* 
 * Draw filled polygon 
 */


struct Edge{
	int x1;
	int y1;
	int x2;
	int y2;
};

// Sort bucket on x
bool DrawStuff::sortBuckets(Bucket bucketOne, Bucket bucketTwo)
{
	if (bucketOne.x < bucketTwo.x)
	{
		return true;
	}
	else if (bucketOne.x > bucketTwo.x)
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
		if (bucketOne.invSlope < bucketTwo.invSlope)
		{
			return true;
		}
		else
		{
			return false;
		}


	}
}

using namespace std;

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
	
	
	for (list<Edge>::const_iterator i = edges.begin(); i != edges.end(); i++)
	{
		const Edge& e = *i;
		Bucket tempBucket;
		int yMin;
		if (e.y1 > e.y2)
		{
			tempBucket.yMax = e.y1;
			tempBucket.x = e.x2;
			yMin = e.y2;
		}
		else
		{
			tempBucket.yMax = e.y2;
			tempBucket.x = e.x1;
			yMin = e.y1;
		}
		
		tempBucket.dx = e.x1 - e.x2;
		tempBucket.dy = e.y1 - e.y2;
		
		// inverse slope
		tempBucket.invSlope = (float)tempBucket.dx/(float)tempBucket.dy;
		
		
		edgeTable[yMin].push_back(tempBucket);
		
	}
	
	for (int i = 0; i < edgeTable.size(); i++)
	{
		if (!edgeTable[i].empty())
		{
			edgeTable[i].sort();
		}
	}
	
	list<Bucket> activeEdgeTable;
	
	//activeEdgeTable.
	
	for (int scanLine = 0; scanLine < edgeTable.size(); scanLine++)
	{
		// Buckets to remove from AET;
		//list<Bucket> toRemoveAET;
	
		for (list<Bucket>::iterator i = activeEdgeTable.begin(); i != activeEdgeTable.end(); i++)
		{
			const Bucket& e = *i;
		
			if (e.yMax == scanLine)
			{
				// Add to remove list
				//toRemoveAET.push_back(e);
				activeEdgeTable.erase(i);
				//activeEdgeTable.erase(<#iterator __position#>);
			}
			
		}
		
		//activeEdgeTable.remove_if(yMax == scanLine);
		
		//activeEdgeTable.r
		
		// Actually remove
//		for (list<Bucket>::const_iterator i = toRemoveAET.begin(); i != toRemoveAET.end(); i++)
//		{
//			const Bucket& e = *i;
//			
//			
//		}

		// add the edges on this scan line to active list
		while(!edgeTable[scanLine].empty())
		{
			activeEdgeTable.push_back(edgeTable[scanLine].front());
			edgeTable[scanLine].pop_front();
		}
		
		// sort them according to our defined < operator
		activeEdgeTable.sort();
		
		int numPairs = activeEdgeTable.size()/2;
		
		list<Bucket>::iterator aeti = activeEdgeTable.begin();
		for (int i = 0; i < numPairs; i++)
		{
			
			//aeti += i*2;
			const Bucket& bucketOne = *aeti;
			const Bucket& bucketTwo = *(++aeti);
			drawLine(bucketOne.x, scanLine, bucketTwo.x, scanLine);
			
			aeti++;
		}
		
		for (list<Bucket>::iterator i = activeEdgeTable.begin(); i != activeEdgeTable.end(); i++)
		{
			Bucket& bucket = *i;
			bucket.x += bucket.invSlope;
		}
	}
	

  /* Your task is to rewrite this using only calls to setPixel() */
//  
//int i;
//
// glBegin( GL_POLYGON ); 
//    for (i = 0; i < n; i++ ) {
//      glVertex2i( x[i], y[i] );
//    }
// glEnd( );



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
  /* provide your implementation here */
	
	ClipEdge bottom, left, top, right;
	
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
	
	int outX1[50];
	int outX2[50];
	int outX3[50];
	
	int outY1[50];
	int outY2[50];
	int outY3[50];
	
//	for (int i = 0; i < in; i++)
//	{
//		outX1[i] = 0;
//		outX2[i] = 0;
//		outX3[i] = 0;
//	
//		outY1[i] = 0;
//		outY2[i] = 0;
//		outY3[i] = 0;
//	}
	
	int length1;
	int length2;
	int length3;
	
	//cout << *in;
	
	SHPC(inx, iny, outX1, outY1, in, &length1, right);
	SHPC(outX1, outY1, outX2, outY2, length1, &length2, top);
	SHPC(outX2, outY2, outX3, outY3, length2, &length3, left);
	SHPC(outX3, outY3, outx, outy, length3, out, bottom);
	
	cout << *out;
	
//	int i = 0;
//	while (i < 1)
//	{
//		i++;
//	}
	
//	for (int i = 0; i < in; i++)
//	{
//		cout << "Vertex in " << i << ": x: " << inx[i] << " y: " << iny[i] << "\r";
//	}
//	
//	cout << "Out size: " << *out << "\n";
//	
//	for (int i = 0; i < *out; i++)
//	{
//		cout << "Vertex out " << i << ": x: " << outx[i] << " y: " << outy[i] << "\r";
//	}
  
}

void DrawStuff::SHPC(int inX[], int inY[], int outX[], int outY[], int inLength, int *outLength, ClipEdge clipboundry)
{
	*outLength = 0;
	int px = inX[inLength-1];
	int py = inY[inLength-1];
	
	for (int i = 0; i < inLength; i++)
	{
		int vx = inX[i];
		int vy = inY[i];
		
		if (clipboundry.isInside(vx, vy))
		{
			if (clipboundry.isInside(px, py))
			{
				outX[*outLength] = vx;
				outY[*outLength] = vy;
				(*outLength)++;
			}
			else
			{
				int intx;
				int inty;
				//void intersect(int edgeX1, int edgeY1, int edgeX2, int edgeY2, int* xOut, int* yOut)
				clipboundry.intersect(px, py, vx, vy, &intx, &inty);
				
				outX[*outLength] = intx;
				outY[*outLength] = inty;
				(*outLength)++;
				
				outX[*outLength] = vx;
				outY[*outLength] = vy;
				(*outLength)++;
			}
		}
		else
		{
			if (clipboundry.isInside(px, py))
			{
				int intx;
				int inty;
				//void intersect(int edgeX1, int edgeY1, int edgeX2, int edgeY2, int* xOut, int* yOut)
				clipboundry.intersect(px, py, vx, vy, &intx, &inty);
				
				outX[*outLength] = intx;
				outY[*outLength] = inty;
				(*outLength)++;
			}
		}
		
		px = vx;
		py = vy;
	}
}


