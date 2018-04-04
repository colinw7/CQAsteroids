//
//  AsteroidsView.mm
//  Asteroids
//
//  Created by Colin Williams on 4/5/10.
//  Copyright 2010 None. All rights reserved.
//

#import "AsteroidsView.h"

#include "CAsteroids.h"

class AsteroidsRenderer : public CAsteroidsRenderer {
 public:
  AsteroidsRenderer();

  void clear(const CGFloat *bg);

  void setForeground(const CGFloat *fg);

  void drawLine(double x1, double y1, double x2, double y2);

 private:
  int w_, h_;
};

static CAsteroids        *asteroids;
static AsteroidsRenderer *renderer;
static bool               left_pressed;
static bool               right_pressed;

@implementation AsteroidsView

- (id)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        // Initialization code
        renderer = new AsteroidsRenderer;

        asteroids = new CAsteroids(renderer);
    }
    return self;
}

- (void) update
{
  static int count;

  ++count;

  if (left_pressed ) asteroids->shipTurnLeft();
  if (right_pressed) asteroids->shipTurnRight();

  if (count & 1) {
    [self setNeedsDisplay];
  }
}

- (void)drawRect:(CGRect)rect {
  asteroids->update();

  CGContextRef context = UIGraphicsGetCurrentContext();

  CGContextMoveToPoint   (context,  50, 430);
  CGContextAddLineToPoint(context,  30, 430);
  CGContextAddLineToPoint(context,  30, 450);
  CGContextAddLineToPoint(context,  50, 450);
  CGContextStrokePath    (context);
  CGContextMoveToPoint   (context,  45, 445);
  CGContextAddLineToPoint(context,  50, 450);
  CGContextAddLineToPoint(context,  45, 455);
  CGContextStrokePath    (context);

  CGContextMoveToPoint   (context, 110, 430);
  CGContextAddLineToPoint(context, 130, 430);
  CGContextAddLineToPoint(context, 130, 450);
  CGContextAddLineToPoint(context, 110, 450);
  CGContextStrokePath    (context);
  CGContextMoveToPoint   (context, 115, 445);
  CGContextAddLineToPoint(context, 110, 450);
  CGContextAddLineToPoint(context, 115, 455);
  CGContextStrokePath    (context);

  CGContextMoveToPoint   (context, 195, 430);
  CGContextAddLineToPoint(context, 210, 440);
  CGContextAddLineToPoint(context, 195, 450);
  CGContextStrokePath    (context);
  CGContextMoveToPoint   (context, 180, 440);
  CGContextAddLineToPoint(context, 210, 440);
  CGContextStrokePath    (context);

  CGContextMoveToPoint   (context, 270, 440);
  CGContextAddLineToPoint(context, 290, 440);
  CGContextStrokePath    (context);
  CGContextMoveToPoint   (context, 280, 430);
  CGContextAddLineToPoint(context, 280, 450);
  CGContextStrokePath    (context);
  CGContextMoveToPoint   (context, 270, 430);
  CGContextAddLineToPoint(context, 290, 450);
  CGContextStrokePath    (context);
  CGContextMoveToPoint   (context, 270, 450);
  CGContextAddLineToPoint(context, 290, 430);
  CGContextStrokePath    (context);
}

-(void) touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
  NSSet *allTouches = [event allTouches];

  int n = [allTouches count];

  for (int i = 0; i < n; ++i) {
    UITouch *touch = [[allTouches allObjects] objectAtIndex:i];

    firstTouch = [touch locationInView:self];
    lastTouch  = firstTouch;

    if (! asteroids->getGameOver()) {
      if      (firstTouch.x <  80)
        left_pressed = true;
      else if (firstTouch.x < 160)
        right_pressed = true;
      else if (firstTouch.x < 240)
        asteroids->shipThrust();
      else if (firstTouch.x < 320)
        asteroids->shipFire();
    }
    else {
    }
  }
}

-(void) touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
  NSSet *allTouches = [event allTouches];

  int n = [allTouches count];

  for (int i = 0; i < n; ++i) {
    UITouch *touch = [[allTouches allObjects] objectAtIndex:i];

    lastTouch = [touch locationInView:self];

    if (! asteroids->getGameOver()) {
      if      (lastTouch.x <  80)
        left_pressed  = false;
      else if (lastTouch.x < 160)
        right_pressed = false;
    }
    else {
      left_pressed  = false;
      right_pressed = false;

      asteroids->newGame();
    }
  }
}

-(void) touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
  NSSet *allTouches = [event allTouches];

  int n = [allTouches count];

  for (int i = 0; i < n; ++i) {
    UITouch *touch = [[allTouches allObjects] objectAtIndex:i];

    lastTouch = [touch locationInView:self];
  }
}

- (void)dealloc {
    [super dealloc];
}

@end

AsteroidsRenderer::
AsteroidsRenderer()
{
  w_ = 320;
  h_ = 320;
}

void
AsteroidsRenderer::
clear(const CGFloat *bg)
{
  CGContextRef context = UIGraphicsGetCurrentContext();

  CGRect brect;

  brect.origin.x    = 0;
  brect.origin.y    = 0;
  brect.size.width  = w_;
  brect.size.height = h_ + 160;

  CGContextSetFillColor(context, bg);

  CGContextFillRect(context, brect);
}

void
AsteroidsRenderer::
setForeground(const CGFloat *fg)
{
  CGContextRef context = UIGraphicsGetCurrentContext();

  CGContextSetLineWidth(context, 1.0);

  CGContextSetStrokeColor(context, fg);
}

void
AsteroidsRenderer::
drawLine(double x1, double y1, double x2, double y2)
{
  CGContextRef context = UIGraphicsGetCurrentContext();

  CGContextMoveToPoint   (context, x1*w_, y1*h_);
  CGContextAddLineToPoint(context, x2*w_, y2*h_);
  CGContextStrokePath    (context);
}
