use std::{collections::HashMap, usize};
use super::instruction::Instruction;

pub(crate) const STACK_SIZE: i32 = 120;
pub struct Assembler {
    pub(crate) registers: [i32; 32],
    pub(crate) instruction_pointer: i32,
    pub(crate) stack: Vec<i32>,
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

    pub(crate) fn overflow() {
        println!("Error: arithmetic overflow");
        std::process::exit(1)
    }

    pub(crate) fn underflow() {
        println!("Error: arithmetic underflow");
        std::process::exit(1)
    }

    pub(crate) fn stack_overflow() {
        println!("Error: stack overflow");
        std::process::exit(1)
    }
}
