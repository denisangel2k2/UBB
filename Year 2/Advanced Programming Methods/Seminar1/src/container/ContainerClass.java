package container;

import model.Task;
import utils.Constants;

public class ContainerClass{
    protected Task[] tasks;
    protected int size;

    public ContainerClass() {
        tasks = new Task[Constants.TASK_INITIAL_SIZE];
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public void add(Task task) {
        if (tasks.length == size) {
            Task[] t = new Task[tasks.length * 2];
            System.arraycopy(tasks, 0, t, 0, tasks.length);
        }
            tasks[size] = task;
            size++;

    }

    public int size() {
        return size;
    }
}
