package model;

import java.util.Vector;

public class SortingTask extends Task {

    private AbstractSorter sorter;

    private int[] numbers;
    public SortingTask(String _taskID, String _descriere, AbstractSorter sorter, int[] numbers) {
        super(_taskID, _descriere);
        this.sorter = sorter;
        this.numbers=numbers;
    }

    public void sort() {
        sorter.sort(numbers);
    }

    @Override
    public void execute() {
        sort();
        for (int number : numbers)
            System.out.print(number + " ");

    }
}
