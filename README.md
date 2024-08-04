# Set Calculator (C Language)

This C program serves as a calculator for performing operations on sets of integer numbers within the range [0,127]. Users can manipulate six sets labeled as SETA through SETF. The operations supported by the calculator are:x

### Operations:

1. **Print Set**: `print_set SETN`
   - Prints the contents of SETN. If the set is empty, it will indicate so.

2. **Read Set**: `read_set SETN, a1, a2, ..., an, -1`
   - Stores the values of a1 through an in SETN. The series of integer numbers (a1, a2, ..., an) must be within the range [0,127]. Use -1 to terminate input.

3. **Union Set**: `union_set SETN1, SETN2, SETN3`
   - Combines the values of SETN2 and SETN3 and stores them in SETN1. The same set can be used more than once.

4. **Intersect Set**: `intersect_set SETN1, SETN2, SETN3`
   - Retrieves the shared values of SETN2 and SETN3 and stores them in SETN1.

5. **Subset**: `sub_set SETN1, SETN2, SETN3`
   - Stores the values exclusive to SETN2 in SETN1.

6. **Symmetric Difference**: `symdiff_set SETN1, SETN2, SETN3`
   - Stores the values exclusive to SETN2 or SETN3, which are not present in both, in SETN1.

### Usage Example:


read_set SETA, 1, 2, 3, 4, 5, -1

read_set SETB, 4, 5, 6, 7, 8, -1

union_set SETC, SETA, SETB

print_set SETC

stop

