use std::{collections::HashMap, usize};

type AssemblyFunction = fn(u32, u32) -> u32;
struct Assembler {
    registers: Vec<u32>,
    sp: u32,
    ip: u32,
    stack: Vec<u32>,
    functions: HashMap<u32, AssemblyFunction>,
}

impl Default for Assembler {
    fn default() -> Self {
        Self {
            registers: Vec::new(),
            functions: HashMap::new(),
            sp: 0,
            ip: 0,
            stack: Vec::new(),
        }
    }
}

trait Display {
    fn display(&mut self, reg: usize);
}

impl Display for Assembler {
    fn display(&mut self, reg: usize) {
        match self.registers.get(reg) {
            Some(val) => {
                println!("{}", *val);
                self.ip += 2;
            }
            None => todo!(),
        }
    }
}

trait PrintStack {
    fn print_stack(&self, num: usize);
}

impl PrintStack for Assembler {
    fn print_stack(&self, num: usize) {
        if self.stack.len() < num {
            stack_underflow();
        } else {
            let peek: Vec<&u32> = self.stack.iter().rev().take(num).collect();
            println!("{:?}", peek);
        }
    }
}

fn stack_underflow() {
    println!("Error: stack underflow");
}
