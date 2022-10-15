package Runners;

import utils.Constants;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class PrinterTaskRunner extends AbstractTaskRunner{


    public PrinterTaskRunner(TaskRunner runner) {
        super(runner);
    }
    @Override
    public void executeOneTask() {
        super.executeOneTask();
        System.out.println("Task-ul a fost executat in " + LocalDateTime.now().format(Constants.DATE_TIME_FORMATTER));
    }

    @Override
    public void executeAll() {
        while(super.hasTask())
            this.executeOneTask();
    }
}
