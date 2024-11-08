use std::fs::File;
use std::io::{
    self,
    prelude::*,
    BufReader
};

const MAX_RED: i32 = 12;
const MAX_BLUE: i32 = 14;
const MAX_GREEN: i32 = 13;

fn main() -> io::Result<()> {
    let data = File::open("data/data.txt")?;
    let buf = BufReader::new(data);

    let mut sum = 0;
    for line in buf.lines() {
        let line = line?;
        
        let id = line.split_whitespace()
            .nth(1)
            .and_then(|n| n.trim_end_matches(':').parse::<i32>().ok())
            .unwrap_or_default();

        let game= line.split(':')
            .last()
            .map(|s| s.trim_end().split(';').collect::<Vec<&str>>())
            .unwrap_or_default();

        let mut valid_line = true;

        for elm in game {
            let sets = elm.split(',')
                .map(|s| s.trim_end())
                .collect::<Vec<&str>>();

            let mut valid_game = true;

            for set in sets {
                let (n, color) = {
                    let mut pair = set.split_whitespace();
                    let n = pair.next().and_then(|n| n.parse::<i32>().ok())
                        .unwrap_or_default();
                    let color = pair.next()
                        .unwrap_or_default();
                    (n, color)
                };
                
                match color {
                    "red" => if n > MAX_RED { valid_game = false },
                    "blue" => if n > MAX_BLUE { valid_game = false },
                    "green" => if n > MAX_GREEN { valid_game = false },
                    _ => {}
                }
            }

            if !valid_game { 
                valid_line = false;
            }
        }

        if valid_line {
            sum += id;
        }
    }

    println!("{}", sum);

    Ok(())
}
