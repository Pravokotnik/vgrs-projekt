#include <gui/screen1_screen/Screen1View.hpp>

//moji editi
#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

//moje
#include <tuple>
#include <vector>
#include <algorithm> // For std::copy
#include <cstdlib>   // For std::rand

//#include <touchgfx/hal/HAL.hpp>
//#include "main.h"


int globalGrid[3][3] = {0};
int jebot = 0;
int pressed = 0;


int zmagep1 = 0;
int zmagep2 = 0;

int roundcount = 0;

int winner = 0;

int borut = 0;

Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();

    for (int i = 0; i < 3; i++) {
    	for (int j = 0; j < 3; j++) {
    		globalGrid[i][j] = 0;
    	}
    }
    jebot = 0;
    pressed = 0;


    zmagep1 = 0;
    zmagep2 = 0;

    roundcount = 0;

    winner = 0;

    borut = 0;
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::botgamemode()
{
	jebot = 1;
}

void Screen1View::prgamemode()
{
	jebot = 0;
}

// ok haha no lol um basically bo tole bot whoops
// bot ma Xe REMEMBER


struct Move
{
    int row, col;
};

int prazno = 0;
int krog = 1; //opp
int kriz = 2; //bot = player

bool isMovesLeft(int board[3][3])
{
    for (int i = 0; i<3; i++)
        for (int j = 0; j<3; j++)
            if (board[i][j]==prazno)
                return true;
    return false;
}

int evaluate(int b[3][3])
{
    // Checking for Rows for X or O victory.
    for (int row = 0; row<3; row++)
    {
        if (b[row][0]==b[row][1] &&
            b[row][1]==b[row][2])
        {
            if (b[row][0]==kriz)
                return +10;
            else if (b[row][0]==krog)
                return -10;
        }
    }

    // Checking for Columns for X or O victory.
    for (int col = 0; col<3; col++)
    {
        if (b[0][col]==b[1][col] &&
            b[1][col]==b[2][col])
        {
            if (b[0][col]==kriz)
                return +10;

            else if (b[0][col]==krog)
                return -10;
        }
    }

    // Checking for Diagonals for X or O victory.
    if (b[0][0]==b[1][1] && b[1][1]==b[2][2])
    {
        if (b[0][0]==kriz)
            return +10;
        else if (b[0][0]==krog)
            return -10;
    }

    if (b[0][2]==b[1][1] && b[1][1]==b[2][0])
    {
        if (b[0][2]==kriz)
            return +10;
        else if (b[0][2]==krog)
            return -10;
    }

    // Else if none of them have won then return 0
    return 0;
}

int minimax(int board[3][3], int depth, bool isMax)
{
    int score = evaluate(board);

    // If Maximizer has won the game return his/her
    // evaluated score
    if (score == 10)
        return score;

    // If Minimizer has won the game return his/her
    // evaluated score
    if (score == -10)
        return score;

    // If there are no more moves and no winner then
    // it is a tie
    if (isMovesLeft(board)==false)
        return 0;

    // If this maximizer's move
    if (isMax)
    {
        int best = -1000;

        // Traverse all cells
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                // Check if cell is empty
                if (board[i][j]==prazno)
                {
                    // Make the move
                    board[i][j] = kriz;

                    // Call minimax recursively and choose
                    // the maximum value
                    best = std::max( best,
                        minimax(board, depth+1, !isMax) );

                    // Undo the move
                    board[i][j] = prazno;
                }
            }
        }
        return best;
    }

    // If this minimizer's move
    else
    {
        int best = 1000;

        // Traverse all cells
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                // Check if cell is empty
                if (board[i][j]==prazno)
                {
                    // Make the move
                    board[i][j] = krog;

                    // Call minimax recursively and choose
                    // the minimum value
                    best = std::min(best,
                           minimax(board, depth+1, !isMax));

                    // Undo the move
                    board[i][j] = prazno;
                }
            }
        }
        return best;
    }
}

Move findBestMove(int board[3][3])
{
    int bestVal = -1000;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;

    // Traverse all cells, evaluate minimax function for
    // all empty cells. And return the cell with optimal
    // value.
    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            // Check if cell is empty
            if (board[i][j]==prazno)
            {
                // Make the move
                board[i][j] = kriz;

                // compute evaluation function for this
                // move.
                int moveVal = minimax(board, 0, false);

                // Undo the move
                board[i][j] = prazno;

                // If the value of the current move is
                // more than the best value, then update
                // best/
                if (moveVal > bestVal)
                {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    return bestMove;
}

/*int prazno = 0;
int krog = 1; //opp
int kriz = 2; //bot = player
*/

int checkIfWin() {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (globalGrid[i][0] == globalGrid[i][1] && globalGrid[i][1] == globalGrid[i][2] && globalGrid[i][0] != 0) {
            return globalGrid[i][0];  // Return the winner (1 or 2)
        }
    }

    // Check columns
    for (int i = 0; i < 3; i++) {
        if (globalGrid[0][i] == globalGrid[1][i] && globalGrid[1][i] == globalGrid[2][i] && globalGrid[0][i] != 0) {
            return globalGrid[0][i];  // Return the winner (1 or 2)
        }
    }

    // Check diagonals
    if (globalGrid[0][0] == globalGrid[1][1] && globalGrid[1][1] == globalGrid[2][2] && globalGrid[0][0] != 0) {
        return globalGrid[0][0];  // Return the winner (1 or 2)
    }

    if (globalGrid[0][2] == globalGrid[1][1] && globalGrid[1][1] == globalGrid[2][0] && globalGrid[0][2] != 0) {
        return globalGrid[0][2];  // Return the winner (1 or 2)
    }

    // Check if the board is full
    bool isFull = true;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (globalGrid[i][j] == 0) {
                isFull = false;  // There is an empty cell, board is not full
                break;
            }
        }
        if (!isFull) {
            break;
        }
    }

    if (isFull) {
        return 3;  // Board is full and no one has won, so it's a draw
    }

    // If there's no winner and the board is not full
    return 0;
}


/*
void Screen1View::updateCount() {
	Unicode::snprintf(p1countBuffer, P1COUNT_SIZE, "%u", zmagep1);
	Unicode::snprintf(p2countBuffer, P2COUNT_SIZE, "%u", zmagep2);
}
*/

void Screen1View::netouchablegumbi() {
	gumb1.setTouchable(false);
	gumb1.invalidate();
	gumb2.setTouchable(false);
	gumb2.invalidate();
	gumb3.setTouchable(false);
	gumb3.invalidate();
	gumb4.setTouchable(false);
	gumb4.invalidate();
	gumb5.setTouchable(false);
	gumb5.invalidate();
	gumb6.setTouchable(false);
	gumb6.invalidate();
	gumb7.setTouchable(false);
	gumb7.invalidate();
	gumb8.setTouchable(false);
	gumb8.invalidate();
	gumb9.setTouchable(false);
	gumb9.invalidate();
}

void Screen1View::touchablegumbi() {
	gumb1.setTouchable(true);
	gumb1.invalidate();
	gumb2.setTouchable(true);
	gumb2.invalidate();
	gumb3.setTouchable(true);
	gumb3.invalidate();
	gumb4.setTouchable(true);
	gumb4.invalidate();
	gumb5.setTouchable(true);
	gumb5.invalidate();
	gumb6.setTouchable(true);
	gumb6.invalidate();
	gumb7.setTouchable(true);
	gumb7.invalidate();
	gumb8.setTouchable(true);
	gumb8.invalidate();
	gumb9.setTouchable(true);
	gumb9.invalidate();
}


void Screen1View::gumbfunkcija()
{
	//HAL_Delay(2000);
	winner = checkIfWin();

	if (winner >  0) {
		netouchablegumbi();
		presenter->zmagovalec(winner);
		return;
	}


    if (jebot) {
    	botigra();

    	winner = checkIfWin();
    	if (winner >  0) {
    		netouchablegumbi();
    		presenter->zmagovalec(winner);
    	}
    }
}

// bot na igri muahahah (ubila sebom)
void Screen1View::botigra() {

	Move bestMove = findBestMove(globalGrid);
	int row = bestMove.row;
	int col = bestMove.col;

	if (row == 0 && col == 0) {
		gumb1.setPressed(true);
		gumb1.invalidate();
		colorbutton1();
	}
	else if (row == 0 && col == 1) {
		gumb2.setPressed(true);
		gumb2.invalidate();
		colorbutton2();
	}
	else if (row == 0 && col == 2) {
		gumb3.setPressed(true);
		gumb3.invalidate();
		colorbutton3();
	}
	else if (row == 1 && col == 0) {
		gumb4.setPressed(true);
		gumb4.invalidate();
		colorbutton4();
	}
	else if (row == 1 && col == 1) {
		gumb5.setPressed(true);
		gumb5.invalidate();
		colorbutton5();
	}
	else if (row == 1 && col == 2) {
		gumb6.setPressed(true);
		gumb6.invalidate();
		colorbutton6();
	}
	else if (row == 2 && col == 0) {
		gumb7.setPressed(true);
		gumb7.invalidate();
		colorbutton7();
	}
	else if (row == 2 && col == 1) {
		gumb8.setPressed(true);
		gumb8.invalidate();
		colorbutton8();
	}
	else {
		gumb9.setPressed(true);
		gumb9.invalidate();
		colorbutton9();
	}
}


void Screen1View::pomocpls() {
	//HAL_Delay(100);
	borut++;

	// napise winnerja
	if (winner == 1) {
		zmagep1++;
		Unicode::snprintf(p1countBuffer, P1COUNT_SIZE, "%u", zmagep1);
		p1count.invalidate();
	}
	else if (winner == 2) {
		zmagep2++;
		Unicode::snprintf(p2countBuffer, P2COUNT_SIZE, "%u", zmagep2);
		p2count.invalidate();
	}
	roundcount++;
	Unicode::snprintf(rundacountBuffer, RUNDACOUNT_SIZE, "%u", roundcount);
	rundacount.invalidate();

	// resetira grid
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            globalGrid[i][j] = 0;
        }
    }

    //HAL_Delay(1000);

    // Reset button states

    touchablegumbi();


    gumb1.setBitmaps(Bitmap(BITMAP_NAVADNGUMB_ID), Bitmap(BITMAP_NAVADNGUMB_ID));
    gumb1.forceState(false);
    gumb1.invalidate();

    gumb2.setBitmaps(Bitmap(BITMAP_NAVADNGUMB_ID), Bitmap(BITMAP_NAVADNGUMB_ID));
    gumb2.forceState(false);
    gumb2.invalidate();

    gumb3.setBitmaps(Bitmap(BITMAP_NAVADNGUMB_ID), Bitmap(BITMAP_NAVADNGUMB_ID));
    gumb3.forceState(false);
    gumb3.invalidate();

    gumb4.setBitmaps(Bitmap(BITMAP_NAVADNGUMB_ID), Bitmap(BITMAP_NAVADNGUMB_ID));
    gumb4.forceState(false);
    gumb4.invalidate();

    gumb5.setBitmaps(Bitmap(BITMAP_NAVADNGUMB_ID), Bitmap(BITMAP_NAVADNGUMB_ID));
    gumb5.forceState(false);
    gumb5.invalidate();

    gumb6.setBitmaps(Bitmap(BITMAP_NAVADNGUMB_ID), Bitmap(BITMAP_NAVADNGUMB_ID));
    gumb6.forceState(false);
    gumb6.invalidate();

    gumb7.setBitmaps(Bitmap(BITMAP_NAVADNGUMB_ID), Bitmap(BITMAP_NAVADNGUMB_ID));
    gumb7.forceState(false);
    gumb7.invalidate();

    gumb8.setBitmaps(Bitmap(BITMAP_NAVADNGUMB_ID), Bitmap(BITMAP_NAVADNGUMB_ID));
    gumb8.forceState(false);
    gumb8.invalidate();

    gumb9.setBitmaps(Bitmap(BITMAP_NAVADNGUMB_ID), Bitmap(BITMAP_NAVADNGUMB_ID));
    gumb9.forceState(false);
    gumb9.invalidate();


    // Reset the pressed counter
    pressed = 0;
    winner = 0;
    return;
}


void Screen1View::colorbutton1() {
	if (pressed % 2 == 0) {
		gumb1.setBitmaps(Bitmap(BITMAP_NAVADNGUMB_ID), Bitmap(BITMAP_KROGEC_ID));
		gumb1.setPressed(true);
		gumb1.invalidate();
		globalGrid[0][0] = 1;
	}
	else {
		gumb1.setBitmaps(Bitmap(BITMAP_NAVADNGUMB_ID), Bitmap(BITMAP_KRIZEC_ID));
		gumb1.setPressed(true);
		gumb1.invalidate();
		globalGrid[0][0] = 2;
	}
	pressed++;
}

void Screen1View::colorbutton2() {
	if (pressed % 2 == 0) {
		gumb2.setBitmaps(Bitmap(BITMAP_NAVADNGUMB_ID), Bitmap(BITMAP_KROGEC_ID));
		gumb2.setPressed(true);
		globalGrid[0][1] = 1;
	}
	else {
		gumb2.setBitmaps(Bitmap(BITMAP_NAVADNGUMB_ID), Bitmap(BITMAP_KRIZEC_ID));
		gumb2.setPressed(true);
		globalGrid[0][1] = 2;
	}
	gumb2.invalidate();
	pressed++;
}

void Screen1View::colorbutton3() {
	if (pressed % 2 == 0) {
		gumb3.setBitmaps(Bitmap(BITMAP_NAVADNGUMB_ID), Bitmap(BITMAP_KROGEC_ID));
		gumb3.setPressed(true);
		globalGrid[0][2] = 1;
	}
	else {
		gumb3.setBitmaps(Bitmap(BITMAP_NAVADNGUMB_ID), Bitmap(BITMAP_KRIZEC_ID));
		gumb3.setPressed(true);
		globalGrid[0][2] = 2;
	}
	pressed++;
	gumb3.invalidate();
}

void Screen1View::colorbutton4() {
	if (pressed % 2 == 0) {
		gumb4.setBitmaps(Bitmap(BITMAP_NAVADNGUMB_ID), Bitmap(BITMAP_KROGEC_ID));
		gumb4.setPressed(true);
		globalGrid[1][0] = 1;
	}
	else {
		gumb4.setBitmaps(Bitmap(BITMAP_NAVADNGUMB_ID), Bitmap(BITMAP_KRIZEC_ID));
		gumb4.setPressed(true);
		globalGrid[1][0] = 2;
	}
	pressed++;
	gumb4.invalidate();
}

void Screen1View::colorbutton5() {
	if (pressed % 2 == 0) {
		gumb5.setBitmaps(Bitmap(BITMAP_NAVADNGUMB_ID), Bitmap(BITMAP_KROGEC_ID));
		gumb5.setPressed(true);
		globalGrid[1][1] = 1;
	}
	else {
		gumb5.setBitmaps(Bitmap(BITMAP_NAVADNGUMB_ID), Bitmap(BITMAP_KRIZEC_ID));
		gumb5.setPressed(true);
		globalGrid[1][1] = 2;
	}
	pressed++;
	gumb5.invalidate();
}

void Screen1View::colorbutton6() {
	if (pressed % 2 == 0) {
		gumb6.setBitmaps(Bitmap(BITMAP_NAVADNGUMB_ID), Bitmap(BITMAP_KROGEC_ID));
		gumb6.setPressed(true);
		globalGrid[1][2] = 1;
	}
	else {
		gumb6.setBitmaps(Bitmap(BITMAP_NAVADNGUMB_ID), Bitmap(BITMAP_KRIZEC_ID));
		gumb6.setPressed(true);
		globalGrid[1][2] = 2;
	}
	pressed++;
	gumb6.invalidate();
}

void Screen1View::colorbutton7() {
	if (pressed % 2 == 0) {
		gumb7.setBitmaps(Bitmap(BITMAP_NAVADNGUMB_ID), Bitmap(BITMAP_KROGEC_ID));
		gumb7.setPressed(true);
		globalGrid[2][0] = 1;
	}
	else {
		gumb7.setBitmaps(Bitmap(BITMAP_NAVADNGUMB_ID), Bitmap(BITMAP_KRIZEC_ID));
		gumb7.setPressed(true);
		globalGrid[2][0] = 2;
	}
	pressed++;
	gumb7.invalidate();
}

void Screen1View::colorbutton8() {
	if (pressed % 2 == 0) {
		gumb8.setBitmaps(Bitmap(BITMAP_NAVADNGUMB_ID), Bitmap(BITMAP_KROGEC_ID));
		gumb8.setPressed(true);
		globalGrid[2][1] = 1;
	}
	else {
		gumb8.setBitmaps(Bitmap(BITMAP_NAVADNGUMB_ID), Bitmap(BITMAP_KRIZEC_ID));
		gumb8.setPressed(true);
		globalGrid[2][1] = 2;
	}
	pressed++;
	gumb8.invalidate();
}

void Screen1View::colorbutton9() {
	if (pressed % 2 == 0) {
		gumb9.setBitmaps(Bitmap(BITMAP_NAVADNGUMB_ID), Bitmap(BITMAP_KROGEC_ID));
		gumb9.setPressed(true);
		globalGrid[2][2] = 1;
	}
	else {
		gumb9.setBitmaps(Bitmap(BITMAP_NAVADNGUMB_ID), Bitmap(BITMAP_KRIZEC_ID));
		gumb9.setPressed(true);
		globalGrid[2][2] = 2;
	}
	pressed++;
	gumb9.invalidate();
}


// 0 == empty
// 1 == krog
// 2 == kriz



void Screen1View::function1() {
	colorbutton1();
	gumbfunkcija();
	return;
}

void Screen1View::function2() {
	colorbutton2();
	gumbfunkcija();
	return;
}
void Screen1View::function3() {
	colorbutton3();
	gumbfunkcija();
	return;
}
void Screen1View::function4() {
	colorbutton4();
	gumbfunkcija();
	return;
}
void Screen1View::function5() {
	colorbutton5();
	gumbfunkcija();
	return;
}
void Screen1View::function6() {
	colorbutton6();
	gumbfunkcija();
	return;
}
void Screen1View::function7() {
	colorbutton7();
	gumbfunkcija();
	return;
}
void Screen1View::function8() {
	colorbutton8();
	gumbfunkcija();
	return;
}
void Screen1View::function9() {
	colorbutton9();
	gumbfunkcija();
	return;
}



// uno k rabm za gumb dami modal window otvori aiaiai

void Screen1View::openWindow() {

	modalWindow1.show();
	winner = 3;
	pomocpls();
	//modalWindow1.invalidate(); // mejbi idk
}




