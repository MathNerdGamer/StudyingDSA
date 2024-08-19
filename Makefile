CC=clang
CFLAGS=-Wall -Wextra -Werror -std=c23 -DQUIET_VSCODE -Iinclude/ -O3
CFLAGS2=-Wall -Wextra -Werror -Iinclude/ -O3
BIN_DIR=bin
JAVAC=javac

hello:
	$(CC) $(CFLAGS) -DTEST hello/hello.c -o $(BIN_DIR)/hello_world
	$(JAVAC) hello/HelloWorld.java

dll:
	$(CC) $(CFLAGS) doubly_linked_list/main.c doubly_linked_list/doubly_linked_list.c -o $(BIN_DIR)/doubly_linked_list
	$(JAVAC) doubly_linked_list/DoublyLinkedList.java

deq:
	$(CC) $(CFLAGS) deque/main.c deque/deque.c -o $(BIN_DIR)/deque
	$(JAVAC) deque/Deque.java

bst:
	$(CC) $(CFLAGS) -Ideque/ binary_search_tree/main.c \
	                         binary_search_tree/binary_search_tree.c \
							 deque/deque.c \
							 -o $(BIN_DIR)/bst
	$(JAVAC) binary_search_tree/BinarySearchTree.java

avl:
	$(CC) $(CFLAGS) -Ideque/ avl_tree/main.c \
	                         avl_tree/avl_tree.c \
							 deque/deque.c \
							 -o $(BIN_DIR)/avl_tree
	$(JAVAC) avl_tree/AVLTree.java

comp:
	$(CC) $(CFLAGS2) -I/usr/include/SDL2      \
	                    sorting/max_heap.c    \
	                    sorting/rendering.c   \
	    				sorting/sorting.c     \
						sorting/utility.c     \
						sorting/main.c        \
						-lm -lSDL2 -lSDL2_ttf \
						-o $(BIN_DIR)/comparisons
# You'll need to provide your own `font.ttf` and have SDL2 installed.

pattern:
	$(CC) $(CCFLAGS) -Iinclude/                        \
					  pattern_matching/dynamic_array.c \
					  pattern_matching/bm.c            \
					  pattern_matching/kmp.c           \
					  pattern_matching/rk.c            \
					  pattern_matching/main.c          \
					  -o $(BIN_DIR)/pattern

dp:
	$(CC) $(CCFLAGS) dynamic_programming/largest_contiguous_sum.c -o $(BIN_DIR)/largest_contiguous_sum
	$(CC) $(CCFLAGS) dynamic_programming/LIS.c -o $(BIN_DIR)/LIS
	$(CC) $(CCFLAGS) dynamic_programming/LCS.c -o $(BIN_DIR)/LCS