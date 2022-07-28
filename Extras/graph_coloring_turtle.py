#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Mar 12 20:46:32 2022

@author: pujawadare
"""

from turtle import Screen, Turtle, mainloop
import turtle
import math


"""
Avnish's idea ::
My plan : 
    1. make a circle
    2. then plot n points on it
    3. after that connect the points to make a complete graph (n*(n-1))/2
    4. then coloring algorithm
         i. first vertex coloring 
        ii. region coloring

"""

"""
Hamiltonian path finding algorithm
"""
"""
this will be terminal : 
    so beautiful print function
SUDOKU : generator
    place a number at random spot and see if the sudoku can be solved



SUDOKU : solver
    put a number and check if this is right or wrong


"""

n = int(input("Enter number of Nodes : "))
connections = [[] for i in range(n)] 
m = int(input("Number of Edges : "))
for i in range(m):
    j, k = list(map(int,input().split()))

    connections[j].append(k)
    connections[k].append(j)
    
r = 300
t = Turtle()
t.hideturtle()
t.speed(0)
# t.pu()
# t.goto(0,-r)
# t.pd()
# t.circle(r)

# points = [i for i in range(n)]

# graph coloring : uisng bfs
color = [0 for i in range(n)]
visited = [0 for i in range(n)]
queue = []
queue.append(0)
visited[0] = 1


while len(queue) != 0:
    a = queue.pop(0)
    
    for i in connections[a]:
        if color[i] == color[a]:
            color[i]+= 1
        if visited[i] == 0:
            queue.append(i)
            visited[i] = 1
print(color)
c = ["pink","red","olive","blue","green","orange","brown","magenta"]
for i in range(n):
    t.pu()
    x = math.cos(2*i*math.pi/n)*r
    y = math.sin(2*i*math.pi/n)*r
    t.goto(x,y-20)
    t.fillcolor(c[color[i]])
    t.begin_fill()
    t.pd()
    t.circle(20)
    t.pu()
    t.end_fill()
    t.goto(x-4,y-8)
    t.write(i, font=("Verdana",15, "normal"))
    


print(connections)
# draw connections
for i in range(n):
    for j in connections[i]:
        x1 = math.cos(2*i*math.pi/n)*r
        y1 = math.sin(2*i*math.pi/n)*r
        
        x2 = math.cos(2*j*math.pi/n)*r
        y2 = math.sin(2*j*math.pi/n)*r
        
        t.pu()
        t.goto(x1,y1)
        t.pd()
        t.goto(x2,y2)
        t.pu()
        

turtle.mainloop()
    
    
    
    
    
    
    
    
    
    
    
    
    
    