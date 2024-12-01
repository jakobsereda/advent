use std::fs::File;
use std::io::{
    self,
    prelude::*,
    BufReader
};

fn main() -> io::Result<()> {
    let data = File::open("data/data.txt")?;
    let buf = BufReader::new(data);
    let lines = buf.lines().collect::<Result<Vec<String>, _>>()?;

    let mut first_list: Vec<i32> = Vec::new();
    let mut second_list: Vec<i32> = Vec::new();

    for line in lines {
        let pair: Vec<i32> = line.split_whitespace()
            .map(|s| s.parse::<i32>().unwrap())
            .collect();
        first_list.push(pair[0]);
        second_list.push(pair[1]);
    }

    first_list.sort();
    second_list.sort();

    // Part one!
    part_one(&first_list, &second_list);

    // Part two!
    part_two(&first_list, &second_list);

    Ok(())
}

fn part_one(first_list: &[i32], second_list: &[i32]) {
    let res: i32 = first_list
        .iter()
        .zip(second_list.iter())
        .map(|(f, s)| (f - s).abs())
        .sum();

    println!("Part One: {}", res);
}

fn part_two(first_list: &[i32], second_list: &[i32]) {
    let res: i32 = first_list
        .iter()
        .map(|e| {
            let count: i32 = second_list
                .iter()
                .filter(|&n| *n == *e)
                .count() as i32;
            e * count
        })
        .sum();

    println!("Part Two: {}", res);
}
