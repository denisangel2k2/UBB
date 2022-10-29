import domain.User;
import domain.validation.UserValidator;
import domain.validation.Validator;
import exceptions.ValidationException;
import presentation.UI;
import repository.FileRepository;
import repository.Repository;
import service.Service;
import service.UserService;
import tests.Tests;



public class Main {
    public static void main(String[] args) {

        Tests.run();
        Validator validator=UserValidator.getInstance();
        Repository repo=new FileRepository("data/users.csv");
        Service service=new UserService(repo,validator);
        UI ui = new UI(service);
        ui.run();


    }
}