//--------------------------------------------------------
// MinesweeperPanel.java        Author: Alex Lehmann
//
// Makes the graphics panel that the game will be played through
//----------------------------------------------------------

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class MinesweeperPanel extends JPanel {
	
	private JButton[][] buttons;
	private JLabel[][] revealed;
	private Minesweeper game;
	private JMenuBar top;
	private JMenu file, diff;
	private JMenuItem restart, exit, easy, normal, hard;
	private GridBagConstraints c;
	private MouseListener ml;
	private JLabel victory, Timer;
	private Timer t;
	private int counter = 0;

	//------------------------------------------------------------	
	// sets up the board and instantiates the menubar also creates the timer
	//------------------------------------------------------------
	public MinesweeperPanel() {

		game = new Minesweeper();
		
		makeBoard(game.getRows(), game.getCols());
	    t = new Timer(1000, new MenuButtonListener());
	    t.start();
		Timer = new JLabel("   Timer : "+ ("0") + "     ");
	    
        victory = new JLabel("");
		top = new JMenuBar();
	}
	
	//------------------------------------------------------------	
	// creates and returns the menubar
	//------------------------------------------------------------
	public JMenuBar getMenuBar() {
		file = new JMenu("File");
		restart = new JMenuItem("new");
		restart.addActionListener(new MenuButtonListener());
		exit = new JMenuItem("exit");
		exit.addActionListener(new MenuButtonListener());
		file.add(restart);
		file.add(exit);
		
		diff = new JMenu("Difficulty");
		easy = new JMenuItem("Easy");
		easy.addActionListener(new MenuButtonListener());
		normal = new JMenuItem("Normal");
		normal.addActionListener(new MenuButtonListener());
		hard = new JMenuItem("Hard");
		hard.addActionListener(new MenuButtonListener());
		diff.add(easy);
		diff.add(normal);
		diff.add(hard);
		
		top.add(file);
		top.add(diff);
		top.add(Timer);
		return top;
	}
	
	//------------------------------------------------------------	
	//creates a board using the demensions passed to it
	//------------------------------------------------------------
	private void makeBoard(int rows, int cols) {
		
		game = new Minesweeper(rows, cols);
		buttons = new JButton[game.getRows()][game.getCols()];
		revealed = new JLabel[game.getRows()][game.getCols()];
		
		ml = new MineButtonListener();
		
		setLayout(new GridBagLayout());
		c = new GridBagConstraints();
		
		c.weightx = 1.0;
		c.weighty = 1.0;
		c.ipadx = -100;
		c.ipady = -100;
		c.fill = GridBagConstraints.BOTH;
		
		for(int x = 0; x < game.getRows(); x++) {
			for(int y = 0; y < game.getCols(); y++) {
				c.gridx = x;
				c.gridy = y;
				buttons[x][y] = new JButton("");
				buttons[x][y].addMouseListener(ml);
				add(buttons[x][y], c);
				buttons[x][y].setMargin(new Insets(0, 0, 0, 0));
				revealed[x][y] = new JLabel();
			}
		}
		setPreferredSize(new Dimension(800,800));
	}
	
	//------------------------------------------------------------
	// adds listener to respond to button being pressed
	//------------------------------------------------------------
	private class MenuButtonListener implements ActionListener {
		//--------------------------------------------------------------
		// listens to the menu buttons and creates a new board of the correct
		// size if new or a difficulty is chosen and closes on exit
		//--------------------------------------------------------------
		public void actionPerformed(ActionEvent event) {
			
			if(counter < 999 && game.getStatus() == "play") {
				Timer.setText("   Timer : "+ (counter++) + "     ");
			}
			
			if(restart.equals(event.getSource())) {
				for(int x = 0; x < game.getRows(); x++) {
					for(int y = 0; y < game.getCols(); y++) {
						remove(buttons[x][y]);
						remove(revealed[x][y]);
					}
				}
				makeBoard(game.getRows(), game.getCols());
                victory.setText("");
                counter = 0;
                revalidate();
                repaint();
			}
			if(easy.equals(event.getSource())) {
				for(int x = 0; x < game.getRows(); x++) {
					for(int y = 0; y < game.getCols(); y++) {
						remove(buttons[x][y]);
						remove(revealed[x][y]);
					}
				}
				makeBoard(9, 9);
                victory.setText("");
                counter = 0;
                revalidate();
                repaint();
			}
			if(normal.equals(event.getSource())) {
				for(int x = 0; x < game.getRows(); x++) {
					for(int y = 0; y < game.getCols(); y++) {
						remove(buttons[x][y]);
						remove(revealed[x][y]);
					}
				}
				makeBoard(16, 16);
                victory.setText("");
                counter = 0;
                revalidate();
                repaint();
			}
			if(hard.equals(event.getSource())) {
				for(int x = 0; x < game.getRows(); x++) {
					for(int y = 0; y < game.getCols(); y++) {
						remove(buttons[x][y]);
						remove(revealed[x][y]);
					}
				}
				makeBoard(24, 24);
                victory.setText("");
                counter = 0;
                revalidate();
                repaint();
			}
			if(exit.equals(event.getSource())) {
				System.exit(0);
			}
		}
	}
	//------------------------------------------------------------
	// adds listener to respond to button being pressed
	//------------------------------------------------------------
	private class MineButtonListener implements MouseListener {
		
		//--------------------------------------------------------------
		//  updates the grid when a tile is clicked on
		//--------------------------------------------------------------
		public void mouseClicked(MouseEvent event) {
			boolean zero = false;
			for(int x = 0; x < game.getRows(); x++) {
				for(int y = 0; y < game.getCols(); y++) {
					if(buttons[x][y].equals(event.getSource())) {
						if(SwingUtilities.isLeftMouseButton(event) && game.getBoard(x, y) != 'F') {
							game.markTile(x, y, 0);
							buttons[x][y].setText(Character.toString(game.getBoard(x, y)));
							buttons[x][y].setEnabled(false);
							remove(buttons[x][y]);
							c.gridx = x;
							c.gridy = y;
							add(revealed[x][y], c);
							revealed[x][y].setHorizontalAlignment(SwingConstants.CENTER);
							if(game.getBoard(x, y) == '!') {
								revealed[x][y].setIcon(new ImageIcon("minered.jpg"));
							} else {
								revealed[x][y].setText(Character.toString(game.getBoard(x, y)));
								switch(game.getBoard(x, y)) {
								case ' ':
									zero = true;
								case '1':
									revealed[x][y].setForeground(Color.BLUE);
									break;
								case '2':
									revealed[x][y].setForeground(Color.GREEN);
									break;
								case '3':
									revealed[x][y].setForeground(Color.RED);
									break;
								case '4':
									revealed[x][y].setForeground(Color.MAGENTA);
									break;
								case '5':
									revealed[x][y].setForeground(Color.ORANGE);
									break;
								case '6':
									revealed[x][y].setForeground(Color.YELLOW);
									break;
								case 7:
									revealed[x][y].setForeground(Color.PINK);
									break;
								case 8:
									revealed[x][y].setForeground(Color.BLACK);
									break;
								default:
									break;
								}
							}
						}
						if(SwingUtilities.isRightMouseButton(event)) {
							game.markTile(x, y, 1);
							if(game.getBoard(x, y) == 'F') {
								buttons[x][y].setIcon(new ImageIcon("flag.jpg"));
							} else if(game.getBoard(x, y) == '?') {
								buttons[x][y].setIcon(new ImageIcon(""));
								buttons[x][y].setText("?");
							} else {
								buttons[x][y].setText("");
							}
						}
					}
				}
			}
			if(zero) {
				for(int x = 0; x < game.getRows(); x++) {
					for(int y = 0; y < game.getCols(); y++) {
						if(game.getTiles(x, y) == 0) {
							buttons[x][y].setText(Character.toString(game.getBoard(x, y)));
							buttons[x][y].setEnabled(false);
							remove(buttons[x][y]);
							c.gridx = x;
							c.gridy = y;
							add(revealed[x][y], c);
							revealed[x][y].setHorizontalAlignment(SwingConstants.CENTER);
							revealed[x][y].setText(Character.toString(game.getBoard(x, y)));
							switch(game.getBoard(x, y)) {
							case ' ':
								zero = true;
							case '1':
								revealed[x][y].setForeground(Color.BLUE);
								break;
							case '2':
								revealed[x][y].setForeground(Color.GREEN);
								break;
							case '3':
								revealed[x][y].setForeground(Color.RED);
								break;
							case '4':
								revealed[x][y].setForeground(Color.MAGENTA);
								break;
							case '5':
								revealed[x][y].setForeground(Color.ORANGE);
								break;
							case '6':
								revealed[x][y].setForeground(Color.YELLOW);
								break;
							case 7:
								revealed[x][y].setForeground(Color.PINK);
								break;
							case 8:
								revealed[x][y].setForeground(Color.BLACK);
								break;
							default:
								break;
							}
						}
					}
				}
				zero = false;
			}

			if(game.getStatus() == "lost") {
				victory.setText("YOU LOSE!!");
				top.add(victory);
				for(int x = 0; x < game.getRows(); x++) {
					for(int y = 0; y < game.getCols(); y++) {
						if(game.getBoard(x, y) == '*') {
							buttons[x][y].setText(Character.toString(game.getBoard(x, y)));
							buttons[x][y].setEnabled(false);
							remove(buttons[x][y]);
							c.gridx = x;
							c.gridy = y;
							add(revealed[x][y], c);
							revealed[x][y].setHorizontalAlignment(SwingConstants.CENTER);
							revealed[x][y].setIcon(new ImageIcon("mine.jpg"));
						}
						if(game.getBoard(x, y) != '*' && game.getTiles(x, y) == 3) {
							buttons[x][y].setText(Character.toString(game.getBoard(x, y)));
							buttons[x][y].setEnabled(false);
							remove(buttons[x][y]);
							c.gridx = x;
							c.gridy = y;
							add(revealed[x][y], c);
							revealed[x][y].setHorizontalAlignment(SwingConstants.CENTER);
							revealed[x][y].setIcon(new ImageIcon("minex.jpg"));
						}
						buttons[x][y].removeMouseListener(ml);
					}
				}
			}
			if(game.getStatus() == "won") {
				victory.setText("YOU WIN!!");
				top.add(victory);
				for(int x = 0; x < game.getRows(); x++) {
					for(int y = 0; y < game.getCols(); y++) {
						buttons[x][y].removeMouseListener(ml);
					}
				}
			}
		}

		public void mousePressed(MouseEvent e) {	
		}

		public void mouseReleased(MouseEvent e) {
		}

		public void mouseEntered(MouseEvent e) {
		}

		public void mouseExited(MouseEvent e) {
		}
	}
}