# Sorting Algorithm Visualizer

This is a very basic visualizer for sorting algorithms written in C using SDL2. I've only tested using WSL2 in Windows 11.

You'll have to make sure SDL2 is installed and provide your own `font.ttf` in whichever directory you run the executable from (or edit to hardcode your font of choice).

This sorting visualizer has my implementations for the following sorting algorithms:

1. Bubble Sort

2. Insertion Sort

3. Selection Sort

4. Merge Sort

5. Heap Sort

6. QuickSort (Multiple Variants)
    * Both Lomuto & Hoare partitioning.
    * Default, randomized, and median-of-three pivots.

7. IntroSort - QuickSort, but switches to Insertion Sort for small subarrays or Heap Sort when it recurses too far.

8. [BogoSort](../Notes/16b.BogoSort.md)