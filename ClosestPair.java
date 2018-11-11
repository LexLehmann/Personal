// Author : Alex Lehmann (awl9x)
// ClosestPair.java
// implements an algorithum to find the closest pair of points in nlogn time
import java.io.*;
import java.util.Arrays;


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
		System.out.println(shortestDis(0, numPoints-1));
	}
	public static float shortestDis(int arrayStart, int arrayEnd) {
		float dis = 0;
		if (arrayEnd - arrayStart < 3) {							// Base Case
			Point tempPoint;
			if (arrayEnd - arrayStart == 1) {
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
			
			one = shortestDis(arrayStart, half);
			two = shortestDis(half + 1, arrayEnd);
			
			delta = Math.min(one, two);
			dis = delta;
			length = arrayEnd - arrayStart + 1;
			
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
			
			for (int i = 0; i < length; i++) {
				if (Math.abs(combList[i].getX() - median) < delta) {
					closeToCenter[closeToCenterLength] = combList[i];
					closeToCenterLength++;
				}
			}
			
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