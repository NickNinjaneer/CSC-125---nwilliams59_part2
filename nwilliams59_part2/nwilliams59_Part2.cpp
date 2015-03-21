//  CSC 125 - Online
//  nwilliams59_Part2.cpp
//  Author: Nick Williams on 3/13/15.
//  Description:
//              This Program Generates a Random, Solved Minesweeper Table
//              based on User input of Size and # of Mines.
//              Extra Credit has been implemented by placing the approprate
//              "How many Mines nearby" values.

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

const int MAX_ARRAY_SIZE = 24;

int get_grid_size();
int get_mines(int);
int** create_array(int);
void initialize_array(int, int**);
void place_mines(int, int, int**);
void generate_adjacent(int, int**);
void print_array(int, int**);
void deallocate_memory(int, int**);
int replay();

int main(int argc, const char * argv[])
{
    int play_again = 1;
    
    cout << "MINESWEEPER!! Kind of... \n";
    
    while (play_again == 1)
    {
        int grid_size = 0, mines = 0;
        
        srand((unsigned)time(NULL));
        
        //Obtain User Values
        grid_size = get_grid_size();
        mines = get_mines(grid_size);
        
        //Dynamic 2D Array Creation
        int** grid_array = create_array(grid_size);
        
        //Initializes Grid to ZEROs (Not NULL, due to Extra Credit)
        initialize_array(grid_size, grid_array);
        
        cout << "\n\nCAUTION: Mines Being Buried!!...\n\n";
        
        //Fills Array with Mines in Random Locations
        place_mines(grid_size, mines, grid_array);
        
        //EXTRA CREDIT - Generate Adjacent-to-Mine-Location Values
        generate_adjacent(grid_size, grid_array);
        
        cout << "If You Are all Suited Up for Minesweeping, Press Enter!\n\n";
        cin.get();
        cin.ignore();
        
        //Prints Array
        print_array(grid_size, grid_array);
        
        //Memory Deallocation
        deallocate_memory(grid_size, grid_array);
        
        play_again = replay();
    }
    
    cout << "\n\nTank You, Come Again!\n\n";
    
    return 0;
}

int get_grid_size()
{
    int grid_size = 0;
    
    cout << "\nEnter the Number of Cells in each Row/Column (1-24): ";
    cin >> grid_size;
    while (grid_size > MAX_ARRAY_SIZE)
    {
        cout << "You'll Never Make it through that Field\n";
        cout << "Choose a smaller Number of Cells in each Row/Column (1-24): ";
        cin >> grid_size;
    }
    
    return grid_size;
}

int get_mines(int grid_size)
{
    int mines = 0;
    
    cout << "Enter the Number of Mines.\n";
    cout << "# Mines Must Be Less Than or Equal to " << (grid_size * grid_size) << "\n";
    cout << "Mines: ";
    cin >> mines;
    
    while (mines > (grid_size * grid_size))
    {
        cout << "That many Mines will not fit!\n";
        cout << "Mines: ";
        cin >> mines;
    }
    
    return mines;
}

int** create_array(int grid_size)
{
    int** grid_array = new int*[grid_size];
    
    for (int i = 0; i < grid_size; i++)
    {
        grid_array[i] = new int[grid_size];
    }
    
    return grid_array;
}

void initialize_array(int grid_size, int** grid_array)
{
    for(int i = 0; i < grid_size; i++)
    {
        for(int j = 0; j < grid_size; j++)
        {
            grid_array[i][j] = 0;
        }
    }
}

void place_mines(int grid_size, int mines, int** grid_array)
{
    int placed = 0, x = 0, y = 0;
    
    while (placed < mines)
    {
        do
        {
            y = rand() % grid_size;
            x = rand() % grid_size;
        } while (grid_array[y][x] == -1);
        
        grid_array[y][x] = -1;
        placed++;
    };
}

//EXTRA CREDIT - Generates the Adjacent-to-Mine-Location Values
void generate_adjacent(int grid_size, int** grid_array)
{
    for (int y = 0; y < grid_size; y++)
    {
        for (int x = 0; x < grid_size; x++)
        {
            if (grid_array[y][x] == -1)
            {
                if ((x+1 < grid_size) && (grid_array[y][x+1] != -1))
                {
                    grid_array[y][x+1] ++;
                }
                
                if ((x-1 >= 0) && (grid_array[y][x-1] != -1))
                {
                    grid_array[y][x-1] ++;
                }
                
                if ((y+1 < grid_size) && (grid_array[y+1][x] != -1))
                {
                    grid_array[y+1][x] ++;
                }
                
                if ((y-1 >= 0) && (grid_array[y-1][x] != -1))
                {
                    grid_array[y-1][x] ++;
                }
                
                if ((x+1 < grid_size) &&
                    (y+1 < grid_size) &&
                    (grid_array[y+1][x+1] != -1))
                {
                    grid_array[y+1][x+1] ++;
                }
                
                if ((x-1 >= 0) &&
                    (y-1 >= 0) &&
                    (grid_array[y-1][x-1] != -1))
                {
                    grid_array[y-1][x-1] ++;
                }
                
                if ((y+1 < grid_size) &&
                    (x-1 >= 0) &&
                    (grid_array[y+1][x-1] != -1))
                {
                    grid_array[y+1][x-1] ++;
                }
                
                if ((x+1 < grid_size) &&
                    (y-1 >= 0) &&
                    (grid_array[y-1][x+1] != -1))
                {
                    grid_array[y-1][x+1] ++;
                }
            }
        }
    }
}

void print_array(int grid_size, int** grid_array)
{
    for(int i = 0; i < grid_size; ++i)
    {
        for(int j = 0; j < grid_size; ++j)
        {
            cout << right << setw(2) << grid_array[i][j] << " ";
        }
        
        cout << "\n";
    }
}

void deallocate_memory(int grid_size, int** grid_array)
{
    for(int i = 0; i < grid_size; ++i)
    {
        delete [] grid_array[i];
    }
    
    delete [] grid_array;
}

int replay()
{
    int choice = 0;
    
    cout << "\n\nWould you Like to Go Again?\n";
    cout << "Enter 1 for Yes. Enter 0 to QUIT:";
    cin >> choice;
    
    while ((!cin) || (choice < 0) || (choice > 1))
    {
        cin.clear();
        cin.ignore();
        cout << "Only Enter a 0 or 1: ";
        
        cin >> choice;
    }
    
    return choice;
}