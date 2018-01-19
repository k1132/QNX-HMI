/**
 * \file
 * Window delegate for Kanzi window.
 *
 * Copyright 2008-2014 by Rightware. All rights reserved.
*/

#import <Cocoa/Cocoa.h>


/** Window Controllers receive window events. */
@interface KzsWindowDelegate : NSResponder<NSWindowDelegate>
{
}
- (NSSize)windowWillResize:(NSWindow*)sender toSize:(NSSize)frameSize;
- (void)windowDidBecomeKey:(NSNotification*)notification;
- (void)windowDidResignKey:(NSNotification*)notification;
@end
