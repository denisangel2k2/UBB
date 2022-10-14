package Runners;

import SortingAlgorithms.BubbleSort;
import SortingAlgorithms.MergeSort;
import container.Container;
import container.QueueContainer;
import container.Strategy;
import model.*;

import java.time.LocalDateTime;
import java.util.Vector;

public class TestRunner {
    private static MessageTask[] createMessages(){
        MessageTask m1=new MessageTask("id1","tema map", "sapt. viitoare", "ubb", "denisut", LocalDateTime.now());
        MessageTask m2=new MessageTask("id2","tema oop", "ex-sapt. viitoare", "ubb", "oti", LocalDateTime.now());
        MessageTask m3=new MessageTask("ide3","tema fp", "ex-ex-sapt. viitoare", "ubb", "fabi", LocalDateTime.now());
        return new MessageTask[]{m1,m2,m3};
    }
    public static void run()
    {
        MessageTask[] msg=createMessages();
        for (MessageTask m : msg)
            m.execute();

        int[] numbers={3,6,2,3,9,2,1,8,3};




        AbstractSorter mergesorter=new MergeSort();
        AbstractSorter bubblesorter=new BubbleSort();
        SortingTask sortingTask=new SortingTask("id1","Sorter merge",mergesorter,numbers);

        sortingTask.execute();

        Container coada=TaskContainerFactory.getInstance().createContainer(Strategy.FIFO);

        coada.add(msg[0]);
        coada.add(msg[1]);
        assert (coada.size()==2);
        coada.remove();
        assert (coada.size()==1);


    }





}
