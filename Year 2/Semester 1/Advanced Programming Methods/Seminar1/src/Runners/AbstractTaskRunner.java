package Runners;

import model.Task;

public abstract class AbstractTaskRunner implements TaskRunner{

    private final TaskRunner runner;

    public AbstractTaskRunner(TaskRunner runner) {
        this.runner = runner;
    }
    @Override
    public void executeOneTask() {
        runner.executeOneTask();

    }
    @Override
    public void executeAll() {
        runner.executeAll();
    }
    @Override
    public void addTask(Task t) {
        runner.addTask(t);
    }
    @Override
    public boolean hasTask() {
        return runner.hasTask();
    }
}
