#include <iostream>
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>

void getArray (int *grid,char *filename){
    //counters to help adding to grid
    int j=0;

    /*opens file and creates reader*/
    std::string fname = filename;
    std::ifstream infile;
    infile.open(fname);
    // creates a string str to hold the file lines
    std::string str;
    // each time the below function runs, the entire line from the text file is stored in string str
    while(std::getline(infile,str)) {
	// you could do this to access each element in each line
        for(int i = 0; i < str.length(); i++) {
            if (str[i] != ',' && str[i]-'0' != 10){
                //convert to num then add to grid
                int num = str[i]-'0';
                grid[j] = num;
                j++;
            }
        }
    }
    infile.close();

}

//function that checks row
bool checkRow (int *grid,int row,int checkNum){
    for(int k=0;k<9;k++){
        if (grid[9*row+k] == checkNum){
            return true;
        }
    }
    return false;
}

//function that checks column
bool checkCol (int *grid,int col,int checkNum){
    for(int k=0;k<9;k++){
        if (grid[9*k+col] == checkNum){
            return true;
        }
    }
    return false;
}

//function that checks box
bool checkBox (int *grid,int row,int col,int checkNum){
    //get coordinates of top left corner of box
    int startX = row - (row%3);
    int startY = col - (col%3);

    //check if number is found in box
    for(int k=0;k<3;k++){
        for (int l=0;l<3;l++){
            if (grid[9*startX+startY] == checkNum){
                return true;
            }
            startY++;
        }
        startX++;
        startY= col - (col%3);
    }
    return false;
}

//function that checks if there is open spaces
bool checkOpen(int * grid) {
    for(int k=0;k<9;k++){
        for (int l=0;l<9;l++){
            if (grid[9*k+l] == 0){
                return true;
            }
        }
    }
    return false;
}

//get x coordinate of open space
int getX(int * grid){

    for(int k=0;k<9;k++){
        for (int l=0;l<9;l++){
            if (grid[9*k+l] == 0){
                return k;
            }
        }
    }
}

//get y coordinate of open space
int getY(int * grid){

    for(int k=0;k<9;k++){
        for (int l=0;l<9;l++){
            if (grid[9*k+l] == 0){
                return l;
            }
        }
    }
}


//function that combines all 3 checks
bool canPlace (int *grid, int row,int col,int checkNum){
    if(checkCol(grid,col,checkNum) || checkRow(grid,row,checkNum) || checkBox(grid,row,col,checkNum)){
        return false;
    }
    return true;
}

bool sudoku(int *grid){
    //if theres no more empty spaces return true
    if (checkOpen(grid) == false){
        return true;
    }

    //get the x and y coordinates of empty spot
    int x = getX(grid);
    int y = getY(grid);

    //loop from 1 to 9
    for (int i = 1; i < 10; i++ ){
        if (canPlace(grid,x,y,i)){

            //make current spot the number
            grid[9*x+y] = i;

            //recurse onward return when finished
            if(sudoku(grid)){
                return true;
            }

            //if that value doesnt work backtrack
            grid[9*x+y] = 0;

        }
    }
    //if none of values from 1 to 9 work backtrack
    return false;
}

int main(int argc, char *argv[]) {

    //initialize grid
    int *grid = new int[9*9];

    getArray(grid,argv[1]);

    sudoku(grid);

    for(int k=0;k<9;k++){
        for (int l=0;l<9;l++){
            if (l ==8){
                std::cout << grid[9*k+l];
            }
            else{
                std::cout << grid[9*k+l] << ",";
            }
        }
        std::cout << std::endl;
    }



   // std::cout << getX(grid) << std::endl;
   // std::cout << getY(grid) << std::endl;

    delete [] grid ;
    return 0;
}