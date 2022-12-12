# All the Chess Clock In a Single Source File

The main goal of this steps to

* understand how the program is meant to be used and
* get an overview of the program structure

## Running the Program

1. Start a *Terminal* with Step-0 as *Working Directory* and
   enter the command `make` to *Compile* and *Run* the code.
   A small menu is then displayed explaining the possible inputs.

1. Set the player clocks to their default start time with the
   `r`-command.

   Opionally that command may be followed by a different start
   time specified as minutes and seconds, separated by a colon.
   This time then becomes the default start time (until changed
   again with another `r` -command).

1. Start the clock with the `s`-command.

   A visually count down of the time remaining for WHITE will
   be displayed until you hitting the <Return>, which switches
   between the players.

1. Once a player's time is exhausted the other player wins and
   the program prints an according message and the time that
   remains on the winning player's clock.

   In case you have started the program with the default of 15
   minutes per player and this is a bit too long to wait and
   watch you may also hit *Crtl-C* to abort program execution.

1. In case you want to have a different default start time you
   can also specify it as command line argument. The following
   sets a default start time of 10 seconds.

   (Maybe too short for a real game of chess but a nice way to
   have one or the other player "win with a number of player
   switches in between.)

```sh
./chessclock 0:10
```

You can also separate the countdowns and from the interactive
menu by setting the environment variable `CHESSCLOCK_AUX_TTY`
accordingly. Use the command `tty` in terminal window to show
the respective device name.

## Reviewing the Code

In the steps following later the code shown here will be improved
and restructured.

* The initial review is mainly about the high-level structure.
* Do **not** go deep down in every detail. Also some newer C++
  features will be introduced.

Here are some questions covered in the discussion following:

1. Which if the following "Modern C++" features can you spot:

   * Uniform initialization (aka. "brace initialization")?
   * Initializer lists?
   * Named and/or anonymous lambdas?
   * Automatic type deduction for variables and functions?
   * Multi-Threading?

   Depending on how much of C++ you already know the code may
   contain C++ features you have not yet seen. These will be
   explained  in the discussion following the review.

   **During the discussion your are welcome to ask any questions
   you may have about that code.**

1. Which classic C constructs do you identify?

1. How make the individual functions in the code use of global
   variables ...

    * ... to only access their current value?
    * ... to access and modify their value?

4. Based on the results of the previous steps and guided by the
   names of `struct`-s, functions, and global data:

    * Assume you have to split the program into separate header
      (`*.h) and implementation (`*.cpp`) files.
    * How would you place the parts into individual compilation
      units?
      * a main program
      * the "business logic" of the "Chess Clock Application"
      * commend line menu related functionality
      * the player(s)
      * their (common) "player clock"
      * the "clockwork" causing the BLACK or WHITE player's clock
        to "tick"
      * common subroutines

   **You should not DO that work now yourself!** It is quite a bit
   time consuming and has already been done in Step-01.

   (Feel free to compare that step to your own ideas.)
