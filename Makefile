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

bst: # C and Java versions not yet implemented.
#	$(CC) $(CFLAGS) bst/main.c bst/bst.c -o $(BIN_DIR)/bst
#	$(JAVAC) bst/BinarySearchTree.java