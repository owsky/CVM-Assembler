impl super::Assembler{
    /// Jumps to the given position
    /// Function code: 22
    pub(super) fn jmp(&mut self, pos: i32) {
        self.instruction_pointer = pos;
    }

    /// Pops one number from the stack and, if it's different than zero, jumps
    /// to the given position
    /// Function code: 23
    pub(super) fn jz(&mut self, pos: i32) {
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
    pub(super) fn jpos(&mut self, pos: i32) {
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
    pub(super) fn jneg(&mut self, pos: i32) {
        let num = self.pop_internal();
        if num < 0 {
            self.instruction_pointer = pos;
        } else {
            self.instruction_pointer += 2;
        }
    }
}