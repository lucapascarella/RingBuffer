/** **************************************************************************
 @Company
 LP Systems https://lpsystems.eu
 
 @File Name
 main.c
 
 @Author
 Luca Pascarella https://lucapascarella.com
 
 @Summary
 This file is a main used to test the RingBuffer library
 
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

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "Test1.h"
#include "RingBuffer.h"

#define SPACE_SIZE      8

void printb(uint8_t *buf, size_t size);
void testLinearSpaces(RING_DATA *ring);
void test1(void);

int main(int argc, const char * argv[]) {
    printf("Start RingBuffer\n\n");
    
    printf("Test creation and destroing: %c\n", Test_CreateAndDestroyRing()?'Y':'N');
    printf("Test size: %c\n", Test_Size()?'Y':'N');
    printf("Test free space: %c\n", Test_FreeSpace()?'Y':'N');
    printf("Test full space: %c\n", Test_FullSpace()?'Y':'N');
    printf("Test space: %c\n", Test_Space()?'Y':'N');
    printf("Test space advanced: %c\n", Test_SpaceAdvanced()?'Y':'N');
    printf("Test fill all: %c\n", Test_FillAll()?'Y':'N');
    printf("Test multiple fill: %c\n", Test_MultipleFill()?'Y':'N');
    printf("Test multiple fill long: %c\n", Test_MultipleFillLong()?'Y':'N');
    printf("Test linear add: %c\n", Test_LinearAdd()?'Y':'N');
    printf("Test linear get: %c\n", Test_LinearGet()?'Y':'N');
    
    printf("\nRingBuffer ended\n");
    return 0;
}
