use std::{
    collections::{HashMap, HashSet},
    fs::File,
    io::{self, prelude::*, BufReader},
};

fn main() -> io::Result<()> {
    let data = File::open("data/data.txt")?;
    let buf = BufReader::new(data);
    let lines = buf.lines().collect::<Result<Vec<String>, _>>()?;

    let split_idx = lines.iter().position(|l| l.is_empty()).unwrap();
    let rules_str = &lines[0..split_idx];
    let updates_str = &lines[(split_idx + 1)..];

    let mut rules: HashMap<i32, HashSet<i32>> = HashMap::new();
    for rule in rules_str {
        let mut pair = rule.split('|');
        let first = pair.next().unwrap().parse::<i32>().unwrap();
        let second = pair.next().unwrap().parse::<i32>().unwrap();
        rules.entry(first).or_default().insert(second);
    }

    let updates: Vec<Vec<i32>> = updates_str
        .iter()
        .map(|line| {
            line.split(',')
                .map(|s| s.trim().parse::<i32>().unwrap())
                .collect::<Vec<i32>>()
        })
        .collect();

    let is_valid_update = |update: &[i32]| -> bool {
        let idx_map: HashMap<i32, usize> = update
            .iter()
            .enumerate()
            .map(|(idx, &n)| (n, idx))
            .collect();

        for (&key, set) in &rules {
            if idx_map.contains_key(&key) {
                for &i in set {
                    if let (Some(&a), Some(&b)) = (idx_map.get(&key), idx_map.get(&i)) {
                        if b < a {
                            return false;
                        }
                    }
                }
            }
        }

        true
    };

    let mut part_one_res = 0;
    for update in &updates {
        if is_valid_update(update) {
            let mid = update.len() / 2;
            part_one_res += update[mid];
        }
    }

    // Part one!
    println!("Part One: {}", part_one_res);

    let mut part_two_res = 0;
    for update in &updates {
        if !is_valid_update(update) {
            let mut reordered = update.clone();
            reordered.sort_by(|a, b| {
                if let Some(set) = rules.get(a) {
                    if set.contains(b) {
                        return std::cmp::Ordering::Less;
                    }
                }
                std::cmp::Ordering::Greater
            });
            let mid = reordered.len() / 2;
            part_two_res += reordered[mid];
        }
    }

    // Part two!
    println!("Part Two: {}", part_two_res);

    Ok(())
}
