/* =============================================================================
	FILE:		UKKQueue.h
	PROJECT:	Filie
    
    COPYRIGHT:  (c) 2003 M. Uli Kusterer, all rights reserved.
    
	AUTHORS:	M. Uli Kusterer - UK
            Matthieu Cormier - M@
 
    LICENSES:   MIT License

	REVISIONS:
    2010-01-23  M@  Fix warning in removePathFromQueue:
                    Reformatted .h file.
                    Removed old singleton accessor.
                    Removed UKKQUEUE_BACKWARDS_COMPATIBLE, UKKQUEUE_SEND_STUPID_NOTIFICATIONS, 
                            UKKQUEUE_OLD_NOTIFICATION_NAMES
                    Removed deprecated category method
                      -(void) kqueue: (UKKQueue*)kq receivedNotification: (NSString*)nm forFile: (NSString*)fpath;
                    Made private methods private with a private category.
                    Require protocol when setting delegate.
		2006-03-13	UK	Clarified license, streamlined UKFileWatcher stuff,
						Changed notifications to be useful and turned off by
						default some deprecated stuff.
		2003-12-21	UK	Created.
   ========================================================================== */

// -----------------------------------------------------------------------------
//  Headers:
// -----------------------------------------------------------------------------

#import <Foundation/Foundation.h>
#include <sys/types.h>
#include <sys/event.h>
#import "UKFileWatcher.h"


// -----------------------------------------------------------------------------
//  Constants:
// -----------------------------------------------------------------------------


// Flags for notifyingAbout:
#define UKKQueueNotifyAboutRename             NOTE_RENAME		// Item was renamed.
#define UKKQueueNotifyAboutWrite              NOTE_WRITE		// Item contents changed (also folder contents changed).
#define UKKQueueNotifyAboutDelete             NOTE_DELETE		// item was removed.
#define UKKQueueNotifyAboutAttributeChange    NOTE_ATTRIB		// Item attributes changed.
#define UKKQueueNotifyAboutSizeIncrease				NOTE_EXTEND		// Item size increased.
#define UKKQueueNotifyAboutLinkCountChanged   NOTE_LINK     // Item's link count changed.
#define UKKQueueNotifyAboutAccessRevocation		NOTE_REVOKE		// Access to item was revoked.




// -----------------------------------------------------------------------------
//  UKKQueue:
// -----------------------------------------------------------------------------

@interface UKKQueue : NSObject <UKFileWatcher>
{
	int       queueFD;			// The actual queue ID (Unix file descriptor).
	
  NSMutableArray *watchedPaths,		// NSStrings containing the paths we're watching.
                 *watchedFDs;			// NSNumbers containing the file descriptors we're watching.
	
  id				delegate,       // Gets messages about changes instead of notification center, if specified.
	  				delegateProxy;	// Proxy object to which we send messages so they reach delegate on the main thread.
	
  BOOL			alwaysNotify,		// Send notifications even if we have a delegate? Defaults to NO.
	    			keepThreadRunning;	// Termination criterion of our thread.
}

// Returns a singleton, a shared kqueue object Handy if you're subscribing to 
// the notifications. Use this, or just create separate objects using alloc/init. 
// Whatever floats your boat.
+(id)	sharedFileWatcher;      

-(int)  queueFD;		// I know you unix geeks want this...

// High-level file watching: (use UKFileWatcher protocol methods instead, where possible!)
-(void) addPathToQueue: (NSString*)path;
-(void) addPathToQueue: (NSString*)path notifyingAbout: (u_int)fflags;
-(void) removePathFromQueue: (NSString*)path;

-(id)	delegate;
-(void)	setDelegate: (id<UKFileWatcherDelegate>)newDelegate;

-(BOOL)	alwaysNotify;
-(void)	setAlwaysNotify: (BOOL)n;

@end
