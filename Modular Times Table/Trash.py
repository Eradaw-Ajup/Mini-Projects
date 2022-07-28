#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Feb 22 11:42:54 2022

@author: pujawadare
"""
import turtle

# Some TRASH

#screen/window setup
wn = turtle.Screen()
wn.title("Proof of Concepts")
wn.bgcolor("black")
wn.setup(width=800, height=600)
wn.tracer(0)

#button
btn = turtle.Turtle()
btn.shape("square")
btn.color("white")
btn.shapesize(stretch_len=4, stretch_wid=2)
btn.penup()
btn.goto(-200,200)


#light
light = turtle.Turtle()
light.shape("circle")
light.color("red")
print(light.color())
light.penup()
light.goto(100,50)

#functions

#button click
def lightup(x,y):
    if light.color() == ('red', 'red'):
        light.color("white")
    elif light.color() == ('white', 'white'):
        light.color("red")
    print(light.color())



btn.onclick(lightup)



#keep the program open.
while True:
    wn.update()


# from turtle import Screen, Turtle, mainloop

# class ColorTurtle(Turtle):

#     def __init__(self, x, y):
#         Turtle.__init__(self)
#         self.shape("turtle")
#         self.resizemode("user")
#         self.shapesize(1,1,2)
#         self.pensize(5)
#         self._color = [0,0,0]
#         self.x = x
#         self._color[x] = y
#         self.color(self._color)
#         self.speed(0)
#         self.left(90)
#         self.pu()
#         self.goto(x,0)
#         self.pd()
#         self.sety(1)
#         self.pu()
#         self.sety(y)
#         self.pencolor("gray25")
#         self.ondrag(self.shift)

#     def shift(self, x, y):
#         self.sety(max(0,min(y,1)))
#         self._color[self.x] = self.ycor()
#         self.fillcolor(self._color)
#         setbgcolor()

# def setbgcolor():
#     screen.bgcolor(red.ycor(), green.ycor(), blue.ycor())

# def main():
#     global screen, red, green, blue
#     screen = Screen()
#     screen.delay(0)
#     screen.setworldcoordinates(-1, -0.3, 3, 1.3)

#     red = ColorTurtle(0, .5)
#     green = ColorTurtle(1, .5)
#     blue = ColorTurtle(2, .5)
#     setbgcolor()

#     writer = Turtle()
#     writer.ht()
#     writer.pu()
#     writer.goto(1,1.15)
#     writer.write("DRAG!",align="center",font=("Arial",30,("bold","italic")))
#     return "EVENTLOOP"

# if __name__ == "__main__":
#     msg = main()
#     print(msg)
#     mainloop()



"""
from turtle import Turtle, Screen
import random

class Puzzle:
    def __init__(self, sideLength, x, y, color):
        self.cells = [[1, 2, 3], [4, 5, 6], [7, 8, 0]]
        self.markers = [[None, None, None], [None, None, None], [None, None, None]]
        self.t = Turtle(visible=False)
        self.s = Screen()
        self.s.tracer(False)
        self.SIZE = sideLength
        self.font = ("Arial", int(0.75 * self.SIZE), "normal")
        self.posX, self.posY = x, y
        self.t.width = 4
        self.t.speed('fastest')
        self.t.color(color, 'white')

    def drawSquare(self, side):
        position = self.t.position()

        self.t.pendown()

        for _ in range(4):
            self.t.forward(side)
            self.t.right(90)

        self.t.penup()
        self.t.goto(position)
        self.t.pendown()

    def isGoal(self):
        temp = []

        for row in range(3):
            for col in range(3):
                temp.append(self.cells[row][col])

        if temp[0] == 0:
            for i in range(8):
                if temp[i] > temp[i + 1]:
                    return False
            return True

        if temp[-1] == 0:
            for i in range(7):
                if temp[i] > temp[i + 1]:
                    return False
            return True

        return False

    def solvable(self):
        temp = []

        for row in range(3):
            for col in range(3):
                temp.append(self.cells[row][col])

        inv_count = 0

        for i in range(len(temp)):
            for j in range(i + 1, len(temp)):
                if temp[j] != 0 and temp[i] != 0 and temp[i] > temp[j]:
                    inv_count += 1

        return inv_count % 2 == 0

    def shuffle(self):
        temp = []

        for row in range(3):
            for col in range(3):
                temp.append(self.cells[row][col])

        for i in range(len(temp)):
            r = random.randint(0, len(temp) - 1)
            t = temp[i]
            temp[i] = temp[r]
            temp[r] = t

        for i in range(len(temp)):
            self.cells[i // 3][i % 3] = temp[i]

    def utility(self):
        manhattan_dist = 0

        for row in range(3):
            for col in range(3):
                tile = self.cells[row][col]
                if tile == 0:
                    continue
                finalRow = (tile - 1) // 3
                finalCol = (tile - 1) % 3
                manhattan_dist += abs(row - finalRow) + abs(col - finalCol)

        return manhattan_dist

    def display(self):
        print(self.cells)

    def up(self, visible):
        found = False
        row, col = 0, 0

        for row in range(3):
            for col in range(3):
                if self.cells[row][col] == 0:
                    found = True
                    break
            if found:
                break

        if row == 2:
            return False

        self.cells[row][col] = self.cells[row + 1][col]
        self.cells[row + 1][col] = 0

        if visible:
            self.updateBoard(row + 1, col, row, col)

        return True

    def down(self, visible):
        found = False
        row, col = 0, 0

        for row in range(3):
            for col in range(3):
                if self.cells[row][col] == 0:
                    found = True
                    break
            if found:
                break

        if row == 0:
            return False

        self.cells[row][col] = self.cells[row - 1][col]
        self.cells[row-1][col] = 0

        if visible:
            self.updateBoard(row - 1, col, row, col)

        return True

    def left(self, visible):
        found = False
        row, col = 0, 0

        for row in range(3):
            for col in range(3):
                if self.cells[row][col] == 0:
                    found = True
                    break
            if found:
                break

        if col == 2:
            return False

        self.cells[row][col] = self.cells[row][col + 1]
        self.cells[row][col + 1] = 0

        if visible:
            self.updateBoard(row, col + 1, row, col)

        return True

    def right(self, visible):
        found = False
        row, col = 0, 0

        for row in range(3):
            for col in range(3):
                if self.cells[row][col] == 0:
                    found = True
                    break
            if found:
                break

        if col == 0:
            return False

        self.cells[row][col] = self.cells[row][col - 1]
        self.cells[row][col - 1] = 0

        if visible:
            self.updateBoard(row, col - 1, row, col)

        return True

    def displayWin(self, count):
        self.t.penup()
        outputX = self.posX
        outputY = self.posY - 5 * self.SIZE
        self.t.goto(outputX, outputY)
        self.t.pendown()
        self.t.write("Solved in " + str(count) + " moves!", move=False, align="center", font=self.font)

    def updateBoard(self, row1, col1, row2, col2):

        data = self.cells[row1][col1] or ''
        marker = self.markers[row1][col1]
        marker.undo()
        marker.write(data, align="center", font=self.font)
        self.s.update()  # don't rely on this happening as a side effect of other turtle functions

        data = self.cells[row2][col2] or ''
        marker = self.markers[row2][col2]
        marker.undo()
        marker.write(data, align="center", font=self.font)
        self.s.update()

    def drawBoard(self):

        for row in range(3):
            for col in range(3):
                self.t.penup()

                topLeftX = self.posX + col * self.SIZE
                topLeftY = self.posY - row * self.SIZE
                self.t.goto(topLeftX, topLeftY)
                self.drawSquare(self.SIZE)

                self.t.penup()
                self.t.goto(topLeftX, topLeftY)
                self.t.right(90)
                self.t.forward(self.SIZE)
                self.t.left(90)
                self.t.forward(self.SIZE / 2)

                data = self.cells[row][col] if self.cells[row][col] != 0 else ''
                marker = self.t.clone()
                marker.write(data, align="center", font=self.font)

                self.markers[row][col] = marker

        self.t.penup()
        self.t.goto(0, 0)
        self.t.pendown()

def play():
    p = Puzzle(50, 0, 0, 'blue')
    p.shuffle()
    while not p.solvable():
        p.shuffle()
    p.display()

    p.drawBoard()
    prevMove = 1
    count = 0

    q = Puzzle(30, -200, 200, 'red')
    q.drawBoard()

    while not p.isGoal():
        # Copy the current state to new puzzle (probably should be a method)

        for row in range(3):
            for col in range(3):
                q.cells[row][col] = p.cells[row][col]

                data = q.cells[row][col] or ''
                marker = q.markers[row][col]
                marker.undo()
                marker.write(data, align="center", font=q.font)
        q.s.update()

        bestMove = 0
        minimum = 1000
        validMoves = []

        # Try out all possible moves on the new puzzle and choose the one that leads to the lowest utility
        # Make the q method calls with False if you don't want to display this board
        if q.down(True):
            validMoves.append(0)
            bestMove = 0
            minimum = q.utility()
            q.up(True)

        if q.right(True):
            validMoves.append(1)
            if q.utility() < minimum:
                minimum = q.utility()
                bestMove = 1
            q.left(True)

        if q.up(True):
            validMoves.append(2)
            if q.utility() < minimum:
                minimum = q.utility()
                bestMove = 2
            q.down(True)

        if q.left(True):
            validMoves.append(3)
            if q.utility() < minimum:
                minimum = q.utility()
                bestMove = 3
            q.right(True)

        # If the best move is the opposite of the one just taken...
        if abs(bestMove - prevMove) == 2:  # UP and DOWN, LEFT and RIGHT are numbered 2 values apart
            #... flip a coin and if it is heads...
            r = random.randint(False, True)
            #... remove the best move from the list of valid moves...
            validMoves.remove(bestMove)
            if r:
                # Randomly choose one of the other valid moves
                index = random.randint(0, len(validMoves) - 1)
                bestMove = validMoves[index]
                # If the coin shows tails, then allow the solver to backtrack over the last move

        if bestMove == 0:
            p.down(True)
            print('down', p.utility())
            count += 1
        elif bestMove == 1:
            p.right(True)
            print('right', p.utility())
            count += 1
        elif bestMove == 2:
            p.up(True)
            print('up', p.utility())
            count += 1
        else:
            p.left(True)
            print('left', p.utility())
            count += 1

        prevMove = bestMove
        print(count)

    print('Solved in ' + str(count) + ' moves')
    p.displayWin(count)

play()
"""
