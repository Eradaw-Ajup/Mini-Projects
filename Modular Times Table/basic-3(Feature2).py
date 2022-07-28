#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Feb 22 09:46:59 2022

@author: pujawadare
"""
# Colouring on the basis of length

import turtle
import math
import random


n = int(input("Enter the value of modulus : "))
my_hash = [0 for i in range(n)]
s =0
a = int(input("Enter the value of multiplier : "))
r = 200
def generator(m : int) -> list:
    global n, my_hash, s, a
    nls = [m]
    my_hash[m] = 1
    while True :
        m *= a
        m %= n
      
        if my_hash[m] == 1:
            nls.append(m)
            break
        nls.append(m)
        my_hash[m] = 1
    # print(nls, len(nls))
    s += len(nls)
    return nls

    t.penup()
    
screen = turtle.getscreen()
screen.clear()
t = turtle.Turtle()
screen.colormode(255)
t.speed(0)
t.penup()
t.right(90)
t.forward(r)
t.left(90)
t.pendown()
t.circle(r)

# t.color(' black')
style = ('Arial', 10)


t.penup()
t.goto(0,r)
t.pendown()
phase = 2*math.pi/n
angle = math.pi/2
# for i in range(1,n+1):
#     t.penup()
#     x = r * math.cos(angle - phase) 
#     y = r * math.sin(angle - phase)
#     t.goto(x,y)
#     angle -= phase;
#     t.pendown()
#     t.write(i, font=style, align='right')
  
# t.fd(100)import turtle
lst = []
lst.append(generator(1))
for i in range(2, n):  
    if (my_hash[i] == 0):
        lst.append(generator(i))
        
        
# print(lst, s)
s = 0
for i in range(n):
    if my_hash[i] == 0:
        s+= 1
# print(s)


prevx = -1
prevy = -1
for i in lst:
    t.penup()
    # t.pencolor(random.randint(0,255),random.randint(0,255),random.randint(0,255))
    prevx = r * math.cos((math.pi/2) - (i[0]*phase))
    prevy = r * math.sin((math.pi/2) - (i[0]*phase))
    t.goto(prevx,prevy)
    t.pendown()

    for j in range(1,len(i)):  
        # t.left(((math.pi/2) - (j*phase))*180/math.pi)
        # t.goto(r * math.cos((math.pi/2) - (j*phase)),r * math.sin((math.pi/2) - (j*phase)))
        x = r * math.cos((math.pi/2) - (i[j]*phase))
        y = r * math.sin((math.pi/2) - (i[j]*phase))
        dist = (((prevx - x)**2) + ((prevy - y)**2))** 0.5
        if prevx - x == 0:
            if (prevy - y > 0):
                theta = 270
            else:
                theta = 90
        else:
            slope = (prevy-y)/(prevx-x)
            theta = math.degrees(math.atan(slope))
            if (prevx > x and prevy > y):
                theta = 180 + theta
            if (prevx > x and prevy < y):
                theta += 180
        t.pencolor(int(dist%255), int((500 - dist)%255), int((400 - dist)%255))
        t.setheading(theta)
        t.forward(dist)
        # t.stamp()
       
        prevx = x
        prevy = y
        # t.stamp()

  
t.hideturtle()
screen.exitonclick()
turtle.done()



# import turtle 

# ninja = turtle.Turtle()

# ninja.speed(10)

# for i in range(180):
#     ninja.forward(100)
#     ninja.right(30)
#     ninja.forward(20)
#     ninja.left(60)
#     ninja.forward(50)
#     ninja.right(30)
    
#     ninja.penup()
#     ninja.setposition(0, 0)
#     ninja.pendown()
    
#     ninja.right(2)
    
# turtle.done()
