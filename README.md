# RingBuffer
RingBuffer is an open-source, versatile, and optimized version of a ring buffer memory. It has been implemented in C to fit limited resource microcontrollers such as Microchip Inc. MCUs. This implementation allows both ring and linear access enabling standard functions to access the ring space. In addition, it is compatible with one-shot and cycling DMA modules.

## Examples
### Ring object creation

The code is re-entrant and allows multiple instances. The returned 'object' handles a single instance.

```C
RING_DATA *ring1 = RING_InitBuffer(NULL, 16);
RING_DATA *ring2 = RING_InitBuffer(NULL, 123);
```


### Ring object destroy

The user must care of unused instances destroying them when no more needed.

```C
RING_DeinitializeBuffer(ring);
````

## Linear access
Both read and write operations can be execute on linear space.

### Read with linear access
This snippet reads _readable_ bytes from the ring buffer memory. With this technique, _memcpy_ can be changed with any user function. 
```C
uint8_t dest[16], *src;
size_t readable;

src = RING_GetBufferDirectly(ring, &readable, sizeof(dest));
memcpy(dest, src, readable);
```

### Write with linear access
This snippet writes _toWrite_ bytes into the ring buffer memory. With this technique, _memcpy_ can be substituted with any user function. 
```C
uint8_t src[16], *dest;
size_t toWrite;

memset(src, 'L', sizeof(src));
dest = RING_AddBufferDirectly(ring, &toWrite, sizeof(src));
memcpy(dest, src, toWrite);
```

## Get free and filled space
Two inline functions return the whole and linear accessible free space, respectively. Same for the filled space. 

```C
size_t freeSpace = RING_GetFreeSpace(ring);
size_t freeLinearSpace = RING_GetFreeLinearSpace(ring);

size_t fullSpace = RING_GetFullSpace(ring);
size_t fullLinearSpace = RING_GetFullLinearSpace(ring);
```
