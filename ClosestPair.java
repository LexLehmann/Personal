// Author : Alex Lehmann (awl9x)
// ClosestPair.java
// implements an algorithum to find the closest pair of points in nlogn time
import java.io.*;
import java.util.Arrays;

// finds the closest pair of points in a list of 2-dimensional points
// runs in O(nlogn) time, but only works in 2d space as the number of
// points you would have to check that cross the cut would grow exponentially
public class ClosestPair {
	static Point[] points;
	public static void main(String[] args)  throws IOException {
		FileReader in = new FileReader("garden.txt");
		int numPoints = 0;
		int next = in.read();
		
		while (next != 13) {
			numPoints = numPoints*10 + Character.getNumericValue(next);
			next = in.read();
		}
		
		
		points = new Point[numPoints];
		
		for(int i = 0; i < numPoints; i++) {
			float x = 0;
			float y = 0;
			in.read();
			int temp = in.read();
			boolean decimal = false;
			int shift = 0;
			
			while(temp != 32) {
				if (temp != 46) {
					x = x*10 + Character.getNumericValue(temp);
					temp = in.read();
					if (decimal == true) {
						shift++;
					}
				} else {
					decimal = true;
					temp = in.read();
				}
			}
			x = (float) (x / Math.pow(10, shift));
			
			shift = 0;
			decimal = false;
			temp = in.read();
			
			while(temp != 13 && temp != -1) {
				if (temp != 46) {
					y = y*10 + Character.getNumericValue(temp);
					temp = in.read();
					if (decimal == true) {
						shift++;
					}
				} else {
					decimal = true;
					temp = in.read();
				}
			}
			y = (float) (y / Math.pow(10, shift));
			
			points[i] = new Point(x, y);
		}
		
		Arrays.sort(points);
		
		// main work done here
		System.out.println(shortestDis(0, numPoints-1));
	}
	public static float shortestDis(int arrayStart, int arrayEnd) {
		float dis = 0;
		if (arrayEnd - arrayStart < 3) {							// Base Case where there are only 2			Point tempPoint;								// 
			if (arrayEnd - arrayStart == 1) {						// or 3 points in the subgroup
				dis = (float) Math.sqrt(Math.pow(points[arrayStart].getX()-points[arrayEnd].getX(),2) 
						+ Math.pow(points[arrayStart].getY()-points[arrayEnd].getY(),2));
				if (points[arrayStart].getY() > points[arrayEnd].getY()) {
					tempPoint = points[arrayEnd];
					points[arrayEnd] = points[arrayStart];
					points[arrayStart] = tempPoint;
				}
			} else {
				float temp;
				dis = (float) Math.sqrt(Math.pow(points[arrayStart].getX()-points[arrayEnd].getX(),2) 
						+ Math.pow(points[arrayStart].getY()-points[arrayEnd].getY(),2));
				temp = (float) Math.sqrt(Math.pow(points[arrayStart].getX()-points[arrayEnd-1].getX(),2) 
						+ Math.pow(points[arrayStart].getY()-points[arrayEnd-1].getY(),2));
				if (temp < dis) {
					dis = temp;
				}
				temp = (float) Math.sqrt(Math.pow(points[arrayEnd-1].getX()-points[arrayEnd].getX(),2) 
						+ Math.pow(points[arrayEnd-1].getY()-points[arrayEnd].getY(),2));
				if (temp < dis) {
					dis = temp;
				}
				if (points[arrayStart].getY() > points[arrayStart + 1].getY()) {
					tempPoint = points[arrayStart];
					points[arrayStart] = points[arrayStart + 1];
					points[arrayStart + 1] = tempPoint;
				}
				if (points[arrayEnd - 1].getY() > points[arrayEnd].getY()) {
					tempPoint = points[arrayEnd - 1];
					points[arrayEnd - 1] = points[arrayEnd];
					points[arrayEnd] = tempPoint;
				}
				if (points[arrayStart].getY() > points[arrayStart + 1].getY()) {
					tempPoint = points[arrayStart];
					points[arrayStart] = points[arrayStart + 1];
					points[arrayStart + 1] = tempPoint;
				}
			}
		} else {									// Recursion
			int half, length, listOne, listTwo;
			float one, two, delta, median;
			half = (arrayStart + arrayEnd) / 2;
			Point[] combList, closeToCenter;
			median = (points[half].getX() + points[half + 1].getX()) / 2;
			
			// run the method on each of the sublists on each side of the split
			one = shortestDis(arrayStart, half);
			two = shortestDis(half + 1, arrayEnd);
			
			// choose what the closest pair of points is
			delta = Math.min(one, two);
			dis = delta;
			length = arrayEnd - arrayStart + 1;
			
			//merge sort the lists into a single list sorted by the y value
			combList = new Point[length];
			listOne = arrayStart;
			listTwo = half +1;
			for (int i = 0; i < length; i++) {
				if (listTwo > arrayEnd) {
					combList[i] = points[listOne];
					listOne++;
				} else if (listOne > half) {
					combList[i] = points[listTwo];
					listTwo++;
				} else {
					if (points[listOne].getY() < points[listTwo].getY()) {
						combList[i] = points[listOne];
						listOne++;
					} else {
						combList[i] = points[listTwo];
						listTwo++;
					}
				}
			}
			
			for (int i = 0; i < length; i++) {
				points[arrayStart + i] = combList[i];
			}
			
			int closeToCenterLength = 0;
			closeToCenter = new Point[length];
			
			// builds the list of points that can be close enough to the split to be closer than the current
			// closest pair
			for (int i = 0; i < length; i++) {
				if (Math.abs(combList[i].getX() - median) < delta) {
					closeToCenter[closeToCenterLength] = combList[i];
					closeToCenterLength++;
				}
			}
			
			// checks if the points across the other side can be close enough to choose over the one on this side
			// of the split
			for (int i = 0; i < closeToCenterLength; i++) {				
				for (int j = i + 1; j < i + 15; j++) {
					if (j < closeToCenterLength) {
						float temp = (float) Math.sqrt(Math.pow(closeToCenter[i].getX()-closeToCenter[j].getX(),2) 
								+ Math.pow(closeToCenter[i].getY()-closeToCenter[j].getY(),2));
						if (dis > temp) {
							dis = temp;
						}
					}
				}
			}
		}
		return dis;
	}
}


// the subclass that helps by holding the information about each point
// and can compare the points to each other based on their X value
class Point implements Comparable<Point>{
	private float xValue;
	private float yValue;
	public Point(float x, float y) {
		xValue = x;
		yValue = y;
	}
	public float getX() {
		return xValue;
	}
	public float getY() {
		return yValue;
	}
	public int compareTo(Point one) {
		int val = (int) Math.signum(xValue - one.getX());
		return val;
	}
};
