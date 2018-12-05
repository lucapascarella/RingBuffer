/* ************************************************************************** */
/** Descriptive File Name
 
 @Company
 LP Systems
 lpsystems.eu
 
 @File Name
 RingBuffer.c
 
 @Author
 Luca Pascarella
 lucapascarella.com
 
 @Summary
 This functions provide the microcontroller optimized version of the basic
 functions for implmenting a ring buffer.
 
 @Description
 This file and the associated header implement a C optimized version of a
 ring buffer. A preprocessor directive must be used to select the base buffer
 size that can be both POWER of 2 than arbitrary size.
 An optimized linear acceess also using a DMA peripheral can be used.
 */


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "RingBuffer.h"

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */



/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

// Returns the rounded down power of 2 of the given number

#ifdef POWER_2_OPTIMIZATION
static size_t RING_RoundDown(size_t x) {
    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >> 16);
    return x - (x >> 1);
}
#endif

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

/*****************************************************************************
 * Function:        RING_DATA * RING_InitBuffer(const uint8_t *buf, size_t size)
 
 * Description:     This function creates a RING_DATA object that allows circling the linear memory.
                    A linearize access to ring space is provided through exposed functions.
 
 * PreCondition:    None
 
 * Input:           buf is the predefined ring buffer, NULL to require a dynamic allocation
                    size is the size of the pre-allocated memory or the required memory
 
 * Return:          Pointer to a RING_DATA type allocated in the dynamic memory
 
 * Side Effects:    RING_DeinitializeBuffer() must be called to correctly release dynamic memory
 
 * Overview:        None
 
 * Note:            The macro POWER_2_OPTIMIZATION speeds up the ring buffer access
                    by rounding down to the closed power of 2
 *****************************************************************************/
RING_DATA * RING_InitBuffer(const uint8_t *buf, size_t size) {
    
    RING_DATA *ring;
    
    if (size == 0)
        return NULL;
    
    if ((ring = malloc(sizeof (RING_DATA))) == NULL)
        return NULL;
    
    // Reset fields
    ring->head = 0;
    ring->tail = 0;
#ifdef POWER_2_OPTIMIZATION
    ring->size = (size_t) RING_RoundDown(size);
#else
    ring->size = size;
#endif
    
    // Check if user already allocates memory
    if (buf == NULL) {
        if((ring->buf = malloc(sizeof (char) * ring->size)) == NULL){
            free((RING_DATA*)ring);
            return NULL;
        }
        ring->dymamic = true;
    }else{
        ring->buf = (uint8_t*) buf;
        ring->dymamic = false;
    }
    
    return ring;
}

/*****************************************************************************
 * Function:        RING_DeinitializeBuffer(const RING_DATA *ring)
 
 * Description:     This function releases dynamically allocated memories
 
 * PreCondition:    RING_InitBuffer() must be successfully called
 
 * Input:           ring the RING_DATA pre-allocated object
 
 * Return:          None
 
 * Side Effects:    Dynamic memory will be released
 
 * Overview:        None
 
 * Note:            None
 *****************************************************************************/
void RING_DeinitializeBuffer(const RING_DATA *ring) {
    if (ring->dymamic)
        free((RING_DATA*)ring->buf);
    free((RING_DATA*)ring);
}

/*****************************************************************************
 * Function:        RING_GetBufferSize(const RING_DATA * const ring)
 
 * Description:     This function returns the associated buffer size
 
 * PreCondition:    RING_InitBuffer() must be successfully called
 
 * Input:           ring the RING_DATA pre-allocated object
 
 * Return:          The associate buffer size
 
 * Side Effects:    None
 
 * Overview:        None
 
 * Note:            The buffer size is always bigger than the maximum available free space
                    To know free space use RING_GetFreeSpace() or RING_GetFreeLinearSpace()
 *****************************************************************************/
inline size_t RING_GetBufferSize(const RING_DATA * const ring) {
    return ring->size;
}

/*****************************************************************************
 * Function:        RING_GetFreeSpace(const RING_DATA * const ring)
 
 * Description:     This function returns the ring buffer free space
 
 * PreCondition:    RING_InitBuffer() must be successfully called
 
 * Input:           ring the RING_DATA pre-allocated object
 
 * Return:          The number of free bytes
 
 * Side Effects:    None
 
 * Overview:        None
 
 * Note:            The free space may not be linear
 *****************************************************************************/
inline size_t RING_GetFreeSpace(const RING_DATA * const ring) {
    return ((ring->tail + ring->size - ring->head - 1) % ring->size + 1) - 1;
}

/*****************************************************************************
 * Function:        RING_GetFreeLinearSpace(const RING_DATA * const ring)
 
 * Description:     This function returns the maximum linear free space available into ring buffer
 
 * PreCondition:    RING_InitBuffer() must be successfully called
 
 * Input:           ring the RING_DATA pre-allocated object
 
 * Return:          The number of linear free bytes
 
 * Side Effects:    None
 
 * Overview:        None
 
 * Note:            The linear free space may be less than RING_GetFreeSpace()
 *****************************************************************************/
inline size_t RING_GetFreeLinearSpace(const RING_DATA * const ring) {
    if (ring->head == 0 && ring->tail == 0)
        return ring->size - 2; //
    else if (ring->head >= ring->tail)
        return ring->size - ring->head;
    else
        return ring->tail - ring->head - 1;
}

/*****************************************************************************
 * Function:        RING_GetFullSpace(const RING_DATA * const ring)
 
 * Description:     This function returns the filled space available into ring buffer
 
 * PreCondition:    RING_InitBuffer() must be successfully called
 
 * Input:           ring the RING_DATA pre-allocated object
 
 * Return:          The number of filled bytes
 
 * Side Effects:    None
 
 * Overview:        None
 
 * Note:            The filled space may be not linear
 *****************************************************************************/
inline size_t RING_GetFullSpace(const RING_DATA * const ring) {
    return ring->size - ((ring->tail + ring->size - ring->head - 1) % ring->size + 1);
}

/*****************************************************************************
 * Function:        RING_GetFullLinearSpace(const RING_DATA *ring)
 
 * Description:     This function returns the filled free linear space available into ring buffer
 
 * PreCondition:    RING_InitBuffer() must be successfully called
 
 * Input:           ring the RING_DATA pre-allocated object
 
 * Return:          The number of linear filled bytes
 
 * Side Effects:    None
 
 * Overview:        None
 
 * Note:            The linear filled space may be less than RING_GetFullSpace()
 *****************************************************************************/
inline size_t RING_GetFullLinearSpace(const RING_DATA *ring) {
    if (ring->head >= ring->tail)
        return ring->head - ring->tail;
    else
        return ring->size - ring->tail;
}

/*****************************************************************************
 * Function:        RING_IncreaseHead(RING_DATA * const ring, size_t count)
 
 * Description:     This function increments the ring head pointer. It allows
                    manipulating internal pointers simulating a buffer write.
 
 * PreCondition:    RING_InitBuffer() must be successfully called
 
 * Input:           ring the RING_DATA pre-allocated object
                    count the size to add to the head of the
 
 * Return:          None
 
 * Side Effects:    None
 
 * Overview:        None
 
 * Note:            The user must care that count is less than free space
 *****************************************************************************/
inline void RING_IncreaseHead(RING_DATA * const ring, size_t count) {
#ifdef POWER_2_OPTIMIZATION
    ring->head = (ring->head + count) & (ring->size - 1);
#else
    ring->head = (ring->head + count) % ring->size;
#endif
}

/*****************************************************************************
 * Function:        RING_IncreaseTail(RING_DATA * const ring, size_t count)
 
 * Description:     This function increments the ring tail pointer. It allows.
                    manipulating internal pointers simulating a buffer read
 
 * PreCondition:    RING_InitBuffer() must be successfully called
 
 * Input:           ring the RING_DATA pre-allocated object
 count the size to add to the head of the
 
 * Return:          None
 
 * Side Effects:    None
 
 * Overview:        None
 
 * Note:            The user must care that count is less than full space
 *****************************************************************************/
inline void RING_IncreaseTail(RING_DATA * const ring, size_t count) {
#ifdef POWER_2_OPTIMIZATION
    ring->tail = (ring->tail + count) & (ring->size - 1);
#else
    ring->tail = (ring->tail + count) % ring->size;
#endif
}

/*****************************************************************************
 * Function:        RING_GetHeadPointer(const RING_DATA * const ring)
 
 * Description:     This function returns the head pointer. It represents the first free byte.
 
 * PreCondition:    RING_InitBuffer() must be successfully called
 
 * Input:           ring the RING_DATA pre-allocated object
 
 * Return:          The head pointer
 
 * Side Effects:    None
 
 * Overview:        None
 
 * Note:            None
 *****************************************************************************/
inline uint8_t * RING_GetHeadPointer(const RING_DATA * const ring) {
    return ring->buf + ring->head;
}

/*****************************************************************************
 * Function:        RING_GetTailPointer(const RING_DATA * const ring)
 
 * Description:     This function returns the tail pointer. It represents the first filled byte.
 
 * PreCondition:    RING_InitBuffer() must be successfully called
 
 * Input:           ring the RING_DATA pre-allocated object
 
 * Return:          The tail pointer
 
 * Side Effects:    None
 
 * Overview:        None
 
 * Note:            None
 *****************************************************************************/
inline uint8_t * RING_GetTailPointer(const RING_DATA * const ring) {
    return ring->buf + ring->tail;
}

/*****************************************************************************
 * Function:        RING_AddByte(RING_DATA * const ring, uint8_t val)
 
 * Description:     This function tries to add a single byte into ring buffer.
 
 * PreCondition:    RING_InitBuffer() must be successfully called
 
 * Input:           ring the RING_DATA pre-allocated object
 val the byte to write
 
 * Return:          true if the byte is added succesfully
 
 * Side Effects:    None
 
 * Overview:        None
 
 * Note:            None
 *****************************************************************************/
bool RING_AddByte(RING_DATA * const ring, uint8_t val) {
    if (RING_GetFreeSpace(ring) > 0) {
        ring->buf[ring->head] = val;
#ifdef POWER_2_OPTIMIZATION
        ring->head = (ring->head + 1) & (ring->size - 1);
#else
        ring->head = (ring->head + 1) % ring->size;
#endif
        return true;
    }
    return false;
}

/*****************************************************************************
 * Function:        RING_AddBuffer(RING_DATA * const ring, uint8_t *buf, size_t size)
 
 * Description:     This function internally copies the given buffer.
 
 * PreCondition:    RING_InitBuffer() must be successfully called
 
 * Input:           ring the RING_DATA pre-allocated object
                    buf pointer of the buffer to copy
                    size number of bytes to copy
 
 * Return:          The number of actual bytes copied
 
 * Side Effects:    None
 
 * Overview:        None
 
 * Note:            None
 *****************************************************************************/
size_t RING_AddBuffer(RING_DATA * const ring, uint8_t *buf, size_t size) {
    size_t i, writable;
    
    writable = min(RING_GetFreeSpace(ring), size);
    for (i = 0; i < writable; i++) {
        ring->buf[ring->head] = buf[i];
#ifdef POWER_2_OPTIMIZATION
        ring->head = (ring->head + 1) & (ring->size - 1);
#else
        ring->head = (ring->head + 1) % ring->size;
#endif

    }
    return i;
}

/*****************************************************************************
 * Function:        RING_AddBufferDirectly(RING_DATA * const ring, size_t *toWrite, size_t size)
 
 * Description:     This function allows an external function to directly write into a linear space of the ring byffer.
 
 * PreCondition:    RING_InitBuffer() must be successfully called
 
 * Input:           ring the RING_DATA pre-allocated object
                    toWrite number of byte that must be copied
                    size number of required bytes
 
 * Return:          The pointer of the first free location. It can be used by an external function to directly write into ring buffer
 
 * Side Effects:    The ring buffer pointer is incremented in advance by this function, therefore, the user must fill that space before use it
 
 * Overview:        None
 
 * Note:            The pointer is incremented in advance
 *****************************************************************************/
uint8_t * RING_AddBufferDirectly(RING_DATA * const ring, size_t *toWrite, size_t size) {
    uint8_t *ptr;
    
    *toWrite = min(RING_GetFreeLinearSpace(ring), size);
    ptr = &ring->buf[ring->head];
#ifdef POWER_2_OPTIMIZATION
    ring->head = (ring->head + *toWrite) & (ring->size - 1);
#else
    ring->head = (ring->head + *toWrite) % ring->size;
#endif
    
    return ptr;
}

/*****************************************************************************
 * Function:        RING_GetByte(RING_DATA * const ring, uint8_t *byte)
 
 * Description:     This function returns a byte if available
 
 * PreCondition:    RING_InitBuffer() must be successfully called
 
 * Input:           ring the RING_DATA pre-allocated object
 byte* readback byta
 
 * Return:          true if the byte is read
 
 * Side Effects:    None
 
 * Overview:        None
 
 * Note:            None
 *****************************************************************************/
bool RING_GetByte(RING_DATA * const ring, uint8_t *byte) {
    if (RING_GetFullSpace(ring) > 0) {
        *byte = ring->buf[ring->tail];
#ifdef POWER_2_OPTIMIZATION
        ring->tail = (ring->tail + 1) & (ring->size - 1);
#else
        ring->tail = (ring->tail + 1) % ring->size;
#endif
        return true;
    } else {
        return false;
    }
}

/*****************************************************************************
 * Function:        RING_GetByteSimple(RING_DATA * const ring)
 
 * Description:     This function returns a byte
 
 * PreCondition:    RING_InitBuffer() must be successfully called
 
 * Input:           ring the RING_DATA pre-allocated object
 
 * Return:          the read byte
 
 * Side Effects:    None
 
 * Overview:        None
 
 * Note:            The user must check the byte aveability
 *****************************************************************************/
inline uint8_t RING_GetByteSimple(RING_DATA * const ring) {
    uint8_t temp;
    temp = ring->buf[ring->tail];
#ifdef POWER_2_OPTIMIZATION
    ring->tail = (ring->tail + 1) & (ring->size - 1);
#else
    ring->tail = (ring->tail + 1) % ring->size;
#endif
    return temp;
}

/*****************************************************************************
 * Function:        RING_GetBuffer(RING_DATA * const ring, uint8_t *ptr, size_t len)
 
 * Description:     This function gets len bytes into user buffer
 
 * PreCondition:    RING_InitBuffer() must be successfully called
 
 * Input:           ring the RING_DATA pre-allocated object
                    ptr user destination buffer
                    len user destination length
 
 * Return:          the actual number of got bytes
 
 * Side Effects:    None
 
 * Overview:        None
 
 * Note:            None
 *****************************************************************************/
size_t RING_GetBuffer(RING_DATA * const ring, uint8_t *ptr, size_t len){
    
    size_t i, min;
    
    min = min(RING_GetFullSpace(ring), len);
    
    for (i = 0; i < min; i++) {
        ptr[i] = ring->buf[ring->tail];
#ifdef POWER_2_OPTIMIZATION
        ring->tail = (ring->tail + 1) & (ring->size - 1);
#else
        ring->tail = (ring->tail + 1) % ring->size;
#endif
    }
    
    return i;
}

/*****************************************************************************
 * Function:        RING_GetBufferDirectly(RING_DATA * const ring, size_t *toRead, size_t size)
 
 * Description:     This function returns a pointer of a linear filled space
 
 * PreCondition:    RING_InitBuffer() must be successfully called
 
 * Input:           ring the RING_DATA pre-allocated object
 val the byte to write
 
 * Return:          true if the byte is added succesfully
 
 * Side Effects:    None
 
 * Overview:        None
 
 * Note:            None
 *****************************************************************************/
uint8_t * RING_GetBufferDirectly(RING_DATA * const ring, size_t *toRead, size_t size) {
    uint8_t *ptr;
    size_t readable;
    
    readable = RING_GetFullLinearSpace(ring);
    
    *toRead = min(readable, size);
    ptr = &ring->buf[ring->tail];
#ifdef POWER_2_OPTIMIZATION
    ring->tail = (ring->tail + *toRead) & (ring->size - 1);
#else
    ring->tail = (ring->tail + *toRead) % ring->size;
#endif
    
    return ptr;
}

/*****************************************************************************
 * Function:        RING_PickBytes(const RING_DATA *ring, uint8_t *buf, size_t len)
 
 * Description:     This function picks bytes without removing from the ring buffer
 
 * PreCondition:    RING_InitBuffer() must be successfully called
 
 * Input:           ring the RING_DATA pre-allocated object
                    buf the buffer where copy bytes
                    len the maximum number of bytes to read
 
 * Return:          the actual number of picked bytes
 
 * Side Effects:    None
 
 * Overview:        None
 
 * Note:            None
 *****************************************************************************/
size_t RING_PickBytes(const RING_DATA *ring, uint8_t *buf, size_t len) {
    size_t i, min;
    size_t tail;
    
    min = min(RING_GetFullSpace(ring), len);
    tail = ring->tail;
    for (i = 0; i < min; i++) {
        buf[i] = ring->buf[tail];
#ifdef POWER_2_OPTIMIZATION
        tail = (tail + 1) & (ring->size - 1);
#else
        tail = (tail + 1) % ring->size;
#endif
    }
    return i;
}






/* *****************************************************************************
 End of File
 */
