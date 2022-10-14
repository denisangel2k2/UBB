package container;

import model.Task;
import utils.Constants;

public class QueueContainer extends ContainerClass implements Container {

    public QueueContainer() {
        super();
    }

    public Task remove() {
        if (!isEmpty()) {
            Task t = tasks[0];
            for (int i = 0; i < size - 1; i++)
                tasks[i] = tasks[i + 1];
            size--;
            return t;
        }
        return null;
    }


}
