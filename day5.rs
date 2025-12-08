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

    let part_1: usize = ingredients.iter().fold(0, |mut acc, i| {
	let options = ranges
	    .iter()
	    .filter(|(x, y)| x <= i);

	if options.into_iter().any(|(ox, oy)| oy >= i) {
	    acc += 1;
	}
	acc
    });


    println!("part_1 = {part_1}");

    ranges.sort_by_key(|r| r.0);

    let part_2: usize = ranges.iter().enumerate().fold(0, |mut acc, (k, v)| {
	let prev_end = if k > 0 { ranges[k - 1].1 } else { 0 };
	let front = v.0.max(prev_end);

	if front <= v.1 {
	    acc += v.1 - front + 1;
	}
	acc
    });

    println!("part_2 = {part_2}");

    Ok(())
}
