use std::{
    fs::File,
    io::{self, prelude::*, BufReader},
};

fn main() -> io::Result<()> {
    let data = File::open("data/data.txt")?;
    let buf = BufReader::new(data);
    let lines = buf.lines().collect::<Result<Vec<String>, _>>()?;

    let mut reports: Vec<Vec<i32>> = Vec::new();

    for line in lines {
        let report: Vec<i32> = line
            .split_whitespace()
            .map(|n| n.parse::<i32>().unwrap())
            .collect();
        reports.push(report);
    }

    // Part one!
    part_one(&reports);

    // Part two!
    part_two(&reports);

    Ok(())
}

fn part_one(reports: &[Vec<i32>]) {
    let count = reports.iter().filter(|r| is_safe_report(r)).count();
    println!("Part One: {}", count);
}

fn part_two(reports: &[Vec<i32>]) {
    let count = reports.iter().filter(|r| is_safe_with_dampener(r)).count();
    println!("Part Two: {}", count);
}

fn is_safe_report(report: &[i32]) -> bool {
    let is_increasing: bool = report
        .windows(2)
        .all(|w| w[1] - w[0] >= 1 && w[1] - w[0] <= 3);

    let is_decreasing: bool = report
        .windows(2)
        .all(|w| w[0] - w[1] >= 1 && w[0] - w[1] <= 3);

    is_increasing || is_decreasing
}

fn is_safe_with_dampener(report: &[i32]) -> bool {
    for i in 0..report.len() {
        let dampened_report: Vec<i32> = report
            .iter()
            .enumerate()
            .filter_map(|(index, &val)| if index == i { None } else { Some(val) })
            .collect();

        if is_safe_report(&dampened_report) {
            return true;
        }
    }

    false
}
