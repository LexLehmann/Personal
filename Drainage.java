import java.io.BufferedReader;
import java.io.FileReader;

public class Drainage {
	static int[][] elevations;
	static PathLengths[][] paths;
	static int rows, columns;
	
	// if given a map that has elevation values it returns the longest
	// strictly decreasing path
	public static void main(String[] args){
		
		try(BufferedReader bR = new BufferedReader(new FileReader("map.txt"))) {
			int testCases;
			String caseName, line;
			String[] info;
			
			line = bR.readLine();
			testCases = Integer.parseInt(line);
			
			for (int caseNumber = 0; caseNumber < testCases; caseNumber++) {
				
				line = bR.readLine();
				info = line.split(" ");
				caseName = info[0];
				rows = Integer.parseInt(info[1]);
				columns = Integer.parseInt(info[2]);
				
				elevations = new int[rows][columns];
				paths =  new PathLengths[rows][columns];
				
				// intializes the paths array
				for (int i = 0; i < rows; i++) {
					line = bR.readLine();
					info = line.split(" ");
					
					for (int j = 0; j < columns; j++) {
						elevations[i][j] = Integer.parseInt(info[j]);
						paths[i][j] = new PathLengths();
					}
				}
				
				//sets the values of the paths array
				// this is done by recursion, but it saves the values
				// of the points it reachs so it doesn't ever get called twice on the 
				// same cell of the array
				for (int i = 0; i < rows; i++) {
					for (int j = 0; j < columns; j++) {
						if (paths[i][j].getPathDown() == 0) {
							setPaths(i, j);
						}
					}
				}
				
				// finds the longest path done by searching the array for the max value
				int max = 0;
				for (int i = 0; i < rows; i++) {
					for (int j = 0; j < columns; j++) {
						if (max < paths[i][j].getPathDown()) {
							max = paths[i][j].getPathDown();
						}
					}
				}
				
				System.out.println(caseName + ": " + max);
			}
			
		} catch (Exception ex) {
			ex.printStackTrace();
			System.err.println("Error");
		}
	}
	
	// gets call of the paths array and runs recursivlly around it on
	// all cells that are set and are below it
	// sets the value of the cell after it determines which path
	// down is the longest and terminates
	// returns the length of the pathdown to make it easier to 
	// select which path down was the longest
	private static int setPaths(int i, int j) {
		int pathDown = 0;
		int temp = 0;
		if (i > 0 && elevations[i-1][j] < elevations[i][j]) {
			if (paths[i-1][j].getPathDown() == 0) {
				temp = setPaths(i-1, j) + 1;
			} else {
				temp = paths[i-1][j].getPathDown() + 1;
			}
			if (pathDown < temp) {
				pathDown = temp;
			}
		}
		if (j > 0 && elevations[i][j-1] < elevations[i][j]) {
			if (paths[i][j-1].getPathDown() == 0) {
				temp = setPaths(i, j-1) + 1;
			} else {
				temp = paths[i][j-1].getPathDown() + 1;
			}
			if (pathDown < temp) {
				pathDown = temp;
			}
		}
		if (j + 1 < columns && elevations[i][j+1] < elevations[i][j]) {
			if (paths[i][j+1].getPathDown() == 0) {
				temp = setPaths(i, j+1) + 1;
			} else {
				temp = paths[i][j+1].getPathDown() + 1;
			}
			if (pathDown < temp) {
				pathDown = temp;
			}
		}
		if (i + 1 < rows && elevations[i+1][j] < elevations[i][j]) {
			if (paths[i+1][j].getPathDown() == 0) {
				temp = setPaths(i + 1, j) + 1;
			} else {
				temp = paths[i+1][j].getPathDown() + 1;
			}
			if (pathDown < temp) {
				pathDown = temp;
			}
		}
		
		if (pathDown == 0) {
			pathDown = 1;
		}
		paths[i][j].setPathDown(pathDown);
		
		return pathDown;
	}
}

// helper class that holds the path down and returns the values
// this is a relic of a previous version of the program that had more information
// stored here
class PathLengths {
	private int pathDown;
	
	public PathLengths() {
		pathDown = 0;
	}
	
	public int getPathDown() {
		return pathDown;
	}
	
	public void setPathDown(int val) {
		pathDown = val;
	}
}
