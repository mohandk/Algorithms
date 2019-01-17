class Sudoku {
public:
    void solveSudoku(vector<vector<char>>& board) {
        //print_board(board);
        pair<int, int> position({0,0});
        bool solution = solveSudokuHelper(board, position);
    }
    
private:
    bool solveSudokuHelper(vector<vector<char>>& board, pair<int, int> position){
        bool solution = false;
        if(position.first < 9 && position.second < 9){    
            vector<char> valid_chars;
            if(board[position.first][position.second] == '.'){
                find_valid(board, position, valid_chars);               
                for(vector<char>::iterator it = valid_chars.begin(); it != valid_chars.end(); ++it){
                    board[position.first][position.second] = *it;
                    pair<int, int> next_position = find_next_position(position);
                    solution = solveSudokuHelper(board, next_position);
                    if(solution){
                        break;
                    }
                }
                if(!solution)
                    board[position.first][position.second] = '.';
            }
            else{
                pair<int, int> next_position = find_next_position(position);
                solution = solveSudokuHelper(board, next_position);  
            }
            return solution;
        }
        else{
            return true;
        }
    }
    
    pair<int, int> find_next_position(pair<int, int> position){
        if(position.second < 8){
            position.second = position.second + 1;
        }
        else{
            position.second = 0;
            position.first++;
        }
        return position;
    }
    
    void find_valid(vector<vector<char>>& board, pair<int, int>& position, vector<char>& valid_chars_vec){
        set<char> valid_chars {'1','2','3','4','5','6','7','8','9'};
		
		//Check current row
        for(int column = 0; column < 9; column++ ){
            if(column == position.second){
                continue;
            }
            if(valid_chars.find(board[position.first][column]) != valid_chars.end()){
                valid_chars.erase(board[position.first][column]);
            }
        }
        
        //Check current column
        for(int row = 0; row < 9; row++ ){
            if(row == position.first){
                continue;
            }
            if(valid_chars.find(board[row][position.second]) != valid_chars.end()){
                valid_chars.erase(board[row][position.second]);
            }
        }
        
        //Check current 3x3 grid
        pair<int, int> sub_position({position.first % 3, position.second % 3});
        pair<int, int> sub_origin({(position.first / 3) * 3, (position.second / 3) * 3});
        for(int row = sub_origin.first; row < (sub_origin.first+3); row++){
            for(int column = sub_origin.second; column < (sub_origin.second+3); column++){
                if(row == position.first && column == position.second){
                    continue;
                }
                if(valid_chars.find(board[row][column]) != valid_chars.end()){
                    valid_chars.erase(board[row][column]);
                }
            }
        }
        for(char num : valid_chars){
            valid_chars_vec.push_back(num);
        }   
    }
    
    void print_board(vector<vector<char>>& board){
        for(auto row : board){
            for(char grid : row){
                cout << grid << "    ";
            }
            cout << endl;
        }
    }
};
