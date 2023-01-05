package Runners;

import SortingAlgorithms.BubbleSort;
import SortingAlgorithms.MergeSort;
import container.Container;
import container.QueueContainer;
import container.Strategy;
import model.*;
import utils.Constants;

import java.time.LocalDateTime;
import java.util.Vector;

public class TestRunner {
    private static MessageTask[] createMessages() {
        MessageTask m1 = new MessageTask("id1", "tema map", "sapt. viitoare", "ubb", "denisut", LocalDateTime.now());
        MessageTask m2 = new MessageTask("id2", "tema oop", "ex-sapt. viitoare", "ubb", "oti", LocalDateTime.now());
        MessageTask m3 = new MessageTask("ide3", "tema fp", "ex-ex-sapt. viitoare", "ubb", "fabi", LocalDateTime.now());
        return new MessageTask[]{m1, m2, m3};
    }

    public static void run() {
        MessageTask[] msg = createMessages();


        int[] numbers = {3, 6, 2, 3, 9, 2, 1, 8, 3};


        AbstractSorter mergesorter = new MergeSort();
        AbstractSorter bubblesorter = new BubbleSort();
        SortingTask sortingTask = new SortingTask("id1", "Sorter merge", mergesorter, numbers);

        sortingTask.execute();

        Container coada = TaskContainerFactory.getInstance().createContainer(Strategy.FIFO);

        coada.add(msg[0]);
        coada.add(msg[1]);
        assert (coada.size() == 2);
        coada.remove();
        assert (coada.size() == 1);
    }

    public static void testTaskRunner(String strategy) {
        MessageTask m1 = new MessageTask("id1", "tema map", "sapt. viitoare", "ubb", "denisut", LocalDateTime.now());
        MessageTask m2 = new MessageTask("id2", "tema oop", "ex-sapt. viitoare", "ubb", "oti", LocalDateTime.now());
        MessageTask m3 = new MessageTask("ide3", "tema fp", "ex-ex-sapt. viitoare", "ubb", "fabi", LocalDateTime.now());
        Vector<MessageTask> taskuri = new Vector<MessageTask>();
        taskuri.add(m1);
        taskuri.add(m2);
        taskuri.add(m3);


        StrategyTaskRunner runner = new StrategyTaskRunner(strategy);

        for (MessageTask task : taskuri)
            runner.addTask(task);

        runner.executeAll();
    }

    public static void testTaskRunner2(String strategy) {
        MessageTask m1 = new MessageTask("id1", "tema map", "sapt. viitoare", "ubb", "denisut", LocalDateTime.now());
        MessageTask m2 = new MessageTask("id2", "tema oop", "ex-sapt. viitoare", "ubb", "oti", LocalDateTime.now());
        MessageTask m3 = new MessageTask("id3", "tema fp", "ex-ex-sapt. viitoare", "ubb", "fabi", LocalDateTime.now());

        Vector<Task> taskuri = new Vector<Task>();
        int[] numbers = {3, 6, 2, 3, 9, 2, 1, 8, 3};
        SortingTask sortingTask = new SortingTask("id1", "Sorter merge", new MergeSort(), numbers);


        taskuri.add(m1);
        taskuri.add(m2);
        taskuri.add(m3);
        taskuri.add(sortingTask);
        StrategyTaskRunner runner_init = new StrategyTaskRunner(strategy);
        runner_init.addTask(m1);
        runner_init.addTask(m2);
        runner_init.addTask(m3);
        runner_init.addTask(sortingTask);


        AbstractTaskRunner runner = new PrinterTaskRunner(runner_init);
        System.out.println();
        runner.executeAll();

        runner.addTask(m1);
        runner.addTask(m2);
        runner.addTask(m3);
        runner.addTask(sortingTask);

        AbstractTaskRunner runner2 = new DelayTaskRunner(runner);
        System.out.println();
        // runner2.executeAll();

    }


}
