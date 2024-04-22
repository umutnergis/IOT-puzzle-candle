# IOT-puzzle-candle

# Puzzle Game with Arduino

This is an Arduino code for a puzzle game that involves buttons and lights. The game starts when a puzzle game is completed, and the player needs to press the buttons in a specific order to win the game.

## Hardware Setup

The following components are used in this code:

- 6 buttons connected to analog pins A0-A5
- 6 lights connected to digital pins 2-7
- 3 output pins for controlling a clock game (pin 9), a fireplace (pin 10), and a relay (pin 11)
- 1 input pin for detecting a puzzle game completion (pin 8)
- 1 output pin for controlling buttons (pin 12)

## Game Flow

1. The game starts when the puzzle game is completed (detected by the input pin 8).
2. All lights turn on, and the relay is activated briefly.
3. The player needs to press the buttons in the correct order (3, 1, 4, 6, 2, 5) to turn off the lights.
4. If the correct order is entered, the clock game is activated (pin 9 goes high for 3 seconds), and the fireplace is turned on (pin 10 goes high).
5. The game waits for the puzzle game to be completed again (input pin 8 goes low).
6. After the puzzle game is completed, the game resets, and all lights turn on again.

## Debugging

The code includes a `DEBUG` macro that can be used to enable debug messages in the Serial Monitor.

## Functions

The code includes the following functions:

- `setup()`: Initializes the Arduino board and sets the pin modes.
- `loop()`: The main loop that checks for the puzzle game completion, starts the game, reads the buttons, and checks the order.
- `reset_game()`: Resets the game by turning on all lights and resetting the button voltages and light states.
- `deactive_game()`: Deactivates the game by turning off all lights and resetting the button voltages and light states.
- `light_sit()`: Turns on all lights with a delay between each light.
- `read_buttons()`: Reads the analog values of the buttons and stores them in variables.
- `write_buttons_to_serial()`: Prints the button voltages to the Serial Monitor.
- `addValue(int value)`: Adds a button value to the order array.
- `checkOrder()`: Checks if the order array matches the correct order.

## Usage

1. Connect the required hardware components as specified.
2. Upload the code to the Arduino board.
3. Open the Serial Monitor to view the debug messages (if `DEBUG` is enabled).
4. Complete the puzzle game to start the button game.
5. Press the buttons in the correct order (3, 1, 4, 6, 2, 5) to turn off the lights and win the game.
6. Repeat the puzzle game to reset and play again.

Note: Make sure to adjust the pin numbers and other constants if your hardware setup is different.
