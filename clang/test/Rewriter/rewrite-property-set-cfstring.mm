// RUN: %clang_cc1 -x objective-c++ -Wno-return-type -fblocks -fms-extensions -rewrite-objc %s -o %t-rw.cpp
// RUN: %clang_cc1 -fsyntax-only -fblocks -Wno-address-of-temporary -D"id=void*" -D"SEL=void*" -D"__declspec(X)=" %t-rw.cpp
// rdar:// 8527018

void *sel_registerName(const char *);

@class NSString;
@interface CoreDAVDiscoveryAccountInfo  {
  NSString *_scheme;
}
@property (retain) NSString *scheme;
- (void) Meth ;
@end

@implementation CoreDAVDiscoveryAccountInfo
@synthesize scheme=_scheme;
- (void) Meth {
  CoreDAVDiscoveryAccountInfo *discoveryInfo;
  discoveryInfo.scheme = @"https";
}
@end
