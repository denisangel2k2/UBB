package airline.client;

import JavaSocket.protobuffnet.ProtoProxy;
import airline.client.controllers.LoginController;
import airline.client.controllers.MainController;
import airline.networking.rpcprotocol.AirlineServicesRpcProxy;
import airline.services.IService;

import javafx.application.Application;

import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import java.io.IOException;
import java.util.Properties;


public class Main extends Application {


    private static int defaultChatPort=55556;
    private static String defaultServer="localhost";
    @Override
    public void start(Stage stage) throws IOException{
        System.out.println("In start");
        Properties clientProps = new Properties();
        try {
            clientProps.load(Main.class.getResourceAsStream("/client.properties"));
            System.out.println("Client properties set. ");
            clientProps.list(System.out);
        } catch (IOException e) {
            System.err.println("Cannot find client.properties " + e);
            return;
        }
        String serverIP = clientProps.getProperty("server.host", defaultServer);
        int serverPort = defaultChatPort;

        try {
            serverPort = Integer.parseInt(clientProps.getProperty("server.port"));
        } catch (NumberFormatException ex) {
            System.err.println("Wrong port number " + ex.getMessage());
            System.out.println("Using default port: " + defaultChatPort);
        }
        System.out.println("Using server IP " + serverIP);
        System.out.println("Using server port " + serverPort);
        //IService service=new AirlineServicesRpcProxy(serverIP,serverPort);
        IService service=new ProtoProxy("localhost",55557);
        FXMLLoader loader = new FXMLLoader(Main.class.getResource("loginView.fxml"));
        FXMLLoader loader2 = new FXMLLoader(Main.class.getResource("mainWindow.fxml"));

        Scene scene=new Scene(loader.load(),300,130);
        Parent root=loader2.load();
        LoginController lgcontroller=loader.getController();
        MainController mainController=loader2.getController();

        lgcontroller.setService(service);
        lgcontroller.setMainController(mainController);
        lgcontroller.setParent(root);

        stage.setTitle("Airline");
        stage.setScene(scene);
        stage.show();


    }

    public static void main(String[] args) {
        launch();
    }
}