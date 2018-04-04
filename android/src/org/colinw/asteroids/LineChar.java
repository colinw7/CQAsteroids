package org.colinw.asteroids;

public class LineChar {
  public char   c;
  public double width;
  public double ascender;
  public double descender;
  public int    num_lines;
  public Line   lines[];
  
  LineChar(char c1, double width1, double ascender1, double descender1, int num_lines1, Line lines1[]) {
    c         = c1;
    width     = width1;
    ascender  = ascender1;
    descender = descender1;
    num_lines = num_lines1;
    lines     = lines1;
  }
}
