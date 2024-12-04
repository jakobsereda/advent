use std::{
    fs::File,
    io::{self, BufReader, Read},
};

fn main() -> io::Result<()> {
    let data = File::open("data/data.txt")?;
    let mut buf = BufReader::new(data);
    let mut input = String::new();
    buf.read_to_string(&mut input)
        .expect("failed to read to string");

    // Part one!
    part_one(&input);

    // Part two!
    part_two(&input);

    Ok(())
}

fn part_one(input: &str) {
    let res: i32 = find_and_eval_muls(input).iter().sum();
    println!("Part One: {}", res);
}

fn part_two(input: &str) {
    let res: i32 = find_and_eval_with_blocks(input).iter().sum();
    println!("Part Two: {}", res);
}

fn find_and_eval_muls(input: &str) -> Vec<i32> {
    let mut res: Vec<i32> = Vec::new();
    let char_stream: Vec<char> = input.chars().collect();
    let mut i: usize = 0;

    while i < char_stream.len() {
        if char_stream[i..].starts_with(&['m', 'u', 'l', '(']) {
            let mut k = i + 4;
            let mut done_first = false;
            let mut num_one = String::new();
            let mut num_two = String::new();

            while k < char_stream.len() {
                match char_stream[k] {
                    '0'..='9' => {
                        if !done_first {
                            num_one.push(char_stream[k]);
                        } else {
                            num_two.push(char_stream[k]);
                        }
                    }
                    ',' => {
                        done_first = true;
                    }
                    ')' => {
                        if let (Ok(x), Ok(y)) = (num_one.parse::<i32>(), num_two.parse::<i32>()) {
                            res.push(x * y);
                        }
                        break;
                    }
                    _ => break,
                }

                k += 1;
            }

            i = k + 1;
        } else {
            i += 1;
        }
    }

    res
}

fn find_and_eval_with_blocks(input: &str) -> Vec<i32> {
    let mut res: Vec<i32> = Vec::new();
    let char_stream: Vec<char> = input.chars().collect();
    let mut i: usize = 0;
    let mut blocked = false;

    while i < char_stream.len() {
        if char_stream[i..].starts_with(&['d', 'o', '(', ')']) {
            i += 4;
            blocked = false;
        } else if char_stream[i..].starts_with(&['d', 'o', 'n', '\'', 't', '(', ')']) {
            i += 7;
            blocked = true;
        } else if !blocked && char_stream[i..].starts_with(&['m', 'u', 'l', '(']) {
            let mut k = i + 4;
            let mut done_first = false;
            let mut num_one = String::new();
            let mut num_two = String::new();

            while k < char_stream.len() {
                match char_stream[k] {
                    '0'..='9' => {
                        if !done_first {
                            num_one.push(char_stream[k]);
                        } else {
                            num_two.push(char_stream[k]);
                        }
                    }
                    ',' => {
                        done_first = true;
                    }
                    ')' => {
                        if let (Ok(x), Ok(y)) = (num_one.parse::<i32>(), num_two.parse::<i32>()) {
                            res.push(x * y);
                        }
                        break;
                    }
                    _ => break,
                }

                k += 1;
            }

            i = k + 1;
        } else {
            i += 1;
        }
    }

    res
}
