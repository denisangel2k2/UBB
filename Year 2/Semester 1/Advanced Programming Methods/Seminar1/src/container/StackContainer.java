package container;

import model.Task;
import utils.Constants;

public class StackContainer extends ContainerClass implements Container{

    public StackContainer(){
        super();
    }

    public Task remove(){
        if (!isEmpty()){
            size--;
            return tasks[size];
        }
        return null;
    }



}
