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

    // uncomment me!!
    // ==============
    // part_one(buf).expect("Error calculating part one...");
    // part_two(buf).expect("Error calculating part two...");

    Ok(())
}

fn part_one(buf: BufReader<File>) -> io::Result<()> {
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

fn part_two(buf: BufReader<File>) -> io::Result<()> {
    let re_1 = Regex::new(r"\d|one|two|three|four|five|six|seven|eight|nine")
        .unwrap_or_else(|e| {
            eprintln!("Regex failed: {}", e);
            std::process::exit(1);
        });

    let re_2 = Regex::new(r"\d|eno|owt|eerht|ruof|evif|xis|neves|thgie|enin")
        .unwrap_or_else(|e| {
            eprintln!("Regex failed: {}", e);
            std::process::exit(1);
        });

    let mut sum = 0;
    for line in buf.lines() {
        let line = line?;
        let first_digit = if let Some(mat) = re_1.find(&line) {
            match &line[mat.start()..mat.end()] {
                "one" | "1" => 1,
                "two" | "2" => 2,
                "three" | "3" => 3,
                "four" | "4" => 4,
                "five" | "5" => 5,
                "six" | "6" => 6,
                "seven" | "7" => 7,
                "eight" | "8" => 8,
                "nine" | "9" => 9,
                _ => 0
            }
        } else {
            0
        };

        let rev = line.chars().rev().collect::<String>();
        let second_digit = if let Some(mat) = re_2.find(&rev) {
            match &rev[mat.start()..mat.end()] {
                "eno" | "1" => 1,
                "owt" | "2" => 2,
                "eerht" | "3" => 3,
                "ruof" | "4" => 4,
                "evif" | "5" => 5,
                "xis" | "6" => 6,
                "neves" | "7" => 7,
                "thgie" | "8" => 8,
                "enin" | "9" => 9,
                _ => 0
            }
        } else {
            0
        };

        let num = (first_digit * 10) + second_digit;
        sum += num;
    }
    
    println!("{}", sum);

    Ok(())
}
