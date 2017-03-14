import java.io.*;

class Queens {
    final boolean available = true;
    final int squares = 5, norm = squares - 1;
    int[] positionInRow = new int[squares];
    boolean[] column = new boolean[squares];
    boolean[] leftDiagonal  = new boolean[squares*2 - 1];
    boolean[] rightDiagonal = new boolean[squares*2 - 1];
    int howMany = 0;
    Queens() {
        for (int i = 0; i < squares; i++) {
            positionInRow[i] = -1;
            column[i] = available;
        }
        for (int i = 0; i < squares*2 - 1; i++)
            leftDiagonal[i] = rightDiagonal[i] = available;
    }
    void printBoard(PrintStream out) {
        //.........
    }
    void putQueen(int row) {
        for (int col = 0; col < squares; col++) 
            if (column[col] == available &&
                leftDiagonal [row+col] == available &&
                rightDiagonal[row-col+norm] == available) {
                positionInRow[row] = col;
                column[col] = !available;
                leftDiagonal[row+col] = !available;
                rightDiagonal[row-col+norm] = !available;
                if (row < squares-1)
                     putQueen(row+1);
                else printBoard(System.out);
                column[col] = available;
                leftDiagonal[row+col] = available;
                rightDiagonal[row-col+norm] = available;
            }
    }
    public static void main(String args[]) {
        Queens queens = new Queens();
        queens.putQueen(0);
        System.out.println(queens.howMany + " solutions found.");
    }
}

