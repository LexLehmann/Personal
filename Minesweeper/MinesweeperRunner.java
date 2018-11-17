//--------------------------------------------------------
// GameRunner.java        Author: Alex Lehmann
//
// Runs the MinesweeperPanel that runs the game
//----------------------------------------------------------

import javax.swing.JFrame;
public class MinesweeperRunner {
	
	//----------------------------------------------
	// Runs the Game
	//----------------------------------------------
	public static void main(String[] args) {
		
	      JFrame frame = new JFrame ("Minesweeper");
	      frame.setDefaultCloseOperation (JFrame.EXIT_ON_CLOSE);
	      
	      MinesweeperPanel panel = new MinesweeperPanel();
	      
	      frame.getContentPane().add(panel);
	      frame.setJMenuBar(panel.getMenuBar());

	      frame.pack();
	      frame.setVisible(true);
	}
}