#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>
//std::array<std::array<int,SIZE>,SIZE>scoring_system;


/*---------------------------------------------------------------------------------------------------*/

struct Point {
    int x, y;
    int score;
    Point() : Point(0,0){}
    Point (int x, int y) : x(x), y(y){}
    Point (int score) : score(score){}
    bool operator==(const Point& rhs) const {
		return x == rhs.x && y == rhs.y;
	}
	bool operator!=(const Point& rhs) const {
		return !operator==(rhs);
	}
	Point operator+(const Point& rhs) const {
		return Point(x + rhs.x, y + rhs.y);
	}
	Point operator-(const Point& rhs) const {
		return Point(x - rhs.x, y - rhs.y);
	}
};




/*---------------------------------------------------------------------------------------------------*/

class Game{
    private:
        int next_player(int current_player)const;
        bool is_spot_on_board(Point p) const ;
        int get_disc(Point p) const ;
        bool is_disc_at(Point p, int disc) const;
        bool is_spot_valid(Point center) const;
        void flip_disc(Point move);
        void set_disc(Point p, int disc);
        
    public:
        enum SPOT_STATE {
            EMPTY = 0,
            BLACK = 1,
            WHITE = 2
        };
        static const int SIZE = 8;
        const std::array<Point, 8> directions{{
            Point(-1, -1),  Point(-1, 0),   Point(-1, 1),
            Point(0, -1),   /*{0, 0},     */Point(0, 1),
            Point(1, -1),   Point(1, 0),    Point(1, 1)
        }};
        const std::array<Point,4>X_Squares{{
            Point(1,1),Point(6,1),Point(1,6),Point(6,6)
        }};
        const std::array<Point,8>C_Squares{{
            Point(0,1),Point(1,0),Point(0,6),Point(1,7),
            Point(6,0),Point(7,1),Point(6,7),Point(7,6)
        }};
        const std::array<Point,16>A_Squares{{//Core Edges
            Point(0,2),Point(0,3),Point(0,4),Point(0,5),
            Point(2,0),Point(3,0),Point(4,0),Point(5,0),
            Point(7,2),Point(7,3),Point(7,4),Point(7,5),
            Point(2,7),Point(3,7),Point(4,7),Point(5,7)
        }};
        const std::array<Point,4>Corner_Squares{{
            Point(0,0),Point(0,7),Point(7,7),Point(7,0)
        }};
        const int scoring_system[SIZE][SIZE]=
            {
                {99,  -8,   8,   6,   6,  8,  -8, 99},
                {-8, -24,  -4,  -3,  -3, -4, -24, -8},
                { 8,  -4,   7,   4,   4,  7,  -4,  8},
                { 6,  -3,   4,   0,   0,  4,  -3,  6},
                { 6,  -3,   4,   0,   0,  4,  -3,  6},
                { 8,  -4,   7,   4,   4,  7,  -4,  8},
                {-8, -24,  -4,  -3,  -3, -4, -24, -8},
                {99,  -8,   8,   6,   6,  8,  -8, 99}
            };
        int current_player;
        int Check_X();
        int Check_C();
        int Check_A();
        int Check_Corner();
        std::array<int,3>score;
        std::vector<Point>next_valid_moves;
        std::array<std::array<int, SIZE>, SIZE> board;
        Game();
        std::vector<Point>valid_moves()const;
        void put_disc(Point p);
        void read_board(std::ifstream& fin) ;
        void read_valid_spots(std::ifstream& fin) ;
        
};
//how
//CLASS MEMBER FUNCTION
/*---------------------------------------------------------------------------------------------------*/

Game::Game(){
    current_player=BLACK;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }
    score[BLACK]=0;
    score[WHITE]=0;   
    board[3][4] = board[4][3] = BLACK;
    board[3][3] = board[4][4] = WHITE;
        }
int Game::next_player(int current_player)const{
    return 3-current_player;
}
bool Game::is_spot_on_board(Point p) const {
        return 0 <= p.x && p.x < SIZE && 0 <= p.y && p.y < SIZE;
}
int Game::get_disc(Point p) const {
    return board[p.x][p.y];
}
void Game::set_disc(Point p, int disc) {
    board[p.x][p.y] = disc;
}
bool Game::is_disc_at(Point p, int disc) const {
    if (!is_spot_on_board(p))
        return false;
    if (get_disc(p) != disc)
        return false;
    return true;
}
int Game::Check_X(){
    int temp_score = 0;
    for(auto i:X_Squares){
        if(board[i.x][i.y]==current_player) temp_score += scoring_system[i.x][i.y];
        if(board[i.x][i.y]==3-current_player) temp_score -= scoring_system[i.x][i.y];
    }
    return temp_score;
}
int Game::Check_C(){
    int temp_score = 0;
    for(auto i:C_Squares){
        if(board[i.x][i.y]==current_player) temp_score += scoring_system[i.x][i.y];
        if(board[i.x][i.y]==3-current_player) temp_score -= scoring_system[i.x][i.y];
    }
    return temp_score;
}
int Game::Check_A(){
    int temp_score = 0;
    for(auto i:A_Squares){
        if(board[i.x][i.y]==current_player) temp_score += scoring_system[i.x][i.y];
        if(board[i.x][i.y]==3-current_player) temp_score -= scoring_system[i.x][i.y];
    }
    return temp_score *0.3;
}
int Game::Check_Corner(){
    int temp_score = 0;
    for(auto i:Corner_Squares){
        if(board[i.x][i.y]==current_player){
            temp_score += scoring_system[i.x][i.y];
            temp_score -= (Check_X() + Check_C());
            temp_score += Check_A();
        }
        else if(board[i.x][i.y]==3-current_player){
            temp_score -= scoring_system[i.x][i.y];
            temp_score -= (Check_X() + Check_C());
            temp_score += Check_A();
        }
        else{
            temp_score += (Check_X() + Check_C());
            temp_score -= Check_A();
        }
    }
    return temp_score*0.6;
}
std::vector<Point> Game::valid_moves()const{
    std::vector<Point>valid_moves;
    for(int i =0 ;i<SIZE;i++){
        for(int j =0;j<SIZE;j++){
            Point p = Point(i,j); 
            if(board[i][j] != EMPTY)continue;
            if(is_spot_valid(p))valid_moves.push_back(p);
        }
    }
    return valid_moves;
}
bool Game::is_spot_valid(Point center) const{
    if(get_disc(center) != EMPTY)return false;
    for(Point dir : directions){
        Point p = dir + center;
        if (!is_disc_at(p, next_player(current_player)))continue;
        p = p + dir; 
        while (is_spot_on_board(p) && get_disc(p) != EMPTY) {
            if (is_disc_at(p, current_player))return true;
            p = p + dir;
        }
    }
    return false;
}
void Game::flip_disc(Point center){
    for (Point dir: directions) {
            // Move along the direction while testing.
            Point p = center + dir;
            if (!is_disc_at(p, next_player(current_player)))
                continue;
            std::vector<Point> discs({p});
            p = p + dir;
            while (is_spot_on_board(p) && get_disc(p) != EMPTY) {
                if (is_disc_at(p, current_player)) {
                    for (Point s: discs) {
                        set_disc(s, current_player);
                        score[current_player] += scoring_system[s.x][s.y];
                        score[next_player(current_player)] -= scoring_system[p.x][p.y];
                    }
                    break;
                }
                discs.push_back(p);
                p = p + dir;
            }
        }
}
void Game::put_disc(Point p){
    //std::cout<<"We are in the put disc "<<std::endl;
    score[current_player] += scoring_system[p.x][p.y];

    //std::cout<<"Scoring system is working"<<std::endl;
    set_disc(p, current_player);
    //std::cout<<"Set disc is working"<<std::endl;
    flip_disc(p);
    //std::cout<<"Flip disc is working"<<std::endl;
    current_player=next_player(current_player);
    //std::cout<<"CHECK CURRENT_PLAYER"<<std::endl;
    next_valid_moves=valid_moves();//DEAD END 
    //std::cout<<"END"<<std::endl;
}
void Game::read_board(std::ifstream& fin) {
    fin >> current_player;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fin >> board[i][j];
        }
    }
}
void Game::read_valid_spots(std::ifstream& fin) {
    int n_valid_spots;
    fin >> n_valid_spots;
    int x, y;
    for (int i = 0; i < n_valid_spots; i++) {
        fin >> x >> y;
        next_valid_moves.push_back({x, y});
    }
}



 Point TOO_EASY(Game ez, int depth, Point alpha, Point beta, int Pro_player) {
    if (depth ==0 ||ez.next_valid_moves.size()==0){
        //std::cout<<"DEPTH 0"<<std::endl;
        
        Point p;
        p.score= ez.score[ez.current_player] + 0.5*ez.Check_Corner();
        return p;
        
        
    }
    if (Pro_player==ez.current_player){
        //std::cout<<"Pro player"<<std::endl;
        Point value;
        value.score=-1000;
        std::vector<Point>::iterator it;
        for(it = ez.next_valid_moves.begin(); it != ez.next_valid_moves.end();++it){
            //std::cout<<"Endless loop"<<std::endl;
            Game tmp = ez;
            //std::cout<<"CHECK1"<<std::endl;
            tmp.put_disc(*it);//found it
            //std::cout<<"CHECK2"<<std::endl;
            Point tmep = TOO_EASY(tmp, depth-1, alpha, beta, Pro_player);
            alpha.score = std::max(alpha.score, tmep.score);
            
            if(value.score!=std::max(value.score, tmep.score)){
                value.score=tmep.score;
                value.x=it->x;
                value.y=it->y;
            }//std::cout<<tmep.score<<"   "<<it->x<<" "<<it->y<<std::endl;
            if(beta.score<=alpha.score){
                break;
            }
        }
        return value;
    }
    else {
        //std::cout<<"Noob player"<<std::endl;
        Point value;
        value.score=1000;
        std::vector<Point>::iterator it;
        for(it = ez.next_valid_moves.begin(); it != ez.next_valid_moves.end();++it){
            Game tmp = ez;
            tmp.put_disc(*it);
            Point tmep = TOO_EASY(tmp, depth-1, alpha, beta ,Pro_player);
            beta.score=std::min(beta.score, tmep.score);
            
            if(value.score!=std::min(value.score, tmep.score)){
                value.score=tmep.score;
                value.x=it->x;
                value.y=it->y;
            }
            if(beta.score<=alpha.score){
                break;
            }
        }
        return value;
    }
 }
void write_valid_spot(std::ofstream& fout, Game g) {
    //std::cout<<"In the write_valid_spot function"<<std::endl;
    Point p = TOO_EASY(g,7,-1000,1000, 3-g.current_player);
    fout << p.x << " " << p.y << std::endl;
    fout.flush();
    std::cout<<"MOVE:    "<<p.x << " " << p.y << std::endl;
}
int main(int, char** argv) {
    Game ez;
    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);
    ez.read_board(fin);
    //std::cout<<"Reading board is done"<<std::endl;
    ez.read_valid_spots(fin);
    //std::cout<<"Reading valid spots is done"<<std::endl;
    write_valid_spot(fout,ez);
    fin.close();
    fout.close();
    return 0;
}
