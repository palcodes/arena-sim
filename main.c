#include "main.h"

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
  world->list = (Entity **)arena_alloc(arena, sizeof(Entity *) * capacity);
}

void world_print(World *world, int n) {
  for (int i = 0; i < n && i < world->count; i++) {
    printf("Info: %p\n", (void *)world->list[i]);
  }
}

void spawn_entities(World *world, Arena *arena, unsigned int n) {
  for (unsigned int i = 0; i < n && world->count < world->capacity; i++) {
    Entity *e = (Entity *)arena_alloc(arena, sizeof(Entity));
    if (!e) break;

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
  return 0;
}
