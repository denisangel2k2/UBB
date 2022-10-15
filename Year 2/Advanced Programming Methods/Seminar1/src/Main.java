import Runners.TestRunner;


public class Main {
    public static void main(String[] args) {

        TestRunner.run();
        System.out.println(args[0]);
        TestRunner.testTaskRunner(args[0]);
        TestRunner.testTaskRunner2(args[0]);
    }

}