package Runners;

import container.Container;
import container.Strategy;
import model.Factory;
import model.Task;
import model.TaskContainerFactory;

public class StrategyTaskRunner implements TaskRunner {
    private Container container;
    private Strategy strategy;

    public StrategyTaskRunner(String strat) {
        if (strat.equals("LIFO"))
            this.strategy = Strategy.LIFO;
        else
            this.strategy = Strategy.FIFO;

        Factory factory = TaskContainerFactory.getInstance();
        this.container = factory.createContainer(this.strategy);
    }

    @Override
    public void executeOneTask() {

        if (!container.isEmpty()){
            Task task = container.remove();
            task.execute();
        }
    }

    @Override
    public void executeAll() {
        /*while (!container.isEmpty()) {
            Task task = container.remove();
            task.execute();
        }*/
        while (hasTask())
            executeOneTask();
    }

    @Override
    public void addTask(Task t) {
        container.add(t);
    }

    @Override
    public boolean hasTask() {
        return !container.isEmpty();
    }
}
