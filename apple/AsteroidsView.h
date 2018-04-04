//
//  AsteroidsView.h
//  Asteroids
//
//  Created by Colin Williams on 4/5/10.
//  Copyright 2010 None. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface AsteroidsView : UIView {
  CGPoint firstTouch;
  CGPoint lastTouch;
}

- (void) update;

@end
