mod read_input;
mod vm;

use crate::vm::Assembler;
use regex::Regex;
use std::env;
use std::io::BufRead;

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() == 2 {
        let file = read_input::read_program_from_file(&args[1]);
        let re = Regex::new(";.*").unwrap();
        let mut program: Vec<i32> = Vec::new();
        for (_index, line) in file.lines().enumerate() {
            let mut line = line.unwrap();
            let filtered_line = re.replace_all(&mut line, "");
            let trimmed_filtered_line = filtered_line.trim();
            if trimmed_filtered_line.len() > 0 {
                program.push(trimmed_filtered_line.parse::<i32>().unwrap());
            }
        }
        let program_sliced = &program[1..];
        let mut assembler = Assembler::new();
        assembler.execute(program_sliced);
    }
}
