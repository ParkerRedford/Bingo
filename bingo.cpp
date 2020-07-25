#include <iostream>
#include <ctime>
#include <iomanip>


using namespace std;

bool duplicates(int length, int array[])
{
    bool b = false;
    for (int i = 0; i <= length; i++)
    {
        for (int j = i + 1; j <= length; j++)
        {
            if (array[i] == array[j])
                b = true;
        }
    }
    return b;
}
char numberToLetter(int number)
{
    switch (number)
    {
    case 0:
        return 'B';
    case 1:
        return 'I';
    case 2:
        return 'N';
    case 3:
        return 'G';
    case 4:
        return 'O';
    default:
        break;
    }
}

//Global variables
int rowIndex = -1;
int columnIndex = -1;
int diagnoal = -1;
int otherDiagnoal = -1;

int main()
{
    srand(time(0));
    int bingo[5][5];

    //Create bingo card
    for (int i = 0; i < 5; i++)
    {
        int counts[5];              //Initiailze array on index 2d array
        for (int j = 0; j < 5; j++)
        {
            if (!(i == 2 && j == 2)) //Free space in middle
            {
                do
                {
                    counts[j] = 1 + rand() % 75;
                } while (duplicates(j, counts));    //Checks if letter has duplicates
                bingo[i][j] = counts[j];
            }
            else
                bingo[i][j] = 0;
        }
    }

    //Display bingo card
    for (int i = 0; i < 5; i++)
    {
        cout << setw(3) << right << numberToLetter(i) << " ";
    }
    cout << "\n\n";
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << setw(3) << right << bingo[j][i] << " ";
        }
        cout << "\n";
    }

    cout << "\nNumbers called: \n";
    int numbersCalled = 0;

    //Initialize 2d array to 0 for checking
    bool isBingo = false;
    int bingoNumbers[5][75];
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            bingoNumbers[i][j] = 0;
        }
    }

    while(!isBingo)
    {
        //Assign a random number
        int letter;
        int number;
        bool duplicates = false;
        do
        {
            letter = 0 + rand() % 5;
            number = 1 + rand() % 75;

            if (bingoNumbers[letter][number] > 0) //Checks if the letter and number has been played before
                duplicates = true;                  //If it does not, reassign number to a new random letter and number
        } while (duplicates);
        
        //Mark bingo number on card if card has letter/number
        for (int i = 0; i < 5; i++)
        {
            if (bingo[letter][i] == number)
            {
                bingo[letter][i] = 0;
                continue;
            }
        }

        //Check for bingo
        //Column
        int column = 0;
        for (int i = 0; i < 5; i++)
        {
            int columnIndex = 0;
            
            int diagnoal = 0;
            int otherDiagnoal = 0;

            column = i;
            for (int j = 0; j < 5; j++)
            {
                columnIndex += bingo[i][j];
                
                diagnoal += bingo[j][j];
                otherDiagnoal += bingo[j][5 - j - 1];
            }
            //Diagonal
            if (diagnoal == 0 || otherDiagnoal == 0)
            {
                isBingo = true;

                ::diagnoal = diagnoal;
                ::otherDiagnoal = otherDiagnoal;
            }
            if (columnIndex == 0)
            {
                isBingo = true;
                ::columnIndex = column;
            } 
        }

        //Row
        int row = 0;
        for (int i = 0; i < 5; i++)
        {
            int rowIndex = 0;
            row = i;
            for (int j = 0; j < 5; j++)
            {
                rowIndex += bingo[j][i];
            }
            if (rowIndex == 0)
            {
                isBingo = true;
                ::rowIndex = row;
            }
        }

        numbersCalled += 1;

        //Display current letter and number
        cout << numberToLetter(letter) << number << "\n";
    }

    cout << "Bingo ";

    //Get row/column/diagonal global variable
    if (rowIndex > -1)
        cout << "in row " << rowIndex + 1;
    if (columnIndex > -1)
        cout << "in column " << columnIndex + 1;
    if (diagnoal == 0 || otherDiagnoal == 0)
        cout << "in a diagnoal";

    cout << "\n\nBINGO in " << numbersCalled << " numbers";
}
