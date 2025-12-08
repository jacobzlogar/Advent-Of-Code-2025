#!/usr/bin/env cargo

use std::io::{self, BufRead, BufReader};
use std::fs::File;
use std::collections::HashSet;

type Result<T> = std::result::Result<T, Box<dyn std::error::Error>>;

fn main() -> Result<()> {
    let mut part_1 = 0;
    let mut part_2 = 0;

    let mut ranges: Vec<(usize, usize)> = Vec::new();
    let mut ingredients: Vec<usize> = Vec::new();
    let mut ids: Vec<(usize, usize)> = Vec::new();

    let mut file = File::open("day5.txt")?;
    let mut reader = BufReader::new(file);
    let mut lines = reader.lines();

    while let Some(Ok(line)) = lines.next() {
        if let Some((x, y)) = line.split_once('-') {
            ranges.push((x.parse::<usize>()?, y.parse::<usize>()?));
            continue;
        }
        if let Ok(n) = line.parse::<usize>() {
            ingredients.push(n);
        }
    }

    part_1 = ingredients.iter().fold(0, |mut acc, i| {
        let options = ranges
            .iter()
            .filter(|(x, y)| x <= i);

        if options.into_iter().any(|(ox, oy)| oy >= i) {
            acc += 1;
        }
        acc
    });

    ranges.sort_by_key(|r| r.0);

    let mut start = ranges[0].0;
    let mut end = ranges[0].1;

    for &(a, b) in &ranges[1..] {
        if a <= end + 1 { // are we still in an interval?
            end = end.max(b);
        } else {
            part_2 += end - start + 1; // found the end, incremenet part2
            start = a;
            end = b;
        }
    }

    part_2 += end - start + 1;

    println!("part 1 = {part_1}, part 2 = {part_2}");

    Ok(())
}
