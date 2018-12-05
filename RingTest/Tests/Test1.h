//
//  Test1.h
//  RingTest
//
//  Created by Luca Pascarella on 12/5/18.
//  Copyright © 2018 Luca Pascarella. All rights reserved.
//

#ifndef Test1_h
#define Test1_h


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <assert.h>
#include "RingBuffer.h"
    

    
    bool Test_CreateAndDestroyRing(void);
    bool Test_Size(void);
    bool Test_FreeSpace(void);
    bool Test_FullSpace(void);
    bool Test_FillAll(void);

    
    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif
    
#endif /* Test1_h */
