//
//  EAGLView.m
//  SimpleSample
//
//  Created by nacho on 27/08/09.
//  Copyright Ignacio Sanchez Gines 2009. All rights reserved.
//



#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/EAGLDrawable.h>

#import "EAGLView.h"

#include "GameManager.h"
#include "test_class.h" // TODO: Get rid of this

#define USE_DEPTH_BUFFER 1

// A class extension to declare private methods
@interface EAGLView ()

@property (nonatomic, retain) EAGLContext *context;
@property (nonatomic, assign) NSTimer *animationTimer;

- (BOOL) createFramebuffer;
- (void) destroyFramebuffer;

@end


@implementation EAGLView

@synthesize context;
@synthesize animationTimer;
@synthesize animationInterval;


// You must implement this method
+ (Class)layerClass {
    return [CAEAGLLayer class];
}


//The GL view is stored in the nib file. When it's unarchived it's sent -initWithCoder:
- (id)initWithCoder:(NSCoder*)coder {
    
    if ((self = [super initWithCoder:coder])) {
        // Get the layer
        CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
        
        eaglLayer.opaque = YES;
        eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                        [NSNumber numberWithBool:NO], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];
        
        context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
        //context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
        
        if (!context || ![EAGLContext setCurrentContext:context]) {
            [self release];
            return nil;
        }
        
        animationInterval = 1.0 / 60.0;
        
        //self.accelerometer = [UIAccelerometer sharedAccelerometer];
        //self.accelerometer.updateInterval = .1;
        //self.accelerometer.delegate = self;
        
        [[UIAccelerometer sharedAccelerometer] setDelegate:self];
    
        
    }
    return self;
}

- (void)accelerometer:(UIAccelerometer *)accelerometer didAccelerate:(UIAcceleration *)acceleration {
//    labelX.text = [NSString stringWithFormat:@"%@%f", @"X: ", acceleration.x];
//    labelY.text = [NSString stringWithFormat:@"%@%f", @"Y: ", acceleration.y];
//    labelZ.text = [NSString stringWithFormat:@"%@%f", @"Z: ", acceleration.z];
//    
//    self.progressX.progress = ABS(acceleration.x);
//    self.progressY.progress = ABS(acceleration.y);
//    self.progressZ.progress = ABS(acceleration.z);
    
    TestClass::Instance().accelX = acceleration.x;
    TestClass::Instance().accelY = acceleration.y;
    TestClass::Instance().accelZ = acceleration.z;
    
    //NSLog(@"X:%f, Y:%f, Z:%f\n", acceleration.x, acceleration.y, acceleration.z);
}

//---fired when the user finger(s) touches the screen---

-(void) touchesBegan: (NSSet *) touches withEvent: (UIEvent *) event {
    
    
    
    //---get all touches on the screen---
    
    NSSet *allTouches = [event allTouches];
    
    
    
    //---compare the number of touches on the screen---
    
    switch ([allTouches count])
    
    {
            
            //---single touch---
            
        case 1: {
            
            //---get info of the touch---
            
            UITouch *touch = [[allTouches allObjects] objectAtIndex:0];
            
            
            
            //---compare the touches---
            
            switch ([touch tapCount])
            
            {
                    
                    //---single tap---
                    
                case 1: {
                    
                    TestClass::Instance().doOrientation = false;
                   // imageView.contentMode = UIViewContentModeScaleAspectFit;
                    
                } break;
                    
                    
                    
                    //---double tap---
                    
                case 2: {
                    
                    TestClass::Instance().doOrientation = true;
                    //imageView.contentMode = UIViewContentModeCenter;
                    
                } break;
                    
            }
            
        }  break;
            
    }
    
}


- (void)drawView {       
	
	GameManager::Instance().Update();   
}


- (void)layoutSubviews {
    [EAGLContext setCurrentContext:context];
    [self destroyFramebuffer];
    [self createFramebuffer];
    [self drawView];
}


- (BOOL)createFramebuffer {
    
    glGenFramebuffersOES(1, &viewFramebuffer);
    glGenRenderbuffersOES(1, &viewRenderbuffer);
    
    glBindFramebufferOES(GL_FRAMEBUFFER_OES, viewFramebuffer);
    glBindRenderbufferOES(GL_RENDERBUFFER_OES, viewRenderbuffer);
    [context renderbufferStorage:GL_RENDERBUFFER_OES fromDrawable:(CAEAGLLayer*)self.layer];
    glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_RENDERBUFFER_OES, viewRenderbuffer);
    
    glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_WIDTH_OES, &backingWidth);
    glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_HEIGHT_OES, &backingHeight);
    
    if (USE_DEPTH_BUFFER) {
        glGenRenderbuffersOES(1, &depthRenderbuffer);
        glBindRenderbufferOES(GL_RENDERBUFFER_OES, depthRenderbuffer);
        glRenderbufferStorageOES(GL_RENDERBUFFER_OES, GL_DEPTH_COMPONENT16_OES, backingWidth, backingHeight);
        glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_DEPTH_ATTACHMENT_OES, GL_RENDERBUFFER_OES, depthRenderbuffer);
    }
    
    if(glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES) != GL_FRAMEBUFFER_COMPLETE_OES) {
        NSLog(@"failed to make complete framebuffer object %x", glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES));
        return NO;
    }
	
	GameManager::Instance().Init(context, viewRenderbuffer, viewFramebuffer, depthRenderbuffer, self.bounds);
    
    return YES;
}


- (void)destroyFramebuffer {
	
	GameManager::Instance().Destroy();
    
    glDeleteFramebuffersOES(1, &viewFramebuffer);
    viewFramebuffer = 0;
    glDeleteRenderbuffersOES(1, &viewRenderbuffer);
    viewRenderbuffer = 0;
    
    if(depthRenderbuffer) {
        glDeleteRenderbuffersOES(1, &depthRenderbuffer);
        depthRenderbuffer = 0;
    }
}


- (void)startAnimation {
    self.animationTimer = [NSTimer scheduledTimerWithTimeInterval:animationInterval target:self selector:@selector(drawView) userInfo:nil repeats:YES];
}


- (void)stopAnimation {
    self.animationTimer = nil;
}


- (void)setAnimationTimer:(NSTimer *)newTimer {
    [animationTimer invalidate];
    animationTimer = newTimer;
}


- (void)setAnimationInterval:(NSTimeInterval)interval {
    
    animationInterval = interval;
    if (animationTimer) {
        [self stopAnimation];
        [self startAnimation];
    }
}


- (void)dealloc {
    
    [self stopAnimation];
    
    if ([EAGLContext currentContext] == context) {
        [EAGLContext setCurrentContext:nil];
    }
    
    [context release];  
    [super dealloc];
}

@end
