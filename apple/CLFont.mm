#include "CLFont.h"
#include "CLFontDef.h"

const CLFontDef &
CLFont::
getFontDef(char c)
{
  if (c >= ' ' && c <= '~')
    return lfont_defs[c - ' '];
  else
    return lfont_defs[0];
}
