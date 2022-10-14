package Runners;

import container.Container;
import container.Strategy;
import model.Factory;
import model.Task;
import model.TaskContainerFactory;

public class StrategyTaskRunner implements TaskRunner{
    private Container container;
    private Strategy strategy;
    public StrategyTaskRunner(Strategy strategy) {
        this.strategy=strategy;
        Factory factory=TaskContainerFactory.getInstance();
        container=factory.createContainer(strategy);
    }

    @Override
    public void executeOneTask() {
        Task task=container.remove();
        task.execute();
    }

    @Override
    public void executeAll() {
        while (!container.isEmpty()){
            Task task=container.remove();
            task.execute();
        }
    }

    @Override
    public void addTask(Task t) {
        container.add(t);
    }

    @Override
    public boolean hasTask() {
        return container.isEmpty();
    }
}
