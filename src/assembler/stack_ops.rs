use crate::Assembler;
use super::STACK_SIZE;

impl super::Assembler{
    /// Prints n numbers stored on the stack
    /// Function code: 2
    pub(super) fn print_stack(&mut self, mut n: i32) {
        while n > 0 {
            let el = self.stack.pop().expect("Stack underflow");
            println!("{} {}", n - 1, el);
            n -= 1;
        }
        self.instruction_pointer += 2;
    }

    /// Inserts the value stored in the given register into the stack
    /// Function code: 10
    pub(super) fn push(&mut self, reg: i32) {
        if self.stack.len() as i32 >= STACK_SIZE {
            Assembler::stack_overflow();
        }
        self.stack.push(self.registers[reg as usize]);
        self.instruction_pointer += 2;
    }

    /// Inserts the number into the stack, for internal implementations
    pub(super) fn push_internal(&mut self, num: i32) {
        if self.stack.len() as i32 >= STACK_SIZE {
            Assembler::stack_overflow();
        }
        self.stack.push(num);
    }

    /// Removes one number from the stack and stores it into the given register
    /// Function code: 11
    pub(super) fn pop(&mut self, reg: i32) {
        self.registers[reg as usize] = self.stack.pop().expect("Stack underflow");
        self.instruction_pointer += 2;
    }

    /// Pops one item from the stack, for internal implementations
    pub(super) fn pop_internal(&mut self) -> i32 {
        return self.stack.pop().expect("Stack underflow");
    }
}