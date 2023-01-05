package SortingAlgorithms;

import model.AbstractSorter;

import java.lang.reflect.Array;
import java.util.Objects;

public class BubbleSort extends AbstractSorter{


    @Override
    public void sort(int[] numbers) {
        boolean sw=true;
        while (sw){
            sw=false;
            for (int i=0; i<numbers.length-1; i++)
                if (numbers[i]>numbers[i+1])
                {
                    sw=true;
                    int aux=numbers[i];
                    numbers[i]=numbers[i+1];
                    numbers[i+1]=aux;
                }
            }
     }
}
