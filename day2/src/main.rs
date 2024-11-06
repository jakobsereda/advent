use std::io::BufReader;
use std::fs::{
    self, 
    File
};

fn main() -> io::Result<()> {
    let data = File::create("data/data.txt")?;
    let buf = BufReader::new(data);

    

    Ok(())
}
