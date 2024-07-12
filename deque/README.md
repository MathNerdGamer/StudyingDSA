# Array-Based Deque

This is an implementation (in [Java](./Deque.java) and in C ([header](./deque.h) / [source](./deque.c))) of an array-based Deque.

#### [Video of C implementation.](https://www.youtube.com/watch?v=vDb8A4eaLGw)

**NOTE:** There are two logic errors in the code as shown in the video:
1. When doing `push_back()` / `push_front()`, the conditional `deque->size == 0` should actually be `deque->size == 0 && deque->front == deque->back`.
2. When copying the old array to the new array in `rebuild_deque`, I should have copied `deque->type_size * deque->front` bytes, not `deque->type_size * deque->back`.