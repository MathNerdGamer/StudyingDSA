package binary_search_tree;

import java.util.ArrayDeque;

public class BinarySearchTree<T extends Comparable<T>> {
    private class Node<E extends Comparable<E>> {
        E data;
        Node<E> parent;
        Node<E> left;
        Node<E> right;

        Node(E data) {
            this(data, null);
        }

        Node(E data, Node<E> parent) {
            this(data, parent, null, null);
        }

        Node(E data, Node<E> parent, Node<E> left, Node<E> right) {
            this.data = data;
            this.parent = parent;
            this.left = left;
            this.right = right;
        }
    }

    Node<T> root;
    int size;

    BinarySearchTree() {
        size = 0;
    }

    BinarySearchTree(T data) {
        size = 1;
        root = new Node<T>(data);
    }

    public boolean isEmpty() {
        return root == null;
    }

    public void insert(T data) {
        if (isEmpty()) {
            root = new Node<T>(data);
            return;
        }

        Node<T> previousNode = null;
        Node<T> currentNode = root;

        int comparison = 0;

        while (currentNode != null) {
            previousNode = currentNode;

            comparison = data.compareTo(currentNode.data);

            if (comparison < 0) {
                currentNode = currentNode.left;
            } else if (comparison > 0) {
                currentNode = currentNode.right;
            } else {
                return;
            }
        }

        Node<T> newNode = new Node<>(data, previousNode);

        if (comparison < 0) {
            previousNode.left = newNode;
        } else {
            previousNode.right = newNode;
        }

        size++;
    }

    public boolean contains(T data) {
        Node<T> currentNode = root;

        while (currentNode != null) {
            int comparison = data.compareTo(currentNode.data);

            if (comparison < 0) {
                currentNode = currentNode.left;
            } else if (comparison > 0) {
                currentNode = currentNode.right;
            } else {
                return true;
            }
        }

        return false;
    }

    public void remove(T data) {
        Node<T> currentNode = root;

        while (currentNode != null) {
            int comparison = data.compareTo(currentNode.data);

            if (comparison < 0) {
                currentNode = currentNode.left;
            } else if (comparison > 0) {
                currentNode = currentNode.right;
            } else {
                break;
            }
        }

        if (currentNode == null) {
            return;
        }

        size--;

        if (currentNode.left == null && currentNode.right == null) {
            removeLeaf(currentNode);
        } else if (currentNode.left == null || currentNode.right == null) {
            removeOneChild(currentNode);
        } else {
            removeTwoChild(currentNode);
        }
    }

    private void removeLeaf(Node<T> node) {
        if (node.parent == null) {
            root = null;
        } else if (node == node.parent.left) {
            node.parent.left = null;
        } else {
            node.parent.right = null;
        }
    }

    private void removeOneChild(Node<T> node) {
        if (node == root) {
            if (root.left != null) {
                root = root.left;
            } else {
                root = root.right;
            }
        } else {
            if (node == node.parent.left) {
                if (node.left != null) {
                    node.parent.left = node.left;
                } else {
                    node.parent.left = node.right;
                }
            } else {
                if (node.left != null) {
                    node.parent.right = node.left;
                } else {
                    node.parent.right = node.right;
                }
            }
        }
    }

    private void removeTwoChild(Node<T> node) {
        Node<T> predecessor = node.left;

        while (predecessor.right != null) {
            predecessor = predecessor.right;
        }

        node.data = predecessor.data;

        if (predecessor.left != null || predecessor.right != null) {
            removeOneChild(predecessor);
        } else {
            removeLeaf(predecessor);
        }
    }

    private String inOrderTraverse(Node<T> node) {
        if (node == null) {
            return "";
        }

        StringBuilder result = new StringBuilder();

        result.append(inOrderTraverse(node.left)).append(node.data).append(" ")
                .append(inOrderTraverse(node.right));

        return result.toString();
    }

    public String inOrder() {
        return inOrderTraverse(root);
    }

    public String toString() {
        return inOrder();
    }

    private String preOrderTraverse(Node<T> node) {
        if (node == null) {
            return "";
        }

        StringBuilder result = new StringBuilder();

        result.append(node.data).append(" ").append(inOrderTraverse(node.left))
                .append(inOrderTraverse(node.right));

        return result.toString();
    }

    public String preOrder() {
        return preOrderTraverse(root);
    }

    private String postOrderTraverse(Node<T> node) {
        if (node == null) {
            return "";
        }

        StringBuilder result = new StringBuilder();

        result.append(inOrderTraverse(node.left))
                .append(inOrderTraverse(node.right)).append(node.data).append(" ");

        return result.toString();
    }

    public String postOrder() {
        return postOrderTraverse(root);
    }

    public String levelOrder() {
        if (isEmpty()) {
            return "";
        }

        ArrayDeque<Node<T>> queue = new ArrayDeque<>();
        StringBuilder result = new StringBuilder();

        queue.add(root);

        while (!queue.isEmpty()) {
            Node<T> node = queue.pollFirst();

            result.append(node.data).append(" ");

            if (node.left != null) {
                queue.add(node.left);
            }

            if (node.right != null) {
                queue.add(node.right);
            }
        }

        return result.toString();
    }

    /*
     * The following method is unnecessary because of Java's garbage collector,
     * but is included because it'll be a helpful guide when implementing the
     * C version:
     * 
     * private void postOrderRemove(Node<T> node) {
     * if (node == null) {
     * return;
     * }
     * 
     * postOrderRemove(node.left);
     * postOrderRemove(node.right);
     * 
     * if (node == root) {
     * root = null;
     * } else if (node == node.parent.left) {
     * node.parent.left = null;
     * } else {
     * node.parent.right = null;
     * }
     * }
     */

    public void clear() {
        // postOrderRemove(root); // Unnecessary because of Java's garbage collector,
        // but the line is included for completion's sake (and because it'll be
        // necessary in the C implementation).
        root = null;
        size = 0;
    }

    public static void main(String[] args) {
        BinarySearchTree<Integer> myBST = new BinarySearchTree<>(5);
        myBST.insert(2);
        myBST.insert(7);
        myBST.insert(-1);
        myBST.insert(9);
        myBST.insert(3);
        myBST.insert(6);
        myBST.insert(3);
        myBST.insert(8);
        myBST.insert(0);

        System.out.println(myBST);
        System.out.println(myBST.preOrder());
        System.out.println(myBST.postOrder());
        System.out.println(myBST.levelOrder());

        myBST.remove(3);
        System.out.println(myBST);
        System.out.println(myBST.preOrder());
        System.out.println(myBST.postOrder());
        System.out.println(myBST.levelOrder());

        myBST.remove(9);
        System.out.println(myBST);
        System.out.println(myBST.preOrder());
        System.out.println(myBST.postOrder());
        System.out.println(myBST.levelOrder());

        myBST.remove(-1);
        System.out.println(myBST);
        System.out.println(myBST.preOrder());
        System.out.println(myBST.postOrder());
        System.out.println(myBST.levelOrder());

        myBST.remove(5);
        System.out.println(myBST);
        System.out.println(myBST.preOrder());
        System.out.println(myBST.postOrder());
        System.out.println(myBST.levelOrder());

        System.out.println("Contains 19? " + myBST.contains(19));
        System.out.println("Contains 8? " + myBST.contains(8));
        System.out.println("Contains 7? " + myBST.contains(7));
        System.out.println("Contains 5? " + myBST.contains(5));

        System.out.println("Empty? " + myBST.isEmpty());
        myBST.clear();
        System.out.println("Empty? " + myBST.isEmpty());
    }
}