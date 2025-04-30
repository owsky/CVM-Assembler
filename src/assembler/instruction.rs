use super::Assembler;

/// defines how many arguments an instruction should take
pub(crate) enum Instruction {
    Zero(fn(&mut Assembler)),
    One(fn(&mut Assembler, i32)),
    Two(fn(&mut Assembler, i32, i32)),
}