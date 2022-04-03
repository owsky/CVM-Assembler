use std::fs::File;
use std::io::BufReader;

pub fn read_program_from_file(file_name: &String) -> BufReader<File> {
    let f = File::open(file_name);

    let file = match f {
        Ok(file) => file,
        Err(e) => panic!("{}", e),
    };

    return BufReader::new(file);
}
