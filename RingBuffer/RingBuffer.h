/* ************************************************************************** */
/** Descriptive File Name
 
 @Company
 Company Name
 
 @File Name
 filename.h
 
 @Summary
 Brief description of the file.
 
 @Description
 Describe the purpose of this file.
 */
/* ************************************************************************** */

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
//#include "system_config.h"
//#include "system_definitions.h"


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif
    
    
    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */
    
    /*  A brief description of a section can be given directly below the section
     banner.
     */
    
    
    /* ************************************************************************** */
    /** Descriptive Constant Name
     
     @Summary
     Brief one-line summary of the constant.
     
     @Description
     Full description, explaining the purpose and usage of the constant.
     <p>
     Additional description in consecutive paragraphs separated by HTML
     paragraph breaks, as necessary.
     <p>
     Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
     
     @Remarks
     Any additional remarks
     */

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
