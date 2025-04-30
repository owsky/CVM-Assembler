use crate::Assembler;

enum ArithmeticOp {
    Add,
    Sub,
    Mul,
    Div
}

impl super::Assembler{
    /// Prints the value stored in the given register
    /// Function code: 1
    pub(super) fn display(&mut self, reg: i32) {
        println!("{}", self.registers[reg as usize]);
        self.instruction_pointer += 2;
    }

    /// Stores the integer into the given register
    /// Function code: 12
    pub(super) fn mov(&mut self, reg: i32, val: i32) {
        self.registers[reg as usize] = val;
        self.instruction_pointer += 3;
    }

    /// Pushes the next instruction pointer and jumps to the given position
    /// Function code: 20
    pub(super) fn call(&mut self, pos: i32) {
        self.push_internal(self.instruction_pointer + 2);
        self.instruction_pointer = pos;
    }

    /// Pops the instruction pointer from the stack and jumps back to it
    /// Function code: 21
    pub(super) fn ret(&mut self) {
        self.instruction_pointer = self.pop_internal();
    }

    fn arithmetic_op(&mut self, reg1: usize, reg2: usize, op: ArithmeticOp) {
        // check for division by zero
        if matches!(op, ArithmeticOp::Div) && self.registers[reg2] == 0 {
            println!("Error: division by zero");
            std::process::exit(1);
        }

        // for operations different from division we need to check overflow/underflow
        if !matches!(op, ArithmeticOp::Div) {
            // lookup the register contents and promote to i64
            let val1 = self.registers[reg1] as i64;
            let val2 = self.registers[reg2] as i64;

            // perform the operation
            let result = match op {
                ArithmeticOp::Add => val1 + val2,
                ArithmeticOp::Sub => val1 - val2,
                ArithmeticOp::Mul => val1 - val2,
                ArithmeticOp::Div => unreachable!()
            };

            // check for overflow/underflow within i32 range
            if result > i32::MAX.into() {
                Assembler::overflow();
            } else if result < i32::MIN.into() {
                Assembler::underflow();
            }
        }

        // if no operation error occurred, perform the actual operation within i32
        let result = match op {
            ArithmeticOp::Add => self.registers[reg1 as usize] + self.registers[reg2 as usize],
            ArithmeticOp::Sub => self.registers[reg1 as usize] - self.registers[reg2 as usize],
            ArithmeticOp::Mul => self.registers[reg1 as usize] * self.registers[reg2 as usize],
            ArithmeticOp::Div => self.registers[reg1 as usize] / self.registers[reg2 as usize],
        };

        // push the result to the stack
        self.push_internal(result);

        // move the instruction pointer forward by 3 positions to account for the operation
        // instruction and its arguments
        self.instruction_pointer += 3;
    }

    /// Adds the values stored in the given registers and pushes the result into the stack
    /// Function code: 30
    pub(super) fn add(&mut self, reg1: i32, reg2: i32) {
        self.arithmetic_op(reg1 as usize, reg2 as usize, ArithmeticOp::Add);
    }

    /// Subtracts the values stored in the given registers and pushes the result into the stack
    /// Function code: 31
    pub(super) fn sub(&mut self, reg1: i32, reg2: i32) {
        self.arithmetic_op(reg1 as usize, reg2 as usize, ArithmeticOp::Sub);
    }

    /// Multiplies the values stored in the given registers and pushes the result into the stack
    /// Function code: 32
    pub(super) fn mul(&mut self, reg1: i32, reg2: i32) {
        self.arithmetic_op(reg1 as usize, reg2 as usize, ArithmeticOp::Mul);
    }

    /// Divides the values stored in the given registers and pushes the result into the stack
    /// Function code: 33
    pub(super) fn div(&mut self, reg1: i32, reg2: i32) {
        self.arithmetic_op(reg1 as usize, reg2 as usize, ArithmeticOp::Div);
    }

}