/** **************************************************************************
 @Company
 LP Systems https://lpsystems.eu
 
 @File Name
 RingBuffer.h
 
 @Author
 Luca Pascarella https://lucapascarella.com
 
 @Summary
 These functions implement an optimized version of a ring buffer.
 
 @Description
 This file implements a C optimized version of a ring buffer. It allows a
 combination of both ring and direct/linear access to the ring memory space.
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

#ifndef _RING_BUFFER_H    /* Guard against multiple inclusion */
#define _RING_BUFFER_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif
    
    
    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */
    
#define POWER_2_OPTIMIZATION
    
#define min(a,b)    (((a)<(b))?(a):(b))
    
    
    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************
    
    typedef struct {
        uint8_t * buf;
        size_t head;
        size_t tail;
        size_t size;
        bool dymamic;
    } RING_DATA;
    
    
    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************
    
    // Initialization functions
    RING_DATA * RING_InitBuffer(const uint8_t *buf, size_t size);
    void RING_DeinitializeBuffer(const RING_DATA *ring);
    
    // Space functions
    size_t RING_GetBufferSize(const RING_DATA * const ring);
    size_t RING_GetFreeSpace(const RING_DATA * const ring);
    size_t RING_GetFreeLinearSpace(const RING_DATA * const ring);
    size_t RING_GetFullSpace(const RING_DATA * const ring);
    size_t RING_GetFullLinearSpace(const RING_DATA * const ring);
    
    // Pointers change
    void RING_IncreaseHead(RING_DATA * const ring, size_t count);
    void RING_IncreaseTail(RING_DATA * const ring, size_t count);
    
    // Access internal pointers
    uint8_t * RING_GetHeadPointer(const RING_DATA * const ring);
    uint8_t * RING_GetTailPointer(const RING_DATA * const ring);
    
    // Write functions
    bool RING_AddByte(RING_DATA * const ring, uint8_t val);
    size_t RING_AddBuffer(RING_DATA * const ring, uint8_t *buf, size_t size);
    uint8_t * RING_AddBufferDirectly(RING_DATA * const ring, size_t *toWrite, size_t size);
    
    // Read functions
    bool RING_GetByte(RING_DATA * const ring, uint8_t *byte);
    uint8_t RING_GetByteSimple(RING_DATA * const ring);
    size_t RING_GetBuffer(RING_DATA * const ring, uint8_t *ptr, size_t len);
    uint8_t * RING_GetBufferDirectly(RING_DATA * const ring, size_t *toRead, size_t size);
    
    // Pick
    size_t RING_PickBytes(const RING_DATA *ring, uint8_t *buf, size_t len);
    
    
    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _RING_BUFFER_H */

/* *****************************************************************************
 End of File
 */
