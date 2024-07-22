package avl_tree;

import java.util.ArrayDeque;

public class AVLTree<T extends Comparable<T>> {
    private class Node<E extends Comparable<E>> {
        private int height;
        private E data;
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
            this.height = 0;
        }

        int getHeight() {
            return height;
        }

        void updateHeight() {
            int leftHeight = (left != null) ? (left.getHeight()) : -1;
            int rightHeight = (right != null) ? (right.getHeight()) : -1;

            height = 1 + Math.max(leftHeight, rightHeight);
        }
    }

    Node<T> root;
    int size;

    AVLTree() {
        size = 0;
    }

    AVLTree(T data) {
        size = 1;
        root = new Node<T>(data);
    }

    public boolean isEmpty() {
        return root == null;
    }

    public int size() {
        return size;
    }

    int height(Node<T> node) {
        return (node != null) ? (node.getHeight()) : -1;
    }

    int balanceFactor(Node<T> node) {
        if (node == null) {
            return 0;
        }

        int leftHeight = height(node.left);
        int rightHeight = height(node.right);

        return leftHeight - rightHeight;
    }

    private Node<T> leftRotate(Node<T> node) {
        if (node.right == null) {
            throw new IllegalArgumentException("Cannot right rotate null.");
        }

        Node<T> rightChild = node.right;

        node.right = rightChild.left;
        if (rightChild.left != null) {
            rightChild.left.parent = node;
        }

        rightChild.left = node;
        rightChild.parent = node.parent;
        if (rightChild.parent != null) {
            if (node.parent.left == node) {
                node.parent.left = rightChild;
            } else {
                node.parent.right = rightChild;
            }
        }

        node.parent = rightChild;

        node.updateHeight();
        rightChild.updateHeight();

        return rightChild;
    }

    private Node<T> rightRotate(Node<T> node) {
        if (node.left == null) {
            throw new IllegalArgumentException("Cannot left rotate null.");
        }

        Node<T> leftChild = node.left;

        node.left = leftChild.right;

        if (leftChild.right != null) {
            leftChild.right.parent = node;
        }

        leftChild.right = node;
        leftChild.parent = node.parent;
        if (leftChild.parent != null) {
            if (node.parent.left == node) {
                node.parent.left = leftChild;
            } else {
                leftChild.parent.right = leftChild;
            }
        }

        node.parent = leftChild;

        node.updateHeight();
        leftChild.updateHeight();

        return leftChild;
    }

    private Node<T> rebalanceNode(Node<T> node) {
        if (balanceFactor(node) > 1) {
            if (balanceFactor(node.left) < 0) {
                node.left = leftRotate(node.left);
            }
            node = rightRotate(node);
        }

        if (balanceFactor(node) < -1) {
            if (balanceFactor(node.right) > 0) {
                node.right = rightRotate(node.right);
            }
            node = leftRotate(node);
        }

        return node;
    }

    public void insert(T data) {
        root = insertRecursive(root, data);
    }

    private Node<T> insertRecursive(Node<T> node, T data) {
        if (node == null) {
            size++;
            return new Node<T>(data);
        }

        int comparison = data.compareTo(node.data);

        if (comparison < 0) {
            node.left = insertRecursive(node.left, data);
            node.left.parent = node;
        } else if (comparison > 0) {
            node.right = insertRecursive(node.right, data);
            node.right.parent = node;
        } else {
            return node;
        }

        node.updateHeight();

        return rebalanceNode(node);
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
        root = removeRecursive(root, data);
    }

    private Node<T> removeRecursive(Node<T> node, T data) {
        if (node == null) {
            return null;
        }

        int comparison = data.compareTo(node.data);

        if (comparison < 0) {
            node.left = removeRecursive(node.left, data);
        } else if (comparison > 0) {
            node.right = removeRecursive(node.right, data);
        } else {
            size--;
            Node<T> parent = node.parent;
            boolean wasLeft = (parent != null && parent.left == node);
            if (node.left != null && node.right != null) {
                node = removeTwoChild(node);
            } else if (node.left != null || node.right != null) {
                node = removeOneChild(node);
            } else {
                node = removeLeaf(node);
            }

            if (parent != null) {
                if (wasLeft) {
                    parent.left = node;
                } else {
                    parent.right = node;
                }
            }
        }

        if (node == null) {
            return null;
        }
        node.updateHeight();

        return rebalanceNode(node);
    }

    private Node<T> removeLeaf(Node<T> node) {
        if (node.parent == null) {
            root = null;
        } else if (node == node.parent.left) {
            node.parent.left = null;
        } else {
            node.parent.right = null;
        }

        return null;
    }

    private Node<T> removeOneChild(Node<T> node) {
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
                    node = node.left;
                } else {
                    node.parent.left = node.right;
                    node = node.right;
                }
            } else {
                if (node.left != null) {
                    node.parent.right = node.left;
                    node = node.left;
                } else {
                    node.parent.right = node.right;
                    node = node.right;
                }
            }
        }

        return node;
    }

    private Node<T> removeTwoChild(Node<T> node) {
        Node<T> predecessor = node.left;

        while (predecessor.right != null) {
            predecessor = predecessor.right;
        }

        node.data = predecessor.data;

        if (predecessor.left != null || predecessor.right != null) {
            predecessor = removeOneChild(predecessor);
        } else {
            predecessor = removeLeaf(predecessor);
        }

        return node;
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

        result.append(node.data).append(" ").append(preOrderTraverse(node.left))
                .append(preOrderTraverse(node.right));

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

        result.append(postOrderTraverse(node.left))
                .append(postOrderTraverse(node.right)).append(node.data).append(" ");

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

    public void clear() {
        root = null;
        size = 0;
    }

    public static void main(String[] args) {
        AVLTree<Integer> myAVL = new AVLTree<>();

        for (int i = 0; i < 15; ++i) {
            System.out.println("Inserting " + (17 * (i + 1) + 3) % 31);
            myAVL.insert((17 * (i + 1) + 3) % 31);
        }

        System.out.println("Pre-order traversal: " + myAVL.preOrder());
        System.out.println("In-order traversal: " + myAVL);
        System.out.println("Post-order traversal: " + myAVL.postOrder());
        System.out.println("Level-order traversal: " + myAVL.levelOrder());
        System.out.println("Size: " + myAVL.size());
        System.out.println("Empty? " + myAVL.isEmpty());

        System.out.println("\nContains 7? " + myAVL.contains(7));
        System.out.println("\nContains 11? " + myAVL.contains(11));

        System.out.println("\nTesting removal of leaf (18).");
        myAVL.remove(18);
        System.out.println("Level-order traversal: " + myAVL.levelOrder());

        System.out.println("\nTesting removal of node with one child (6).");
        myAVL.remove(6);
        System.out.println("Level-order traversal: " + myAVL.levelOrder());

        System.out.println("\nTesting removal of node with two children (20).");
        myAVL.remove(20);
        System.out.println("Level-order traversal: " + myAVL.levelOrder());

        System.out.println("\nClearing tree. The traversals should be blank below this line.");
        myAVL.clear();

        System.out.println("Pre-order traversal: " + myAVL.preOrder());
        System.out.println("In-order traversal: " + myAVL);
        System.out.println("Post-order traversal: " + myAVL.postOrder());
        System.out.println("Level-order traversal: " + myAVL.levelOrder());
        System.out.println("Size: " + myAVL.size());
        System.out.println("Empty? " + myAVL.isEmpty());
    }
}