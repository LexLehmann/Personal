//--------------------------------------------------------
// Minesweeper.java        Author: Alex Lehmann
//
// Stores the boards and determines the actions to
// the board
//----------------------------------------------------------

public class Minesweeper {

	private int[][] mines;
	private int[][] tiles;
	private String status;

	//------------------------------------------------------------	
	// default constructor board size 9 x 9
	//------------------------------------------------------------	
	public Minesweeper() {
		initGame(9, 9);
	}

	//------------------------------------------------------------	
	// alternate constructor use specifies board size
	//------------------------------------------------------------	
	public Minesweeper(int newRows, int newCols) {
		initGame(newRows, newCols);
	}

	//------------------------------------------------------------	
	// returns game status
	//------------------------------------------------------------	
	public String getStatus() {
		return status;
	}

	//------------------------------------------------------------	
	// returns number of rows
	//------------------------------------------------------------	
	public int getRows() {
		return mines.length;
	}

	//------------------------------------------------------------	
	// returns number of columns
	//------------------------------------------------------------	
	public int getCols() {
		return mines[0].length;
	}

	//------------------------------------------------------------	
	//returns the value on the mine array
	//------------------------------------------------------------	
	public int getMines(int r, int c) {
		if (validIndex(r, c)) {
			return mines[r][c];
		} else {
			return -1;
		}
	}

	//------------------------------------------------------------	
	//returns the value on the tiles array
	//------------------------------------------------------------	
	public int getTiles(int r, int c) {
		if (validIndex(r, c)) {
			return tiles[r][c];
		} else {
			return -1;
		}
	}
	
	//------------------------------------------------------------	
	// mark tile - open tile, close tile, <br>
	// flag tile as mine, set tile as question mark, close tile
	//------------------------------------------------------------	
	public void markTile(int r, int c, int t) {
		if (tiles[r][c] != 0) {
			if (t == 0 && tiles[r][c] != 3) {
				openTile(r, c);
				if (gameWon()) {
					status = "won";
				}
				if (mines[r][c] == 9) {
					status = "lost";
				}
			}
			if (t == 1) {
				if (tiles[r][c] == 1) {
					tiles[r][c] = 3;
				}else if (tiles[r][c] == 3) {
					tiles[r][c] = 2;
				}else if (tiles[r][c] == 2) {
					tiles[r][c] = 1;
				}
			}
		}
	}
	
	//------------------------------------------------------------	
	// Opens a Tiles recursively opens tiles around it if the tile is 0
	//------------------------------------------------------------	
	private void openTile(int r, int c) {
		tiles[r][c] = 0;
		if(mines[r][c] == 0) {
			for(int y = -1; y < 2; y++) {
				for(int z = -1; z < 2; z++) {
					if(validIndex(r + y, c + z) && tiles[r + y][c + z] != 0) {
						openTile(r + y, c + z);
					}
				}
			}
		} 
	}

	//------------------------------------------------------------	
	// returns the mines array as a string
	//------------------------------------------------------------	
	public String toStringMines() {
		String result = "\n";

		for (int r = 0; r < mines.length; r++) {
			for (int c = 0; c < mines[r].length; c++)
				result = result + mines[r][c];

			result += "\n";
		}

		return result;
	}

	//------------------------------------------------------------	
	// returns the tiles array as a string
	//------------------------------------------------------------	
	public String toStringTiles() {
		String result = "\n";

		for (int r = 0; r < mines.length; r++) {
			for (int c = 0; c < mines[r].length; c++)
				result = result + tiles[r][c];

			result += "\n";
		}

		return result;
	}

	//------------------------------------------------------------	
	// returns the game board as a string
	//------------------------------------------------------------	
	public String toStringBoard() {
		String result = "";

		for (int r = 0; r < tiles.length; r++) {
			for (int c = 0; c < tiles[r].length; c++) {
				result += this.getBoard(r, c);
			}
			result += "\n"; //advance to next line
		}

		return result;
	}

	//------------------------------------------------------------	
	// getBoard - determines current game board character for r,c position
	//------------------------------------------------------------	
	public char getBoard(int r, int c) {
		char val = '0';
		if (status == "play" && tiles[r][c] != 0) {
			switch(tiles[r][c]) {
			case 1:
				val = 'X';
				break;
			case 2:
				val = '?';
				break;
			case 3:
				val = 'F';
				break;
			}
		} else {
			switch(mines[r][c]) {
			case 0: 
				val = ' ';
				break;
			case 1:
				val = '1';
				break;
			case 2:
				val = '2';
				break;
			case 3:
				val = '3';
				break;
			case 4:
				val = '4';
				break;
			case 5:
				val = '5';
				break;
			case 6:
				val = '6';
				break;
			case 7:
				val = '7';
				break;
			case 8:
				val = '8';
				break;
			case 9: 
				val = '*';
				break;
			default:
				break;
			}
			if (status == "won") {
				if(mines[r][c] == 9) {
					val = 'F';
				}
			}
			if (status == "lost") {
				if (tiles[r][c] == 0  && mines[r][c] == 9) {
					val = '!';
				}
				if (tiles[r][c] == 3 && mines[r][c] != 9) {
					val = '-';
				}
			}
		}
		return val;
	}

	//------------------------------------------------------------	
	// create mines & tiles arrays
	//------------------------------------------------------------	
	private void initGame(int newRows, int newCols) {
		if ((newRows >= 1) && (newCols >= 1)) {
			mines = new int[newRows][newCols];
			tiles = new int[newRows][newCols];

			resetTiles();
			placeMines();
			calculateClues();
			status = "play";
		}
	}

	//------------------------------------------------------------	
	// starts the tiles board with closed tiles
	//------------------------------------------------------------	
	private void resetTiles() {
		for(int i = 0; i < mines.length; i++) {
			for(int j = 0; j < mines[i].length; j++) {
				tiles[i][j] = 1;
			}
		}
	}

	//------------------------------------------------------------	
	// places mines randomly on grid
	//------------------------------------------------------------	
	private void placeMines() {
		int numMines = 0;
		while(numMines < 1) {
			for(int i = 0; i < mines.length; i++) {
				for(int j = 0; j < mines[i].length; j++) {
					double temp = Math.random();
					if(temp < (avgMines() / (double)(mines.length * mines[0].length))) {
						mines[i][j] = 9;
						numMines++;
					}
				}
			}
		}
	}
	
	//------------------------------------------------------------	
	// calculates the average number of mines there can be
	//------------------------------------------------------------	
	private double avgMines() {
		double val = ( (mines.length + 1) * mines[0].length) / 10.0;
		return val;
	}

	//------------------------------------------------------------	
	// calculates clue values and adds them to array
	//------------------------------------------------------------	
	private void calculateClues() {
		for (int i = 0; i < mines.length; i++) {
			for (int j = 0; j < mines[i].length; j++) {
				if (mines[i][j] != 9) {
					mines[i][j] = 0;
					for (int y = -1; y < 2; y++) {
						for (int z = -1; z < 2; z++) {
							if (validIndex(i+z, j+y) && mines[i+z][j+y] == 9) {
								mines[i][j]++;
							}
						}
					}
				}
			}
		}
	}

	//------------------------------------------------------------	
	// determines if x,y is valid position
	//------------------------------------------------------------	
	private boolean validIndex(int x, int y) {
		boolean val;
		try {
			int test = mines[x][y];
			val = true;
		}catch(ArrayIndexOutOfBoundsException exception) {
			val = false;
		}
		return val;
	}

	//------------------------------------------------------------	
	//determines if game is won
	//------------------------------------------------------------	
	private boolean gameWon() {
		boolean val = true;
		for(int i = 0; i < mines.length; i++) {
			for(int j = 0; j < mines[i].length; j++) {
				if(!(tiles[i][j] == 0 || mines[i][j] == 9)) {
					val = false;
				}
			}
		}
		return val;
	}

}