package doubly_linked_list;

import java.util.Iterator;

public class DoublyLinkedList<T extends Comparable<T>> implements Iterable<T> {
    private class Node<E extends Comparable<E>> {
        private E data;
        private Node<E> next;
        private Node<E> prev;

        private Node(E data) {
            this(data, null);
        }

        private Node(E data, Node<E> next) {
            this(data, next, null);
        }

        private Node(E data, Node<E> next, Node<E> prev) {
            this.data = data;
            this.next = next;
            this.prev = prev;
        }
    }

    private class LLIterator implements Iterator<T> {
        private Node<T> cursor;

        LLIterator() {
            cursor = head;
        }

        public boolean hasNext() {
            return cursor != null;
        }

        public T next() {
            if (hasNext()) {
                T temp = cursor.data;
                cursor = cursor.next;
                return temp;
            }

            return null;
        }
    }

    private Node<T> head;
    private Node<T> tail;
    private int size;

    DoublyLinkedList() {
        head = null;
        tail = null;
        size = 0;
    }

    DoublyLinkedList(T data) {
        insert(data);
    }

    public boolean isEmpty() {
        return (head == null);
    }

    public void insert(T data) {
        size++;

        if (isEmpty()) {
            head = new Node<T>(data);
            tail = head;
            return;
        }

        Node<T> currentNode = head;

        while (currentNode != null && currentNode.data.compareTo(data) < 0) {
            currentNode = currentNode.next;
        }

        if (currentNode == null) {
            tail.next = new Node<T>(data, null, tail);
            tail = tail.next;
        } else {
            Node<T> newNode = new Node<T>(data);
            if (currentNode == head) {
                head = newNode;
            } else {
                currentNode.prev.next = newNode;
            }

            newNode.next = currentNode;
            newNode.prev = currentNode.prev;
            currentNode.prev = newNode;
        }
    }

    public T accessAtHead() {
        if (isEmpty()) {
            return null;
        }

        return head.data;
    }

    public T accessAtTail() {
        if (isEmpty()) {
            return null;
        }

        return tail.data;
    }

    public T accessAtIndex(int index) {
        if (index >= size || index < 0) {
            throw new IllegalArgumentException("Index " + index + " is out of bounds.");
        }

        Node<T> currentNode = head;

        for (int i = 0; i < index; i++) {
            currentNode = currentNode.next;
        }

        return currentNode.data;
    }

    public T accesByValue(T data) {
        Node<T> currentNode = head;

        while (currentNode != null && !currentNode.data.equals(data)) {
            currentNode = currentNode.next;
        }

        if (currentNode == null) {
            return null;
        }

        return currentNode.data;
    }

    public T removeAtHead() {
        if (isEmpty()) {
            return null;
        }

        size--;

        T data = head.data;

        if (head == tail) {
            tail = null;
        }

        head = head.next;
        head.prev = null;

        return data;
    }

    public T removeAtTail() {
        if (isEmpty()) {
            return null;
        }

        size--;

        T data = tail.data;

        if (head == tail) {
            head = null;
        }

        tail = tail.prev;
        tail.next = null;

        return data;
    }

    public T removeAtIndex(int index) {
        if (index >= size || index < 0) {
            throw new IllegalArgumentException("Index " + index + " is out of bounds.");
        }

        Node<T> currentNode = head;

        for (int i = 0; i < index; i++) {
            currentNode = currentNode.next;
        }

        T data = currentNode.data;

        if (currentNode.prev != null) {
            currentNode.prev.next = currentNode.next;
        }

        if (currentNode.next != null) {
            currentNode.next.prev = currentNode.prev;
        }
        size--;

        return data;
    }

    public T removeByValue(T data) {
        Node<T> currentNode = head;

        while (currentNode != null && !currentNode.data.equals(data)) {
            currentNode = currentNode.next;
        }

        if (currentNode == null) {
            return null;
        }

        if (currentNode.prev != null) {
            currentNode.prev.next = currentNode.next;
        }

        if (currentNode.next != null) {
            currentNode.next.prev = currentNode.prev;
        }

        size--;

        return data;
    }

    public boolean contains(T data) {
        return data.equals(accesByValue(data));
    }

    public void clear() {
        head = null;
        size = 0;
    }

    public int getSize() {
        return size;
    }

    public String toString() {
        StringBuilder result = new StringBuilder();

        Node<T> currentNode = head;

        while (currentNode != null) {
            result.append(currentNode.data);

            if (currentNode.next != null) {
                result.append(" <-> ");
            }

            currentNode = currentNode.next;
        }

        result.append("\n");

        return result.toString();
    }

    public Iterator<T> iterator() {
        return new LLIterator();
    }

    public static void main(String[] args) {
        DoublyLinkedList<Integer> intList = new DoublyLinkedList<>();

        for (int i = 0; i < 15; i++) {
            intList.insert((17 * (i + 1) + 3) % 12);
            System.out.println("Inserting " + (17 * (i + 1) + 3) % 12);
        }

        System.out.print("\nOriginal list:\n" + intList);
        System.out.println("Head: " + intList.accessAtHead());
        System.out.println("Tail: " + intList.accessAtTail());
        System.out.println("Index 4: " + intList.accessAtIndex(4));
        System.out.println("Contains 7: " + intList.contains(7));
        System.out.println("Contains 6: " + intList.contains(6));
        System.out.println("Size: " + intList.getSize());

        intList.removeAtHead();
        System.out.print("\nremoveAtHead():\n" + intList);
        System.out.println("Head: " + intList.accessAtHead());
        System.out.println("Tail: " + intList.accessAtTail());
        System.out.println("Index 4: " + intList.accessAtIndex(4));
        System.out.println("Contains 7: " + intList.contains(7));
        System.out.println("Contains 6: " + intList.contains(6));
        System.out.println("Size: " + intList.getSize());

        intList.removeAtTail();
        System.out.print("\nremoveAtTail():\n" + intList);
        System.out.println("Head: " + intList.accessAtHead());
        System.out.println("Tail: " + intList.accessAtTail());
        System.out.println("Index 4: " + intList.accessAtIndex(4));
        System.out.println("Contains 7: " + intList.contains(7));
        System.out.println("Contains 6: " + intList.contains(6));
        System.out.println("Size: " + intList.getSize());

        intList.removeByValue(7);
        System.out.print("\nremoveByValue(7):\n" + intList);
        System.out.println("Head: " + intList.accessAtHead());
        System.out.println("Tail: " + intList.accessAtTail());
        System.out.println("Index 4: " + intList.accessAtIndex(4));
        System.out.println("Contains 7: " + intList.contains(7));
        System.out.println("Contains 6: " + intList.contains(6));
        System.out.println("Size: " + intList.getSize());

        intList.removeAtIndex(4);
        System.out.print("\nremoveatIndex(4):\n" + intList);
        System.out.println("Head: " + intList.accessAtHead());
        System.out.println("Tail: " + intList.accessAtTail());
        System.out.println("Index 4: " + intList.accessAtIndex(4));
        System.out.println("Contains 7: " + intList.contains(7));
        System.out.println("Contains 6: " + intList.contains(6));
        System.out.println("Size: " + intList.getSize());

        try {
            intList.removeAtIndex(70);
        } catch (Exception e) {
            System.out.println(e.toString());
        }
        System.out.print("\nremoveatIndex(70)):\n" + intList);
        System.out.println("Head: " + intList.accessAtHead());
        System.out.println("Tail: " + intList.accessAtTail());
        System.out.println("Index 4: " + intList.accessAtIndex(4));
        System.out.println("Contains 7: " + intList.contains(7));
        System.out.println("Contains 6: " + intList.contains(6));
        System.out.println("Size: " + intList.getSize());

        intList.removeByValue(100);
        System.out.print("\nremoveByValue(100):\n" + intList);
        System.out.println("Head: " + intList.accessAtHead());
        System.out.println("Tail: " + intList.accessAtTail());
        System.out.println("Index 4: " + intList.accessAtIndex(4));
        System.out.println("Contains 7: " + intList.contains(7));
        System.out.println("Contains 6: " + intList.contains(6));
        System.out.println("Size: " + intList.getSize());

        intList.clear();
        System.out.println("There should be no integer list output after this line.\n\n");

        System.out.println(intList);

        DoublyLinkedList<String> strList = new DoublyLinkedList<>();

        for (int i = 0; i < args.length; i++) {
            strList.insert(args[i]);
            System.out.println("Inserting " + args[i]);
        }

        System.out.print("\nOriginal list:\n" + strList);
        System.out.println("Head: " + strList.accessAtHead());
        System.out.println("Tail: " + strList.accessAtTail());
        System.out.println("Index 4: " + strList.accessAtIndex(4));
        System.out.println("Contains \"should\": " + strList.contains("should"));
        System.out.println("Size: " + strList.getSize());

        strList.removeAtHead();
        System.out.print("\nremoveAtHead():\n" + strList);
        System.out.println("Head: " + strList.accessAtHead());
        System.out.println("Tail: " + strList.accessAtTail());
        System.out.println("Index 4: " + strList.accessAtIndex(4));
        System.out.println("Contains \"should\": " + strList.contains("should"));
        System.out.println("Size: " + strList.getSize());

        strList.removeAtTail();
        System.out.print("\nremoveAtTail():\n" + strList);
        System.out.println("Head: " + strList.accessAtHead());
        System.out.println("Tail: " + strList.accessAtTail());
        System.out.println("Index 4: " + strList.accessAtIndex(4));
        System.out.println("Contains \"should\": " + strList.contains("should"));
        System.out.println("Size: " + strList.getSize());

        strList.removeByValue("should");
        System.out.print("\nremoveByValue(\"should\"):\n" + strList);
        System.out.println("Head: " + strList.accessAtHead());
        System.out.println("Tail: " + strList.accessAtTail());
        System.out.println("Index 4: " + strList.accessAtIndex(4));
        System.out.println("Contains \"should\": " + strList.contains("should"));
        System.out.println("Size: " + strList.getSize());

        strList.removeAtIndex(4);
        System.out.print("\nremoveAtIndex(4):\n" + strList);
        System.out.println("Head: " + strList.accessAtHead());
        System.out.println("Tail: " + strList.accessAtTail());
        System.out.println("Index 4: " + strList.accessAtIndex(4));
        System.out.println("Contains \"should\": " + strList.contains("should"));
        System.out.println("Size: " + strList.getSize());

        try {
            strList.removeAtIndex(70);
        } catch (Exception e) {
            System.out.println(e.toString());
        }
        System.out.print("\nremoveAtIndex(70):\n" + strList);
        System.out.println("Head: " + strList.accessAtHead());
        System.out.println("Tail: " + strList.accessAtTail());
        System.out.println("Index 4: " + strList.accessAtIndex(4));
        System.out.println("Contains \"should\": " + strList.contains("should"));
        System.out.println("Size: " + strList.getSize());

        strList.clear();
        System.out.println("There should be no string list output after this line.\n\n");
        System.out.println(strList);
    }
}
