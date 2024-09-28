/**
 * $ Pomodoro timer in C
//  * Bek Brace [Amir] project for September in C.
# Writing a program that counts intervals of 25 min by default with quick breaks - technique called Pomodoro

#----------------------------------------------------------
# Now, you know the GUI, right ? Graphical User Interface ?
#----------------------------------------------------------

You also know the CLI, Command Line Interface.
I don't think I have created any Terminal User Interface on my channel, so today I'm gonna show you that ,and of course we are coding this beauty in C language.

I know you guys have missed FastAPI, Django, React, etc.. but believe me learning programming in my humble opinion is much more important than gettin caught up in learning a certain framework.

The Pomodoro Timer program is a simple terminal-based application that implements the Pomodoro Technique, a time management method that encourages people to work in intervals, typically 25 minutes in length, separated by short breaks. This application allows users to set custom work and break intervals, start a timer for each interval, and get notified when the time is up.

- Why It’s Useful for C Beginner Programmers:

# Basic to Intermediate Concepts:
Standard Libraries: This program uses stdlib.h and unistd.h for basic operations, demonstrating how to include and use standard C libraries.
ncurses Library: By using ncurses, it introduces beginners to a powerful library for creating text-based user interfaces, which is useful for learning how to handle user input and output in a terminal.

# Structured Programming:
The code is organized into functions, each responsible for a specific part of the program. This teaches beginners the importance of modularity and clean code practices.
User Interaction:

The program demonstrates how to interact with users by capturing their input and responding with appropriate actions. This is essential for understanding user-driven programs.

# Color and Visual Formatting:
Learning to use colors and formatting in the terminal enhances the visual appeal and usability of text-based applications, providing a more engaging user experience.

# Loops and Conditionals:
The program makes extensive use of loops and conditional statements, reinforcing these fundamental programming concepts.

# Time Management Functions:
Using functions like sleep teaches beginners how to handle time-based operations in their programs.
What You Can Learn from This Program:

# Setting Up and Using ncurses:
Initializing ncurses, setting up the screen, handling special keys, and using colors.
Functions like initscr, endwin, cbreak, noecho, keypad, and start_color.

# Creating a Simple User Interface:
Drawing menus, capturing user input, and creating a visually appealing interface with boxes and colors.

# Implementing a Timer:
Creating a countdown timer, updating the display in 
real-time, and managing time-based events.

# Handling User Input:
Using getch to capture user input and implementing a menu system to navigate different options.

# Modular Programming:
Structuring the code into different functions, making it easier to understand, maintain, and extend.

# Basic Program Flow Control:
Using loops for continuous program execution and conditionals to handle different user choices.
 */



#include <ncurses.h> // Include ncurses library for terminal UI
#include <stdlib.h> // Include standard library for general purposes
#include <unistd.h> // Include POSIX operating system API for sleep function

// Function declarations
void init(); // Initialize ncurses and settings
void close_app(); // Close ncurses and cleanup
void main_menu(); // Display the main menu
void set_timer(int *minutes, const char *prompt); // Set the timer duration
void start_timer(int minutes, const char *message); // Start the countdown timer
void draw_menu(int work_minutes, int break_minutes); // Draw the main menu layout
void draw_box(int y, int x, int height, int width); // Draw a box around menu items

int main() {
    init(); // Initialize ncurses
    main_menu(); // Display the main menu
    close_app(); // Close ncurses
    return 0; // Exit the program
}

// Initialize ncurses
void init() {
    initscr(); // Initialize the screen
    start_color(); // Enable color functionality
    cbreak(); // Disable line buffering
    noecho(); // Disable echoing of typed characters
    keypad(stdscr, TRUE); // Enable special keys to be captured
    curs_set(0); // Hide the cursor

    // Initialize color pairs
    init_pair(1, COLOR_WHITE, COLOR_BLUE); // Color pair 1: white text on blue background
    init_pair(2, COLOR_YELLOW, COLOR_BLACK); // Color pair 2: yellow text on black background
    init_pair(3, COLOR_GREEN, COLOR_BLACK); // Color pair 3: green text on black background
    init_pair(4, COLOR_RED, COLOR_BLACK); // Color pair 4: red text on black background
}

// Close ncurses
void close_app() {
    endwin(); // End ncurses mode
}

// Display the main menu
void main_menu() {
    int work_minutes = 25; // Default work interval in minutes
    int break_minutes = 5; // Default break interval in minutes
    int choice; // Variable to store user choice
    
    while (1) { // Infinite loop to display the menu until exit
        clear(); // Clear the screen
        draw_menu(work_minutes, break_minutes); // Draw the menu with current intervals
        refresh(); // Refresh the screen to show changes
        
        choice = getch(); // Get user input
        switch (choice) { // Handle user input
            case '1': // If '1' is pressed
                set_timer(&work_minutes, "Enter work interval (minutes): "); // Set work interval
                break;
            case '2': // If '2' is pressed
                set_timer(&break_minutes, "Enter break interval (minutes): "); // Set break interval
                break;
            case '3': // If '3' is pressed
                start_timer(work_minutes, "Work period ended! Take a break."); // Start work timer
                break;
            case '4': // If '4' is pressed
                start_timer(break_minutes, "Break period ended! Get back to work."); // Start break timer
                break;
            case '5': // If '5' is pressed
                return; // Exit the menu
            default: // If any other key is pressed
                attron(COLOR_PAIR(4)); // Turn on color pair 4 (red text)
                mvprintw(LINES - 2, (COLS - 30) / 2, "Invalid choice. Press any key to try again."); // Display error message
                attroff(COLOR_PAIR(4)); // Turn off color pair 4
                getch(); // Wait for user to press a key
        }
    }
}

// Draw the menu
void draw_menu(int work_minutes, int break_minutes) {
    int mid_col = COLS / 2; // Calculate middle column for centering text
    attron(COLOR_PAIR(1)); // Turn on color pair 1 (white text on blue background)
    mvprintw(1, mid_col - 10, "Pomodoro Timer"); // Print title centered
    attroff(COLOR_PAIR(1)); // Turn off color pair 1
    draw_box(2, mid_col - 30, 10, 60); // Draw a box around the menu
    mvprintw(4, mid_col - 20, "1. Set Work Interval (current: %d minutes)", work_minutes); // Print menu option 1
    mvprintw(5, mid_col - 20, "2. Set Break Interval (current: %d minutes)", break_minutes); // Print menu option 2
    mvprintw(6, mid_col - 20, "3. Start Work Timer"); // Print menu option 3
    mvprintw(7, mid_col - 20, "4. Start Break Timer"); // Print menu option 4
    mvprintw(8, mid_col - 20, "5. Exit"); // Print menu option 5
}

// Draw a box around menu items
void draw_box(int y, int x, int height, int width) {
    attron(COLOR_PAIR(2)); // Turn on color pair 2 (yellow text)
    for (int i = 0; i < width; i++) { // Draw top and bottom borders
        mvprintw(y, x + i, "-"); // Draw top border
        mvprintw(y + height, x + i, "-"); // Draw bottom border
    }
    for (int i = 0; i < height; i++) { // Draw left and right borders
        mvprintw(y + i, x, "|"); // Draw left border
        mvprintw(y + i, x + width, "|"); // Draw right border
    }
    mvprintw(y, x, "+"); // Draw top-left corner
    mvprintw(y, x + width, "+"); // Draw top-right corner
    mvprintw(y + height, x, "+"); // Draw bottom-left corner
    mvprintw(y + height, x + width, "+"); // Draw bottom-right corner
    attroff(COLOR_PAIR(2)); // Turn off color pair 2
}

// Set the timer interval
void set_timer(int *minutes, const char *prompt) {
    char input[4]; // Buffer to store user input
    echo(); // Enable echoing of typed characters
    curs_set(1); // Show the cursor
    attron(COLOR_PAIR(3)); // Turn on color pair 3 (green text)
    mvprintw(LINES - 3, (COLS - strlen(prompt)) / 2, "%s", prompt); // Print prompt centered
    getstr(input); // Get user input
    *minutes = atoi(input); // Convert input to integer and set the timer
    noecho(); // Disable echoing of typed characters
    curs_set(0); // Hide the cursor
    attroff(COLOR_PAIR(3)); // Turn off color pair 3
}

// Start the timer
void start_timer(int minutes, const char *message) {
    clear(); // Clear the screen
    int total_seconds = minutes * 60; // Calculate total seconds from minutes
    while (total_seconds > 0) { // Loop until the timer ends
        int mins = total_seconds / 60; // Calculate remaining minutes
        int secs = total_seconds % 60; // Calculate remaining seconds
        attron(COLOR_PAIR(1)); // Turn on color pair 1 (white text on blue background)
        mvprintw(LINES / 2, (COLS - 20) / 2, "Time remaining: %02d:%02d", mins, secs); // Print remaining time centered
        attroff(COLOR_PAIR(1)); // Turn off color pair 1
        refresh(); // Refresh the screen to show changes
        sleep(1); // Wait for one second
        total_seconds--; // Decrement total seconds
    }
    attron(COLOR_PAIR(3)); // Turn on color pair 3 (green text)
    mvprintw(LINES / 2 + 1, (COLS - strlen(message)) / 2, "%s", message); // Print end message centered
    mvprintw(LINES / 2 + 2, (COLS - 30) / 2, "Press any key to return to the main menu."); // Print prompt to return to menu
    attroff(COLOR_PAIR(3)); // Turn off color pair 3
    getch(); // Wait for user to press a key
}
