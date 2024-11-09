use std::collections::HashMap;
use std::fs::File;
use std::io::{
    self,
    prelude::*,
    BufReader
};

const MAX_NUMS: &[(&str, i32)] = &[
    ("red", 12),
    ("blue", 14),
    ("green", 13),
];

fn main() -> io::Result<()> {
    let data = File::open("data/data.txt")?;
    let buf = BufReader::new(data);
    let lines = buf.lines().collect::<Result<Vec<String>, _>>()?;

    // Part one!
    // =========
    part_one(&lines);

    // Part two!
    // =========
    part_two(&lines);

    Ok(())
}

// ==================
// PART ONE FUNCTIONS
// ==================

fn part_one(lines: &[String]) {
    let map: HashMap<&str, i32> = MAX_NUMS.iter().cloned().collect();
    let mut sum = 0;

    for line in lines {
        if let Some(id) = get_id(&line) {
            if is_valid_game(&line, &map) { sum += id }
        }
    }

    println!("😍 Part One: {}", sum);
}

fn get_id(line: &str) -> Option<i32> {
    line.split_whitespace()
        .nth(1)
        .and_then(|n| n.trim_end_matches(':').parse::<i32>().ok())
}

fn is_valid_game(line: &str, map: &HashMap<&str, i32>) -> bool {
    line.split(':')
        .last()
        .map(|game| game.split(';').all(|set| is_valid_set(set, &map)))
        .unwrap_or(false)
}

fn is_valid_set(set: &str, map: &HashMap<&str, i32>) -> bool {
    set.split(',')
        .all(|cubes| {
            let mut pair = cubes.split_whitespace();
            let n = pair.next().and_then(|n| n.parse::<i32>().ok()).unwrap_or(0);
            let color = pair.next().unwrap_or("");
            map.get(color).map_or(true, |&max| n <= max)
        })
}

// ==================
// PART TWO FUNCTIONS
// ==================

fn part_two(lines: &[String]) {
    let mut sum = 0;

    for line in lines {
        sum += get_max_sets(line)
            .unwrap_or_default()
            .iter()
            .fold(1, |acc, &n| n * acc)
    }

    println!("😳 Part Two: {}", sum);
}

fn get_max_sets(line: &str) -> Option<Vec<i32>> {
    let mut ret: Vec<i32> = vec![i32::MIN; 3];

    line.split(':')
        .last()?
        .split(';')
        .for_each(|game| {
            let vals = vectorize_game(game);
            for (i, &val) in vals.iter().enumerate() {
                ret[i] = std::cmp::max(ret[i], val);
            }
        });

    Some(ret)
}

fn vectorize_game(game: &str) -> Vec<i32> {
    let mut maxes = vec![i32::MIN; 3];

    game.split(',')
        .for_each(|cubes| {
            let mut pair = cubes.split_whitespace();
            let n = pair.next().and_then(|n| n.parse::<i32>().ok()).unwrap_or(0);
            let color = pair.next().unwrap_or("");
            if let Some(index) = color_to_index(color) {
                maxes[index] = n;
            }
        });
    
    maxes
}

fn color_to_index(color: &str) -> Option<usize> {
    match color {
        "red" => Some(0),
        "blue" => Some(1),
        "green" => Some(2),
        _ => None,
    }
}