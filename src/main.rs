mod assembler;
mod read_input;

use assembler::Assembler;
use clap::Parser;
use std::path::Path;

#[derive(Parser, Debug)]
#[command(name = "Rust Assembler")]
#[command(author = "Nicolò Bertocco <nick.bertocco@gmail.com>")]
#[command(version = "1.0")]
#[command(about = "Simple assembler implemented in Rust", long_about = None)]
struct Cli {
    /// path to source file
    #[arg(short, long)]
    source_path: String,
}

fn main() {
    // parse the cli arguments
    let args = Cli::parse();

    // create a new Path object
    let source_path = Path::new(&args.source_path);

    // try to parse an assembly program from the input file
    let program = read_input::read_program_from_file(&source_path);

    // create an instance of the assembler
    let mut assembler = Assembler::new();

    // execute the program
    assembler.execute(&program);
}
