#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <utility>
#include <vector>
#include <iomanip>
#include <math.h>

using namespace std;

class Game {
    public :
        int board[4][4];
        // D R U L
        int dirLine[4] = {1,0,-1,0};
        int dirColumn[4] = {0,1,0,-1};
        int gameVar;
        double PI = 3.1415926f;
        int score = 0;
        int best_score = 0;
        
        pair<int, int> generateUnoccupiedPosition();
        void addPiece();
        void newGame();
        bool canDoMove (int line, int column, int nextLine, int nextColumn);
        bool isFull();
        bool isWin();
        int applyMove(int direction);
};

pair<int, int> Game :: generateUnoccupiedPosition(){
    vector <pair<int, int> > v;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (board[i][j] == 0)
                v.push_back(make_pair(i,j));
    return v[rand() % (v.size())];
}

void Game :: addPiece(){
    pair <int, int> pos = generateUnoccupiedPosition();
    board[pos.first][pos.second] = 2;
}

void Game :: newGame(){
    gameVar = 0;
    score = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            board[i][j] = 0;
    addPiece();
}

bool Game :: canDoMove (int line, int column, int nextLine, int nextColumn){
    if (nextLine < 0 || nextColumn < 0 || nextLine > 3 || nextColumn > 3 || 
        (board[nextLine][nextColumn] != 0 and board[line][column] != board[nextLine][nextColumn]))
        return false;
    return true;
}
bool Game :: isFull(){
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (board[i][j] == 0)
                return false;
    
        
    for (int direction = 0; direction < 4; direction++){
        int startLine = 0, startColoumn = 0, lineStep = 1, columnStep = 1;
        if (direction == 0)
            startLine = 3,lineStep = -1;
        if (direction == 1)
            startColoumn = 3,columnStep = -1;
                
        for (int i = startLine; i >= 0 and i < 4; i += lineStep)
            for (int j = startColoumn; j >= 0 and j < 4; j += columnStep){
                int nextI = i + dirLine[direction], nextJ = j + dirColumn[direction];
                if (board[i][j] and canDoMove(i,j,nextI,nextJ))
                    return false;
            }
        
    }
    gameVar == 2;
    return true;
}

bool Game :: isWin(){
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (board[i][j] == 2048)
                {gameVar = 1; return true;}
    return false;
}

int Game :: applyMove(int direction){
    if (gameVar != 0)
        return 0;
    int startLine = 0, startColoumn = 0, lineStep = 1, columnStep = 1;
    if (direction == 0)
        startLine = 3,lineStep = -1;
    if (direction == 1)
        startColoumn = 3,columnStep = -1;

    int movePossible, canAddPiece = 0;
    do {
        movePossible = 0;
        for (int i = startLine; i >= 0 and i < 4; i += lineStep)
            for (int j = startColoumn; j >= 0 and j < 4; j += columnStep){
                int nextI = i + dirLine[direction], nextJ = j + dirColumn[direction];
                if (board[i][j] and canDoMove(i,j,nextI,nextJ))
                    board[nextI][nextJ] += board[i][j], board[i][j] = 0, 
                    movePossible++, canAddPiece++, score += board[nextI][nextJ];

            }
        glutPostRedisplay();
    }while (movePossible);
    if (canAddPiece)
        {addPiece();return 1;}
    return 0;
} ;

/// class Game is Over

Game game;

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable( GL_BLEND );
    glDepthMask( GL_FALSE );
    int a = 1;
    glColor4ub(250,248,240,a);
    glBegin(GL_POLYGON);
        
        glVertex2i(0,0);
        glVertex2i(0,270);
        glVertex2i(245,270);
        glVertex2i(245,0);

    glEnd();
    
    glColor4ub(185,173,161,a);
    glHint(GL_POLYGON_SMOOTH, GL_NICEST);
    glEnable(GL_POLYGON_SMOOTH);
    glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    
    glBegin(GL_POLYGON);
        
        glVertex2i(10,10);
        glVertex2i(10,235);
        glVertex2i(235,235);
        glVertex2i(235,10);

    glEnd();
    
    int xl=15,yl=15;
    for (int i = 0; i < 4; i++){
        
        for (int j = 0; j < 4; j++){
            if (game.board[i][j] == 0){
                glColor4ub(202,193,181,a);
                glBegin(GL_POLYGON);
            
                    glVertex2i(xl,yl);
                    glVertex2i(xl+50,yl);
                    glVertex2i(xl+50,yl+50);
                    glVertex2i(xl,yl+50);

                glEnd();
                xl += 55;
            }
            else if (game.board[i][j] == 2){
                glColor4ub(236,228,219,a);
                glBegin(GL_POLYGON);
            
                    glVertex2i(xl,yl);
                    glVertex2i(xl+50,yl);
                    glVertex2i(xl+50,yl+50);
                    glVertex2i(xl,yl+50);

                glEnd();
                glColor4ub(117,110,102,a);
                glRasterPos2f(xl+23,yl+22);
                //glScalef(0.005,0.005,1);
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '2');
                
                xl += 55;
            }
            else if (game.board[i][j] == 4){
                glColor4ub(236,225,204,a);
                glBegin(GL_POLYGON);
            
                    glVertex2i(xl,yl);
                    glVertex2i(xl+50,yl);
                    glVertex2i(xl+50,yl+50);
                    glVertex2i(xl,yl+50);

                glEnd();
                glColor4ub(117,110,102,a);
                glRasterPos2f(xl+23,yl+22);
                //glScalef(0.005,0.005,1);
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '4');
                
                xl += 55;
            }
            else if (game.board[i][j] == 8){
                glColor4ub(233,181,130,a);
                glBegin(GL_POLYGON);
            
                    glVertex2i(xl,yl);
                    glVertex2i(xl+50,yl);
                    glVertex2i(xl+50,yl+50);
                    glVertex2i(xl,yl+50);

                glEnd();
                glColor4ub(255,255,255,a);
                glRasterPos2f(xl+23,yl+22);
                //glScalef(0.005,0.005,1);
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '8');
                
                xl += 55;
                
                
            }
            else if (game.board[i][j] == 16){
                glColor4ub(233,154,109,a);
                glBegin(GL_POLYGON);
            
                    glVertex2i(xl,yl);
                    glVertex2i(xl+50,yl);
                    glVertex2i(xl+50,yl+50);
                    glVertex2i(xl,yl+50);

                glEnd();
                
                glColor4ub(255,255,255,a);
                glRasterPos2f(xl+20,yl+22);
                //glScalef(0.005,0.005,1);
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '1');
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '6');
                
                xl += 55;
            }
            else if (game.board[i][j] == 32){
                glColor4ub(231,131,103,a);
                glBegin(GL_POLYGON);
            
                    glVertex2i(xl,yl);
                    glVertex2i(xl+50,yl);
                    glVertex2i(xl+50,yl+50);
                    glVertex2i(xl,yl+50);

                glEnd();
                
                glColor4ub(255,255,255,a);
                glRasterPos2f(xl+20,yl+22);
                //glScalef(0.005,0.005,1);
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '3');
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '2');
                
                xl += 55;
            }
            else if (game.board[i][j] == 64){
                glColor4ub(229,105,72,a);
                glBegin(GL_POLYGON);
            
                    glVertex2i(xl,yl);
                    glVertex2i(xl+50,yl);
                    glVertex2i(xl+50,yl+50);
                    glVertex2i(xl,yl+50);

                glEnd();
                
                glColor4ub(255,255,255,a);
                glRasterPos2f(xl+20,yl+22);
                //glScalef(0.005,0.005,1);
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '6');
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '4');
                
                
                xl += 55;
            }
            else if (game.board[i][j] == 128){
                glColor4ub(232,209,128,a);
                glBegin(GL_POLYGON);
            
                    glVertex2i(xl,yl);
                    glVertex2i(xl+50,yl);
                    glVertex2i(xl+50,yl+50);
                    glVertex2i(xl,yl+50);

                glEnd();
                
                glColor4ub(255,255,255,a);
                glRasterPos2f(xl+17,yl+22);
                //glScalef(0.005,0.005,1);
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '1');
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '2');
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '8');
                
                xl += 55;
            }
            else if (game.board[i][j] == 256){
                glColor4ub(232,205,114,a);
                glBegin(GL_POLYGON);
            
                    glVertex2i(xl,yl);
                    glVertex2i(xl+50,yl);
                    glVertex2i(xl+50,yl+50);
                    glVertex2i(xl,yl+50);

                glEnd();
                glColor4ub(255,255,255,a);
                glRasterPos2f(xl+17,yl+22);
                //glScalef(0.005,0.005,1);
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '2');
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '5');
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '6');
                
                xl += 55;
            }
            else if (game.board[i][j] == 512){
                glColor4ub(231,202,101,a);
                glBegin(GL_POLYGON);
            
                    glVertex2i(xl,yl);
                    glVertex2i(xl+50,yl);
                    glVertex2i(xl+50,yl+50);
                    glVertex2i(xl,yl+50);

                glEnd();
                
                glColor4ub(255,255,255,a);
                glRasterPos2f(xl+17,yl+22);
                //glScalef(0.005,0.005,1);
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '5');
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '1');
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '2');
                
                
                xl += 55;
            }
            else if (game.board[i][j] == 1024){
                glColor4ub(231,202,101,a);
                glBegin(GL_POLYGON);
            
                    glVertex2i(xl,yl);
                    glVertex2i(xl+50,yl);
                    glVertex2i(xl+50,yl+50);
                    glVertex2i(xl,yl+50);

                glEnd();
                
                glColor4ub(255,255,255,a);
                glRasterPos2f(xl+14,yl+22);
                //glScalef(0.005,0.005,1);
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '1');
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '0');
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '2');
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '4');
                
                xl += 55;
            }
            else if (game.board[i][j] == 2048){
            
                glColor4ub(230,197,66,a);
                glBegin(GL_POLYGON);
            
                    glVertex2i(xl,yl);
                    glVertex2i(xl+50,yl);
                    glVertex2i(xl+50,yl+50);
                    glVertex2i(xl,yl+50);

                glEnd();
                
                glColor4ub(255,255,255,a);
                glRasterPos2f(xl+14,yl+22);
                //glScalef(0.005,0.005,1);
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '2');
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '0');
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '4');
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '8');
                
                xl += 55;
            }
            else {
            glColor4ub(0,193,181,a);
            glBegin(GL_POLYGON);
            
                glVertex2i(xl,yl);
                glVertex2i(xl+50,yl);
                glVertex2i(xl+50,yl+50);
                glVertex2i(xl,yl+50);

            glEnd();
            xl += 55;
            }
            
                
        }
        xl = 15;
        yl += 55;
        
    }
    
    glDepthMask( GL_TRUE );
    glDisable( GL_BLEND );
    
    if (game.isWin()){
        glColor4ub(251,248,240,a);
        glBegin(GL_POLYGON);
            
            glVertex2i(10,100);
            glVertex2i(10,145);
            glVertex2i(235,145);
            glVertex2i(235,100);


        glEnd();
        string s = "You Won !";
        glColor4ub(117,110,102,a);
        glRasterPos2f(100,120);
        
        for (int i = 0; i < s.size(); i++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
    }
    else if (game.isFull()){
        glColor4ub(251,248,240,a);
        glBegin(GL_POLYGON);
            
            glVertex2i(10,100);
            glVertex2i(10,145);
            glVertex2i(235,145);
            glVertex2i(235,100);


        glEnd();
        string s = "Game Over !";
        glColor4ub(117,110,102,a);
        glRasterPos2f(100,120);
        for (int i = 0; i < s.size(); i++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
    }
    if (game.score > game.best_score)
        game.best_score = game.score;
    
    glColor4ub(185,173,161,a);
    glBegin(GL_POLYGON);
            
        glVertex2i(20,240);
        glVertex2i(20,265);
        glVertex2i(100,265);
        glVertex2i(100,240);


    glEnd();
    string s = "SCORE";
    glColor4ub(236,228,219,a);
    glRasterPos2f(30,250);
    for (int i = 0; i < s.size(); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
    
    glColor4ub(255,255,255,a);
    
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ' ');
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ':');
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ' ');
    
    
    string temp = to_string(game.score);
    
    for (int i = 0; i < temp.size(); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, temp[i]);
    
    glColor4ub(185,173,161,a);
    glBegin(GL_POLYGON);
            
        glVertex2i(145,240);
        glVertex2i(145,265);
        glVertex2i(225,265);
        glVertex2i(225,240);


    glEnd();
    
    s = "BEST";
    glColor4ub(236,228,219,a);
    glRasterPos2f(155,250);
    for (int i = 0; i < s.size(); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
    
    glColor4ub(255,255,255,a);
    
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ' ');
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ':');
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ' ');
    
    
    temp = to_string(game.best_score);
    
    for (int i = 0; i < temp.size(); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, temp[i]);
    
    glFlush();
    glutSwapBuffers();
}

void keyboard(int key, int x, int y){
    if(key == GLUT_KEY_LEFT)    
        game.applyMove(3);
    else if(key == GLUT_KEY_RIGHT)
        game.applyMove(1);
    else if(key == GLUT_KEY_DOWN)
        game.applyMove(2);
    else if(key == GLUT_KEY_UP)
        game.applyMove(0);
}

void processKeys(unsigned char key, int x, int y) {
    if (key == 32) 
        {game.newGame();glutPostRedisplay();}
}

void myInit() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 245, 0, 270);
}

int main(int argc, char **argv) {
    game.newGame();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(550, 500);
    glutInitWindowPosition(200, 300);
    glutCreateWindow("2048");
    myInit();
    glutSpecialFunc(keyboard);
    glutKeyboardFunc(processKeys);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}