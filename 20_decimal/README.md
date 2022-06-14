## Multiplication
- The length of the second operand must be less than or equal to 8, and
- The first operand must have as many bytes of high-order zeroes as there are bytes (all bytes)
in the second operand.


## Issues


### S0C6 – Specification Exception (Multiplication)
An address doesn’t specify the boundary required.
- The multiplier or divisor in a decimal (packed) arithmetic instruction exceeds 15 digits and sign.
- The first operand field is shorter than or equal to the second operand field in a decimal (packed) multiplication or division instruction.

### S0C7 – Data Exception
Data was incorrect format for the instruction that attempting to process it. The ABEND can occur when packed decimal instruction are used.
- The decimal multiplicand has too many high-order significant digits
- Data fields was not initialized, blanks were read into a field designed to be processed with packed decimal instruction.