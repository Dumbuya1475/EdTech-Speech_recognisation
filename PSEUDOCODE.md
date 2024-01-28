# Pseudocode:

## Greet the user

### *If the user says "teach me":*

* Display the list of things the AI can teach.
* If the user chooses an option (e.g., option 2 for reading months):
* Print a prompt to repeat after the AI.
* Enter a loop where the AI spells a month and pronounces it.
* Wait for the user to spell the month.
* If correct, move to the next month; otherwise, repeat the loop.
* If all 12 months are successfully read, print a message and ask if the user wants to try again.
* If the user chooses a different option, repeat the main loop.

### *If the user says "test" or "exam":*

* Print a message about calling out the month and asking the user to spell it.
* Enter a loop for each option in the list (e.g., reading and spelling months).
* For each month, wait for the user to spell it, and provide feedback.
* If the user spells each month correctly, print "correct"; otherwise, ask them to try again.
