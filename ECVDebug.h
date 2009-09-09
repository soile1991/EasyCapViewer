/* Copyright (c) 2009, Ben Trask
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * The names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY BEN TRASK ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL BEN TRASK BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */
#import <Cocoa/Cocoa.h>
#import <IOKit/usb/IOUSBLib.h>

extern NSString *ECVIOKitErrorToString(IOReturn error);

#define ECVRetryDefault 3

#define ECVIOReturn(error, retry) do {\
	int __i = 0;\
	IOReturn __e;\
	for(; __i <= (retry) && kIOReturnSuccess != (__e = (error)); __i++) usleep(100000);\
	if(kIOReturnNoDevice == __e) goto ECVNoDeviceError;\
	if(kIOReturnSuccess != __e) goto ECVGenericError;\
} while(NO)

#define ECVOSStatus(error, retry) do {\
	int __i = 0;\
	OSStatus __e;\
	for(; __i <= (retry) && noErr != (__e = (error)); __i++) usleep(100000);\
	if(noErr != __e) NSLog(@"%s:%d (%s) %s: '%d'", __FILE__, __LINE__, __PRETTY_FUNCTION__, #error, __e);\
} while(NO)

#define ECVglError(x) \
	do {\
		(x);\
		GLenum __e;\
		while((__e = glGetError()) != GL_NO_ERROR) NSLog(@"%s:%d %s/%s glGetError(): 0x%03x", __FILE__, __LINE__, __PRETTY_FUNCTION__, #x, __e);\
	} while(NO)

#define ECVAssertNotReached(desc) [[NSAssertionHandler currentHandler] handleFailureInMethod:_cmd object:self file:[NSString stringWithUTF8String:__FILE__] lineNumber:__LINE__ description:(desc)]
