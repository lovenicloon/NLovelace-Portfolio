# Programmer: Nicolas Lovelace
# Program: 4
# Date: 07/22/22
# Description: Single Player Mastermind (bugged version)

from tkinter import *
import random
root = Tk()
root.geometry("250x600")
root.title("Mastermind")

class Game: # i created this class to get around the "global variable" problems i was having
    def __init__(self):
        self.colors = ["blue", "green", "yellow", "red", "black", "white"]
        self.row = 0
        self.key = ["one", "two", "three", "four"]
        self.guess = ["empty", "empty", "empty", "empty"]
        self.blanks = []
        self.cycle = 0

game = Game()

# the b1-b4 are to identify within the buttonClick function which button is being pressed to indicate position
def b1():
    buttonClick(0)
def b2():
    buttonClick(1)
def b3():
    buttonClick(2)
def b4():
    buttonClick(3)
def buttonClick(button):
    #change current undecided button between the colors
    if game.cycle == 6: # there are 6 total colors that you might cycle through upon each click of the button
        game.cycle = 0
    col = game.colors[game.cycle] # get the color
    C.delete(game.blanks[button+4*game.row]) # delete the original button in the right position, then replace with new
    game.blanks[button+4*game.row] = C.create_oval(30 + button * 40, 398 - game.row * 35, 50 + button * 40, 417 - game.row * 35, fill=col)
    game.guess[button] = col
    game.cycle += 1 # after each click one color should be progressed

def confirmation(): # this function contains the main mechanics of the game
    truth = {"blue": False, "green": False, "yellow": False, "red": False, "black": False, "white": False}
    truthB = {"blue": False, "green": False, "yellow": False, "red": False, "black": False, "white": False}
    # i was unable to fully understand a mathematical way of testing for the white dots, so
    # the above dictionaries are for my convenience/laziness
    if game.row == 0: # game.row being 0 means the game has just started
        random.seed() # randomize
        for x in range(4):
            game.key[x] = game.colors[random.randint(0,5)] # create the random solution
            truth[game.key[x]] = True # mark the correct colors in the key as being present
    for f in range(4):
        if game.guess[f]=="empty": # checking to make sure player has entered a full row
            print("Finish guessing!")
            return
        truthB[game.guess[f]] = True # mark the correct colors in the player guess as being present

    # counters for the clue dots
    red = 0
    white = 0
    for h in range(4):
        if game.guess[h] == game.key[h]: # if the position and color are identical, 1 red is found
            red+=1
    z = 0
    for n in range(6): # if the colors are found to be shared in any position, 1 white is found for each color
        if truth[game.colors[n]] and truthB[game.colors[n]]:
            if(game.guess[z] == game.key[z] and z<4):
                z+=1
                continue
            white+=1# that is not included per the rules of the game
    if game.row +1== 10 or red==4: # if the player gets the right answer or reaches the end of the rows
        for a in range(4): # the solution is revealed
            game.blanks.append(C.create_oval(45 + a * 40, 40, 65 + a * 40, 59, fill=game.key[a]))

    for b in range(4): # reset the player guess array to keep the full row checker working
        game.guess[b] = "empty"
    buts = ["gray","gray","gray","gray"] # set the default color for the clue buttons in case some are unchanged
    print(red, white)
    for q in range(4):
        if red>0: # reds get priority and come first on the board
            buts[q] = "red"
            red-=1
        elif white>0: # once reds run out, whites can be placed
            buts[q] = "white"
            white-=1
    # change the colors of the clue dots, deleting the old dots and replacing their position in the blanks array
    C.delete(game.blanks[40 + 4 * game.row+0])
    game.blanks[40 + 4 * game.row+0] = C.create_oval(203, 396 - game.row * 35, 213, 406 - game.row * 35, fill=buts[0])
    C.delete(game.blanks[40 + 4 * game.row+1])
    game.blanks[40 + 4 * game.row+1] = C.create_oval(191, 396 - game.row * 35, 201, 406 - game.row * 35, fill=buts[1])
    C.delete(game.blanks[40 + 4 * game.row+2])
    game.blanks[40 + 4 * game.row+2] = C.create_oval(203, 408 - game.row * 35, 213, 418 - game.row * 35, fill=buts[2])
    C.delete(game.blanks[40 + 4 * game.row+3])
    game.blanks[40 + 4 * game.row+3] = C.create_oval(191, 408 - game.row * 35, 201, 418 - game.row * 35, fill=buts[3])
    game.row += 1 # move the game a row forward!



    ### GUI STUFF ###
### TITLE FRAME ###
title = Frame(root)
title.pack()
B = Canvas(title, bg = "black", height = 25, width = 230)
B.pack(pady = 5)
name = Label(title, text = "MASTERMIND", font = ("Times New Roman", 16))
name.pack()

### DISPLAY FRAME ###
display = Frame(root)
display.pack(pady = 5)

C = Canvas(display, bg = "black", height = 430, width = 230)
C.pack()
for i in range(10): # creating the background block rows
    C.create_polygon(20, 395-i*35, 215, 395-i*35, 215, 420-i*35, 20, 420-i*35, fill="dark gray")
C.create_polygon(180,0,190,0,190,430,180,430, fill = "black") # separating stripe for the rows and boxes on the side
C.create_polygon(40,30, 190,30, 190,70, 40,70, fill = "gray") # top bar where solution is "hidden"

for i in range(10):
    for j in range(4): # these are the main 4 placeholder dots for each row
        game.blanks.append(C.create_oval(30+j*40, 398-i*35, 50+j*40, 417-i*35, fill="gray"))

for i in range(10): # these are all the clue dots
    game.blanks.append(C.create_oval(203, 396-i*35, 213, 406-i*35, fill="gray"))
    game.blanks.append(C.create_oval(191, 396-i*35, 201, 406-i*35, fill="gray"))
    game.blanks.append(C.create_oval(203, 408-i*35, 213, 418-i*35, fill="gray"))
    game.blanks.append(C.create_oval(191, 408-i*35, 201, 418-i*35, fill="gray"))

### MENU FRAME ###
menu = Frame(root)
menu.pack()

button1 = Button(menu, text = "1", padx = 6, command = b1)
button1.pack(side = LEFT)
button2 = Button(menu, text = "2", padx = 6, command = b2)
button2.pack(side = LEFT)
button3 = Button(menu, text = "3", padx = 6, command = b3)
button3.pack(side = LEFT)
button4 = Button(menu, text = "4", padx = 6, command = b4)
button4.pack(side = RIGHT)

confirm = Button(root, text = "Confirm", padx = 10, font = ("Helvetica", 8, "bold"), command = confirmation)
confirm.pack()

quit = Button(root, text = "Quit", padx = 5, command = root.destroy)
quit.pack(side = LEFT, padx = 10)

root.mainloop()
