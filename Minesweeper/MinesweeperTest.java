/*
 * 
 * minesweeperTest.java
 *
 */
public class MinesweeperTest {

	public static void main(String[] args) {
        
        //create new minesweeper instance 2 rows by 5 columns
	Minesweeper game = new Minesweeper(3, 3);

        //display mines
        System.out.println( game.toStringMines() );
        
	//display tiles
	System.out.println( game.toStringTiles() );
	    
	//display board
	System.out.println( game.toStringBoard() );
	
		
	//mark tile at 0,0 as Open
	game.markTile(0,0,0);
	
	//mark tile at 0,1 as Question
	game.markTile(0,1,1);
	game.markTile(0,1,1);
			
	//mark tile at 0,0 as Mine
	game.markTile(0,2,1);
		  
        //display tiles 
   	System.out.println( game.toStringTiles() );
	   
	//display board
	System.out.println( game.toStringBoard() );
		
	System.exit(0);
     }

}//minesweeperTest