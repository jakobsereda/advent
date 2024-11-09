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

    let map: HashMap<&str, i32> = MAX_NUMS.iter().cloned().collect();
    let mut sum = 0;

    for line in buf.lines() {
        let line = line?;
        if let Some(id) = get_id(&line) {
            if is_valid_game(&line, &map) { sum += id }
        }
    }

    println!("{}", sum);

    Ok(())
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