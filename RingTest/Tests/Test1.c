//
//  Test1.c
//  RingTest
//
//  Created by Luca Pascarella on 12/5/18.
//  Copyright © 2018 Luca Pascarella. All rights reserved.
//

#include "Test1.h"
#include "string.h"

#define TEST_1_RING_BUFFER_SPACE        17

bool Test_CreateAndDestroyRing(void) {
    
    bool rtn = true;

    RING_DATA *ring1, *ring2;
    uint8_t dynBuffer[TEST_1_RING_BUFFER_SPACE];
    
    // Test user given buffer
    ring1 = RING_InitBuffer(dynBuffer, TEST_1_RING_BUFFER_SPACE);
    rtn &= (ring1 != NULL);
    
    // Test function provided buffer
    ring2 = RING_InitBuffer(NULL, TEST_1_RING_BUFFER_SPACE);
    rtn &= (ring2 != NULL);
    
    // Release memory
    RING_DeinitializeBuffer(ring1);
    RING_DeinitializeBuffer(ring2);
    
    return rtn;
}

bool Test_Size(void) {
    
    RING_DATA *ring1, * ring2;
    size_t size1, size2;
    bool rtn = true;

    // Create Ring object
    ring1 = RING_InitBuffer(NULL, 19);
    rtn &= (ring1 != NULL);
    ring2 = RING_InitBuffer(NULL, 35);
    rtn &= (ring2 != NULL);
    
    size1 = RING_GetBufferSize(ring1);
    size2 = RING_GetBufferSize(ring2);
#ifdef POWER_2_OPTIMIZATION
    rtn &= (size1 == 16);
    rtn &= (size2 == 32);
#else
    rtn &= (size1 == 19);
    rtn &= (size2 == 35);
#endif
    
    // Destroy Ring object
    RING_DeinitializeBuffer(ring1);
    RING_DeinitializeBuffer(ring2);
    
    return rtn;
}

bool Test_FreeSpace(void) {
    RING_DATA *ring;
    size_t free, freeLinear;
     bool rtn = true;
    
    ring = RING_InitBuffer(NULL, 17);
    rtn &= (ring != NULL);
    
    free = RING_GetFreeSpace(ring);
    freeLinear = RING_GetFreeLinearSpace(ring);
#ifdef POWER_2_OPTIMIZATION
    rtn &= (free == 15);
    rtn &= (freeLinear == 14);
#else
    rtn &= (free == 16);
    rtn &= (freeLinear == 15);
#endif
    RING_DeinitializeBuffer(ring);
    
    return rtn;
}

bool Test_FullSpace(void) {
    RING_DATA *ring;
    size_t full, fullLinear;
    bool rtn = true;
    
    ring = RING_InitBuffer(NULL, 17);
    rtn &= (ring != NULL);
    
    full = RING_GetFullSpace(ring);
    fullLinear = RING_GetFullLinearSpace(ring);
#ifdef POWER_2_OPTIMIZATION
    rtn &= (full == 0);
    rtn &= (fullLinear == 0);
#else
    rtn &= (full == 0);
    rtn &= (fullLinear == 0);
#endif
    RING_DeinitializeBuffer(ring);
    
    return rtn;
}

bool Test_FillAll(void){
    RING_DATA *ring;
    char buf[] = "0123456789ABCDEF"; // 16 bytes
    size_t len;
    bool rtn = true;
    
    // Test same size
    ring = RING_InitBuffer(NULL, 16);
    rtn &= (ring != NULL);
    len = RING_AddBuffer(ring, (uint8_t*) buf, strlen(buf));
    rtn &= (len == 15);
    RING_DeinitializeBuffer(ring);
    
    ring = RING_InitBuffer(NULL, 9);
    rtn &= (ring != NULL);
    len = RING_AddBuffer(ring, (uint8_t*) buf, strlen(buf));
#ifdef POWER_2_OPTIMIZATION
    rtn &= (len == 7);
#else
    rtn &= (len == 8);
#endif
    RING_DeinitializeBuffer(ring);
    
    return rtn;
}
