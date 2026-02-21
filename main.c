/**
 * Description: An arena allocator implementation.

 * Arena allocators are just a linear memory with a moving cursor.
 * Allocation happens with the cursor moving forward.
 * Freeing (deallocating) happens with resetting the cursor position to 0.
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  unsigned char *base; // char* because pointer arithmetic must be byte-accurate
  size_t size;
  size_t offset;
} Arena;

typedef enum {
  CLASS_HOBBIT,
  CLASS_RANGER,
  CLASS_ELF,
  CLASS_DWARF,
  CLASS_WIZARD,
  CLASS_ORC,
  CLASS_URUK,
  CLASS_GONDOR_SOLDIER
} EntityClass;

typedef struct {
  unsigned int id;
  EntityClass class;

  double x, y;
  double vx, vy;

  float rotation;
  float health;

  unsigned int flags; // bitmask: alive, visible, etc.
} Entity;

typedef struct {
  Entity **list; // pointer array (arena allocated)
  unsigned int count;
  unsigned int capacity;
} World;

typedef struct {
  double x, y;
} Point;

// core operations
void arena_init(Arena *arena, size_t size) {
  arena->base = malloc(size);
  if (!arena->base) {
    fprintf(stderr, "Arena malloc failed\n");
  }
  arena->size = size;
  arena->offset = 0;
}

void *arena_alloc(Arena *arena, size_t size) {
  size_t align = 8;
  size = (size + (align - 1)) & ~(align - 1);

  if (arena->offset + size > arena->size) {
    fprintf(stderr, "Not enough space\n");
    return NULL;
  }

  void *ptr = arena->base + arena->offset;
  arena->offset += size;
  return ptr;
}

void arena_reset(Arena *arena) { arena->offset = 0; }

void arena_destroy(Arena *arena) { free(arena->base); }

void world_init(World *world, Arena *arena, unsigned int capacity) {
  world->count = 0;
  world->capacity = capacity;
  world->list = arena_alloc(arena, sizeof(Entity *) * capacity);
}

void world_update();
void world_print(World *world, int n) {
  for (int i = 0; i < n; i++) {
    printf("Info: %p\n", world->list[i]);
  }
}

void spawn_entities(World *world, Arena *arena, unsigned int n) {
    for (unsigned int i = 0; i < n && world->count < world->capacity; i++) {
        Entity *e = arena_alloc(arena, sizeof(Entity));

        world->list[world->count] = e;

        e->id = world->count;
        e->class = rand() % 8;
        e->x = e->y = 0;
        e->vx = e->vy = 0;
        e->rotation = 0;
        e->health = 100.0f;
        e->flags = 0;

        world->count++;
    }
}

int main() {
  Arena arena;
  arena_init(&arena, 1000000);

  World world;
  world_init(&world, &arena, 1000);
  spawn_entities(&world, &arena, 1000);

  world_print(&world, 100);

  arena_destroy(&arena);
}
