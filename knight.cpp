#include <iostream>
#include <string>
#include <sstream>
#include <vector>

void outputing(std::vector<int> pathRow, std::vector<int> pathCol, const std::vector<char> ALPHABET, int endCol, int endRow)
{
    for(int i = 0; i < pathCol.size(); i++)
        std::cout << ALPHABET.at(pathCol.at(i)) << pathRow.at(i) + 1 << " ";

	std::cout << ALPHABET.at(endCol) << endRow << "\n";
}

bool findingKnightsTour(std::vector<std::vector<int>> &board, std::vector<int> &pathRow,  std::vector<int> &pathCol, const int SIZE, int startRow, int startCol, int endRow, int endCol)
{
    const std::vector<int> ROW_MOVES = {1, 2, 2, 1, -1, -2, -2, -1};
	const std::vector<int> COLUMN_MOVES = {2, 1, -1, -2, -2, -1, 1, 2};
	int nextSqRow = 0, nextSqCol = 0;
	bool success;

    if(startRow == endRow && startCol == endCol)
        return true;
    
    for(int i = 0; i < 8; i++)
    {
        nextSqRow = startRow + ROW_MOVES.at(i);
        nextSqCol = startCol + COLUMN_MOVES.at(i);

        if(nextSqRow >= 0 && nextSqRow < SIZE && nextSqCol >= 0 && nextSqCol < SIZE && board.at(nextSqRow).at(nextSqCol) == 0)
        {
            board.at(nextSqRow).at(nextSqCol) = 1;

            pathCol.push_back(startCol);
            pathRow.push_back(startRow);

            success = findingKnightsTour(board, pathRow, pathCol, SIZE, nextSqRow, nextSqCol, endRow, endCol);

            if(success)
                return true;

            board.at(nextSqRow).at(nextSqCol) = 0;

            pathCol.pop_back();
            pathRow.pop_back();
        }
    }

    return false;
}

int main (int argc, char* argv[])
{
    const std::vector<char> ALPHABET = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    std::vector<int> pathRow, pathCol;
    char startLetter, endLetter;
    int startRow, startCol = -1, endRow, endCol = -1, boardSize;

	try
    {
    	if(argc != 4)
        {
            throw std::runtime_error("invalid parameter list\n");
        }

        std::istringstream size(argv[1]);
        std::istringstream startSq (argv[2]);
        std::istringstream endSq (argv[3]);
  
        size >> boardSize;
        startSq >> startLetter >> startRow;
        endSq >> endLetter >> endRow;

        if(boardSize <= 0 || boardSize > 26)
        {
            throw std::runtime_error("invalid parameter list\n");
        }

        if(startRow <= 0 || startRow > boardSize || endRow <= 0 || endRow > boardSize)
        {
            throw std::runtime_error("invalid parameter list\n");
        }
    
    	for(int i = 0; i < boardSize; i++)
    	{
    		if(startLetter == ALPHABET.at(i))
            	startCol = i;
            
        	if(endLetter == ALPHABET.at(i))
            	endCol = i;
		}

        if((startCol == -1) || (endCol == -1))
        {
           throw std::runtime_error("invalid parameter list\n");
        }

    	std::vector<std::vector<int>> board (boardSize, std::vector<int> (boardSize, 0));

    	board.at(startRow - 1).at(startCol) = 1;

    	if(findingKnightsTour(board, pathRow, pathCol, boardSize, startRow - 1, startCol, endRow - 1, endCol))
		{
			outputing(pathRow, pathCol, ALPHABET, endCol, endRow);

		} else
		{
			std::cout << "could not find a knight's tour\n";
			return 0;
		}
	} catch(std::runtime_error &excpt)
    {
        std::cerr << excpt.what() << std::endl;
        return 0;
    }

    return 0;
}
