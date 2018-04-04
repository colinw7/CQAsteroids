#ifndef CVFONT_H
#define CVFONT_H

struct CLFontPoinfDef {
  double x, y;
};

struct CLFontLineDef {
  CLFontPoinfDef start;
  CLFontPoinfDef end;
};

struct CLFontDef {
  char           c;
  double         width;
  double         ascender;
  double         descender;
  int            num_lines;
  CLFontLineDef *lines;
};

class CLFont {
 public:
  static const CLFontDef &getFontDef(char c);

 private:
  CLFont() { }
};

#endif
