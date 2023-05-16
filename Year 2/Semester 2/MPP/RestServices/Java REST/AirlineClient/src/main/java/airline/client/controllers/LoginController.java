package airline.client.controllers;
import airline.model.Employee;
import airline.services.IService;

import javafx.event.EventHandler;
import javafx.fxml.FXML;

import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;



public class LoginController {

    private static final Logger logger= LogManager.getLogger();
    @FXML
    private Button loginButton;

    @FXML
    private TextField passwordTestField;

    @FXML
    private TextField usernameTextField;


    private IService service;
    public void setService(IService service){
        this.service=service;
    }

    private Parent root;
    public void setParent(Parent root){
        this.root=root;
    }

    private MainController mainController;
    public void setMainController(MainController mainController){
        this.mainController=mainController;
    }
    private final Stage stage=new Stage();
    @FXML
    private void onLoginButtonClicked(){
        String username=usernameTextField.getText();
        String password=passwordTestField.getText();
        Employee toLogin=new Employee("","",username,password);

        try{
            Employee employee=service.login(toLogin,mainController);
            if (employee != null){
                mainController.setService(service,employee);
                mainController.setStage((Stage)loginButton.getScene().getWindow());

                stage.setTitle("Airline");
                if (stage.getScene()==null)
                    stage.setScene(new Scene(root, 600, 400));
                stage.setOnCloseRequest(new EventHandler<WindowEvent>() {
                    @Override
                    public void handle(WindowEvent event) {
                        mainController.logout();
                    }
                });

                stage.show();
                Stage currentStage=(Stage)loginButton.getScene().getWindow();
                currentStage.close();

            }

        }
        catch (Exception e){
            logger.error(e);
            Alert alert=new Alert(Alert.AlertType.ERROR,e.getMessage());
            alert.show();
        }
    }
}
