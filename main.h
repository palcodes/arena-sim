#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>

// --- Arena Allocator ---

typedef struct {
  unsigned char *base;
  size_t size;
  size_t offset;
} Arena;

void arena_init(Arena *arena, size_t size);
void *arena_alloc(Arena *arena, size_t size);
void arena_reset(Arena *arena);
void arena_destroy(Arena *arena);

// --- Game Entities ---

typedef enum {
  CLASS_HOBBIT, CLASS_RANGER, CLASS_ELF, CLASS_DWARF,
  CLASS_WIZARD, CLASS_ORC, CLASS_URUK, CLASS_GONDOR_SOLDIER
} EntityClass;

typedef struct {
  unsigned int id;
  EntityClass class;
  double x, y;
  double vx, vy;
  float rotation;
  float health;
  unsigned int flags;
} Entity;

typedef struct {
  Entity **list;
  unsigned int count;
  unsigned int capacity;
} World;

// --- World Operations ---

void world_init(World *world, Arena *arena, unsigned int capacity);
void world_print(World *world, int n);
void spawn_entities(World *world, Arena *arena, unsigned int n);

#endif
