package deque;

@SuppressWarnings("unchecked")
public class Deque<T> {
    T[] deque;
    int front;
    int back;
    int size;
    int capacity;

    Deque() {
        front = 0;
        back = 0;
        size = 0;
        capacity = 3; // Default capacity of 3 just because.
        deque = (T[]) new Object[capacity];
    }

    private void rebuildDeque() {
        int newCapacity = capacity + capacity / 2; // 1.5x growth

        T[] newDeque = (T[]) new Object[newCapacity];

        int i = 0;
        int j = front;

        while (j != back) {
            newDeque[i] = deque[j];

            i++;
            j++;
            j %= capacity;
        }
        newDeque[i] = deque[back];

        capacity = newCapacity;
        deque = newDeque;
        front = 0;
        back = i;
    }

    public int getSize() {
        return size;
    }

    public int getCapacity() {
        return capacity;
    }

    public boolean isFull() {
        return size == capacity;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public T top() {
        return deque[front]; // returns null if empty
    }

    public T bottom() {
        return deque[back]; // returns null if empty
    }

    public void pushFront(T data) {
        if (isFull()) {
            rebuildDeque();
        } else if (isEmpty()) {
            front = 1;
        }

        front += capacity - 1; // n - 1
        front %= capacity; // = -1 (mod n)

        deque[front] = data;
        size++;
    }

    public void pushBack(T data) {
        if (isFull()) {
            rebuildDeque();
        } else if (isEmpty()) {
            back = -1;
        }

        back++;
        back %= capacity;

        deque[back] = data;
        size++;
    }

    public T popFront() {
        if (isEmpty()) {
            return null;
        }

        T data = deque[front];
        deque[front] = null;

        front++;
        front %= capacity;
        size--;

        return data;
    }

    public T popBack() {
        if (isEmpty()) {
            return null;
        }

        T data = deque[back];
        deque[back] = null;

        back += capacity - 1;
        back %= capacity;
        size--;

        return data;
    }

    public void clear() {
        deque = (T[]) new Object[capacity];
        size = 0;
        front = 0;
        back = 0;
    }

    public String toString() {
        if (isEmpty()) {
            return "";
        }

        StringBuilder result = new StringBuilder();

        int i = front;

        while (i != back) {
            if (deque[i] == null) {
                continue;
            } else {
                result.append(deque[i]).append(" ");
            }

            i++;
            i %= capacity;
        }

        result.append(deque[back]);

        return result.toString();
    }

    public static void main(String[] args) {
        Deque<Integer> intDeque = new Deque<>();

        for (int i = 0; i < 11; ++i) {
            int number = (7 * (i + 3)) % 11;
            System.out.printf("pushBack(%d)\n", number);
            intDeque.pushBack(number);
        }

        System.out.println("\nOriginal Deque");
        System.out.println("top(): " + intDeque.top());
        System.out.println("bottom(): " + intDeque.bottom());
        System.out.println("getSize(): " + intDeque.getSize());
        System.out.println("getCapacity(): " + intDeque.getCapacity());
        System.out.println("Deque: " + intDeque);

        intDeque.pushFront(17);
        System.out.println("\npushFront(17)");
        System.out.println("top(): " + intDeque.top());
        System.out.println("bottom(): " + intDeque.bottom());
        System.out.println("getSize(): " + intDeque.getSize());
        System.out.println("getCapacity(): " + intDeque.getCapacity());
        System.out.println("Deque: " + intDeque);

        intDeque.pushBack(12);
        System.out.println("\npushBack(12)");
        System.out.println("top(): " + intDeque.top());
        System.out.println("bottom(): " + intDeque.bottom());
        System.out.println("getSize(): " + intDeque.getSize());
        System.out.println("getCapacity(): " + intDeque.getCapacity());
        System.out.println("Deque: " + intDeque);

        intDeque.popFront();
        System.out.println("\npopFront()");
        System.out.println("top(): " + intDeque.top());
        System.out.println("bottom(): " + intDeque.bottom());
        System.out.println("getSize(): " + intDeque.getSize());
        System.out.println("getCapacity(): " + intDeque.getCapacity());
        System.out.println("Deque: " + intDeque);

        intDeque.popBack();
        System.out.println("\npopBack()");
        System.out.println("top(): " + intDeque.top());
        System.out.println("bottom(): " + intDeque.bottom());
        System.out.println("getSize(): " + intDeque.getSize());
        System.out.println("getCapacity(): " + intDeque.getCapacity());
        System.out.println("Deque: " + intDeque);

        intDeque.clear();
        System.out.println("\npopBack()");
        System.out.println("top(): " + intDeque.top());
        System.out.println("bottom(): " + intDeque.bottom());
        System.out.println("getSize(): " + intDeque.getSize());
        System.out.println("getCapacity(): " + intDeque.getCapacity());
        System.out.println("Deque: " + intDeque);
    }
}
