#!/usr/bin/env cargo

use std::io::{self, BufRead, BufReader};
use std::fs::File;
use std::collections::HashSet;

type Result<T> = std::result::Result<T, Box<dyn std::error::Error>>;


fn main() -> Result<()> {
    let mut part_1 = 0;
    let mut part_2 = 0;

    let mut file = File::open("day6.txt")?;
    let mut reader = BufReader::new(file);
    let mut lines = reader.lines();

    while let Some(Ok(line)) = lines.next() {
    }
    Ok(())
}
