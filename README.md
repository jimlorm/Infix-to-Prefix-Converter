              INFIX TO PREFIX CONVERTER AND EVALUATOR
======================================================================

A C application that tokenizes mathematical infix expressions, 
validates them for anomalies or mismatched parentheses, converts them 
into prefix expressions, and evaluates the final result.

----------------------------------------------------------------------
1. PREREQUISITES
----------------------------------------------------------------------
Ensure you have a GCC compiler installed on your system that supports 
the C99 standard.

----------------------------------------------------------------------
2. HOW TO COMPILE AND RUN
----------------------------------------------------------------------
Open your Command Prompt (or terminal), navigate to the folder 
containing your source files, and run the following exact commands:

[STEP 1: COMPILATION]
Type or paste this command to compile the main.c file.

gcc -Wall -std=c99 main.c -o my_program


[STEP 2: RUNNING THE APPLICATION]
Once compilation finishes with no errors, execute the generated binary:

* On Windows:
  my_program

* On Linux / macOS:
  ./my_program

----------------------------------------------------------------------
3. PROGRAM FEATURES
----------------------------------------------------------------------
When you run the application, you can choose from these options:
1. Convert and Evaluate an Expression: Input custom infix expressions 
   (e.g., ((10 + 20) * (30 + 40)) / 50) to view their prefix conversion 
   and see the final evaluated mathematical result.
2. Execution Time Analysis: Runs an internal automated benchmark 
   measuring processing speed.
3. Exit: Safely exits the program console.

----------------------------------------------------------------------
4. PROJECT STRUCTURE
----------------------------------------------------------------------
* main.c       - Main terminal user interface menu driver loop.
* tokenizer.h  - Contains string tokenization and expression verification.
* conversion.h - Implements stack/queue-driven infix-to-prefix translation.
* evaluation.h - Evaluates the translated prefix arithmetic tokens.
* queue.h      - Linked-list implementation for queue tracking.
* stacks.h     - Linked-list implementation for stack tracking.
* token.h      - Token configurations and ErrorStatus statuses.
