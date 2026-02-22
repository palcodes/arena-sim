# Linear Arena Allocator

High-performance linear memory allocator and entity management system implemented in C.

---

### Core Architecture

#### 1. Arena Allocator

* **Mechanism:** Linear cursor-based allocation.
* **Performance:**  allocation and deallocation.
* **Alignment:** Enforces 8-byte boundaries.
* **Memory Safety:** Fixed-size pool prevents fragmentation but requires manual lifetime tracking.

#### 2. Entity System

* **World:** Contiguous array of entity pointers.
* **Entity:** 48/54-byte struct containing class, spatial data, and status flags.

---

### API Reference

| Function | Description |
| --- | --- |
| `arena_init` | Allocates the backing memory pool. |
| `arena_alloc` | Reserves an aligned block from the pool. |
| `arena_reset` | Reclaims all pool memory instantly. |
| `world_init` | Pre-allocates entity list within the arena. |
| `spawn_entities` | Batch-allocates and initializes entities. |

---

### Build & Run

1. **Compile:** `make`
2. **Execute:** `./arena_app`
3. **Clean:** `make clean`
