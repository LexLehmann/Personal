import java.io.BufferedReader;
import java.io.FileReader;

public class Drainage {
	static int[][] elevations;
	static PathLengths[][] paths;
	static int rows, columns;
	
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
				
				for (int i = 0; i < rows; i++) {
					line = bR.readLine();
					info = line.split(" ");
					
					for (int j = 0; j < columns; j++) {
						elevations[i][j] = Integer.parseInt(info[j]);
						paths[i][j] = new PathLengths();
					}
				}
				
				for (int i = 0; i < rows; i++) {
					for (int j = 0; j < columns; j++) {
						if (paths[i][j].getPathDown() == 0) {
							setPaths(i, j);
						}
					}
				}
				
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
