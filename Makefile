CC=clang
CFLAGS=-Wall -Wextra -Werror -std=c23 -DQUIET_VSCODE -Iinclude/
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

avl: # C version not yet implemented.
	$(CC) $(CFLAGS) -Ideque/ avl_tree/main.c \
	                         avl_tree/avl_tree.c \
							 deque/deque.c \
							 -o $(BIN_DIR)/avl_tree
	$(JAVAC) avl_tree/AVLTree.java