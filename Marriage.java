import java.io.BufferedReader;
import java.io.FileReader;

public class Marriage {
	
	// finds the shortest paths for w to x and y to z such
	// that the two things moving through the graph are never agjancent to each other
	// does this by building a new graph with v^2 vertices
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		try(BufferedReader bR = new BufferedReader(new FileReader("chapel.txt"))) {
			int numVertices;
			String line;
			String[] info;
			int hisStart, hisEnd, herStart, herEnd;
			int[][] chapel;
			int[][] loverLoc;
			int[] edges;
			
			line = bR.readLine();
			numVertices = Integer.parseInt(line);
			chapel = new int[numVertices][];
			
			line = bR.readLine();
			info = line.split(" ");
			hisStart = Integer.parseInt(info[0]);
			hisEnd = Integer.parseInt(info[1]);
			
			line = bR.readLine();
			info = line.split(" ");
			herStart = Integer.parseInt(info[0]);
			herEnd = Integer.parseInt(info[1]);
			
			for (int i = 0; i < numVertices; i++) {
				line = bR.readLine();
				info = line.split(" ");
				edges = new int[info.length + 1];
				for (int j  = 0; j < info.length; j++) {
					edges[j + 1] = Integer.parseInt(info[j]);
				}
				edges[0] = i;
				chapel[i] = edges;
			}
			
			loverLoc = new int[numVertices * numVertices][];
			
			// builds the new graph that represents where both
			// lovers are at the same time
			for (int i = 0; i < loverLoc.length; i++) {
				int one = i / numVertices;
				int two = i % numVertices;
				int[] newEdges = new int[numVertices * numVertices];
				boolean notAdj = true;
				int count = 0;
				
				for (int j = 0; j < chapel[one].length; j++) {
					if (chapel[one][j] == two) {
						notAdj = false;
					}
				}
				
				if (notAdj) {
					for (int j = 0; j < chapel[one].length; j++)  {
						for (int k = 0; k < chapel[two].length; k++) {
							notAdj = true;
							
							for (int l = 0; l < chapel[chapel[one][j]].length; l++) {
								if (chapel[chapel[one][j]][l] == chapel[two][k]) {
									notAdj = false;
								}
							}
							if (notAdj && (j != 0 || k != 0)) {
								newEdges[count] = chapel[one][j] * numVertices + chapel[two][k];
								count++;
							}
						}
					}
					
					int[] edgeList = new int[count];
					
					for (int j = 0; j < count; j++) {
						edgeList[j] = newEdges[j];
					}
					
					loverLoc[i] = edgeList;
				} else {
					loverLoc[i] = new int[0];
				}
			}
			
			// runs breadth-first search to find the
			// shortest path
			int start = hisStart * numVertices + herStart;
			int end = hisEnd * numVertices + herEnd;
			int removed;
			
			int[] queue = new int[loverLoc.length];
			int queueStart = 0;
			int queueEnd = 0;
			
			queue[queueEnd] = start;
			queueEnd++;
			
			int[] branches = new int[loverLoc.length];
			branches[start] = -1;
			
			do {
				removed = queue[queueStart];
				queueStart++;
				
				for (int i = 0; i < loverLoc[removed].length; i++) {
					if (branches[loverLoc[removed][i]] == 0) {
						queue[queueEnd] = loverLoc[removed][i];
						queueEnd++;
						branches[loverLoc[removed][i]] = removed;
					}
				}
			} while (removed != end);
			
			String hisPath = "";
			String herPath = "";
			
			// prints out the two paths
			while (removed != -1) {
				hisPath = (int)(removed / numVertices) + " " + hisPath;
				herPath = (removed % numVertices) + " " + herPath;
				
				removed = branches[removed];
			}
			
			System.out.println(hisPath);
			System.out.println(herPath);
			/*for (int i = 0; i < loverLoc.length; i++) {
				for (int j = 0; j < loverLoc[i].length; j++) {
					System.out.print(loverLoc[i][j] + " ");
				}
				System.out.println("");
			}
			*/
		} catch (Exception ex) {
			ex.printStackTrace();
			System.err.println("Error");
		}
	}

}
