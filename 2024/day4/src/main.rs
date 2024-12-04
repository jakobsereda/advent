use std::{
    fs::File,
    io::{self, prelude::*, BufReader},
};

fn main() -> io::Result<()> {
    let data = File::open("data/data.txt")?;
    let buf = BufReader::new(data);
    let chars: Vec<Vec<char>> = buf
        .lines()
        .map(|line| line.unwrap().chars().collect())
        .collect();

    // Part one!
    part_one(&chars);

    // Part two!
    part_two(&chars);

    Ok(())
}

fn part_one(chars: &[Vec<char>]) {
    let res: i32 = search_all_xmas(chars);
    println!("Part One: {}", res);
}

fn part_two(chars: &[Vec<char>]) {
    let res = search_all_x_mas(chars);
    println!("Part Two: {}", res);
}

fn search_all_xmas(chars: &[Vec<char>]) -> i32 {
    let mut res = 0;
    let w = chars.len() as i32;
    let h = chars[0].len() as i32;

    let directions = [
        (1, 0),
        (1, 1),
        (0, 1),
        (-1, 0),
        (0, -1),
        (-1, -1),
        (-1, 1),
        (1, -1),
    ];

    for i in 0..w {
        for j in 0..h {
            for (di, dj) in &directions {
                res += find_xmas_from_pos(chars, 0, i, j, *di, *dj);
            }
        }
    }

    res
}

fn find_xmas_from_pos(chars: &[Vec<char>], idx: i32, i: i32, j: i32, di: i32, dj: i32) -> i32 {
    if idx == 4 {
        return 1;
    }

    let i_bound = chars.len() as i32;
    let j_bound = chars[0].len() as i32;
    if i < 0 || i >= i_bound || j < 0 || j >= j_bound {
        return 0;
    }

    let xmas = ['X', 'M', 'A', 'S'];
    if chars[i as usize][j as usize] != xmas[idx as usize] {
        return 0;
    }

    find_xmas_from_pos(chars, idx + 1, i + di, j + dj, di, dj)
}

fn search_all_x_mas(chars: &[Vec<char>]) -> i32 {
    let mut res = 0;
    let w = chars.len() as i32;
    let h = chars[0].len() as i32;

    for i in 0..w {
        for j in 0..h {
            if chars[i as usize][j as usize] == 'A' {
                res += find_x_mas_from_pos(chars, i, j);
            }
        }
    }

    res
}

fn find_x_mas_from_pos(chars: &[Vec<char>], i: i32, j: i32) -> i32 {
    let i_bound = chars.len() as i32 - 1;
    let j_bound = chars[0].len() as i32 - 1;
    if i >= j_bound || j >= i_bound || i <= 0 || j <= 0 {
        return 0;
    }

    let diag1 = [
        chars[(i - 1) as usize][(j - 1) as usize],
        chars[(i + 1) as usize][(j + 1) as usize],
    ];
    let diag2 = [
        chars[(i - 1) as usize][(j + 1) as usize],
        chars[(i + 1) as usize][(j - 1) as usize],
    ];

    let ms = ['M', 'S'];
    let sm = ['S', 'M'];
    if (diag1 == ms || diag1 == sm) && (diag2 == ms || diag2 == sm) {
        return 1;
    }

    0
}
