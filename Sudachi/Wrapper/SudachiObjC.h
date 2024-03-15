//
//  SudachiObjC.h
//  Sudachi
//
//  Created by Jarrod Norwell on 1/8/24.
//

#import <Foundation/Foundation.h>
#import <MetalKit/MetalKit.h>

#import "SudachiGameInformation/SudachiGameInformation.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, VirtualControllerAnalogType) {
    VirtualControllerAnalogTypeLeft = 0,
    VirtualControllerAnalogTypeRight = 1
};

typedef NS_ENUM(NSUInteger, VirtualControllerButtonType) {
    VirtualControllerButtonTypeA = 0,
    VirtualControllerButtonTypeB = 1,
    VirtualControllerButtonTypeX = 2,
    VirtualControllerButtonTypeY = 3,
    VirtualControllerButtonTypeL = 4,
    VirtualControllerButtonTypeR = 5,
    VirtualControllerButtonTypeTriggerL = 6,
    VirtualControllerButtonTypeTriggerR = 7,
    VirtualControllerButtonTypeTriggerZL = 8,
    VirtualControllerButtonTypeTriggerZR = 9,
    VirtualControllerButtonTypePlus = 10,
    VirtualControllerButtonTypeMinus = 11,
    VirtualControllerButtonTypeDirectionalPadLeft = 12,
    VirtualControllerButtonTypeDirectionalPadUp = 13,
    VirtualControllerButtonTypeDirectionalPadRight = 14,
    VirtualControllerButtonTypeDirectionalPadDown = 15,
    VirtualControllerButtonTypeSL = 16,
    VirtualControllerButtonTypeSR = 17,
    VirtualControllerButtonTypeHome = 18,
    VirtualControllerButtonTypeCapture = 19
};

@interface SudachiObjC : NSObject {
    CAMetalLayer *_layer;
    CGSize _size;
}

@property (nonatomic, strong) SudachiGameInformation *gameInformation;

+(SudachiObjC *) sharedInstance NS_SWIFT_NAME(shared());
-(void) configureLayer:(CAMetalLayer *)layer withSize:(CGSize)size NS_SWIFT_NAME(configure(layer:with:));
-(void) bootOS;
-(void) insertGame:(NSURL *)url NS_SWIFT_NAME(insert(game:));
-(void) insertGames:(NSArray<NSURL *> *)games NS_SWIFT_NAME(insert(games:));
-(void) step;

-(void) touchBeganAtPoint:(CGPoint)point index:(NSUInteger)index NS_SWIFT_NAME(touchBegan(at:for:));
-(void) touchEndedForIndex:(NSUInteger)index;
-(void) touchMovedAtPoint:(CGPoint)point index:(NSUInteger)index NS_SWIFT_NAME(touchMoved(at:for:));

-(void) thumbstickMoved:(VirtualControllerAnalogType)analog x:(CGFloat)x y:(CGFloat)y;

-(void) virtualControllerButtonDown:(VirtualControllerButtonType)button;
-(void) virtualControllerButtonUp:(VirtualControllerButtonType)button;

-(void) orientationChanged:(UIInterfaceOrientation)orientation with:(CAMetalLayer *)layer size:(CGSize)size NS_SWIFT_NAME(orientationChanged(orientation:with:size:));

-(void) settingsChanged;
@end

NS_ASSUME_NONNULL_END
