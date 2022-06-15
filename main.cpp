#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

bool lineIsCorrected(int (&table)[9][9], int current_row, int current_col){

    vector<int> current;
    for(int i = 0 ; i < 9 ; i++){
        if(table[current_row][i] != 0 && find(current.begin(), current.end(), table[current_row][i]) == current.end()){
            current.push_back(table[current_row][i]);
        } else {
            if(table[current_row][i] != 0) return false;
        }
    }
    //cout << "Retornei True 1" << endl;
    return true;
}

bool columnIsCorrected(int (&table)[9][9], int current_row, int current_col){

    vector<int> current;
    for(int i = 0 ; i < 9 ; i++){
        if(table[i][current_col] != 0 && find(current.begin(), current.end(), table[i][current_col]) == current.end()){
            current.push_back(table[i][current_col]);
        } else {
            if(table[i][current_col] != 0) return false;
        }
    }
    //cout << "Retornei True 2" << endl;
    return true;
}

bool squareIsCorrected(int (&table)[9][9], int current_row, int current_col){
    
    vector<int> current;
    
    int init_line = 3*(int)(current_row/3);
    int init_col = 3*(int)(current_col/3);

    for(int i = 0 ; i < 3 ; i++){
        for(int j = 0 ; j < 3 ; j++){
            //cout << "Verificando linha: " << init_line+i << ", coluna: " << init_col+j << ", valor: " << table[init_line+i][init_col+j] << endl;
            if(table[init_line+i][init_col+j] != 0 && find(current.begin(), current.end(), table[init_line+i][init_col+j]) == current.end()){
                current.push_back(table[init_line+i][init_col+j]);
            } else {
                //cout << "Achei um igual ou achei um Zero " << table[init_line+i][init_col+j] << endl;
                if(table[init_line+i][init_col+j] != 0){
                    return false;
                }
            }
        }
    }
    
    //cout << "Retornei True 3" << endl;
    return true;
}


bool solve(int (&table)[9][9], int current_row, int current_col){

    if(current_row == 9){
        return true;
    }
    if(table[current_row][current_col] != 0){
        return (current_col == 8) ? solve(table, current_row+1, 0) : solve(table, current_row, current_col+1);
    } else {
        for(int i = 1; i < 10 ; i++){
            table[current_row][current_col] = i;
            if(lineIsCorrected(table, current_row, current_col) && columnIsCorrected(table, current_row, current_col) && squareIsCorrected(table, current_row, current_col)){
                if((current_col == 8) ? solve(table, current_row+1, 0) : solve(table, current_row, current_col+1)){
                    return true;
                }
            } else {
                //cout << "O " << i << " não pode ser inserido em (" << current_row << ", " << current_col << ")\n";
            }
        }
    }

    table[current_row][current_col] = 0;
    return false;
}

void printTable(int (&table)[9][9]){
    for(int i = 0 ; i < 9 ; i++){
        for(int j = 0 ; j < 9 ; j++){
            if(j != 0 && (j)%3 == 0) cout << " || ";
            cout << table[i][j] << " ";
            
        }
        if((i+1)%3 == 0) cout << "\n==========================\n";
        else cout << endl;
    }
}

/*
int table[9][9] = { 
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
        {4, 5, 6, 7, 8, 9, 1, 2, 3},
        {7, 8, 9, 1, 2, 3, 4, 5, 6},
        {2, 3, 4, 5, 6, 7, 8, 9, 1},
        {5, 6, 7, 8, 9, 1, 2, 3, 4},
        {8, 9, 1, 2, 3, 4, 5, 6, 7},
        {3, 4, 5, 6, 7, 8, 9, 1, 2},
        {6, 7, 8, 9, 1, 2, 3, 4, 5},
        {9, 1, 2, 3, 4, 5, 6, 7, 8}};
*/

int main(){
    int table[9][9] = { 
        {4, 0, 0, 3, 0, 7, 0, 0, 6},
        {0, 3, 0, 4, 0, 5, 0, 0, 0},
        {0, 0, 0, 9, 0, 0, 0, 4, 0},
        {2, 8, 0, 0, 0, 0, 4, 0, 0},
        {0, 0, 5, 0, 0, 0, 0, 6, 0},
        {3, 4, 9, 0, 0, 0, 7, 0, 0},
        {9, 7, 0, 8, 2, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 7, 4},
        {6, 2, 0, 0, 0, 0, 9, 8, 0}};

    printTable(table);
    cout << endl << "Solving...." << endl << endl;
    if(solve(table, 0, 0)){
        cout << "Consegui resolver" << endl;
    } else {
        cout << "Não consegui resolver" << endl;
    }
    printTable(table);


    return 0;
}