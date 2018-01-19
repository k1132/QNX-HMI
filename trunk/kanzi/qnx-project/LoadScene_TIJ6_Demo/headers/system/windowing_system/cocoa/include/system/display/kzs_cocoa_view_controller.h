/**
 * \file
 * View controller specialization for Kanzi view.
 *
 * Copyright 2008-2014 by Rightware. All rights reserved.
*/

#if 0

#import <UIKit/UIKit.h>

/** View controllers control a view, handling events like orientation change. */
@interface KzaViewController : UIViewController {

}
/** Override to allow orientation change events. */
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)orientation;
/** Override orientation change event. */
- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation;
/** Override touch events. */
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event;
@end

#endif

