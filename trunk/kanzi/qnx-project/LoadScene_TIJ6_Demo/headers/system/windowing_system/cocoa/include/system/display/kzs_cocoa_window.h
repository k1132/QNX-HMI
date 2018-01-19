/**
* \file
* Cocoa window specialization for Kanzi.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/

#import <Cocoa/Cocoa.h>


/* Forward declarations. */
struct KzsWindow;
struct KzsEventQueue;


@interface KzsCocoaWindow : NSWindow
{
    /* Callback context parameters: */
    struct KzsWindow* systemWindow;    /**< Parent window. */
    struct KzsEventQueue* activeQueue; /**< Active event queue. */
}

- (void)setSystemWindow:(struct KzsWindow*)window;
- (struct KzsWindow*)systemWindow;
- (void)setActiveEventQueue:(struct KzsEventQueue*)queue;
- (struct KzsEventQueue*)activeEventQueue;

@end
