use std::{
    fs::File,
    io::{self, prelude::*, BufReader},
};

fn main() -> io::Result<()> {
    let data = File::open("data/data.txt")?;
    let buf = BufReader::new(data);
    let lines = buf.lines().collect::<Result<Vec<String>, _>>()?;

    // Part one!
    part_one();

    // Part two!
    part_two();

    Ok(())
}

fn part_one() {
    let res = 0;
    println!("Part One: {}", res);
}

fn part_two() {
    let res = 0;
    println!("Part Two: {}", res);
}
