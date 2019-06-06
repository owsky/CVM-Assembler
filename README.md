# CVM-Assembler
This project is a simplified virtual machine that prints or executes assembly programs by crossreferencing its table of functions with a .cvm file. Each one is addressed through an integer code and may have one or two parameters.
The supported commands are <italic>print</italic> and <italic>execute</italic> and both require a valid .cvm file. It's assumed that the input program is correct (minus the overflow, which was required to test for) and that it is written with the following specifics:
<ul>
  <li>The very first numbers represents the total number of lines minus the ones that contain only comments</li>
  <li>Comments are delimited by the semilicon character and comprehend the whole line on its right side</li>
  <li>Spaces and tabs are ignored so their use is not restricted</li>
</ul>

Command and file name are to be typed as parameters at execution, as per instruction from the course's professor.

<h3>Table of Functions</h3>
<table>
  <tr>
    <th>Function Name</th>
    <th>Machine code number</th>
    <th>First Parameter</th>
    <th>Second Parameter</th>
    <th>Description</th>
  </tr>
  <tr>
    <td>
      HALT
    </td>
    <td>
      0
    </td>
    <td>
      -
    </td>
    <td>
      -
    </td>
    <td>
      Stops the execution
    </td>
  </tr>
  <tr>
    <td>
      DISPLAY
    </td>
    <td>
      1
    </td>
    <td>
      Reg R0-R31
    </td>
    <td>
      -
    </td>
    <td>
      Prints the value stored in the given register
    </td>
  </tr>
  <tr>
    <td>
      PRINT_STACK
    </td>
    <td>
      2
    </td>
    <td>
      Integer
    </td>
    <td>
      -
    </td>
    <td>
      Prints n numbers stored on the stack
    </td>
  </tr>
  <tr>
    <td>
      PUSH
    </td>
    <td>
      10
    </td>
    <td>
      Reg R0-R31
    </td>
    <td>
      -
    </td>
    <td>
      Inserts the value stored in the given register into the stack
    </td>
  </tr>
  <tr>
    <td>
      POP
    </td>
    <td>
      11
    </td>
    <td>
      Reg R0-R31
    </td>
    <td>
      -
    </td>
    <td>
      Removes one number from the stack and stores it into the given register
    </td>
  </tr>
  <tr>
    <td>
      MOV
    </td>
    <td>
      12
    </td>
    <td>
      Reg R0-R31
    </td>
    <td>
      Integer
    </td>
    <td>
      Stores the integer into the given register
    </td>
  </tr>
  <tr>
    <td>
      CALL
    </td>
    <td>
      20
    </td>
    <td>
      Position (Integer)
    </td>
    <td>
      -
    </td>
    <td>
      Pushes the next instruction pointer and jumps to the given position 
    </td>
  </tr>
  <tr>
    <td>
      RET
    </td>
    <td>
      21
    </td>
    <td>
      -
    </td>
    <td>
      -
    </td>
    <td>
      Pops the instruction pointer from the stack and jumps back to it
    </td>
  </tr>
  <tr>
    <td>
      JMP
    </td>
    <td>
      22
    </td>
    <td>
      Position (Integer)
    </td>
    <td>
      -
    </td>
    <td>
      Jumps to the given position
    </td>
  </tr>
  <tr>
    <td>
      JZ
    </td>
    <td>
      23
    </td>
    <td>
      Position (Integer)
    </td>
    <td>
      -
    </td>
    <td>
      Pops one number from the stack, and jumps to it if it's different than zero
    </td>
  </tr>
  <tr>
    <td>
      JPOS
    </td>
    <td>
      24
    </td>
    <td>
      Position (Integer)
    </td>
    <td>
      -
    </td>
    <td>
      Pops one number from the stack, and jumps to it if it's greater than zero
    </td>
  </tr>
  <tr>
    <td>
      JNEG
    </td>
    <td>
      25
    </td>
    <td>
      Position (Integer)
    </td>
    <td>
      -
    </td>
    <td>
      Pops one number from the stack, and jumps to it if it's smaller than zero 
    </td>
  </tr>
  <tr>
    <td>
      ADD
    </td>
    <td>
      30
    </td>
    <td>
      Reg R0-R31
    </td>
    <td>
      Reg R0-R31
    </td>
    <td>
      Adds the values stored in the given registers and pushes the result into the stack
    </td>
  </tr>
    <tr>
    <td>
      SUB
    </td>
    <td>
      31
    </td>
    <td>
      Reg R0-R31
    </td>
    <td>
      Reg R0-R31
    </td>
    <td>
      Subtracts the values stored in the given registers and pushes the result into the stack
    </td>
  </tr>
    <tr>
    <td>
      MUL
    </td>
    <td>
      32
    </td>
    <td>
      Reg R0-R31
    </td>
    <td>
      Reg R0-R31
    </td>
    <td>
      Multiplies the values stored in the given registers and pushes the result into the stack
    </td>
  </tr>
    <tr>
    <td>
      DIV
    </td>
    <td>
      33
    </td>
    <td>
      Reg R0-R31
    </td>
    <td>
      Reg R0-R31
    </td>
    <td>
      Divides the values stored in the given registers and pushes the result into the stack
    </td>
  </tr>
</table>
