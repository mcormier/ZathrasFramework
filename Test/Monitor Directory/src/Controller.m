//
//  Controller.m
//  Zathras
//
//  Created by Matthieu Cormier on 1/23/10.
//  Copyright 2010 Preen and Prune Software and Design. All rights reserved.
//

#import "Controller.h"


@implementation Controller

-(id) init {
  self = [super init];
  if( !self ) 
    return nil;
 
  desktopPath = [@"~/Desktop/" stringByExpandingTildeInPath];
  [desktopPath retain];

  homePath = [@"~/" stringByExpandingTildeInPath];
  [homePath retain];

  
  return self;
}

-(void)awakeFromNib {
  id<UKFileWatcher> watcher;
  
  // A UKFNSubscribeFileWatcher will notify your
  // application when it has focus.
  // UKFNSubscribeFileWatcher can only monitor directories.
  watcher = [UKFNSubscribeFileWatcher sharedFileWatcher];
  [watcher addPath:desktopPath];
  [watcher setDelegate:self];
  
  // A UKKQueue will notify your application as soon
  // as the change occurs, whether you application is
  // currently focused or not.
  // UKKQueue can monitor files and directories.
  watcher = [UKKQueue sharedFileWatcher];
  [watcher addPath:homePath];
  [watcher setDelegate:self];
  
  // NOTE:
  // Whether you monitor a directory with either type
  // of watcher you will only receive UKFileWatcherWriteNotification
  // for directories.
}

-(void)dealloc {
  [desktopPath release];
  [super dealloc];
}

-(void) watcher:(id<UKFileWatcher>)kq receivedNotification:(NSString*)nm 
        forPath: (NSString*)fpath {
  // If the notification is for ~/Desktop there is no point
  // at looking at the notification string. 
  // We are using UKFNSubscribeFileWatcher to monitor ~/Desktop
  // and UKFNSubscribeFileWatcher always returns a notification of
  // UKFileWatcherWriteNotification because it uses FNSubscribe and
  // FNSubscribe doesn't provide any specific information on what changed.
  if( [desktopPath caseInsensitiveCompare:fpath] == NSOrderedSame ) {
    NSLog(@"Something in the Desktop folder changed.");
  } else {
    NSLog(@"Something in the Home folder changed.");    
  }
  
  
}

@end
