#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Feb 22 11:42:54 2022

@author: pujawadare
"""
# Final Project


from turtle import Screen, Turtle, mainloop
import math
import random

n = 10
a = 10
t = Turtle()
gameVar = 0
#  o - normal 1 - colored loops 2 - colored lengths 
class Slider(Turtle):

    def __init__(self, x, y, z):
        Turtle.__init__(self)
        self.shape("circle")
        # self.resizemode("user")
        self.shapesize(0.5,0.5,1)
        self.pensize(5)
        # self.speed(0)
        self.i = z
        self.pu()
        self.x = int(x)
        self.left(90)
        self.goto(10,y)
        
        self.write(10, align="Center",font=("Arial",15,"bold"))
        
        self.my_hash = []
        self.s = 0
        self.r = 200
        self.ondrag(self.shift)
        self.draw()
        # self.listen()
        
        
    def shift(self, x, y):
        # print ("called")
        self.my_hash.clear()
        self.setx(max(1,min(int(x),200)))
        self.x = max(1,min(int(x),200))
        self.onrelease(self.update_val)
        
    def update_val(self, x, y):
        global n, a, t
        self.my_hash.clear()
        self.clear()
        t.clear()
        self.write(int(self.x), align="Center",font=("Arial",15,"bold"))
        if self.i == 0 :
            n = int(self.x)
        else:
            a = int(self.x)
        self.draw()
   
    def generator(self, m : int) -> list:
        global n,a, t
        m = int(m)
        nls = [m]
        self.my_hash[m] = 1
        while True :
            m *= a
            m %= n
          
            if self.my_hash[m] == 1:
                nls.append(m)
                break
            nls.append(m)
            self.my_hash[m] = 1
        # print(nls, len(nls))
        self.s += len(nls)
        return nls
    
    def draw(self):
        global n,a, t, gameVar
        self.my_hash.clear()
        self.my_hash = [0 for i in range(n)]
        self.s =0
      
        t.speed(0)
        t.penup()
        t.goto(0,self.r)
        t.pendown()
        phase = 2*math.pi/n
        angle = math.pi/2
   
        lst = []
        lst.append(self.generator(int(1)))
        for i in range(2, n):  
            if (self.my_hash[i] == 0):
                lst.append(self.generator(i))
        self.s = 0
        for i in range(n):
            if self.my_hash[i] == 0:
                self.s+= 1
        
        print(n,a,lst)
        prevx = -1
        prevy = -1
        for i in lst:
            
            t.penup()
            if gameVar == 1:
                t.pencolor(random.randint(0,255),random.randint(0,255),random.randint(0,255))
            for j in i:  
                x = self.r * math.cos(angle - (j*phase))
                y = 100 +self.r * math.sin(angle - (j*phase))
                if gameVar == 2:
                    dist = (((prevx - x)**2) + ((prevy - y)**2))** 0.5
                    t.pencolor(int(dist%255), int((500 - dist)%255), int((400 - dist)%255))
                prevx = x
                prevy = y
                t.goto(x,y)
                t.pendown()          
        t.hideturtle()

class Button():
    def __init__(self, x, y, label):
        self.pen = Turtle()
        self.pen.speed(0)
        self.pen.hideturtle()
        self.pen.pu()
        self.pen.goto(x,y)
        self.pen.pd()
        self.pen.pensize(2)
        self.pen.circle(10)
        self.pen.color("Black")
        self.pen.pu()
        self.pen.goto(x, y+10.5)
        
        self.pen.showturtle()
        self.pen.shape("circle")
        self.pen.shapesize(0.5,0.5,1)
        
        self.w = Turtle()
        self.w.hideturtle()
        self.w.penup()
        self.w.goto(x+14, y+4)
        self.w.write(label, font=("Arial",12,"bold") )
        
    
class ToggleButton():
    def __init__(self):
        
        self.loopCbtn = Button(-150, -300, "Color Loop")
        self.lenCbtn = Button(60, -300, "Color Lines")
        
        self.loopCbtn.pen.onclick(self.btnClick1)
        self.lenCbtn.pen.onclick(self.btnClick2)
    
    def btnClick1(self,x,y):
        global gameVar
        if gameVar == 1:
            self.loopCbtn.pen.color("Black")
            gameVar = 0
        else :
            self.loopCbtn.pen.color("Red")
            self.lenCbtn.pen.color("Black")
            gameVar = 1
    def btnClick2(self,x,y):
        global gameVar
        if gameVar == 2:
            self.lenCbtn.pen.color("Black")
            gameVar = 0
        else :
            self.lenCbtn.pen.color("Red")
            self.loopCbtn.pen.color("Black")
            gameVar = 2

class Game():
    
    def __init__(self):
        self.modulus = Slider(200, -200, 0)
        self.multiplier = Slider(200, -240, 1)
        self.tg = ToggleButton()
 
        self.writer = Turtle()
        self.writer.speed(0)
        self.writer.pu()
        self.writer.pensize(2)
        self.writer.goto(0,-100)
        self.writer.pd()
        self.writer.circle(200)
        
        
        self.writer.pu()
        self.writer.pensize(5)
        self.writer.goto(0,-200)
        self.writer.pd()
        self.writer.setx(200)
        self.writer.pu()
        
        self.writer.pu()
        self.writer.goto(0,-240)
        self.writer.pd()
        self.writer.setx(200)
        self.writer.pu()
        
        
        
        self.writer.ht()
        self.writer.pu()
        self.writer.goto(-150,-207)
        self.writer.write("Modulus  : ",align="Left",font=("Arial",15,"bold"))
        
        self.writer.pensize(1.5)
        self.writer.goto(-150,-247)
        self.writer.write("Multiplier : ",align="Left",font=("Arial",15,"bold"))
        self.writer.pu()
        self.writer.goto(-500, -150)
        self.writer.pd()
        self.writer.goto(500, -150)
        
        self.writer.pu()
        self.writer.goto(-500, -155)
        self.writer.pd()
        self.writer.goto(500, -155)
        self.writer.hideturtle()

def main():
    global screen, red, green, blue
    screen = Screen()
    screen.delay(0)
    screen.colormode(255)
    screen.title("Modular Times Table")
    # screen.tracer(0)
    game = Game()    
    return "EVENTLOOP"

if __name__ == "__main__":
    msg = main()
    print(msg)
    mainloop()
