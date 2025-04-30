use std::{collections::HashMap, process::exit, usize};

/// defines how many arguments an instruction should take
enum Instruction {
    Zero(fn(&mut Assembler)),
    One(fn(&mut Assembler, i32)),
    Two(fn(&mut Assembler, i32, i32)),
}

const STACK_SIZE: i32 = 120;
pub struct Assembler {
    registers: [i32; 32],
    instruction_pointer: i32,
    stack: Vec<i32>,
    // the function definition uses a vector to pass arguments to achieve compatibility with all the functions
    // if a function tries to access more arguments than the ones defined in the spec sheet it will panic
    functions_table: HashMap<i32, Instruction>,
}

impl Assembler {

    /// initializes the functions table
    fn init_map(&mut self) {
        self.functions_table.insert(1, Instruction::One(Self::display));
        self.functions_table.insert(2, Instruction::One(Self::print_stack));
        self.functions_table.insert(10, Instruction::One(Self::push));
        self.functions_table.insert(11, Instruction::One(Self::pop));
        self.functions_table.insert(12, Instruction::Two(Self::mov));
        self.functions_table.insert(20, Instruction::One(Self::call));
        self.functions_table.insert(21, Instruction::Zero(Self::ret));
        self.functions_table.insert(22, Instruction::One(Self::jmp));
        self.functions_table.insert(23, Instruction::One(Self::jz));
        self.functions_table.insert(24, Instruction::One(Self::jpos));
        self.functions_table.insert(25, Instruction::One(Self::jneg));
        self.functions_table.insert(30, Instruction::Two(Self::add));
        self.functions_table.insert(31, Instruction::Two(Self::sub));
        self.functions_table.insert(32, Instruction::Two(Self::mul));
        self.functions_table.insert(33, Instruction::Two(Self::div));
    }

    // constructor
    pub fn new() -> Assembler {
        let mut new_assembler = Assembler {
            registers: [0; 32],
            functions_table: HashMap::new(),
            instruction_pointer: 0,
            stack: Vec::new(),
        };
        new_assembler.init_map();
        return new_assembler;
    }

    // interprets the program line by line and executes it
    pub fn execute(&mut self, program: &[i32]) {
        loop {
            // lookup the function code to execute next
            let func_code = program[(self.instruction_pointer) as usize];
            // code 0 means exit
            if func_code == 0 {
                return;
            }

            // lookup the associated implementation of the function
            let func = self.functions_table.get(&func_code).expect("function not found");

            // check the arity of the function and provide the appropriate arguments
            match func {
                Instruction::Zero(f) => {
                    f(self);
                }
                Instruction::One(f) => {
                    let arg = program[(self.instruction_pointer + 1) as usize];
                    f(self, arg);
                }
                Instruction::Two(f) => {
                    let arg1 = program[(self.instruction_pointer + 1) as usize];
                    let arg2 = program[(self.instruction_pointer + 2) as usize];
                    f(self, arg1, arg2);
                }
            }
        }
    }

    /// Prints the value stored in the given register
    /// Function code: 1
    fn display(&mut self, reg: i32) {
        println!("{}", self.registers[reg as usize]);
        self.instruction_pointer += 2;
    }

    /// Prints n numbers stored on the stack
    /// Function code: 2
    fn print_stack(&mut self, mut n: i32) {
        while n > 0 {
            let el = self.stack.pop().expect("Stack underflow");
            println!("{} {}", n - 1, el);
            n -= 1;
        }
        self.instruction_pointer += 2;
    }

    /// Inserts the value stored in the given register into the stack
    /// Function code: 10
    fn push(&mut self, reg: i32) {
        if self.stack.len() as i32 >= STACK_SIZE {
            Assembler::stack_overflow();
        }
        self.stack.push(self.registers[reg as usize]);
        self.instruction_pointer += 2;
    }

    /// Inserts the number into the stack, for internal implementations
    fn push_internal(&mut self, num: i32) {
        if self.stack.len() as i32 >= STACK_SIZE {
            Assembler::stack_overflow();
        }
        self.stack.push(num);
    }

    /// Removes one number from the stack and stores it into the given register
    /// Function code: 11
    fn pop(&mut self, reg: i32) {
        self.registers[reg as usize] = self.stack.pop().expect("Stack underflow");
        self.instruction_pointer += 2;
    }

    /// Pops one item from the stack, for internal implementations
    fn pop_internal(&mut self) -> i32 {
        return self.stack.pop().expect("Stack underflow");
    }

    /// Stores the integer into the given register
    /// Function code: 12
    fn mov(&mut self, reg: i32, val: i32) {
        self.registers[reg as usize] = val;
        self.instruction_pointer += 3;
    }

    /// Pushes the next instruction pointer and jumps to the given position
    /// Function code: 20
    fn call(&mut self, pos: i32) {
        self.push_internal(self.instruction_pointer + 2);
        self.instruction_pointer = pos;
    }

    /// Pops the instruction pointer from the stack and jumps back to it
    /// Function code: 21
    fn ret(&mut self) {
        self.instruction_pointer = self.pop_internal();
    }

    /// Jumps to the given position
    /// Function code: 22
    fn jmp(&mut self, pos: i32) {
        self.instruction_pointer = pos;
    }

    /// Pops one number from the stack and, if it's different than zero, jumps
    /// to the given position
    /// Function code: 23
    fn jz(&mut self, pos: i32) {
        let num = self.pop_internal();
        if num == 0 {
            self.instruction_pointer = pos;
        } else {
            self.instruction_pointer += 2;
        }
    }

    /// Pops one number from the stack and, if it's greater than zero, jumps
    /// to the given position
    /// Function code: 24
    fn jpos(&mut self, pos: i32) {
        let num = self.pop_internal();
        if num > 0 {
            self.instruction_pointer = pos;
        } else {
            self.instruction_pointer += 2;
        }
    }

    /// Pops one number from the stack and, if it's smaller than zero, jumps
    /// to the given position
    /// Function code: 25
    fn jneg(&mut self, pos: i32) {
        let num = self.pop_internal();
        if num < 0 {
            self.instruction_pointer = pos;
        } else {
            self.instruction_pointer += 2;
        }
    }

    /// Adds the values stored in the given registers and pushes the result into the stack
    /// Function code: 30
    fn add(&mut self, reg1: i32, reg2: i32) {
        // lookup the register contents and promote to i64
        let val1 = self.registers[reg1 as usize] as i64;
        let val2 = self.registers[reg2 as usize] as i64;
        // perform the addition and verify that no overflow/underflow occurred within i32 ranges
        let result = val1 + val2;
        if result > i32::MAX.into() {
            Assembler::overflow();
        } else if result < i32::MIN.into() {
            Assembler::underflow();
        }
        // if no errors occurred, push the result to the stack
        self.push_internal(self.registers[reg1 as usize] + self.registers[reg2 as usize]);
        // increase the instruction pointer by three positions to account for the add instruction
        // and the two arguments
        self.instruction_pointer += 3;
    }

    /// Subtracts the values stored in the given registers and pushes the result into the stack
    /// Function code: 31
    fn sub(&mut self, reg1: i32, reg2: i32) {
        // lookup the register contents and promote to i64
        let val1 = self.registers[reg1 as usize] as i64;
        let val2 = self.registers[reg2 as usize] as i64;
        // perform the subtraction and verify that no overflow/underflow occurred within i32 ranges
        let result = val1 - val2;
        if result > i32::MAX.into() {
            Assembler::overflow();
        } else if result < i32::MIN.into() {
            Assembler::underflow();
        }
        // if no errors occurred, push the result to the stack
        self.push_internal(self.registers[reg1 as usize] - self.registers[reg2 as usize]);
        // increase the instruction pointer by three positions to account for the sub instruction
        // and the two arguments
        self.instruction_pointer += 3;
    }

    /// Multiplies the values stored in the given registers and pushes the result into the stack
    /// Function code: 32
    fn mul(&mut self, reg1: i32, reg2: i32) {
        // lookup the register contents and promote to i64
        let val1 = self.registers[reg1 as usize] as i64;
        let val2 = self.registers[reg2 as usize] as i64;
        // perform the multiplication and verify that no overflow/underflow occurred within i32 ranges
        let result = val1 * val2;
        if result > i32::MAX.into() {
            Assembler::overflow();
        } else if result < i32::MIN.into() {
            Assembler::underflow();
        }
        // if no errors occurred, push the result to the stack
        self.push_internal(self.registers[reg1 as usize] * self.registers[reg2 as usize]);
        // increase the instruction pointer by three positions to account for the mul instruction
        // and the two arguments
        self.instruction_pointer += 3;
    }

    /// Divides the values stored in the given registers and pushes the result into the stack
    /// Function code: 33
    fn div(&mut self, reg1: i32, reg2: i32) {
        if self.registers[reg2 as usize] == 0 {
            println!("Error: can't divide by zero");
            exit(1)
        } else {
            self.push_internal(self.registers[reg1 as usize] / self.registers[reg2 as usize]);
            // increase the instruction pointer by three positions to account for the div instruction
            // and the two arguments
            self.instruction_pointer += 3;
        }
    }

    fn overflow() {
        println!("Error: arithmetic overflow");
        exit(1)
    }

    fn underflow() {
        println!("Error: arithmetic underflow");
        exit(1)
    }

    fn stack_overflow() {
        println!("Error: stack overflow");
        exit(1)
    }
}
