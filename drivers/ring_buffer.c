#include <ring_buffer.h>

bool ring_buffer_empty(struct ring_buffer *q) {
	return q->read_index == q->write_index;
}

bool ring_buffer_full(struct ring_buffer *q) 
{	
	uint8_t reserved_index = q->write_index + 1;
	if (reserved_index == q->size) 
		reserved_index = 0;
	
	return reserved_index == q->read_index;
}

uint8_t ring_buffer_put(struct ring_buffer *q, uint8_t data)
{
	q->buffer[q->write_index] = data; // *(q->buffer + q->write_index)

	/* Avoid modulo operation */
	q->write_index++;
	if (q->write_index == q->size)
		q->write_index = 0;

	return 0;
}

uint8_t ring_buffer_get(struct ring_buffer *q)
{
	uint8_t ret = q->buffer[q->read_index];

	/* Avoid modulo operation */
	q->read_index++;
	if (q->read_index == q->size)
		q->read_index = 0;

	return ret;
}

