/** **************************************************************************
 @Company
 LP Systems https://lpsystems.eu
 
 @File Name
 Test1.h
 
 @Author
 Luca Pascarella https://lucapascarella.com
 
 @Summary
 This file is the first test for the RingBuffer library
 
 @Description
 This file is the entry point for testing the RingBuffer library.
 A preprocessor directive must be used to select the base buffer
 size that can be both POWER of 2 than arbitrary size.
 
 @License
 Copyright (C) 2016 LP Systems
 
 Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
 in compliance with the License. You may obtain a copy of the License at
 
 https://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software distributed under the License
 is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
 or implied. See the License for the specific language governing permissions and limitations under
 the License.
 ************************************************************************** */
#ifndef Test1_h
#define Test1_h


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif
    
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "RingBuffer.h"
#include "string.h"
    
    
    bool Test_CreateAndDestroyRing(void);
    bool Test_Size(void);
    bool Test_FreeSpace(void);
    bool Test_FullSpace(void);
    bool Test_Space(void);
    bool Test_SpaceAdvanced(void);
    bool Test_FillAll(void);
    bool Test_MultipleFill(void);
    bool Test_MultipleFillLong(void);
    bool Test_LinearAdd(void);
    bool Test_LinearGet(void);
    
    
    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* Test1_h */
