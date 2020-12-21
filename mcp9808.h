#ifndef _MCP9808_H
#define _MCP9808_H

#include <stdint.h>

void mcp9808_init();
uint16_t mcp9808_read_deg();

#endif //_MCP9808_H