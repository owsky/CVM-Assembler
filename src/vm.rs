use std::{collections::HashMap, usize};

const STACK_SIZE: i32 = 120;
pub struct Assembler {
    registers: [i32; 32],
    instruction_pointer: i32,
    stack: Vec<i32>,
    // the function definition uses a vector to pass arguments to achieve compatibility with all the functions
    // if a function tries to access more arguments than the ones defined in the spec sheet it will panic
    functions_table: HashMap<i32, fn(&mut Self, args: &Vec<i32>)>,
}

impl Assembler {
    fn init_map(&mut self) {
        self.functions_table.insert(1, Self::display);
        self.functions_table.insert(2, Self::print_stack);
        self.functions_table.insert(10, Self::push);
        self.functions_table.insert(11, Self::pop);
        self.functions_table.insert(12, Self::mov);
        self.functions_table.insert(20, Self::call);
        self.functions_table.insert(21, Self::ret);
        self.functions_table.insert(22, Self::jmp);
        self.functions_table.insert(23, Self::jz);
        self.functions_table.insert(24, Self::jpos);
        self.functions_table.insert(25, Self::jneg);
        self.functions_table.insert(30, Self::add);
        self.functions_table.insert(31, Self::sub);
        self.functions_table.insert(32, Self::mul);
        self.functions_table.insert(33, Self::div);
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
            let func_code = program[(self.instruction_pointer) as usize];
            if func_code == 0 {
                return;
            }

            let arg_size = match func_code {
                21 => 0,
                1 | 2 | 10 | 11 | 20 | 22 | 23 | 24 | 25 => 1,
                12 | 30 | 31 | 32 | 33 => 2,
                _ => 0,
            };

            let func = self
                .functions_table
                .get(&func_code)
                .expect("function not found");
            let mut args: Vec<i32> = Vec::new();
            for i in 0..arg_size {
                let arg_code = program[(self.instruction_pointer + i + 1) as usize];
                args.push(arg_code);
            }
            func(self, &args);
        }
    }

    // Prints the value stored in the given register
    // Function code: 1
    // Parameters: Registry<R0-R31>
    fn display(&mut self, args: &Vec<i32>) {
        let reg = args[0];
        println!("{}", self.registers[reg as usize]);
        self.instruction_pointer += 2;
    }

    // Prints n numbers stored on the stack
    // Function code: 2
    // Parameters: Integer
    fn print_stack(&mut self, args: &Vec<i32>) {
        let mut num = args[0];
        while num > 0 {
            let el = self.stack.pop().expect("Stack underflow");
            println!("{} {}", num - 1, el);
            num -= 1;
        }
        self.instruction_pointer += 2;
    }

    // Inserts the value stored in the given register into the stack
    // Function code: 10
    // Parameters: Registry<R0-R31>
    fn push(&mut self, args: &Vec<i32>) {
        if self.stack.len() as i32 >= STACK_SIZE {
            Assembler::stack_overflow();
        }
        let reg = args[0];
        self.stack.push(self.registers[reg as usize]);
        self.instruction_pointer += 2;
    }

    // Inserts the number into the stack, for internal implementations
    fn push_internal(&mut self, num: i32) {
        if self.stack.len() as i32 >= STACK_SIZE {
            Assembler::stack_overflow();
        }
        self.stack.push(num);
    }

    // Removes one number from the stack and stores it into the given register
    // Function code: 11
    // Parameters: Registry<R0-R31>
    fn pop(&mut self, args: &Vec<i32>) {
        let reg = args[0];
        self.registers[reg as usize] = self.stack.pop().expect("Stack underflow");
        self.instruction_pointer += 2;
    }

    // Pops one item from the stack, for internal implementations
    fn pop_internal(&mut self) -> i32 {
        return self.stack.pop().expect("Stack underflow");
    }

    // Stores the integer into the given register
    // Function code: 12
    // Parameters: Registry<R0-R31> Integer
    fn mov(&mut self, args: &Vec<i32>) {
        let reg = args[0];
        let num = args[1];
        self.registers[reg as usize] = num;
        self.instruction_pointer += 3;
    }

    // Pushes the next instruction pointer and jumps to the given position
    // Function code: 20
    // Parameters: Integer
    fn call(&mut self, args: &Vec<i32>) {
        self.push_internal(self.instruction_pointer + 2);
        let pos = args[0];
        self.instruction_pointer = pos;
    }

    // Pops the instruction pointer from the stack and jumps back to it
    // Function code: 21
    // Parameters: none
    fn ret(&mut self, _args: &Vec<i32>) {
        self.instruction_pointer = self.pop_internal();
    }

    //Jumps to the given position
    // Function code: 22
    // Parameters: Integer
    fn jmp(&mut self, args: &Vec<i32>) {
        let pos = args[0];
        self.instruction_pointer = pos;
    }

    // Pops one number from the stack, and jumps to it if it's different than zero
    // Function code: 23
    // Parameters: Integer
    fn jz(&mut self, args: &Vec<i32>) {
        let pos = args[0];
        let num = self.pop_internal();
        if num == 0 {
            self.instruction_pointer = pos;
        } else {
            self.instruction_pointer += 2;
        }
    }

    // Pops one number from the stack, and jumps to it if it's greater than zero
    // Function code: 24
    // Parameters: Integer
    fn jpos(&mut self, args: &Vec<i32>) {
        let pos = args[0];
        let num = self.pop_internal();
        if num > 0 {
            self.instruction_pointer = pos;
        } else {
            self.instruction_pointer += 2;
        }
    }

    // Pops one number from the stack, and jumps to it if it's smaller than zero
    // Function code: 25
    // Parameters: Integer
    fn jneg(&mut self, args: &Vec<i32>) {
        let pos = args[0];
        let num = self.pop_internal();
        if num < 0 {
            self.instruction_pointer = pos;
        } else {
            self.instruction_pointer += 2;
        }
    }

    // Adds the values stored in the given registers and pushes the result into the stack
    // Function code: 30
    // Parameters: Registry<R0-R1> Registry<R0-R31>
    fn add(&mut self, args: &Vec<i32>) {
        let reg1 = args[0] as i64;
        let reg2 = args[1] as i64;
        let check = reg1 + reg2;
        if check > i32::MAX.into() {
            Assembler::overflow();
        } else if check < i32::MIN.into() {
            Assembler::underflow();
        }
        self.push_internal(self.registers[reg1 as usize] + self.registers[reg2 as usize]);
        self.instruction_pointer += 3;
    }

    // Subtracts the values stored in the given registers and pushes the result into the stack
    // Function code: 31
    // Parameters: Registry<R0-R1> Registry<R0-R31>
    fn sub(&mut self, args: &Vec<i32>) {
        let reg1 = args[0] as i64;
        let reg2 = args[1] as i64;
        let check = reg1 - reg2;
        if check > i32::MAX.into() {
            Assembler::overflow();
        } else if check < i32::MIN.into() {
            Assembler::underflow();
        }
        self.push_internal(self.registers[reg1 as usize] - self.registers[reg2 as usize]);
        self.instruction_pointer += 3;
    }

    // Multiplies the values stored in the given registers and pushes the result into the stack
    // Function code: 32
    // Parameters: Registry<R0-R1> Registry<R0-R31>
    fn mul(&mut self, args: &Vec<i32>) {
        let reg1 = args[0] as i64;
        let reg2 = args[1] as i64;
        let check = reg1 * reg2;
        if check > i32::MAX.into() {
            Assembler::overflow();
        } else if check < i32::MIN.into() {
            Assembler::underflow();
        }
        self.push_internal(self.registers[reg1 as usize] * self.registers[reg2 as usize]);
        self.instruction_pointer += 3;
    }

    // Divides the values stored in the given registers and pushes the result into the stack
    // Function code: 33
    // Parameters: Registry<R0-R1> Registry<R0-R31>
    fn div(&mut self, args: &Vec<i32>) {
        let reg1 = args[0] as usize;
        let reg2 = args[1] as usize;
        if self.registers[reg2] == 0 {
            panic!("Error: can't divide by zero");
        } else {
            self.push_internal(self.registers[reg1] / self.registers[reg2]);
            self.instruction_pointer += 3;
        }
    }

    fn overflow() {
        panic!("Error: arithmetic overflow");
    }

    fn underflow() {
        panic!("Error: arithmetic underflow");
    }

    fn stack_overflow() {
        panic!("Error: stack overflow");
    }
}
