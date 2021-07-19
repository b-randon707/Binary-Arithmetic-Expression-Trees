### Binary-Arithmetic-Expression-Trees
Design and implement expression trees, which are special cases of parse trees or grammar trees.

Program does the following:

- Reads arithmetic expressions from a text file.
- Takes binary arithmetic expression as input and builds a binary expression tree for that expression.
- Implements two stack-type data structures. 
- Checks whether there are any syntactic or semantic errors in the expression. If yes, it reports the errors.
  - Table blow lists operation precedence and association orders:
  
| Operator | Precedence (Priority) | Association Order |
| :---: | :---: | :---: |
| ( ) | 0 (highest precedence) | left to right |
| * / | 1 | left to right |
| + - | 2 | left to right |

- If there are no errors in the input expression,  then 
    - Calculates and displays the value of the input expression.
    - Prints the infix (in-order traversal), prefix (pre-order traversal) and postfix (post-order traversal) expressions of the input expression.
      
- Uses the following input arithmetic expressions to test the program:
    - with no errors: (10.24 + 5.4 * 2.5) / 6.7 + (12.5 * 20.67 + 10) * 25
    - with 1 error: (10.24 + 5.4 * 2.5) / 6.7 + (12.5 * 20.67 + 10) * 25)
    - with 1 error: (10.24 + 5.4 * 2.5) / 6.7 + (12.5 * 20.67 + ) * 25
