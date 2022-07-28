#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Mar 24 18:15:44 2022

@author: pujawadare
"""
from turtle import Screen, Turtle, mainloop, onscreenclick
import math
import random

# game variables
N = 4
board = [[i*N + j +1 for j in range(N) ] for i in range(N)]
board[N-1][N-1] = 0
board_position = [[ (0,0) for j in range(N) ] for i in range(N)]
c = 0

def find_index():
    global N, c, board
    for i in range(N):
        for j in range(N):
            if (board[i][j] == 0):
                return i,j
    return -1,-1

def generate_puzzle(prevoperation : int):
    global N, c, board
    if c == 500:
        return ;
    x,y = find_index()
    possibilities = []
    if (y > 0):
        possibilities.append(0)
    if (y < N-1):
        possibilities.append(1)
    if (x > 0):
        possibilities.append(2)
    if (x < N-1):
        possibilities.append(3)
    ch = random.randint(0, len(possibilities)-1)
    if (possibilities[ch] == 0 and prevoperation != 1):
        board[x][y], board[x][y-1] = board[x][y-1] , board[x][y]
    elif (possibilities[ch] == 1 and prevoperation != 0):
        board[x][y], board[x][y+1] = board[x][y+1] , board[x][y]
    elif (possibilities[ch] == 2 and prevoperation != 3):
        board[x][y], board[x-1][y] = board[x-1][y], board[x][y]
    elif (possibilities[ch] == 3 and prevoperation != 2):
        board[x][y], board[x+1][y] = board[x+1][y], board[x][y]
    c+=1
    generate_puzzle(possibilities[ch])

def round_rectangle(center_x,center_y,width,height,cornersize, color, t):

    t.hideturtle()
    t.speed(0)
    t.pensize(2)
    t.pencolor(color)
    
    t.speed(0)
    t.up()
    t.hideturtle()
    t.up()
    t.goto(center_x-width/2+cornersize,center_y-height/2)
    t.down()
    t.fillcolor(color)
    t.begin_fill()
    for _ in range(2):
        t.fd(width-2*cornersize)
        t.circle(cornersize,90)
        t.fd(height-2*cornersize)
        t.circle(cornersize,90)
    t.end_fill()

class Game(Turtle):
    def __init__(self):
        Turtle.__init__(self)
        self.hideturtle()
        self.speed(0)
        self.display()
        onscreenclick(self.move)
        
        
    def display(self):
        for i in range(N):
            for j in range(N):
                if (board[i][j] != 0):
                    round_rectangle(board_position[i][j][0], board_position[i][j][1], 100, 100, 5, "#8C7B68",self)
                    self.goto(board_position[i][j][0], board_position[i][j][1]-30)
                    self.pencolor("#FFFFFF")
                    self.write(board[i][j], align="Center",font=("Courier New",50,"bold"))
    def move(self, x, y):
        
        x = int(x)
        y = int(y)
        for i in range(N):
            for j in range(N):
                if abs(board_position[i][j][0]-x) <= 50 and abs(board_position[i][j][1]-y) <= 50 and board[i][j] != 0:
                    if (i > 0 and board[i-1][j] == 0):
                        self.update_board(i,j,i-1,j)
                    elif (i < N-1 and board[i+1][j] == 0):
                        self.update_board(i,j,i+1,j)
                    elif (j > 0 and board[i][j-1] == 0):
                        self.update_board(i,j,i,j-1)
                    elif (j < N-1 and board[i][j+1] == 0):
                        self.update_board(i,j,i,j+1)
                        
    def update_board(self, x1,y1,x2,y2):
        board[x1][y1], board[x2][y2] = board[x2][y2], board[x1][y1]
        round_rectangle(board_position[x1][y1][0], board_position[x1][y1][1], 100, 100, 5, "#CAC1B5",self)
        
        round_rectangle(board_position[x2][y2][0], board_position[x2][y2][1], 100, 100, 5, "#8C7B68",self)
        self.goto(board_position[x2][y2][0], board_position[x2][y2][1]-30)
        self.pencolor("#FFFFFF")
        self.write(board[x2][y2], align="Center",font=("Courier New",50,"bold"))

        
def main():
    sc = Screen()
    t = Turtle()
    sc.setup(500,500)
    sc.bgcolor("#FAF8F0")
    round_rectangle(0, 0, 450, 450, 10,"#BEB19E", t)
    x,y = 0,0
    for i in [165, 55, -55, -165]:
        for j in [-165, -55, 55, 165]:
            round_rectangle(j,i, 100, 100, 5, "#CAC1B5",t)
            board_position[x][y] = (j,i)
            y+=1
        x+=1
        y%=N
    generate_puzzle(-1)
    game = Game()
    
    

if __name__ == "__main__":
    main()
    mainloop()



