# Test file for "Lab4_SMsDDL"


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

test "PINA: 0x01, 0x03, 0x07 => PORTB: 0x00, state: init"
set digit = start
setPINA 0x01
continue 2
setPINA 0x03
continue 2
setPINA 0x07
continue 2
expectPORTB 0x00
expect digit init
checkResult

test "PINA: 0x01, 0x04, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01 => PORTB: 0x01, state: unlock"
set digit = start
setPINA 0x01
continue 2
expect digit init
setPINA 0x04
continue 2
echo \n
print digit
expect digit Hash
setPINA 0x00
continue 2
print digit
print i
setPINA 0x01
continue 2
print digit
print i
setPINA 0x00
continue 2
print digit
print i
echo comb[i]: 
print comb[i]
setPINA 0x02
continue 2
print digit
print i
setPINA 0x00
continue 2
print digit
print i
setPINA 0x01
continue 2
print digit
print i
setPINA 0x00
continue 2
print digit
print i
expectPORTB 0x01
expect digit unlock
checkResult

test "button at a time test : PINA: 0x01, 0x06, 0x00, 0x02 => PORTB: 0x00, state: init"
set digit = start
setPINA 0x01
continue 2
setPINA 0x06
continue 2
setPINA 0x00
continue 2
setPINA 0x02
continue 2
expectPORTB 0x00
expect digit init
checkResult

test "PINA: 0x04, 0x00, 0x01, 0x00, 0x02, 0x01, 0x00 => PORTB: 0x01, state: init"
set digit = start
setPINA 0x04
continue 2
setPINA 0x00
continue 2
setPINA 0x01
continue 10
setPINA 0x00
continue 10
setPINA 0x02
continue 10
setPINA 0x00
continue 10
setPINA 0x01
continue 10
setPINA 0x00
continue 10
print digit
expectPORTB 0x01
expect digit unlock
checkResult

set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
