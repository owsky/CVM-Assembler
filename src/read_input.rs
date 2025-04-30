use std::fs::File;
use std::io::{BufRead, BufReader};
use std::path::Path;

/// Tries to parse a program, formed as a vector of integers, from
/// the given source file
pub fn read_program_from_file(source_path: &Path) -> Vec<i32> {
    // try to open the file
    let f = File::open(source_path);
    let file = match f {
        Ok(file) => file,
        Err(_e) => {
            println!(
                "Error: input source file does not exist: \n{}",
                source_path.display()
            );
            std::process::exit(1);
        }
    };

    // create a buffer from the file
    let buf = BufReader::new(file);

    // define the program as a vector of instructions
    let mut program: Vec<i32> = Vec::new();

    for line in buf.lines() {
        // unwrap the line content, panic if malformed
        let line_content = line.unwrap();
        // filter out comments marked by ';'
        let cleaned = line_content.split(";").next().unwrap_or("").trim();
        // if the instruction is an integer32, add it to the program
        if let Ok(value) = cleaned.parse::<i32>() {
            program.push(value);
        }
    }

    return program;
}
