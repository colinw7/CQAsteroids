'use strict';

//------

function LFont () {
  this.charWidth   = 1.0;
  this.charAscent  = 1.0;
  this.charDescent = 0.5;
  this.charHeight  = this.charAscent + this.charDescent;

  this.xMargin  = 0.125;
  this.ySpacing = 0.1;   // ???

  this.delta = 0.0625;

  this.font_defs = [];

  this.start_cc = ' '.charCodeAt(0);
  this.end_cc   = '~'.charCodeAt(0);
}

LFont.prototype.init = function() {
  /*
    characters in 0,0 1,1 box

    descent = 0.5;

    left margin  = 0.125
    right margin = 0.125

    grid cell 0.0625 x 0.0625
  */
  var lines00 = [ /*   */
    new LFontLine(new Point(0.0000, 0.0000), new Point(0.0000, 0.0000)),
  ];
  var lines01 = [ /* ! */
    new LFontLine(new Point(0.5000, 1.0000), new Point(0.5000, 0.2500)),
    new LFontLine(new Point(0.5000, 0.2500), new Point(0.5000, 1.0000)),
    new LFontLine(new Point(0.5000, 0.1250), new Point(0.5000, 0.0000)),
    new LFontLine(new Point(0.5000, 0.1250), new Point(0.5000, 0.0000))
  ];
  var lines02 = [ /* " */
    new LFontLine(new Point(0.3750, 1.0000), new Point(0.3750, 0.8750)),
    new LFontLine(new Point(0.3750, 1.0000), new Point(0.3750, 0.8750)),
    new LFontLine(new Point(0.6250, 1.0000), new Point(0.6250, 0.8750)),
    new LFontLine(new Point(0.6250, 1.0000), new Point(0.6250, 0.8750)),
    new LFontLine(new Point(0.6875, 0.9375), new Point(0.5625, 0.7500)),
    new LFontLine(new Point(0.4375, 0.9375), new Point(0.3125, 0.7500))
  ];
  var lines03 = [ /* # */
    new LFontLine(new Point(0.3750, 0.0000), new Point(0.3750, 1.0000)),
    new LFontLine(new Point(0.6250, 0.0000), new Point(0.6250, 1.0000)),
    new LFontLine(new Point(0.1250, 0.3750), new Point(0.8750, 0.3750)),
    new LFontLine(new Point(0.1250, 0.6250), new Point(0.8750, 0.6250))
  ];
  var lines04 = [ /* $ */
    new LFontLine(new Point(0.3750, 0.0000), new Point(0.3750, 1.0000)),
    new LFontLine(new Point(0.6250, 0.0000), new Point(0.6250, 1.0000)),
    new LFontLine(new Point(0.1250, 0.7500), new Point(0.8750, 0.2500)),
    new LFontLine(new Point(0.5000, 0.0000), new Point(0.1250, 0.2500)),
    new LFontLine(new Point(0.5000, 1.0000), new Point(0.1250, 0.7500)),
    new LFontLine(new Point(0.8750, 0.2500), new Point(0.5000, 0.0000)),
    new LFontLine(new Point(0.8750, 0.7500), new Point(0.5000, 1.0000))
  ];
  var lines05 = [ /* % */
    new LFontLine(new Point(0.1250, 0.0000), new Point(0.8750, 1.0000)),
    new LFontLine(new Point(0.1250, 0.8750), new Point(0.2500, 1.0000)),
    new LFontLine(new Point(0.2500, 1.0000), new Point(0.3750, 0.8750)),
    new LFontLine(new Point(0.3750, 0.8750), new Point(0.2500, 0.7500)),
    new LFontLine(new Point(0.2500, 0.7500), new Point(0.1250, 0.8750)),
    new LFontLine(new Point(0.7500, 0.0000), new Point(0.8750, 0.1250)),
    new LFontLine(new Point(0.8750, 0.1250), new Point(0.7500, 0.2500)),
    new LFontLine(new Point(0.7500, 0.2500), new Point(0.6250, 0.1250)),
    new LFontLine(new Point(0.6250, 0.1250), new Point(0.7500, 0.0000))
  ];
  var lines06 = [ /* & */
    new LFontLine(new Point(0.3125, 0.0000), new Point(0.5000, 0.0000)),
    new LFontLine(new Point(0.8750, 0.0000), new Point(0.2500, 0.7500)),
    new LFontLine(new Point(0.2500, 0.4375), new Point(0.5625, 0.7500)),
    new LFontLine(new Point(0.1250, 0.1875), new Point(0.3125, 0.0000)),
    new LFontLine(new Point(0.2500, 0.4375), new Point(0.1250, 0.1875)),
    new LFontLine(new Point(0.4375, 1.0000), new Point(0.2500, 0.7500)),
    new LFontLine(new Point(0.5625, 0.7500), new Point(0.4375, 1.0000)),
    new LFontLine(new Point(0.8750, 0.5000), new Point(0.5000, 0.0000))
  ];
  var lines07 = [ /* ' */
    new LFontLine(new Point(0.5000, 1.0000), new Point(0.5000, 0.8750)),
    new LFontLine(new Point(0.5000, 1.0000), new Point(0.5000, 0.8750)),
    new LFontLine(new Point(0.5625, 0.9375), new Point(0.4375, 0.7500))
  ];
  var lines08 = [ /* ( */
    new LFontLine(new Point(0.6250, 1.0000), new Point(0.6250, 0.0000))
  ];
  var lines09 = [ /* ) */
    new LFontLine(new Point(0.3750, 1.0000), new Point(0.3750, 0.0000))
  ];
  var lines10 = [ /* * */
    new LFontLine(new Point(0.5000, 0.5000), new Point(0.5000, 0.7500)),
    new LFontLine(new Point(0.5000, 0.5000), new Point(0.2500, 0.6250)),
    new LFontLine(new Point(0.5000, 0.5000), new Point(0.7500, 0.6250)),
    new LFontLine(new Point(0.5000, 0.5000), new Point(0.2500, 0.2500)),
    new LFontLine(new Point(0.5000, 0.5000), new Point(0.7500, 0.2500))
  ];
  var lines11 = [ /* + */
    new LFontLine(new Point(0.2500, 0.5000), new Point(0.7500, 0.5000)),
    new LFontLine(new Point(0.5000, 0.2500), new Point(0.5000, 0.7500))
  ];
  var lines12 = [ /* , */
    new LFontLine(new Point(0.5000, 0.0000), new Point(0.5000, 0.1250)),
    new LFontLine(new Point(0.5000, 0.1250), new Point(0.5000, 0.0000)),
    new LFontLine(new Point(0.5625, 0.0625), new Point(0.4375,-0.1875))
  ];
  var lines13 = [ /* - */
    new LFontLine(new Point(0.2500, 0.5000), new Point(0.7500, 0.5000))
  ];
  var lines14 = [ /* . */
    new LFontLine(new Point(0.5000, 0.1250), new Point(0.5000, 0.0000)),
    new LFontLine(new Point(0.5000, 0.1250), new Point(0.5000, 0.0000))
  ];
  var lines15 = [ /* / */
    new LFontLine(new Point(0.1250, 0.0000), new Point(0.8750, 1.0000))
  ];
  var lines16 = [ /* 0 */
    new LFontLine(new Point(0.3750, 1.0000), new Point(0.6250, 1.0000)),
    new LFontLine(new Point(0.1250, 0.7500), new Point(0.1250, 0.2500)),
    new LFontLine(new Point(0.8750, 0.7500), new Point(0.8750, 0.2500)),
    new LFontLine(new Point(0.3750, 0.0000), new Point(0.6250, 0.0000)),
    new LFontLine(new Point(0.1250, 0.0000), new Point(0.8750, 1.0000)),
    new LFontLine(new Point(0.3750, 0.0000), new Point(0.1250, 0.2500)),
    new LFontLine(new Point(0.1250, 0.7500), new Point(0.3750, 1.0000)),
    new LFontLine(new Point(0.6250, 1.0000), new Point(0.8750, 0.7500)),
    new LFontLine(new Point(0.6250, 0.0000), new Point(0.8750, 0.2500))
  ];
  var lines17 = [ /* 1 */
    new LFontLine(new Point(0.2500, 0.0000), new Point(0.7500, 0.0000)),
    new LFontLine(new Point(0.5000, 0.0000), new Point(0.5000, 1.0000)),
    new LFontLine(new Point(0.5000, 1.0000), new Point(0.3125, 0.7500))
  ];
  var lines18 = [ /* 2 */
    new LFontLine(new Point(0.1250, 0.0000), new Point(0.8750, 0.0000)),
    new LFontLine(new Point(0.5000, 1.0000), new Point(0.1250, 0.7500)),
    new LFontLine(new Point(0.5000, 1.0000), new Point(0.8750, 0.7500)),
    new LFontLine(new Point(0.8750, 0.7500), new Point(0.5000, 0.5000)),
    new LFontLine(new Point(0.1250, 0.0000), new Point(0.5000, 0.5000))
  ];
  var lines19 = [ /* 3 */
    new LFontLine(new Point(0.3750, 0.5000), new Point(0.5000, 0.5000)),
    new LFontLine(new Point(0.1250, 0.7500), new Point(0.5000, 1.0000)),
    new LFontLine(new Point(0.5000, 1.0000), new Point(0.8750, 0.7500)),
    new LFontLine(new Point(0.8750, 0.2500), new Point(0.5000, 0.0000)),
    new LFontLine(new Point(0.5000, 0.0000), new Point(0.1250, 0.2500)),
    new LFontLine(new Point(0.8750, 0.7500), new Point(0.5000, 0.5000)),
    new LFontLine(new Point(0.5000, 0.5000), new Point(0.8750, 0.2500))
  ];
  var lines20 = [ /* 4 */
    new LFontLine(new Point(0.6250, 0.0000), new Point(0.6250, 1.0000)),
    new LFontLine(new Point(0.6250, 1.0000), new Point(0.5000, 1.0000)),
    new LFontLine(new Point(0.5000, 1.0000), new Point(0.1250, 0.5000)),
    new LFontLine(new Point(0.1250, 0.5000), new Point(0.1250, 0.3750)),
    new LFontLine(new Point(0.1250, 0.3750), new Point(0.8750, 0.3750))
  ];
  var lines21 = [ /* 5 */
    new LFontLine(new Point(0.1250, 0.5000), new Point(0.1875, 1.0000)),
    new LFontLine(new Point(0.1875, 1.0000), new Point(0.8750, 1.0000)),
    new LFontLine(new Point(0.5000, 0.6250), new Point(0.8750, 0.3125)),
    new LFontLine(new Point(0.8750, 0.3125), new Point(0.5000, 0.0000)),
    new LFontLine(new Point(0.1250, 0.2500), new Point(0.5000, 0.0000)),
    new LFontLine(new Point(0.1250, 0.5000), new Point(0.5000, 0.6250))
  ];
  var lines22 = [ /* 6 */
    new LFontLine(new Point(0.1250, 0.6250), new Point(0.1250, 0.3125)),
    new LFontLine(new Point(0.1250, 0.6250), new Point(0.5000, 1.0000)),
    new LFontLine(new Point(0.5000, 1.0000), new Point(0.8750, 0.7500)),
    new LFontLine(new Point(0.1250, 0.3125), new Point(0.5000, 0.0000)),
    new LFontLine(new Point(0.5000, 0.0000), new Point(0.8750, 0.3125)),
    new LFontLine(new Point(0.8750, 0.3125), new Point(0.5000, 0.5625)),
    new LFontLine(new Point(0.1250, 0.3125), new Point(0.5000, 0.5625))
  ];
  var lines23 = [ /* 7 */
    new LFontLine(new Point(0.1250, 1.0000), new Point(0.8750, 1.0000)),
    new LFontLine(new Point(0.8750, 1.0000), new Point(0.3750, 0.0000))
  ];
  var lines24 = [ /* 8 */
    new LFontLine(new Point(0.5000, 1.0000), new Point(0.1250, 0.7500)),
    new LFontLine(new Point(0.1250, 0.7500), new Point(0.5000, 0.5000)),
    new LFontLine(new Point(0.5000, 0.5000), new Point(0.1250, 0.2500)),
    new LFontLine(new Point(0.1250, 0.2500), new Point(0.5000, 0.0000)),
    new LFontLine(new Point(0.5000, 0.5000), new Point(0.8750, 0.2500)),
    new LFontLine(new Point(0.8750, 0.2500), new Point(0.5000, 0.0000)),
    new LFontLine(new Point(0.5000, 0.5000), new Point(0.8750, 0.7500)),
    new LFontLine(new Point(0.8750, 0.7500), new Point(0.5000, 1.0000))
  ];
  var lines25 = [ /* 9 */
    new LFontLine(new Point(0.8750, 0.7500), new Point(0.8750, 0.3750)),
    new LFontLine(new Point(0.1250, 0.7500), new Point(0.1250, 0.6875)),
    new LFontLine(new Point(0.5000, 1.0000), new Point(0.1250, 0.7500)),
    new LFontLine(new Point(0.1250, 0.2500), new Point(0.5000, 0.0000)),
    new LFontLine(new Point(0.5000, 0.0000), new Point(0.8750, 0.3750)),
    new LFontLine(new Point(0.8750, 0.7500), new Point(0.5000, 1.0000)),
    new LFontLine(new Point(0.1250, 0.6875), new Point(0.5000, 0.4375)),
    new LFontLine(new Point(0.5000, 0.4375), new Point(0.8750, 0.6875))
  ];
  var lines26 = [ /* : */
    new LFontLine(new Point(0.5000, 0.7500), new Point(0.5000, 0.6250)),
    new LFontLine(new Point(0.5000, 0.7500), new Point(0.5000, 0.6250)),
    new LFontLine(new Point(0.5000, 0.3750), new Point(0.5000, 0.2500)),
    new LFontLine(new Point(0.5000, 0.3750), new Point(0.5000, 0.2500))
  ];
  var lines27 = [ /* ; */
    new LFontLine(new Point(0.5000, 0.7500), new Point(0.5000, 0.6250)),
    new LFontLine(new Point(0.5000, 0.7500), new Point(0.5000, 0.6250)),
    new LFontLine(new Point(0.5000, 0.3750), new Point(0.5000, 0.2500)),
    new LFontLine(new Point(0.5000, 0.3750), new Point(0.5000, 0.2500)),
    new LFontLine(new Point(0.5625, 0.3125), new Point(0.4375, 0.1250))
  ];
  var lines28 = [ /* < */
    new LFontLine(new Point(0.7500, 0.0000), new Point(0.2500, 0.5000)),
    new LFontLine(new Point(0.2500, 0.5000), new Point(0.7500, 1.0000))
  ];
  var lines29 = [ /* = */
    new LFontLine(new Point(0.2500, 0.3750), new Point(0.7500, 0.3750)),
    new LFontLine(new Point(0.2500, 0.6250), new Point(0.7500, 0.6250))
  ];
  var lines30 = [ /* > */
    new LFontLine(new Point(0.2500, 0.0000), new Point(0.7500, 0.5000)),
    new LFontLine(new Point(0.7500, 0.5000), new Point(0.2500, 1.0000))
  ];
  var lines31 = [ /* ? */
    new LFontLine(new Point(0.5000, 0.4375), new Point(0.5000, 0.2500)),
    new LFontLine(new Point(0.2500, 0.7500), new Point(0.5000, 1.0000)),
    new LFontLine(new Point(0.5000, 1.0000), new Point(0.7500, 0.7500)),
    new LFontLine(new Point(0.7500, 0.7500), new Point(0.5000, 0.4375)),
    new LFontLine(new Point(0.5000, 0.1250), new Point(0.5000, 0.0000)),
    new LFontLine(new Point(0.5000, 0.1250), new Point(0.5000, 0.0000))
  ];
  var lines32 = [ /* @ */
    new LFontLine(new Point(0.6250, 0.6875), new Point(0.6250, 0.3125)),
    new LFontLine(new Point(0.6250, 0.6250), new Point(0.3750, 0.6250)),
    new LFontLine(new Point(0.3750, 0.6250), new Point(0.3750, 0.3750)),
    new LFontLine(new Point(0.3750, 0.3750), new Point(0.6250, 0.3750)),
    new LFontLine(new Point(0.6250, 0.3125), new Point(0.8750, 0.5000)),
    new LFontLine(new Point(0.1250, 0.5000), new Point(0.5000, 0.0000)),
    new LFontLine(new Point(0.8750, 0.5000), new Point(0.5000, 1.0000)),
    new LFontLine(new Point(0.5000, 1.0000), new Point(0.1250, 0.5000)),
    new LFontLine(new Point(0.5000, 0.0000), new Point(0.7500, 0.1250))
  ];
  var lines33 = [ /* A */
    new LFontLine(new Point(0.1250, 0.0000), new Point(0.5000, 1.0000)),
    new LFontLine(new Point(0.5000, 1.0000), new Point(0.8750, 0.0000)),
    new LFontLine(new Point(0.3125, 0.5000), new Point(0.6875, 0.5000))
  ];
  var lines34 = [ /* B */
    new LFontLine(new Point(0.1250, 0.0000), new Point(0.6250, 0.0000)),
    new LFontLine(new Point(0.6250, 1.0000), new Point(0.1250, 1.0000)),
    new LFontLine(new Point(0.1250, 1.0000), new Point(0.1250, 0.0000)),
    new LFontLine(new Point(0.1250, 0.5000), new Point(0.6250, 0.5000)),
    new LFontLine(new Point(0.6250, 1.0000), new Point(0.8750, 0.7500)),
    new LFontLine(new Point(0.8750, 0.7500), new Point(0.6250, 0.5000)),
    new LFontLine(new Point(0.6250, 0.5000), new Point(0.8750, 0.2500)),
    new LFontLine(new Point(0.8750, 0.2500), new Point(0.6250, 0.0000))
  ];
  var lines35 = [ /* C */
    new LFontLine(new Point(0.3750, 1.0000), new Point(0.6250, 1.0000)),
    new LFontLine(new Point(0.1250, 0.7500), new Point(0.1250, 0.2500)),
    new LFontLine(new Point(0.3750, 0.0000), new Point(0.6250, 0.0000)),
    new LFontLine(new Point(0.8750, 0.7500), new Point(0.6250, 1.0000)),
    new LFontLine(new Point(0.3750, 1.0000), new Point(0.1250, 0.7500)),
    new LFontLine(new Point(0.1250, 0.2500), new Point(0.3750, 0.0000)),
    new LFontLine(new Point(0.8750, 0.2500), new Point(0.6250, 0.0000))
  ];
  var lines36 = [ /* D */
    new LFontLine(new Point(0.1250, 0.0000), new Point(0.6250, 0.0000)),
    new LFontLine(new Point(0.6250, 1.0000), new Point(0.1250, 1.0000)),
    new LFontLine(new Point(0.1250, 1.0000), new Point(0.1250, 0.0000)),
    new LFontLine(new Point(0.8750, 0.7500), new Point(0.8750, 0.2500)),
    new LFontLine(new Point(0.6250, 1.0000), new Point(0.8750, 0.7500)),
    new LFontLine(new Point(0.8750, 0.2500), new Point(0.6250, 0.0000))
  ];
  var lines37 = [ /* E */
    new LFontLine(new Point(0.1250, 0.0000), new Point(0.8750, 0.0000)),
    new LFontLine(new Point(0.1250, 0.5000), new Point(0.5000, 0.5000)),
    new LFontLine(new Point(0.1250, 1.0000), new Point(0.8750, 1.0000)),
    new LFontLine(new Point(0.1250, 0.0000), new Point(0.1250, 1.0000))
  ];
  var lines38 = [ /* F */
    new LFontLine(new Point(0.1250, 0.5000), new Point(0.5000, 0.5000)),
    new LFontLine(new Point(0.1250, 1.0000), new Point(0.8750, 1.0000)),
    new LFontLine(new Point(0.1250, 0.0000), new Point(0.1250, 1.0000))
  ];
  var lines39 = [ /* G */
    new LFontLine(new Point(0.5000, 0.5000), new Point(0.8750, 0.5000)),
    new LFontLine(new Point(0.8750, 0.5000), new Point(0.8750, 0.0000)),
    new LFontLine(new Point(0.6250, 0.0000), new Point(0.3750, 0.0000)),
    new LFontLine(new Point(0.1250, 0.2500), new Point(0.1250, 0.7500)),
    new LFontLine(new Point(0.3750, 1.0000), new Point(0.6250, 1.0000)),
    new LFontLine(new Point(0.1250, 0.7500), new Point(0.3750, 1.0000)),
    new LFontLine(new Point(0.1250, 0.2500), new Point(0.3750, 0.0000)),
    new LFontLine(new Point(0.8750, 0.2500), new Point(0.6250, 0.0000)),
    new LFontLine(new Point(0.6250, 1.0000), new Point(0.8750, 0.7500))
  ];
  var lines40 = [ /* H */
    new LFontLine(new Point(0.1250, 0.0000), new Point(0.1250, 1.0000)),
    new LFontLine(new Point(0.8750, 0.0000), new Point(0.8750, 1.0000)),
    new LFontLine(new Point(0.1250, 0.5000), new Point(0.8750, 0.5000))
  ];
  var lines41 = [ /* I */
    new LFontLine(new Point(0.5000, 0.0000), new Point(0.5000, 1.0000)),
    new LFontLine(new Point(0.3750, 0.0000), new Point(0.6250, 0.0000)),
    new LFontLine(new Point(0.3750, 1.0000), new Point(0.6250, 1.0000))
  ];
  var lines42 = [ /* J */
    new LFontLine(new Point(0.2500, 1.0000), new Point(0.7500, 1.0000)),
    new LFontLine(new Point(0.6250, 0.2500), new Point(0.6250, 1.0000)),
    new LFontLine(new Point(0.2500, 0.2500), new Point(0.4375, 0.0000)),
    new LFontLine(new Point(0.4375, 0.0000), new Point(0.6250, 0.2500))
  ];
  var lines43 = [ /* K */
    new LFontLine(new Point(0.1250, 0.0000), new Point(0.1250, 1.0000)),
    new LFontLine(new Point(0.3750, 0.5000), new Point(0.8750, 0.0000)),
    new LFontLine(new Point(0.1250, 0.2500), new Point(0.8750, 1.0000))
  ];
  var lines44 = [ /* L */
    new LFontLine(new Point(0.1250, 0.0000), new Point(0.1250, 1.0000)),
    new LFontLine(new Point(0.1250, 0.0000), new Point(0.8750, 0.0000))
  ];
  var lines45 = [ /* M */
    new LFontLine(new Point(0.1250, 0.0000), new Point(0.1250, 1.0000)),
    new LFontLine(new Point(0.1250, 1.0000), new Point(0.5000, 0.5000)),
    new LFontLine(new Point(0.5000, 0.5000), new Point(0.8750, 1.0000)),
    new LFontLine(new Point(0.8750, 1.0000), new Point(0.8750, 0.0000))
  ];
  var lines46 = [ /* N */
    new LFontLine(new Point(0.1250, 0.0000), new Point(0.1250, 1.0000)),
    new LFontLine(new Point(0.1250, 1.0000), new Point(0.8750, 0.0000)),
    new LFontLine(new Point(0.8750, 0.0000), new Point(0.8750, 1.0000))
  ];
  var lines47 = [ /* O */
    new LFontLine(new Point(0.3750, 0.0000), new Point(0.6250, 0.0000)),
    new LFontLine(new Point(0.3750, 1.0000), new Point(0.6250, 1.0000)),
    new LFontLine(new Point(0.1250, 0.2500), new Point(0.1250, 0.7500)),
    new LFontLine(new Point(0.8750, 0.2500), new Point(0.8750, 0.7500)),
    new LFontLine(new Point(0.1250, 0.7500), new Point(0.3750, 1.0000)),
    new LFontLine(new Point(0.3750, 0.0000), new Point(0.1250, 0.2500)),
    new LFontLine(new Point(0.6250, 1.0000), new Point(0.8750, 0.7500)),
    new LFontLine(new Point(0.8750, 0.2500), new Point(0.6250, 0.0000))
  ];
  var lines48 = [ /* P */
    new LFontLine(new Point(0.1250, 0.0000), new Point(0.1250, 1.0000)),
    new LFontLine(new Point(0.1250, 1.0000), new Point(0.6250, 1.0000)),
    new LFontLine(new Point(0.6250, 0.5000), new Point(0.1250, 0.5000)),
    new LFontLine(new Point(0.6250, 1.0000), new Point(0.8750, 0.7500)),
    new LFontLine(new Point(0.8750, 0.7500), new Point(0.6250, 0.5000))
  ];
  var lines49 = [ /* Q */
    new LFontLine(new Point(0.8750, 0.0000), new Point(0.6250, 0.2500)),
    new LFontLine(new Point(0.3750, 1.0000), new Point(0.6250, 1.0000)),
    new LFontLine(new Point(0.1250, 0.7500), new Point(0.1250, 0.2500)),
    new LFontLine(new Point(0.8750, 0.7500), new Point(0.8750, 0.2500)),
    new LFontLine(new Point(0.3750, 0.0000), new Point(0.6250, 0.0000)),
    new LFontLine(new Point(0.3750, 1.0000), new Point(0.1250, 0.7500)),
    new LFontLine(new Point(0.1250, 0.2500), new Point(0.3750, 0.0000)),
    new LFontLine(new Point(0.6250, 1.0000), new Point(0.8750, 0.7500)),
    new LFontLine(new Point(0.8750, 0.2500), new Point(0.6250, 0.0000))
  ];
  var lines50 = [ /* R */
    new LFontLine(new Point(0.1250, 0.0000), new Point(0.1250, 1.0000)),
    new LFontLine(new Point(0.6250, 0.5000), new Point(0.1250, 0.5000)),
    new LFontLine(new Point(0.5000, 0.5000), new Point(0.8750, 0.0000)),
    new LFontLine(new Point(0.1250, 1.0000), new Point(0.6250, 1.0000)),
    new LFontLine(new Point(0.6250, 0.5000), new Point(0.8750, 0.7500)),
    new LFontLine(new Point(0.8750, 0.7500), new Point(0.6250, 1.0000))
  ];
  var lines51 = [ /* S */
    new LFontLine(new Point(0.3750, 0.0000), new Point(0.6250, 0.0000)),
    new LFontLine(new Point(0.6250, 0.5000), new Point(0.3750, 0.5000)),
    new LFontLine(new Point(0.3750, 1.0000), new Point(0.6250, 1.0000)),
    new LFontLine(new Point(0.3750, 1.0000), new Point(0.1250, 0.7500)),
    new LFontLine(new Point(0.1250, 0.7500), new Point(0.3750, 0.5000)),
    new LFontLine(new Point(0.6250, 0.5000), new Point(0.8750, 0.2500)),
    new LFontLine(new Point(0.8750, 0.2500), new Point(0.6250, 0.0000)),
    new LFontLine(new Point(0.3750, 0.0000), new Point(0.1250, 0.2500)),
    new LFontLine(new Point(0.6250, 1.0000), new Point(0.8750, 0.7500))
  ];
  var lines52 = [ /* T */
    new LFontLine(new Point(0.5000, 0.0000), new Point(0.5000, 1.0000)),
    new LFontLine(new Point(0.1250, 1.0000), new Point(0.8750, 1.0000))
  ];
  var lines53 = [ /* U */
    new LFontLine(new Point(0.1250, 1.0000), new Point(0.1250, 0.2500)),
    new LFontLine(new Point(0.3750, 0.0000), new Point(0.6250, 0.0000)),
    new LFontLine(new Point(0.8750, 0.2500), new Point(0.8750, 1.0000)),
    new LFontLine(new Point(0.1250, 0.2500), new Point(0.3750, 0.0000)),
    new LFontLine(new Point(0.8750, 0.2500), new Point(0.6250, 0.0000))
  ];
  var lines54 = [ /* V */
    new LFontLine(new Point(0.1250, 1.0000), new Point(0.5000, 0.0000)),
    new LFontLine(new Point(0.5000, 0.0000), new Point(0.8750, 1.0000))
  ];
  var lines55 = [ /* W */
    new LFontLine(new Point(0.1250, 1.0000), new Point(0.3125, 0.0000)),
    new LFontLine(new Point(0.3125, 0.0000), new Point(0.5000, 0.5000)),
    new LFontLine(new Point(0.5000, 0.5000), new Point(0.6875, 0.0000)),
    new LFontLine(new Point(0.6875, 0.0000), new Point(0.8750, 1.0000))
  ];
  var lines56 = [ /* X */
    new LFontLine(new Point(0.1250, 0.0000), new Point(0.8750, 1.0000)),
    new LFontLine(new Point(0.1250, 1.0000), new Point(0.8750, 0.0000))
  ];
  var lines57 = [ /* Y */
    new LFontLine(new Point(0.5000, 0.0000), new Point(0.5000, 0.5000)),
    new LFontLine(new Point(0.5000, 0.5000), new Point(0.1250, 1.0000)),
    new LFontLine(new Point(0.5000, 0.5000), new Point(0.8750, 1.0000))
  ];
  var lines58 = [ /* Z */
    new LFontLine(new Point(0.1250, 1.0000), new Point(0.8750, 1.0000)),
    new LFontLine(new Point(0.8750, 1.0000), new Point(0.1250, 0.0000)),
    new LFontLine(new Point(0.1250, 0.0000), new Point(0.8750, 0.0000))
  ];
  var lines59 = [ /* [ */
    new LFontLine(new Point(0.6250, 0.0000), new Point(0.3750, 0.0000)),
    new LFontLine(new Point(0.3750, 0.0000), new Point(0.3750, 1.0000)),
    new LFontLine(new Point(0.3750, 1.0000), new Point(0.6250, 1.0000))
  ];
  var lines60 = [ /* \ */
    new LFontLine(new Point(0.1250, 1.0000), new Point(0.8750, 0.0000))
  ];
  var lines61 = [ /* ] */
    new LFontLine(new Point(0.3750, 0.0000), new Point(0.6250, 0.0000)),
    new LFontLine(new Point(0.6250, 0.0000), new Point(0.6250, 1.0000)),
    new LFontLine(new Point(0.6250, 1.0000), new Point(0.3750, 1.0000))
  ];
  var lines62 = [ /* ^ */
    new LFontLine(new Point(0.2500, 0.7500), new Point(0.5000, 1.0000)),
    new LFontLine(new Point(0.5000, 1.0000), new Point(0.7500, 0.7500))
  ];
  var lines63 = [ /* _ */
    new LFontLine(new Point(0.1250, 0.0000), new Point(0.8750, 0.0000))
  ];
  var lines64 = [ /* ` */
    new LFontLine(new Point(0.5000, 1.0000), new Point(0.5000, 0.8750)),
    new LFontLine(new Point(0.5000, 1.0000), new Point(0.5000, 0.8750)),
    new LFontLine(new Point(0.5625, 0.7500), new Point(0.4375, 0.9375))
  ];
  var lines65 = [ /* a */
    new LFontLine(new Point(0.7500, 0.3750), new Point(0.7500, 0.0000)),
    new LFontLine(new Point(0.5000, 0.2500), new Point(0.2500, 0.1250)),
    new LFontLine(new Point(0.2500, 0.1250), new Point(0.5000, 0.0000)),
    new LFontLine(new Point(0.5000, 0.0000), new Point(0.7500, 0.1250)),
    new LFontLine(new Point(0.7500, 0.1250), new Point(0.5000, 0.2500)),
    new LFontLine(new Point(0.7500, 0.3750), new Point(0.5000, 0.5000)),
    new LFontLine(new Point(0.5000, 0.5000), new Point(0.2500, 0.3750))
  ];
  var lines66 = [ /* b */
    new LFontLine(new Point(0.2500, 0.0000), new Point(0.2500, 1.0000)),
    new LFontLine(new Point(0.5000, 0.5000), new Point(0.7500, 0.2500)),
    new LFontLine(new Point(0.7500, 0.2500), new Point(0.5000, 0.0000)),
    new LFontLine(new Point(0.5000, 0.0000), new Point(0.2500, 0.2500)),
    new LFontLine(new Point(0.2500, 0.2500), new Point(0.5000, 0.5000))
  ];
  var lines67 = [ /* c */
    new LFontLine(new Point(0.2500, 0.2500), new Point(0.5000, 0.5000)),
    new LFontLine(new Point(0.2500, 0.2500), new Point(0.5000, 0.0000)),
    new LFontLine(new Point(0.5000, 0.0000), new Point(0.7500, 0.1250)),
    new LFontLine(new Point(0.7500, 0.3750), new Point(0.5000, 0.5000))
  ];
  var lines68 = [ /* d */
    new LFontLine(new Point(0.7500, 0.0000), new Point(0.7500, 1.0000)),
    new LFontLine(new Point(0.7500, 0.2500), new Point(0.5000, 0.5000)),
    new LFontLine(new Point(0.5000, 0.5000), new Point(0.2500, 0.2500)),
    new LFontLine(new Point(0.2500, 0.2500), new Point(0.5000, 0.0000)),
    new LFontLine(new Point(0.5000, 0.0000), new Point(0.7500, 0.2500))
  ];
  var lines69 = [ /* e */
    new LFontLine(new Point(0.2500, 0.2500), new Point(0.7500, 0.2500)),
    new LFontLine(new Point(0.7500, 0.2500), new Point(0.5000, 0.5000)),
    new LFontLine(new Point(0.5000, 0.5000), new Point(0.2500, 0.2500)),
    new LFontLine(new Point(0.2500, 0.2500), new Point(0.5000, 0.0000)),
    new LFontLine(new Point(0.5000, 0.0000), new Point(0.7500, 0.1250))
  ];
  var lines70 = [ /* f */
    new LFontLine(new Point(0.3750, 0.0000), new Point(0.3750, 0.7500)),
    new LFontLine(new Point(0.3750, 0.5000), new Point(0.5625, 0.5000)),
    new LFontLine(new Point(0.3750, 0.7500), new Point(0.5000, 1.0000)),
    new LFontLine(new Point(0.5000, 1.0000), new Point(0.6250, 0.8125))
  ];
  var lines71 = [ /* g */
    new LFontLine(new Point(0.7500,-0.2500), new Point(0.7500, 0.5000)),
    new LFontLine(new Point(0.2500, 0.2500), new Point(0.5000, 0.5000)),
    new LFontLine(new Point(0.5000, 0.5000), new Point(0.7500, 0.2500)),
    new LFontLine(new Point(0.7500, 0.2500), new Point(0.5000, 0.0000)),
    new LFontLine(new Point(0.5000, 0.0000), new Point(0.2500, 0.2500)),
    new LFontLine(new Point(0.7500,-0.2500), new Point(0.5000,-0.5000)),
    new LFontLine(new Point(0.5000,-0.5000), new Point(0.2500,-0.2500))
  ];
  var lines72 = [ /* h */
    new LFontLine(new Point(0.2500, 0.0000), new Point(0.2500, 1.0000)),
    new LFontLine(new Point(0.7500, 0.2500), new Point(0.7500, 0.0000)),
    new LFontLine(new Point(0.2500, 0.2500), new Point(0.5000, 0.5000)),
    new LFontLine(new Point(0.5000, 0.5000), new Point(0.7500, 0.2500))
  ];
  var lines73 = [ /* i */
    new LFontLine(new Point(0.5000, 0.0000), new Point(0.5000, 0.5000)),
    new LFontLine(new Point(0.5000, 0.6875), new Point(0.5000, 0.7500)),
    new LFontLine(new Point(0.4375, 0.5000), new Point(0.5000, 0.5000)),
    new LFontLine(new Point(0.3750, 0.0000), new Point(0.6250, 0.0000))
  ];
  var lines74 = [ /* j */
    new LFontLine(new Point(0.6250, 0.6250), new Point(0.6250, 0.7500)),
    new LFontLine(new Point(0.5000, 0.5000), new Point(0.6250, 0.5000)),
    new LFontLine(new Point(0.6250, 0.5000), new Point(0.6250,-0.2500)),
    new LFontLine(new Point(0.3750,-0.2500), new Point(0.5000,-0.5000)),
    new LFontLine(new Point(0.6250,-0.2500), new Point(0.5000,-0.5000))
  ];
  var lines75 = [ /* k */
    new LFontLine(new Point(0.3125, 0.0000), new Point(0.3125, 1.0000)),
    new LFontLine(new Point(0.3125, 0.2500), new Point(0.6250, 0.4375)),
    new LFontLine(new Point(0.3125, 0.2500), new Point(0.6875, 0.0000))
  ];
  var lines76 = [ /* l */
    new LFontLine(new Point(0.3750, 0.1250), new Point(0.3750, 1.0000)),
    new LFontLine(new Point(0.3750, 0.1250), new Point(0.5000, 0.0000)),
    new LFontLine(new Point(0.5000, 0.0000), new Point(0.6250, 0.1250))
  ];
  var lines77 = [ /* m */
    new LFontLine(new Point(0.2500, 0.0000), new Point(0.2500, 0.5000)),
    new LFontLine(new Point(0.7500, 0.2500), new Point(0.7500, 0.0000)),
    new LFontLine(new Point(0.2500, 0.2500), new Point(0.3750, 0.5000)),
    new LFontLine(new Point(0.5000, 0.2500), new Point(0.6250, 0.5000)),
    new LFontLine(new Point(0.6250, 0.5000), new Point(0.7500, 0.2500)),
    new LFontLine(new Point(0.3750, 0.5000), new Point(0.5000, 0.2500))
  ];
  var lines78 = [ /* n */
    new LFontLine(new Point(0.2500, 0.0000), new Point(0.2500, 0.5000)),
    new LFontLine(new Point(0.7500, 0.2500), new Point(0.7500, 0.0000)),
    new LFontLine(new Point(0.2500, 0.2500), new Point(0.5000, 0.5000)),
    new LFontLine(new Point(0.5000, 0.5000), new Point(0.7500, 0.2500))
  ];
  var lines79 = [ /* o */
    new LFontLine(new Point(0.2500, 0.2500), new Point(0.5000, 0.5000)),
    new LFontLine(new Point(0.5000, 0.5000), new Point(0.7500, 0.2500)),
    new LFontLine(new Point(0.7500, 0.2500), new Point(0.5000, 0.0000)),
    new LFontLine(new Point(0.5000, 0.0000), new Point(0.2500, 0.2500))
  ];
  var lines80 = [ /* p */
    new LFontLine(new Point(0.2500,-0.5000), new Point(0.2500, 0.5000)),
    new LFontLine(new Point(0.2500, 0.2500), new Point(0.5000, 0.5000)),
    new LFontLine(new Point(0.5000, 0.5000), new Point(0.7500, 0.2500)),
    new LFontLine(new Point(0.7500, 0.2500), new Point(0.5000, 0.0000)),
    new LFontLine(new Point(0.5000, 0.0000), new Point(0.2500, 0.2500))
  ];
  var lines81 = [ /* q */
    new LFontLine(new Point(0.7500, 0.5000), new Point(0.7500,-0.5000)),
    new LFontLine(new Point(0.2500, 0.2500), new Point(0.5000, 0.5000)),
    new LFontLine(new Point(0.5000, 0.5000), new Point(0.7500, 0.2500)),
    new LFontLine(new Point(0.7500, 0.2500), new Point(0.5000, 0.0000)),
    new LFontLine(new Point(0.5000, 0.0000), new Point(0.2500, 0.2500))
  ];
  var lines82 = [ /* r */
    new LFontLine(new Point(0.2500, 0.0000), new Point(0.2500, 0.5000)),
    new LFontLine(new Point(0.2500, 0.3125), new Point(0.5000, 0.5000)),
    new LFontLine(new Point(0.5000, 0.5000), new Point(0.7500, 0.3125))
  ];
  var lines83 = [ /* s */
    new LFontLine(new Point(0.2500, 0.1250), new Point(0.5000, 0.0000)),
    new LFontLine(new Point(0.2500, 0.3750), new Point(0.5000, 0.5000)),
    new LFontLine(new Point(0.2500, 0.3750), new Point(0.5000, 0.2500)),
    new LFontLine(new Point(0.5000, 0.2500), new Point(0.7500, 0.1250)),
    new LFontLine(new Point(0.7500, 0.3750), new Point(0.5000, 0.5000)),
    new LFontLine(new Point(0.7500, 0.1250), new Point(0.5000, 0.0000))
  ];
  var lines84 = [ /* t */
    new LFontLine(new Point(0.3750, 0.1250), new Point(0.3750, 1.0000)),
    new LFontLine(new Point(0.3750, 0.5000), new Point(0.6250, 0.5000)),
    new LFontLine(new Point(0.3750, 0.1250), new Point(0.5000, 0.0000)),
    new LFontLine(new Point(0.5000, 0.0000), new Point(0.6250, 0.1250))
  ];
  var lines85 = [ /* u */
    new LFontLine(new Point(0.2500, 0.5000), new Point(0.2500, 0.2500)),
    new LFontLine(new Point(0.7500, 0.0000), new Point(0.7500, 0.5000)),
    new LFontLine(new Point(0.2500, 0.2500), new Point(0.5000, 0.0000)),
    new LFontLine(new Point(0.5000, 0.0000), new Point(0.7500, 0.2500))
  ];
  var lines86 = [ /* v */
    new LFontLine(new Point(0.2500, 0.5000), new Point(0.5000, 0.0000)),
    new LFontLine(new Point(0.5000, 0.0000), new Point(0.7500, 0.5000))
  ];
  var lines87 = [ /* w */
    new LFontLine(new Point(0.2500, 0.5000), new Point(0.3750, 0.0000)),
    new LFontLine(new Point(0.3750, 0.0000), new Point(0.5000, 0.2500)),
    new LFontLine(new Point(0.5000, 0.2500), new Point(0.6250, 0.0000)),
    new LFontLine(new Point(0.6250, 0.0000), new Point(0.7500, 0.5000))
  ];
  var lines88 = [ /* x */
    new LFontLine(new Point(0.2500, 0.0000), new Point(0.7500, 0.5000)),
    new LFontLine(new Point(0.2500, 0.5000), new Point(0.7500, 0.0000))
  ];
  var lines89 = [ /* y */
    new LFontLine(new Point(0.7500, 0.5000), new Point(0.7500,-0.2500)),
    new LFontLine(new Point(0.2500, 0.5000), new Point(0.5000, 0.0000)),
    new LFontLine(new Point(0.5000, 0.0000), new Point(0.7500, 0.5000)),
    new LFontLine(new Point(0.2500,-0.2500), new Point(0.5000,-0.5000)),
    new LFontLine(new Point(0.5000,-0.5000), new Point(0.7500,-0.2500))
  ];
  var lines90 = [ /* z */
    new LFontLine(new Point(0.2500, 0.5000), new Point(0.7500, 0.5000)),
    new LFontLine(new Point(0.7500, 0.5000), new Point(0.2500, 0.0000)),
    new LFontLine(new Point(0.2500, 0.0000), new Point(0.7500, 0.0000))
  ];
  var lines91 = [ /* { */
    new LFontLine(new Point(0.6250, 1.0000), new Point(0.3750, 0.5000)),
    new LFontLine(new Point(0.3750, 0.5000), new Point(0.6250, 0.0000))
  ];
  var lines92 = [ /* | */
    new LFontLine(new Point(0.5000, 0.0000), new Point(0.5000, 0.3750)),
    new LFontLine(new Point(0.5000, 1.0000), new Point(0.5000, 0.6250))
  ];
  var lines93 = [ /* } */
    new LFontLine(new Point(0.3750, 0.0000), new Point(0.5000, 0.0000)),
    new LFontLine(new Point(0.5000, 0.0000), new Point(0.5000, 0.3750)),
    new LFontLine(new Point(0.5000, 0.3750), new Point(0.6250, 0.5000)),
    new LFontLine(new Point(0.6250, 0.5000), new Point(0.5000, 0.6250)),
    new LFontLine(new Point(0.5000, 0.6250), new Point(0.5000, 1.0000)),
    new LFontLine(new Point(0.5000, 1.0000), new Point(0.3750, 1.0000)),
    new LFontLine(new Point(0.3750, 1.0000), new Point(0.6250, 0.5000)),
    new LFontLine(new Point(0.6250, 0.5000), new Point(0.3750, 0.0000))
  ];
  var lines94 = [ /* ~ */
    new LFontLine(new Point(0.2500, 0.6250), new Point(0.7500, 0.6250))
  ];

  //------

  this.setFontDef(new LFontDef( ' ', 0.2500, 1.0000, 0.0000,  0, lines00)); /*   */
  this.setFontDef(new LFontDef( '!', 0.1250, 1.0000, 0.0000,  4, lines01)); /* ! */
  this.setFontDef(new LFontDef( '"', 0.3750, 1.0000, 0.0000,  6, lines02)); /* " */
  this.setFontDef(new LFontDef( '#', 0.7500, 1.0000, 0.0000,  4, lines03)); /* # */
  this.setFontDef(new LFontDef( '$', 0.7500, 1.0000, 0.0000,  7, lines04)); /* $ */
  this.setFontDef(new LFontDef( '%', 0.7500, 1.0000, 0.0000,  9, lines05)); /* % */
  this.setFontDef(new LFontDef( '&', 0.7500, 1.0000, 0.0000,  8, lines06)); /* & */
  this.setFontDef(new LFontDef('\'', 0.1250, 1.0000, 0.0000,  3, lines07)); /* ' */
  this.setFontDef(new LFontDef( '(', 0.2500, 1.0000, 0.0000,  1, lines08)); /* ( */
  this.setFontDef(new LFontDef( ')', 0.2500, 1.0000, 0.0000,  1, lines09)); /* ) */
  this.setFontDef(new LFontDef( '*', 0.5000, 1.0000, 0.0000,  5, lines10)); /* * */
  this.setFontDef(new LFontDef( '+', 0.5000, 1.0000, 0.0000,  2, lines11)); /* + */
  this.setFontDef(new LFontDef( ',', 0.1250, 1.0000, 0.1875,  3, lines12)); /* , */
  this.setFontDef(new LFontDef( '-', 0.5000, 1.0000, 0.0000,  1, lines13)); /* - */
  this.setFontDef(new LFontDef( '.', 0.1250, 1.0000, 0.0000,  2, lines14)); /* . */
  this.setFontDef(new LFontDef( '/', 1.0000, 1.0000, 0.0000,  1, lines15)); /* / */
  this.setFontDef(new LFontDef( '0', 0.7500, 1.0000, 0.0000,  9, lines16)); /* 0 */
  this.setFontDef(new LFontDef( '1', 0.5000, 1.0000, 0.0000,  3, lines17)); /* 1 */
  this.setFontDef(new LFontDef( '2', 0.7500, 1.0000, 0.0000,  5, lines18)); /* 2 */
  this.setFontDef(new LFontDef( '3', 0.7500, 1.0000, 0.0000,  7, lines19)); /* 3 */
  this.setFontDef(new LFontDef( '4', 0.7500, 1.0000, 0.0000,  5, lines20)); /* 4 */
  this.setFontDef(new LFontDef( '5', 0.7500, 1.0000, 0.0000,  6, lines21)); /* 5 */
  this.setFontDef(new LFontDef( '6', 0.7500, 1.0000, 0.0000,  7, lines22)); /* 6 */
  this.setFontDef(new LFontDef( '7', 0.7500, 1.0000, 0.0000,  2, lines23)); /* 7 */
  this.setFontDef(new LFontDef( '8', 0.7500, 1.0000, 0.0000,  8, lines24)); /* 8 */
  this.setFontDef(new LFontDef( '9', 0.7500, 1.0000, 0.0000,  8, lines25)); /* 9 */
  this.setFontDef(new LFontDef( ':', 0.2500, 1.0000, 0.0000,  4, lines26)); /* : */
  this.setFontDef(new LFontDef( ';', 0.2500, 1.0000, 0.0000,  5, lines27)); /* ; */
  this.setFontDef(new LFontDef( '<', 0.5000, 1.0000, 0.0000,  2, lines28)); /* < */
  this.setFontDef(new LFontDef( '=', 0.5000, 1.0000, 0.0000,  2, lines29)); /* = */
  this.setFontDef(new LFontDef( '>', 0.5000, 1.0000, 0.0000,  2, lines30)); /* > */
  this.setFontDef(new LFontDef( '?', 0.5000, 1.0000, 0.0000,  6, lines31)); /* ? */
  this.setFontDef(new LFontDef( '@', 0.7500, 1.0000, 0.0000,  9, lines32)); /* @ */
  this.setFontDef(new LFontDef( 'A', 0.7500, 1.0000, 0.0000,  3, lines33)); /* A */
  this.setFontDef(new LFontDef( 'B', 0.7500, 1.0000, 0.0000,  8, lines34)); /* B */
  this.setFontDef(new LFontDef( 'C', 0.7500, 1.0000, 0.0000,  7, lines35)); /* C */
  this.setFontDef(new LFontDef( 'D', 0.7500, 1.0000, 0.0000,  6, lines36)); /* D */
  this.setFontDef(new LFontDef( 'E', 0.7500, 1.0000, 0.0000,  4, lines37)); /* E */
  this.setFontDef(new LFontDef( 'F', 0.7500, 1.0000, 0.0000,  3, lines38)); /* F */
  this.setFontDef(new LFontDef( 'G', 0.7500, 1.0000, 0.0000,  9, lines39)); /* G */
  this.setFontDef(new LFontDef( 'H', 0.7500, 1.0000, 0.0000,  3, lines40)); /* H */
  this.setFontDef(new LFontDef( 'I', 0.2500, 1.0000, 0.0000,  3, lines41)); /* I */
  this.setFontDef(new LFontDef( 'J', 0.5000, 1.0000, 0.0000,  4, lines42)); /* J */
  this.setFontDef(new LFontDef( 'K', 0.7500, 1.0000, 0.0000,  3, lines43)); /* K */
  this.setFontDef(new LFontDef( 'L', 0.7500, 1.0000, 0.0000,  2, lines44)); /* L */
  this.setFontDef(new LFontDef( 'M', 0.7500, 1.0000, 0.0000,  4, lines45)); /* M */
  this.setFontDef(new LFontDef( 'N', 0.7500, 1.0000, 0.0000,  3, lines46)); /* N */
  this.setFontDef(new LFontDef( 'O', 0.7500, 1.0000, 0.0000,  8, lines47)); /* O */
  this.setFontDef(new LFontDef( 'P', 0.7500, 1.0000, 0.0000,  5, lines48)); /* P */
  this.setFontDef(new LFontDef( 'Q', 0.7500, 1.0000, 0.0000,  9, lines49)); /* Q */
  this.setFontDef(new LFontDef( 'R', 0.7500, 1.0000, 0.0000,  6, lines50)); /* R */
  this.setFontDef(new LFontDef( 'S', 0.7500, 1.0000, 0.0000,  9, lines51)); /* S */
  this.setFontDef(new LFontDef( 'T', 0.7500, 1.0000, 0.0000,  2, lines52)); /* T */
  this.setFontDef(new LFontDef( 'U', 0.7500, 1.0000, 0.0000,  5, lines53)); /* U */
  this.setFontDef(new LFontDef( 'V', 0.7500, 1.0000, 0.0000,  2, lines54)); /* V */
  this.setFontDef(new LFontDef( 'W', 0.7500, 1.0000, 0.0000,  4, lines55)); /* W */
  this.setFontDef(new LFontDef( 'X', 0.7500, 1.0000, 0.0000,  2, lines56)); /* X */
  this.setFontDef(new LFontDef( 'Y', 0.7500, 1.0000, 0.0000,  3, lines57)); /* Y */
  this.setFontDef(new LFontDef( 'Z', 0.7500, 1.0000, 0.0000,  3, lines58)); /* Z */
  this.setFontDef(new LFontDef( '[', 0.2500, 1.0000, 0.0000,  3, lines59)); /* [ */
  this.setFontDef(new LFontDef('\\', 1.0000, 1.0000, 0.0000,  1, lines60)); /* \ */
  this.setFontDef(new LFontDef( ']', 0.2500, 1.0000, 0.0000,  3, lines61)); /* ] */
  this.setFontDef(new LFontDef( '^', 0.5000, 1.0000, 0.0000,  2, lines62)); /* ^ */
  this.setFontDef(new LFontDef( '_', 0.5000, 1.0000, 0.0000,  1, lines63)); /* _ */
  this.setFontDef(new LFontDef( '`', 0.1250, 1.0000, 0.0000,  3, lines64)); /* ` */
  this.setFontDef(new LFontDef( 'a', 0.5000, 1.0000, 0.0000,  7, lines65)); /* a */
  this.setFontDef(new LFontDef( 'b', 0.5000, 1.0000, 0.0000,  5, lines66)); /* b */
  this.setFontDef(new LFontDef( 'c', 0.5000, 1.0000, 0.0000,  4, lines67)); /* c */
  this.setFontDef(new LFontDef( 'd', 0.5000, 1.0000, 0.0000,  5, lines68)); /* d */
  this.setFontDef(new LFontDef( 'e', 0.5000, 1.0000, 0.0000,  5, lines69)); /* e */
  this.setFontDef(new LFontDef( 'f', 0.2500, 1.0000, 0.0000,  4, lines70)); /* f */
  this.setFontDef(new LFontDef( 'g', 0.5000, 1.0000, 0.5000,  7, lines71)); /* g */
  this.setFontDef(new LFontDef( 'h', 0.5000, 1.0000, 0.0000,  4, lines72)); /* h */
  this.setFontDef(new LFontDef( 'i', 0.2500, 1.0000, 0.0000,  4, lines73)); /* i */
  this.setFontDef(new LFontDef( 'j', 0.2500, 1.0000, 0.0000,  5, lines74)); /* j */
  this.setFontDef(new LFontDef( 'k', 0.3750, 1.0000, 0.0000,  3, lines75)); /* k */
  this.setFontDef(new LFontDef( 'l', 0.2500, 1.0000, 0.0000,  3, lines76)); /* l */
  this.setFontDef(new LFontDef( 'm', 0.5000, 1.0000, 0.0000,  6, lines77)); /* m */
  this.setFontDef(new LFontDef( 'n', 0.5000, 1.0000, 0.0000,  4, lines78)); /* n */
  this.setFontDef(new LFontDef( 'o', 0.5000, 1.0000, 0.0000,  4, lines79)); /* o */
  this.setFontDef(new LFontDef( 'p', 0.5000, 1.0000, 0.5000,  5, lines80)); /* p */
  this.setFontDef(new LFontDef( 'q', 0.5000, 1.0000, 0.5000,  5, lines81)); /* q */
  this.setFontDef(new LFontDef( 'r', 0.5000, 1.0000, 0.0000,  3, lines82)); /* r */
  this.setFontDef(new LFontDef( 's', 0.5000, 1.0000, 0.0000,  6, lines83)); /* s */
  this.setFontDef(new LFontDef( 't', 0.3750, 1.0000, 0.0000,  4, lines84)); /* t */
  this.setFontDef(new LFontDef( 'u', 0.5000, 1.0000, 0.0000,  4, lines85)); /* u */
  this.setFontDef(new LFontDef( 'v', 0.5000, 1.0000, 0.0000,  2, lines86)); /* v */
  this.setFontDef(new LFontDef( 'w', 0.5000, 1.0000, 0.0000,  4, lines87)); /* w */
  this.setFontDef(new LFontDef( 'x', 0.5000, 1.0000, 0.0000,  2, lines88)); /* x */
  this.setFontDef(new LFontDef( 'y', 0.5000, 1.0000, 0.5000,  5, lines89)); /* y */
  this.setFontDef(new LFontDef( 'z', 0.5000, 1.0000, 0.0000,  3, lines90)); /* z */
  this.setFontDef(new LFontDef( '{', 0.2500, 1.0000, 0.0000,  2, lines91)); /* { */
  this.setFontDef(new LFontDef( '|', 0.1250, 1.0000, 0.0000,  2, lines92)); /* | */
  this.setFontDef(new LFontDef( '}', 0.2500, 1.0000, 0.0000,  2, lines93)); /* } */
  this.setFontDef(new LFontDef( '~', 0.5000, 1.0000, 0.0000,  1, lines94)); /* ~ */
};

LFont.prototype.getFontDef = function(c) {
  var cc = c.charCodeAt(0);

  if (cc >= this.start_cc && cc <= this.end_cc)
    return this.font_defs[cc - this.start_cc];
  else
    return this.font_defs[0];
};

LFont.prototype.setFontDef = function(fontDef) {
  var cc = fontDef.c.charCodeAt(0);

  if (cc >= this.start_cc && cc <= this.end_cc)
    this.font_defs[cc - this.start_cc] = fontDef;
  else
    assert(false, "bad char");
};

LFont.prototype.snapPoint = function(p) {
  return new Point(Math.roundDown(p.x*16.0)/16.0, Math.roundDown(p.y*16.0)/16.0);
};

//------

function LFontLine (start, end) {
  this.start = start;
  this.end   = end;
}

//---

function LFontDef (c, width, ascender, descender, numLines, lines) {
  this.c         = c;
  this.width     = width;
  this.ascender  = ascender;
  this.descender = descender;
  this.lines     = [];

  for (var i = 0; i < numLines; ++i)
    this.lines.push(new LFontLine(lines[i].start, lines[i].end));
}
