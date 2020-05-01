/* ENGGEN131 Project - C Project - 2019 */
/* The Warehouse */

/* Dave Shin - jshi911 - 592493909 */

#include "project.h"

/*
TimeWorked calculates the length of a worker's shift in seconds. This time is the 
time that is elapsed between the cloking in and cloking out times. 

First pair of inputs (minuteA and secondA) may represent a time either before or 
after the second pair of inputs (minuteB and secondB), so the order doesn't matter.
Because of this, the smaller value is always subtracted from the larger value 
using the if statement in order to always return positive value as an output.
*/
int TimeWorked(int minuteA, int secondA, int minuteB, int secondB)
{
	if (minuteA > minuteB) {
		return (minuteA - minuteB) * 60 + (secondA - secondB);
		
	} else if (minuteB > minuteA) {
		return (minuteB - minuteA) * 60 + (secondB - secondA);
		
	} else if (minuteA == minuteB && secondA > secondB) {
		return secondA - secondB;
		
	} else {
		return secondB - secondA;
	}
}

/*
WarehouseAddress calculaltes the largest prime nuber which is less than the input 
upper bound.

The function works by using the modulus. If the remainder is 0, one is added to 
the variable "count". At the end of the inner loop, if the count is equal to zero, 
it means that the number is a prime number. By using this algorithm, the largest
possible prime number is found.
*/
int WarehouseAddress(int maximum)
{
	int i, j;
	int count;

	for (i = maximum - 1; i > 1; i--) {
		count = 0;
			
		for (j = 2; j < i; j++) {
			if (i % j == 0 ) {
				count++;
			}
		}
		
		if (count == 0) {
			return i;
		}
	}
	
	return i;
}

/*
Advertise rotates the characters in a character array, by moving every character 
one position to the left, and the lefmost character being wrapped around and 
being joined on the right-hand end of the string.

This function uses for loop to perform the task and the character that will be 
wrapped around is initially stored in the variable "temp" so that it is not lost.
*/
void Advertise(char *words)
{
	int i;
	int length = strlen(words);
	char temp = words[0];
	
	for (i = 0; i < length - 1; i++) {
	words[i] = words[i + 1];
	}
	
	words[length - 1] = temp;
}

/*
WinningBid calculates the minimum unique bid of the auction. If there is no 
minimum unique bid then the function returns -1.

This function first finds the maximum bid so that the initial winningBid can
be set to maximum bid. Then nested for loop is used to compare other bids to
the current winningBid to check whether the value is unique or not.
*/
int WinningBid(int *values, int length)
{
	int i, j;
	int count, winningBid;
	int max = values[0];
	
	// Find the maximum bid
	for (i = 1; i < length; i++) {
		if (values[i] > max) {
			max = values[i];
		}
	}
	
	winningBid = max;
	
	for (i = 0; i < length; i++) {
		count = 0;
		
		// Compare other bids to the current winningBid. If the bid is 
		// unique, the count should be 1 as it will have been only compared
		// to itself.
		for (j = 0; j < length; j++) {
			if (values[i] == values[j]) {
				count++;
			}
		}
		
		if (count == 1 && values[i] < winningBid) {
			winningBid = values[i];
		}
	}
	
	// If winningBid == max, there is a chance of the winningBid not being
	// unique. Check whether the winningBid is unique. If not, it means 
	// the minimum unique bid does not exist. In such case, return -1.
	if (winningBid == max) {
		count = 0;
		
		for (i = 0; i < length; i++) {
					if (values[i] == max) {
						count++;
					}
			}
			if (count != 1) {
				return -1;
			}
	} 
	
	return winningBid;
}

/*
BoxDesign generates a string that represents box. The centre of the box will 
be marked with 'X'.

Different formulae have been used which calculate the index positions of the 
border, centre and spaces. 
*/
void BoxDesign(char *design, int width, int height)
{
	int i;
	int size = (width + 1) * height;
	
	// Draw the outline of the box.
	for (i = 0; i < size; i++) {
		
		if ( (i < width) || ((i >= size - width - 1) && (i < size - 1)) ) {
			design[i] = '*';
			
		} else if ( (i % (width + 1) == 0) 
					|| (i % (width + 1) == width - 1) ) {
			design[i] = '*'; 
			
		} else if (i % (width + 1) == width) {
			design[i] = '\n';
			
		} else {
			design[i] = ' ';
		}
	}
	
	// Check if the width and length of the box are larger than 2.
	if (width > 2 && height > 2) {
		
		if (width % 2 == 1) {
			if (height % 2 == 1) {
				design[(size / 2) - 1] = 'X';
				
			} else if (height % 2 == 0) {
				design[(int)( (width + 1) * ((height / 2) - 1) 
						+ (double)width / 2 - 0.5 )] = 'X';
						
				design[(int)( size - (width + 1) * (height / 2) 
						+ (double)width / 2 - 0.5 )] = 'X';
			}
			
		} else if (width % 2 == 0) {
			if (height % 2 == 1) {
				design[size / 2] = 'X';
				design[size / 2 - 1] = 'X';
				
			} else if (height % 2 == 0) {
				design[(width + 1) * ((height / 2) - 1) 
						+ (width / 2) - 1] = 'X';
						
				design[(width + 1) * ((height / 2) - 1) 
						+ width / 2] = 'X';
						
				design[size - (width + 1) * (height / 2) 
						+ (width / 2) - 1] = 'X';
						
				design[size - (width + 1) * (height / 2) 
						+ width / 2] = 'X';
			}
		}
	}
}

/*
WorkerRoute draws a route on the exisiting array of warehouse. The worker moves 
horizeontally first then vertically from the initial position to the position 
of the box.

The function first calculatest the location of the worker and box. Then 
depending on the positions of the two objects, the route is drawn using a for 
loop.
*/
void WorkerRoute(int warehouse[10][10])
{
	// row, col.
	int i, j;
	
	int workerRow = 0, workerCol = 0, boxRow = 0, boxCol = 0;
	
	// Calculate the row and col of the worker and box.
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			if (warehouse[i][j] == 1) {
				workerRow = i;
				workerCol = j;
			} else if (warehouse[i][j] == 2) {
				boxRow = i;
				boxCol = j;
			}
		}
	}
	
	// Draw the route horizontally.
	if (workerCol < boxCol && workerRow != boxRow) {
		for (j = workerCol + 1; j <= boxCol; j++) {
			warehouse[workerRow][j] = 3;
		}
	} else if (workerCol > boxCol && workerRow != boxRow) {
		for (j = workerCol - 1; j >= boxCol; j--) {
			warehouse[workerRow][j] = 3;
		}
	} else if (workerCol < boxCol && workerRow == boxRow) {
		for (j = workerCol + 1; j < boxCol; j++) {
			warehouse[workerRow][j] = 3;
		}
	} else if (workerCol > boxCol && workerRow == boxRow) {
		for (j = workerCol - 1; j > boxCol; j--) {
			warehouse[workerRow][j] = 3;
		}
	}
			
	// Draw the route vertically.
	if (workerRow < boxRow) {
		for (i = workerRow + 1; i < boxRow; i++) {
			warehouse[i][boxCol] = 3;
		}
	} else if (workerRow > boxRow) {
		for (i = workerRow - 1; i > boxRow; i--) {
			warehouse[i][boxCol] = 3;
		}
	}		
}

/*
MakeMove moves the worker in four perpendicular directions. The direction that the 
worker moves to depends on the input by the user, which can be 'w', 's', 'a' or 
'd'. For detailed information about which moves are possible and which moves are 
prohibited, refer to the C Project brief.

This function works by checking the current situation of the warehouse (e.g. is 
the worker next to a box? Is the worker on the target? Is the box next to the 
wall?) then moving the location of the objects if certain conditions are met.
Whether the task is finished is worked out by checking if there are any remaining
targets and if the worker is standing on the target or not.
*/
int MakeMove(int warehouse[10][10], char move)
{
	// row, col.
	int i, j;
	
	int workerRow = 0, workerCol = 0;
	int count = 0;
	int workerOnTarget = 0;
	
	// Calculate the row and col of the worker.
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			if (warehouse[i][j] == WORKER || warehouse[i][j] == WORKER_ON_TARGET) {
				workerRow = i;
				workerCol = j;
			}
		}
	}
	
	if (move == 'a') {
		// No boxes involved.
		if (warehouse[workerRow][workerCol - 1] == SPACE 
			&& warehouse[workerRow][workerCol] == WORKER) {
			warehouse[workerRow][workerCol - 1] = WORKER;
			warehouse[workerRow][workerCol] = SPACE;
		
		} else if (warehouse[workerRow][workerCol - 1] == SPACE 
					&& warehouse[workerRow][workerCol] == WORKER_ON_TARGET) {
			warehouse[workerRow][workerCol - 1] = WORKER;
			warehouse[workerRow][workerCol] = TARGET;
		
		} else if (warehouse[workerRow][workerCol - 1] == TARGET 
					&& warehouse[workerRow][workerCol] == WORKER) {
			warehouse[workerRow][workerCol - 1] = WORKER_ON_TARGET;
			warehouse[workerRow][workerCol] = SPACE;
		
		} else if (warehouse[workerRow][workerCol - 1] == TARGET 
					&& warehouse[workerRow][workerCol] == WORKER_ON_TARGET) {
			warehouse[workerRow][workerCol - 1] = WORKER_ON_TARGET;
			warehouse[workerRow][workerCol] = TARGET;	
			
			
		// Boxes involved.
		} else if (warehouse[workerRow][workerCol - 1] == BOX 
					&& warehouse[workerRow][workerCol] == WORKER) {
			if (warehouse[workerRow][workerCol - 2] == SPACE) {
				warehouse[workerRow][workerCol - 2] = BOX;
				warehouse[workerRow][workerCol - 1] = WORKER;
				warehouse[workerRow][workerCol] = SPACE;
				
			} else if (warehouse[workerRow][workerCol - 2] == TARGET) {
				warehouse[workerRow][workerCol - 2] = BOX_ON_TARGET;
				warehouse[workerRow][workerCol - 1] = WORKER;
				warehouse[workerRow][workerCol] = SPACE;
			}
			
		} else if (warehouse[workerRow][workerCol - 1] == BOX 
					&& warehouse[workerRow][workerCol] == WORKER_ON_TARGET) {
			if (warehouse[workerRow][workerCol - 2] == SPACE) {
				warehouse[workerRow][workerCol - 2] = BOX;
				warehouse[workerRow][workerCol - 1] = WORKER;
				warehouse[workerRow][workerCol] = TARGET;
				
			} else if (warehouse[workerRow][workerCol - 2] == TARGET) {
				warehouse[workerRow][workerCol - 2] = BOX_ON_TARGET;
				warehouse[workerRow][workerCol - 1] = WORKER;
				warehouse[workerRow][workerCol] = TARGET;
			}
			
		} else if (warehouse[workerRow][workerCol - 1] == BOX_ON_TARGET 
					&& warehouse[workerRow][workerCol] == WORKER) {	
			if (warehouse[workerRow][workerCol - 2] == SPACE) {
				warehouse[workerRow][workerCol - 2] = BOX;
				warehouse[workerRow][workerCol - 1] = WORKER_ON_TARGET;
				warehouse[workerRow][workerCol] = SPACE;
				
			} else if (warehouse[workerRow][workerCol - 2] == TARGET) {
				warehouse[workerRow][workerCol - 2] = BOX_ON_TARGET;
				warehouse[workerRow][workerCol - 1] = WORKER_ON_TARGET;
				warehouse[workerRow][workerCol] = SPACE;
			}
		
		} else if (warehouse[workerRow][workerCol - 1] == BOX_ON_TARGET 
					&& warehouse[workerRow][workerCol] == WORKER_ON_TARGET) {	
			if (warehouse[workerRow][workerCol - 2] == SPACE) {
				warehouse[workerRow][workerCol - 2] = BOX;
				warehouse[workerRow][workerCol - 1] = WORKER_ON_TARGET;
				warehouse[workerRow][workerCol] = TARGET;
				
			} else if (warehouse[workerRow][workerCol - 2] == TARGET) {
				warehouse[workerRow][workerCol - 2] = BOX_ON_TARGET;
				warehouse[workerRow][workerCol - 1] = WORKER_ON_TARGET;
				warehouse[workerRow][workerCol] = TARGET;
			}
		}

			
	} else if (move == 'd') {
		// No boxes involved.
		if (warehouse[workerRow][workerCol + 1] == SPACE 
			&& warehouse[workerRow][workerCol] == WORKER) {
			warehouse[workerRow][workerCol + 1] = WORKER;
			warehouse[workerRow][workerCol] = SPACE;
		
		} else if (warehouse[workerRow][workerCol + 1] == SPACE 
					&& warehouse[workerRow][workerCol] == WORKER_ON_TARGET) {
			warehouse[workerRow][workerCol + 1] = WORKER;
			warehouse[workerRow][workerCol] = TARGET;
		
		} else if (warehouse[workerRow][workerCol + 1] == TARGET 
					&& warehouse[workerRow][workerCol] == WORKER) {
			warehouse[workerRow][workerCol + 1] = WORKER_ON_TARGET;
			warehouse[workerRow][workerCol] = SPACE;
		
		} else if (warehouse[workerRow][workerCol + 1] == TARGET 
					&& warehouse[workerRow][workerCol] == WORKER_ON_TARGET) {
			warehouse[workerRow][workerCol + 1] = WORKER_ON_TARGET;
			warehouse[workerRow][workerCol] = TARGET;	
			
			
		// Boxes involved.
		} else if (warehouse[workerRow][workerCol + 1] == BOX 
					&& warehouse[workerRow][workerCol] == WORKER) {
			if (warehouse[workerRow][workerCol + 2] == SPACE) {
				warehouse[workerRow][workerCol + 2] = BOX;
				warehouse[workerRow][workerCol + 1] = WORKER;
				warehouse[workerRow][workerCol] = SPACE;
				
			} else if (warehouse[workerRow][workerCol + 2] == TARGET) {
				warehouse[workerRow][workerCol + 2] = BOX_ON_TARGET;
				warehouse[workerRow][workerCol + 1] = WORKER;
				warehouse[workerRow][workerCol] = SPACE;
			}
			
		} else if (warehouse[workerRow][workerCol +1] == BOX 
					&& warehouse[workerRow][workerCol] == WORKER_ON_TARGET) {
			if (warehouse[workerRow][workerCol + 2] == SPACE) {
				warehouse[workerRow][workerCol + 2] = BOX;
				warehouse[workerRow][workerCol + 1] = WORKER;
				warehouse[workerRow][workerCol] = TARGET;
				
			} else if (warehouse[workerRow][workerCol + 2] == TARGET) {
				warehouse[workerRow][workerCol + 2] = BOX_ON_TARGET;
				warehouse[workerRow][workerCol + 1] = WORKER;
				warehouse[workerRow][workerCol] = TARGET;
			}
			
		} else if (warehouse[workerRow][workerCol + 1] == BOX_ON_TARGET 
					&& warehouse[workerRow][workerCol] == WORKER) {	
			if (warehouse[workerRow][workerCol + 2] == SPACE) {
				warehouse[workerRow][workerCol + 2] = BOX;
				warehouse[workerRow][workerCol + 1] = WORKER_ON_TARGET;
				warehouse[workerRow][workerCol] = SPACE;
				
			} else if (warehouse[workerRow][workerCol + 2] == TARGET) {
				warehouse[workerRow][workerCol + 2] = BOX_ON_TARGET;
				warehouse[workerRow][workerCol + 1] = WORKER_ON_TARGET;
				warehouse[workerRow][workerCol] = SPACE;
			}
		
		} else if (warehouse[workerRow][workerCol + 1] == BOX_ON_TARGET 
					&& warehouse[workerRow][workerCol] == WORKER_ON_TARGET) {	
			if (warehouse[workerRow][workerCol + 2] == SPACE) {
				warehouse[workerRow][workerCol + 2] = BOX;
				warehouse[workerRow][workerCol + 1] = WORKER_ON_TARGET;
				warehouse[workerRow][workerCol] = TARGET;
				
			} else if (warehouse[workerRow][workerCol + 2] == TARGET) {
				warehouse[workerRow][workerCol + 2] = BOX_ON_TARGET;
				warehouse[workerRow][workerCol + 1] = WORKER_ON_TARGET;
				warehouse[workerRow][workerCol] = TARGET;
			}
		}
		
		
		
	} else if (move == 'w') {
		// No boxes involved.
		if (warehouse[workerRow - 1][workerCol] == SPACE 
			&& warehouse[workerRow][workerCol] == WORKER) {
			warehouse[workerRow - 1][workerCol] = WORKER;
			warehouse[workerRow][workerCol] = SPACE;
		
		} else if (warehouse[workerRow - 1][workerCol] == SPACE 
					&& warehouse[workerRow][workerCol] == WORKER_ON_TARGET) {
			warehouse[workerRow - 1][workerCol] = WORKER;
			warehouse[workerRow][workerCol] = TARGET;
		
		} else if (warehouse[workerRow - 1][workerCol] == TARGET 
					&& warehouse[workerRow][workerCol] == WORKER) {
			warehouse[workerRow - 1][workerCol] = WORKER_ON_TARGET;
			warehouse[workerRow][workerCol] = SPACE;
		
		} else if (warehouse[workerRow - 1][workerCol] == TARGET 
					&& warehouse[workerRow][workerCol] == WORKER_ON_TARGET) {
			warehouse[workerRow - 1][workerCol] = WORKER_ON_TARGET;
			warehouse[workerRow][workerCol] = TARGET;	
			
			
		// Boxes involved.
		} else if (warehouse[workerRow - 1][workerCol] == BOX 
					&& warehouse[workerRow][workerCol] == WORKER) {
			if (warehouse[workerRow - 2][workerCol] == SPACE) {
				warehouse[workerRow - 2][workerCol] = BOX;
				warehouse[workerRow - 1][workerCol] = WORKER;
				warehouse[workerRow][workerCol] = SPACE;
				
			} else if (warehouse[workerRow - 2][workerCol] == TARGET) {
				warehouse[workerRow - 2][workerCol] = BOX_ON_TARGET;
				warehouse[workerRow - 1][workerCol] = WORKER;
				warehouse[workerRow][workerCol] = SPACE;
			}
			
		} else if (warehouse[workerRow - 1][workerCol] == BOX 
					&& warehouse[workerRow][workerCol] == WORKER_ON_TARGET) {
			if (warehouse[workerRow - 2][workerCol] == SPACE) {
				warehouse[workerRow - 2][workerCol] = BOX;
				warehouse[workerRow - 1][workerCol] = WORKER;
				warehouse[workerRow][workerCol] = TARGET;
				
			} else if (warehouse[workerRow - 2][workerCol] == TARGET) {
				warehouse[workerRow - 2][workerCol] = BOX_ON_TARGET;
				warehouse[workerRow - 1][workerCol] = WORKER;
				warehouse[workerRow][workerCol] = TARGET;
			}
			
		} else if (warehouse[workerRow - 1][workerCol] == BOX_ON_TARGET 
					&& warehouse[workerRow][workerCol] == WORKER) {	
			if (warehouse[workerRow - 2][workerCol] == SPACE) {
				warehouse[workerRow - 2][workerCol] = BOX;
				warehouse[workerRow - 1][workerCol] = WORKER_ON_TARGET;
				warehouse[workerRow][workerCol] = SPACE;
				
			} else if (warehouse[workerRow - 2][workerCol] == TARGET) {
				warehouse[workerRow - 2][workerCol] = BOX_ON_TARGET;
				warehouse[workerRow - 1][workerCol] = WORKER_ON_TARGET;
				warehouse[workerRow][workerCol] = SPACE;
			}
		
		} else if (warehouse[workerRow - 1][workerCol] == BOX_ON_TARGET 
					&& warehouse[workerRow][workerCol] == WORKER_ON_TARGET) {	
			if (warehouse[workerRow - 2][workerCol] == SPACE) {
				warehouse[workerRow - 2][workerCol] = BOX;
				warehouse[workerRow - 1][workerCol] = WORKER_ON_TARGET;
				warehouse[workerRow][workerCol] = TARGET;
				
			} else if (warehouse[workerRow - 2][workerCol] == TARGET) {
				warehouse[workerRow - 2][workerCol] = BOX_ON_TARGET;
				warehouse[workerRow - 1][workerCol] = WORKER_ON_TARGET;
				warehouse[workerRow][workerCol] = TARGET;
			}
		}
		
		
		
	} else if (move == 's') {
		// No boxes involved.
		if (warehouse[workerRow + 1][workerCol] == SPACE 
			&& warehouse[workerRow][workerCol] == WORKER) {
			warehouse[workerRow + 1][workerCol] = WORKER;
			warehouse[workerRow][workerCol] = SPACE;
		
		} else if (warehouse[workerRow + 1][workerCol] == SPACE 
					&& warehouse[workerRow][workerCol] == WORKER_ON_TARGET) {
			warehouse[workerRow + 1][workerCol] = WORKER;
			warehouse[workerRow][workerCol] = TARGET;
		
		} else if (warehouse[workerRow + 1][workerCol] == TARGET 
					&& warehouse[workerRow][workerCol] == WORKER) {
			warehouse[workerRow + 1][workerCol] = WORKER_ON_TARGET;
			warehouse[workerRow][workerCol] = SPACE;
		
		} else if (warehouse[workerRow + 1][workerCol] == TARGET 
					&& warehouse[workerRow][workerCol] == WORKER_ON_TARGET) {
			warehouse[workerRow + 1][workerCol] = WORKER_ON_TARGET;
			warehouse[workerRow][workerCol] = TARGET;	
			
			
		// Boxes involved.
		} else if (warehouse[workerRow + 1][workerCol] == BOX 
					&& warehouse[workerRow][workerCol] == WORKER) {
			if (warehouse[workerRow + 2][workerCol] == SPACE) {
				warehouse[workerRow + 2][workerCol] = BOX;
				warehouse[workerRow + 1][workerCol] = WORKER;
				warehouse[workerRow][workerCol] = SPACE;
				
			} else if (warehouse[workerRow + 2][workerCol] == TARGET) {
				warehouse[workerRow + 2][workerCol] = BOX_ON_TARGET;
				warehouse[workerRow + 1][workerCol] = WORKER;
				warehouse[workerRow][workerCol] = SPACE;
			}
			
		} else if (warehouse[workerRow + 1][workerCol] == BOX 
					&& warehouse[workerRow][workerCol] == WORKER_ON_TARGET) {
			if (warehouse[workerRow + 2][workerCol] == SPACE) {
				warehouse[workerRow + 2][workerCol] = BOX;
				warehouse[workerRow + 1][workerCol] = WORKER;
				warehouse[workerRow][workerCol] = TARGET;
				
			} else if (warehouse[workerRow + 2][workerCol] == TARGET) {
				warehouse[workerRow + 2][workerCol] = BOX_ON_TARGET;
				warehouse[workerRow + 1][workerCol] = WORKER;
				warehouse[workerRow][workerCol] = TARGET;
			}
			
		} else if (warehouse[workerRow + 1][workerCol] == BOX_ON_TARGET 
					&& warehouse[workerRow][workerCol] == WORKER) {	
			if (warehouse[workerRow + 2][workerCol] == SPACE) {
				warehouse[workerRow + 2][workerCol] = BOX;
				warehouse[workerRow + 1][workerCol] = WORKER_ON_TARGET;
				warehouse[workerRow][workerCol] = SPACE;
				
			} else if (warehouse[workerRow + 2][workerCol] == TARGET) {
				warehouse[workerRow + 2][workerCol] = BOX_ON_TARGET;
				warehouse[workerRow + 1][workerCol] = WORKER_ON_TARGET;
				warehouse[workerRow][workerCol] = SPACE;
			}
		
		} else if (warehouse[workerRow + 1][workerCol] == BOX_ON_TARGET 
					&& warehouse[workerRow][workerCol] == WORKER_ON_TARGET) {	
			if (warehouse[workerRow + 2][workerCol] == SPACE) {
				warehouse[workerRow + 2][workerCol] = BOX;
				warehouse[workerRow + 1][workerCol] = WORKER_ON_TARGET;
				warehouse[workerRow][workerCol] = TARGET;
				
			} else if (warehouse[workerRow + 2][workerCol] == TARGET) {
				warehouse[workerRow + 2][workerCol] = BOX_ON_TARGET;
				warehouse[workerRow + 1][workerCol] = WORKER_ON_TARGET;
				warehouse[workerRow][workerCol] = TARGET;
			}
		}
	}
	
	// Check if the task is finished.
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			if (warehouse[i][j] == TARGET) {
				count++;
			}
			
			if (warehouse[i][j] == WORKER_ON_TARGET) {
				workerOnTarget = 1;
			}
		}
	}
	
	if (count == 0 && workerOnTarget) {
		return 1;
	}
	
	return 0;
}

