//
//  AsteroidsAppDelegate.h
//  Asteroids
//
//  Created by Colin Williams on 4/5/10.
//  Copyright None 2010. All rights reserved.
//

#import <UIKit/UIKit.h>

@class AsteroidsViewController;

@interface AsteroidsAppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow                *window;
    AsteroidsViewController *viewController;
}

#ifdef OBJC2
@property (nonatomic, retain) IBOutlet UIWindow                *window;
@property (nonatomic, retain) IBOutlet AsteroidsViewController *viewController;
#endif

@end

