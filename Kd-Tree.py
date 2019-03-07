import java.io.BufferedReader;
import java.io.FileReader;
import java.util.Arrays;
import java.util.Random;

// implements a kd Tree and uses it to find the closest pair of
// points in any demensional space in O(nlogn) time
public class kdTree {
	static int k, numPoints;
	static double[][] tree;

	public static void main(String[] args) {
		try(BufferedReader bR = new BufferedReader(new FileReader("points.txt"))) {
		double[][] inputArray;
		double[][][] sortedArrays;
		String[] info;
		String line;
		int treeSize, tempNumPoints;
		
		line = bR.readLine();
		info = line.split(" ");
		
		k = Integer.parseInt(info[0]);
		numPoints = Integer.parseInt(info[1]);
		
		inputArray = new double[numPoints][];
		for(int i = 0; i < numPoints; i++) {
			line = bR.readLine();
			info = line.split(" ");
			double[] nextPoint = new double[k];
			
			for (int j = 0; j < k; j++) {
				nextPoint[j] = Double.parseDouble(info[j]);
			}
			
			inputArray[i] = nextPoint;
		}
		
		sortedArrays = new double[k][][];
		
		for (int i = 0; i < k; i++) {
			double[][] newCopy = Arrays.copyOf(inputArray, numPoints);
			quickSort(newCopy, 0, numPoints-1, i);
			
			sortedArrays[i] = newCopy;
		}
		
		treeSize = 1;
		tempNumPoints = numPoints;
		while (tempNumPoints != 0) {
			treeSize = treeSize*2;
			tempNumPoints = tempNumPoints/2;
		}
		
		
		tree = new double[treeSize][];
		
		buildTree(sortedArrays, 1, 0);
		
		
		double[] neighborTest = {6,5,41};
		
		
		System.out.println(closestPair(inputArray));
		
		} catch (Exception ex) {
			ex.printStackTrace();
			System.err.println("Error");
		}
	}
	
	private static double closestPair(double[][] input) {
		double dis = Double.MAX_VALUE;
		double temp;
		for (int i = 0; i < input.length; i++) {
			temp = nearestNeighbor(input[i], 1, 0);
			if (temp < dis) {
				dis = temp;
			}
		}
		
		return dis;
	}
	
	private static double nearestNeighbor(double[] point, int i, int dem) {
		double dis = Double.MAX_VALUE;
		double disToHere = 0;
		double disAcross = Double.MAX_VALUE;
		boolean left = true;
		
		
		if (i * 2 < tree.length) {
			if (tree[i * 2] != null && point[dem] < tree[i][dem]) {
				dis = nearestNeighbor(point, i * 2, (dem + 1) % k);
				left = true;
			} else if (tree[(i * 2) + 1] != null) {
				dis = nearestNeighbor(point, (i * 2) + 1, (dem + 1) % k);
				left = false;
			}
		}
		
		for(int j = 0; j < k; j++) {
			disToHere = disToHere + Math.pow((point[j] - tree[i][j]), 2);
		}
		disToHere = Math.sqrt(disToHere);
		
		
		if (dis > disToHere && tree[i] != point) {
			dis = disToHere;
		}
		
		if (i * 2 < tree.length) {
			if (tree[(i * 2) + 1] != null && left && point[dem] + dis > tree[i][dem]) {
				disAcross = nearestNeighbor(point, (i * 2) + 1, (dem + 1) % k);
			} else if (tree[i * 2] != null && !left && point[dem] - dis < tree[i][dem]) {
				disAcross = nearestNeighbor(point, i * 2, (dem + 1) % k);
			}
		}
		
		if (dis > disAcross) {
			dis = disAcross;
		}
		
		return dis;
	}


	private static void buildTree(double[][][] arrays, int place, int demCompare) {
		
		/*System.out.println("input array");
		for (int i = 0; i < k; i++) {
			for (int j = 0; j < arrays[0].length; j++) {
				for (int val = 0; val < k; val++) {
					System.out.print(arrays[i][j][val] + " ");
				}
				System.out.println("");
			}
			System.out.println("");
		}*/
		
		tree[place] = arrays[demCompare][arrays[0].length/2];
		
//		System.out.println("center choice");
//		System.out.println(arrays[demCompare][arrays[0].length/2][0] + " " + arrays[demCompare][arrays[0].length/2][1] + " " + arrays[demCompare][arrays[0].length/2][2]);
				
		if (arrays[0].length > 1) {
			double[][][] left = new double[k][arrays[0].length/2][];
			double[][][] right = new double[k][arrays[0].length - arrays[0].length/2 - 1][];
			
			for (int i = 0; i < k; i++) {
				int leftCount = 0;
				int rightCount = 0;
				for (int j = 0; j < arrays[0].length; j++) {
					if (arrays[i][j][demCompare] < arrays[demCompare][arrays[0].length/2][demCompare]) {
						left[i][leftCount] = arrays[i][j];
						leftCount++;
					} else if (arrays[i][j][demCompare] > arrays[demCompare][arrays[0].length/2][demCompare]) {
						right[i][rightCount] = arrays[i][j];
						rightCount++;
					} else {
						int pointTest = 0;
						while (arrays[demCompare][pointTest] != arrays[i][j]) {
							pointTest++;
						}
						if (pointTest < arrays[0].length/2) {
							left[i][leftCount] = arrays[i][j];
							leftCount++;
						} else if (pointTest > arrays[0].length/2) {
							right[i][rightCount] = arrays[i][j];
							rightCount++;
						}
					}
				}
			}
			
			if (left[0].length > 0) {
				buildTree(left, place * 2, (demCompare + 1) % k);
			}
			if (right[0].length > 0) {
				buildTree(right, (place * 2) + 1, (demCompare + 1) % k);
			}
		}
	}


	public static void quickSort(double[][] array, int start, int end, int k) {
		Random rand = new Random(); 
		if (start < end) {
			int pivot = rand.nextInt(end - start) + start;
			
			double[] temp = array[pivot];
			array[pivot] = array[start];
			array[start] = temp;
			
			int front = start;
			int back = end;
			boolean pivotFront = true;
			while (front < back) {
				if (array[front][k] > array[back][k]) {
					temp = array[front];
					array[front] = array[back];
					array[back] = temp;
					if (pivotFront) {
						front++;
						pivotFront = false;
					} else {
						back--;
						pivotFront = true;
					}
				} else {
					if (pivotFront) {
						back--;
					} else {
						front++;
					}
				}
			}
			quickSort(array, start, front-1, k);
			quickSort(array, front+1, end, k);
		}
	}
}
