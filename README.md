# Dot Jump Nicole Boie
# CS/EE 120B Custom Laboratory Project Report
June 9 2022

# Introduction
Dot Jump is a game where the user uses buttons to make a dot jump and avoid on coming objects. The more times a user avoids an object the higher the level goes. As the levels increase so does the speed of the on coming objects. The player loses when their dot collides with the on coming object. To win the player must survive all ten levels and then an additional ten seconds. Different sounds will play at the start, jump, win and lose. At the end of play, win or lose, the player will get to see their score, which is the number of levels passed.

# Demo Videos
https://youtu.be/H_95Dfrq58I 
https://youtu.be/-CdgDrg8a38
https://youtu.be/RM6ZrBSmg5A

# Changes
In the original plan for the game, there was going to be increased objects per level. However the increased speed made the game difficult enough to win. With the increasing of the objects the game would lose before much of an increase to speed, and rarely (if ever) be able to win the game.

The fan complexity is still used, however it is either on during play or off during out of play. The analogWrite to the speedPin interrupts the functionality of the whole game. This is most likely due to analogWrite using PWM which may interrupt the loop. 
(I ended up breaking a metal connector off the fan as I kept trying to change it’s functionality, so in some of the separate videos to show basic functionality the fan is not shown for that reason.) 

# Complexities (all complexities were implemented)
Planned Complexities
1. Nokia 5110 LCD: Where the game takes place

2 and 3. Fan Blade and Motor: Fan is either on (1 speed) or off instead of off and on with increasing speeds

# Additional Complexities (These were added as they were needed to make the other complexities work)
4. Power Supply Module: To power the motor
5. L293D: Control motor

# User Guide
Inputs buttons: start (middle), jump (right), reset (left)

Outputs on LCD: Start Screen, In Game, Win Screen, Lose Screen

Output on Buzzer: Start Song, Jump Note, Win Song, Lose Song

Output on motor/fan: ON (increases in speed in game), OFF (out of game)

# Instructions and Scenarios:

When the game is run the LCD lights up with a start screen (“DOT.JUMP”) int the center.

To start the game the user must press the start button (middle button).

A start song will play and the game will start after the song ends.

The user’s dot is in the middle of the screen.

An object (another dot) will approach the user’s dot from left to right.

The user must press the jump button (left button) at the right time to avoid the incoming object.

A jump sound will occur whenever the user presses the jump button.

If the dots collide the LCD will light up with the loser screen and the score (level they lost on) and a lose song will play once.

To reset and play the game again the user must press the (right button).

If the user avoids the object in play, the object will continue moving past the dot.

A new object will arrive after the preceding dot exits with an increased level, object speed, and fan speed.

If the user passes all ten levels and plays an additional ten seconds the LCD will light up with a win statement and the highscore (level), and a win song will play once.

The user can start the game again through the reset button.

# Hardware Components:

	UNO R3 Controller Board

	USB Cable

	Nokia 5110 LCD

	Fan blade and 3-6V motor

	Power Supply Module

	L293D

	Wires

	3 buttons

	Potentiometer


	Buzzer

	7 10k Ohm resistors

	1 1k Ohm resistor

	1 330 Ohm resistor

	1 100 Ohm resistor


# Software Libraries Used
PCD8544.h: This library is used so arduino can interact with the Nokia 5110 LCD. It’s used just as the library for the lcd given in class, just for this specific LCD. For example, lcd.setCursor(), lcd.print(), and delay() are all used the same as previously used LCD libraries

# Wiring Diagram		 	 	 		
	
![Screen Shot 2022-10-04 at 3 30 11 PM Small](https://user-images.githubusercontent.com/86252234/193943664-f6ba0920-94a4-47c2-b3d9-7efa4443f385.jpeg)

	 	 	 		
![Screen Shot 2022-10-04 at 3 40 01 PM Small](https://user-images.githubusercontent.com/86252234/193943803-92b7dd36-a6d8-40f6-8a6d-c1ba2140aec6.jpeg)
		 			
		
# Task Diagram

![Screen Shot 2022-10-04 at 3 40 44 PM Small](https://user-images.githubusercontent.com/86252234/193943903-e2b878fd-1a30-45c6-9ec4-ff9aed86980c.jpeg)

# Tasks
Game (Task 1), 25 ms: Where the game occurs

Physical Inputs: Start button, reset button

Non physical inputs: 

	 From Buzzer Task: bool StartG, pWsong, pLsong
	
	From Jump Task: bool here
	
	From itself: int counter, int lvl, int del, bool keepG, bool lose, and int k
	
	From reset Button: bool counter, int lvl, int speeder, int del, bool keepG, bool lose, int k
	
Physcial Outputs:

	Idle screen
	
	Win screen (uses int lvl)
	
	Lose screen (uses int lvl)
	
	In Game screen (uses k)
	
Outputs
	Buzzer Task: bool pSong, bool pWsong, bool pLsong
	
	Motor Task: through bool keepG, bool Lose, int Speeder
	
	Jump Task: bool here
	
	Jump (Task 2), 50 ms: Controlling the movement of the dot
	
	Physcial Inputs: Jump by pressing JUMP BUTTON
	
	Non Physical Inputs: bool here
	
Physical Output: 

	Jump Sound
	
	Jump on LCD
	
	Non Physical Ouput: bool here
	
	Buzzer (Task 3), 250 ms: Plays songs
	
Non physical input:

	From Game: bool pSong, bool pWsong, bool pLsong
	
	Non physical output: bool startG, bool pWSong, bool pLsong
	
	Physical Output: buzzer sounds
	
	Motor (Task 4), 250 ms: Control motor and Fan
	
Non physcial Inputs:

	From Game: bool KeepG, bool lose, int speeder
	
Physical Output: motor movement


# SyncSMs (4)

![Screen Shot 2022-10-04 at 3 41 48 PM Small](https://user-images.githubusercontent.com/86252234/193944127-a37f9e2c-5bc0-4dc0-bfbf-55fefd733a07.jpeg)



