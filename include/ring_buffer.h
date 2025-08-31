#ifndef	RING_BUFFER_H
#define RING_BUFFER_H

#include <stdint.h>
#include <stdbool.h>

struct ring_buffer {
        uint8_t *buffer;
        uint8_t write_index;
        uint8_t read_index;
        uint8_t size;
};

/* 
 * Ring Buffer APIs
 */

bool ring_buffer_empty(struct ring_buffer *q);
bool ring_buffer_full(struct ring_buffer *q);
uint8_t ring_buffer_set(struct ring_buffer *q, uint8_t data);
uint8_t ring_buffer_get(struct ring_buffer *q);

#endif /* RING_BUFFER_H */
