import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class Celebrity {


	// Implement this method
	public String findCelebrity(List<String> guests) {
		
		String celebrity = "";
		if (guests.size() > 1) {
			List<String> notEliminated = new ArrayList<String>();
			for (int i = 0; i < guests.size() - 1; i = i + 2) {
				boolean oneKnowsTwo = knows(guests.get(i), guests.get(i+1));
				boolean twoKnowsOne = knows(guests.get(i+1), guests.get(i));
			
				if (!oneKnowsTwo && twoKnowsOne) {
					notEliminated.add(guests.get(i));
				} else if (oneKnowsTwo && !twoKnowsOne) {
					notEliminated.add(guests.get(i+1));
				}
			}
			if ((guests.size() - 1) % 2 == 0) {
				notEliminated.add(guests.get(guests.size() - 1));
			}
		
			celebrity = findCelebrity(notEliminated);
		} else { 
			celebrity = guests.get(0);
		}

		return celebrity;
	}

	/************************************************
	 * Under penalty of the Honor Code  
	 * Do Not Change Anything Below Here 
	 * (In your final submission)        
	 ************************************************/

	// Helper method. Will say if the first parameter knows the second parameter.
	// if a knows b, returns true.  Otherwise, returns false.
	public boolean knows(String a, String b) {
		countOfCallsToKnows++;
		if (knowsWhoFileStorageMap.get(a).contains(b))
			return true;
		return false;
	}


	/************************************************
	 * Under penalty of the Honor Code  
	 * Do not use anything (fields OR methods) 
	 * initialized or defined below
	 * (In your final submission)        
	 ************************************************/


	// Field (DO NOT CHANGE)
	private HashMap<String, List<String>> knowsWhoFileStorageMap;
	private int countOfCallsToKnows = 0;

	public void run() {
		knowsWhoFileStorageMap = new HashMap<>();

		// Read in the input file
		try (BufferedReader br = new BufferedReader(new FileReader("party.txt"))) {
			String line;
			while ((line = br.readLine()) != null) {
				if (line.isEmpty()) continue;
				String[] parts = line.split(" ");
				if (parts.length > 0) {
					String subject = parts[0];
					ArrayList<String> knows = new ArrayList<>();
					for (int i = 1; i < parts.length; i++)
						knows.add(parts[i]);
					knowsWhoFileStorageMap.put(subject, knows);
				}
			}        

			// Call findCelebrity and print the result
			System.out.println(findCelebrity(new ArrayList<String>(knowsWhoFileStorageMap.keySet()))
					+ " " + countOfCallsToKnows);

		} catch (Exception e) {
			e.printStackTrace();
			System.err.println("Error occurred when reading file");
		}

	}

	public static void main(String[] args) {
		Celebrity cp = new Celebrity();
		cp.run();
	}

}