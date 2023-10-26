#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

void initChunk(Chunk* chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = NULL;
  chunk->lineCount = 0;
  chunk->lineCap = 0;
  chunk->lines = NULL;
  initValueArray(&chunk->constants);
}

void freeChunk(Chunk* chunk) {
  FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
  FREE_ARRAY(LineStart*, chunk->lines, chunk->lineCap);
  freeValueArray(&chunk->constants);
  initChunk(chunk);
}

void writeChunk(Chunk* chunk, uint8_t byte, int line) {
  if (chunk->capacity < chunk->count + 1) {
    int oldCapacity = chunk->capacity;
    chunk->capacity = GROW_CAPACITY(oldCapacity);
    chunk->code = GROW_ARRAY(uint8_t, chunk->code,
        oldCapacity, chunk->capacity);
  }

  chunk->code[chunk->count] = byte;
  chunk->count++;

  if (chunk->lineCount > 0 && chunk->lines[chunk->lineCount - 1].line == line) {
    return;
  }

  if (chunk->lineCap < chunk->lineCount + 1) {
    int oldCap = chunk->lineCap;
    chunk->lineCap = GROW_CAPACITY(oldCap);
    chunk->lines = GROW_ARRAY(LineStart, chunk->lines, oldCap, chunk->lineCap);
  }

  LineStart* linestart = &chunk->lines[chunk->lineCount++];
  linestart->offset = chunk->count-1;
  // linestart->line;
}

int addConstant(Chunk* chunk, Value value) {
  writeValueArray(&chunk->constants, value);
  return chunk->constants.count - 1;
}

int getLine(Chunk* chunk, int instr) {
  int start = 0;
  int end = chunk->lineCount - 1;

  for (;;) {
    int mid = (start + end) / 2;
    LineStart* line = &chunk->lines[mid];
    if (instr < line->offset) {
      end = mid - 1;
    }
    else if (mid == chunk->lineCount - 1 || instr < chunk->lines[mid + 1].offset) {
      return line->line;
    }
    else {
      start = mid + 1;
    }
  }
}

