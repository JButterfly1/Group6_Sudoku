//Developer/Coder: Jennifer Papillon & Kelsey Fallon
//log: Date: November 10th 2024
//Description: Making a Sudoku game using backtracking.
//Log: November 10th, 2024: Jennifer Started code. 
//log: November 11th, 2024: Jennifer & Kelsey discussed the code, and the process
//Developer/Coder: Jennifer Papillon & Kelsey Fallon
//Log: Date: November 13th, 2024
// Description: Making a Sudoku game using backtracking.
//log: November 13th, 2024: Jennifer continued the code, and added the necessary components and comments

#include <iostream>
#include <vector>
#include <sstream>

//the void function is in charge of what the sudoku grid looks like. It is only displayed if it's called in the main function
void printGame (int arr[9][9])
{ 
  for(int r = 0; r<9; r++) //r represents the rows
  {
    if(r % 3 ==0 && r!=0) // this adds the divider lines in the grid after every 3 rows
    {
      std::cout<<"------ ------  -------"<<std::endl; 
    }

    for(int c = 0; c<9; c++) //c represents column
    {
      if(c % 3 == 0 && c!=0) //this adds vertical lines in the grid after every 3 column
      {
        std::cout<<"| "; 
      }

      if(arr[r][c] == 0)
      {
        std::cout<<". ";  //used for empty spaces within the grid
      }
      else
      {
      std::cout<<arr[r][c]<< " ";
      }
    }
  std::cout<<std::endl;
  }


}
//canPlace checks if the number the user is trying to place follows sudoku rules
bool canPlace (int arr[9][9], int row, int col, int num)
{
  if(arr[row][col] != 0 ) //checking if the cell is occupied
  {
    return false; 
  }
  bool status = true;

  int gridx = (col / 3) * 3; // checks if the number the user inputs is w/in the 3x3 grid without scanning the whole sudoku board
  int gridy = (row / 3) * 3; 

  for (int i =0; i<9; i++) //checking if there is a value in each column, row, and cell
  {
    if(arr[row][i] == num || arr[i][col]== num) //if the number user inserted is already in the the grid, the bool will come up as false.
    {
      return false;
    }
  
    if(arr[gridy + i/3][gridx + i%3] == num)
    {
      return false; 
    }
 
  }
  return true; // if return true, then the number the player want to place can be entered.
}
 //finding all the numbers that can be placed 
std::vector<int> findPlaceables(int arr[9][9], int row, int col)
{
  std::vector<int>options;

  for(int num = 1; num <=9; num++) // the for-loop will check if numbers 1-9 can be placed in the certain row and col.
  {
    if(canPlace(arr,row,col,num))
    {
      options.push_back(num); 
    }
  }
  return options; //return the list of numbers
}

bool checkBoardComplete (int arr[9][9])
{
  for (int r = 0; r<9; r++)
  {
    for(int c = 0 ; c< 9; c++)
    {
      if (arr[r][c] == 0)
      {
        return false; 
      }
    }
  }
  return true; 
}

void playGame ( int arr[9][9])
{
  std::string input; 
  int row, col, num; 

  while(true) //let's users keep playing by applying guesses 
  {
    printGame(arr); //displays the Sudoku board
    
    std::cout<<"Please enter your guess, press V to quit, or h for hint:  \n"<<std::endl;
    std::getline(std::cin, input); 

    if(input == "v" || input == "V") //checking if user wants to quit the game
    {
      std::cout<<"You have decided to Quit the Game..... \n Thank you for Playing!"<<std::endl;
      break;
    }

    std::istringstream iss(input); //using stringstream to parse input
    char command; 

    if( iss >> command)
    {
     if( command == 'h' || command == 'H') //checking if the user wants a Hint
    {
      if (iss >>row >>col)
      {
      auto hints = findPlaceables (arr , row, col);

      if (!hints.empty())
      {
        std::cout<<"Hint!! You can enter the following number in ("<<row<<","<<col<<"): \n"<<std::endl;
        for(int n : hints)
        { //looping through all of the number options
          std::cout<<n<<" "<<std::endl; //displaying them
        }
        std::cout<< std::endl; 
      }
      else 
      {
        std::cout<<" Can't place a number here! Its Occupied! :)"<<std::endl;
      }

     }else 
     {
      std::cout<<"Wrong Key for hint. Please press 'h row col' if you would like a hint"<<std::endl; 
     }
    }
    else
    {
      iss.putback(command); 
      
      if(iss >> row >> col >> num)
      {
        if (canPlace(arr, row, col, num))
        {
          arr[row][col] = num; //placing a number in the board
          std::cout<<"Your number is in the Board!"<<std::endl; 
        }

        if (checkBoardComplete (arr))  // checking if the board is completed
        {
          printGame(arr); 
          std::cout<<" Congratulations!!! You have completed the Sudoku puzzle!"<<std::endl;
          break; 
        }
        else{
          std::cout<<"So Close! Try a different number....If you're still stuck check the rules:)"<<std::endl;
        }
        
      }
      else{
        std::cout<<"Sooo Close! you're almost there! \n Please enter 'row col num' to make a correct guess"<<std::endl;
      }
    }
    }
  } 
}



int main()
{
  std::cout<<"      Game Rules & Information: \n----------------------------------------\n 1)Please insert your answer in the following format: ('2 3 5' to place 5 at row 2, column 3) "<<std::endl;
  std::cout<<" 2) . represent the empty spaces \n 3) For a hint, enter 'h[row] [col]' \n 4) Press 'V' to quit"<<std::endl;
  std::cout<<"----------------------------------------------------------\n Enjoy the Game :) \n--------------------------------------------------------------"<<std::endl;

  int board[9][9] = { // [9][9] is the sudoku grid defined
    {4,3,0,1,8,0,2,9,0},
    {0,0,1,0,0,9,0,0,6},
    {2,9,0,6,4,0,8,7,0},
    {0,0,8,0,0,5,0,0,4},
    {3,6,0,8,7,1,0,5,2},
    {9,0,0,4,0,0,7,0,0},
    {0,8,7,0,5,2,0,4,3},
    {5,0,0,3,0,0,1,0,0},
    {0,4,3,0,1,8,0,2,9}
  }; 


  playGame(board); //calls the playGame void function and adds the board we created into it.


  return 0; 
}