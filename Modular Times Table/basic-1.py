#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Feb 21 19:37:13 2022

@author: pujawadare
"""
# Simple program


import turtle
import math



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
turtle.clear()

t = turtle.Turtle()
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
for i in range(1,n+1):
    t.penup()
    x = r * math.cos(angle - phase) 
    y = r * math.sin(angle - phase)
    t.goto(x,y)
    angle -= phase;
    t.pendown()
    # t.write(i, font=style, align='right')
  
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

for i in lst:
    t.penup()
    for j in i:  
        t.goto(r * math.cos((math.pi/2) - (j*phase)),r * math.sin((math.pi/2) - (j*phase)))
        # t.dot
        t.pendown()
  
t.hideturtle()
screen.exitonclick()
turtle.done()
