package model;

import container.Container;
import container.QueueContainer;
import container.StackContainer;
import container.Strategy;

import java.util.HashMap;

public class TaskContainerFactory implements Factory{



    private static TaskContainerFactory instance = new TaskContainerFactory();
    public static TaskContainerFactory getInstance(){
        return instance;
    }
    private TaskContainerFactory(){}
    @Override
    public Container createContainer(Strategy strategy) {

        if (strategy==Strategy.LIFO)
            return new StackContainer();
        else if (strategy==Strategy.FIFO)
            return new QueueContainer();
        else return null;
    }
}
