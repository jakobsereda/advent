use std::{
    collections::HashSet,
    fs::File,
    io::{self, prelude::*, BufReader},
};

#[derive(Debug, Eq, PartialEq, Hash, Clone)]
enum Direction {
    Up,
    Right,
    Down,
    Left,
}

impl Direction {
    fn turn_right(&self) -> Self {
        match self {
            Direction::Up => Direction::Right,
            Direction::Right => Direction::Down,
            Direction::Down => Direction::Left,
            Direction::Left => Direction::Up,
        }
    }

    fn walk(&self, x: &mut usize, y: &mut usize) {
        match self {
            Direction::Up => *y = y.saturating_sub(1),
            Direction::Right => *x += 1,
            Direction::Down => *y += 1,
            Direction::Left => *x = x.saturating_sub(1),
        }
    }
}

fn main() -> io::Result<()> {
    let data = File::open("data/data.txt")?;
    let buf = BufReader::new(data);
    let lines = buf.lines().collect::<Result<Vec<String>, _>>()?;

    let map: Vec<Vec<i32>> = lines
        .iter()
        .map(|line| {
            line.chars()
                .filter_map(|c| match c {
                    '.' => Some(0),
                    '#' => Some(-1),
                    '^' => Some(1),
                    _ => None,
                })
                .collect::<Vec<i32>>()
        })
        .collect();

    let part_one_res = calculate_guard_path(&map);
    println!("Part One: {}", part_one_res.len());

    //let part_two_res = calculate_possible_blocks(&map);
    //println!("Part Two: {}", part_two_res);

    Ok(())
}

fn calculate_guard_path(map: &[Vec<i32>]) -> HashSet<(usize, usize)> {
    let mut visited: HashSet<(usize, usize)> = HashSet::new();
    let mut direction = Direction::Up;
    let mut x = 0;
    let mut y = 0;

    'a: for (j, row) in map.iter().enumerate() {
        for (i, &val) in row.iter().enumerate() {
            if val == 1 {
                x = i;
                y = j;
                break 'a;
            }
        }
    }

    visited.insert((x, y));

    loop {
        let mut dx = x;
        let mut dy = y;
        direction.walk(&mut dx, &mut dy);

        if dy >= map.len() || dx >= map[0].len() {
            break;
        }

        if map[dy][dx] == -1 {
            direction = direction.turn_right();
        } else {
            x = dx;
            y = dy;
            visited.insert((x, y));
        }
    }

    visited
}
