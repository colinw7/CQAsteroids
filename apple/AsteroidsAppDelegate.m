//
//  AsteroidsAppDelegate.m
//  Asteroids
//
//  Created by Colin Williams on 4/5/10.
//  Copyright None 2010. All rights reserved.
//

#import "AsteroidsAppDelegate.h"
#import "AsteroidsViewController.h"

@implementation AsteroidsAppDelegate

#ifdef OBJC2
@synthesize window;
@synthesize viewController;
#endif


- (void)applicationDidFinishLaunching:(UIApplication *)application {

    // Override point for customization after app launch
    [window addSubview:viewController.view];
    [window makeKeyAndVisible];
}


- (void)dealloc {
    [viewController release];
    [window release];
    [super dealloc];
}


@end
