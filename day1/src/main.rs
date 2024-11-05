use std::fs::File;
use regex::Regex;
use std::io::{
    self,
    prelude::*,
    BufReader
};

fn main() -> io::Result<()> {
    let data = File::open("data/data.txt")?;
    let buf = BufReader::new(data);

    let re = Regex::new(r"\d")
        .unwrap_or_else(|e| {
            eprintln!("Regex failed: {}", e);
            std::process::exit(1);
        });

    let mut sum = 0;
    for line in buf.lines() {
        let line = line?;
        let first_digit = if let Some(mat) = re.find(&line) {
            line[mat.start()..mat.end()].parse::<i32>().unwrap_or(0)
        } else {
            0
        };

        let rev = line.chars().rev().collect::<String>();
        let second_digit = if let Some(mat) = re.find(&rev) {
            rev[mat.start()..mat.end()].parse::<i32>().unwrap_or(0)
        } else {
            0
        };

        let num = (first_digit * 10) + second_digit;
        sum += num;
    }

    println!("{}", sum);

    Ok(())
}
