package airline.client.controllers;

import airline.client.Main;
import airline.model.Constants;
import airline.model.Employee;
import airline.model.Flight;
import airline.model.Ticket;
import airline.services.IAirlineObserver;
import airline.services.IService;
import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import javafx.util.Callback;

import java.io.IOException;
import java.net.URL;
import java.time.LocalDateTime;
import java.util.List;
import java.util.ResourceBundle;

public class MainController implements IAirlineObserver, Initializable {

    private static final Logger logger = LogManager.getLogger();
    @FXML
    private TextField addressTextField;

    @FXML
    private TableView<Flight> allFlightsTableView;

    @FXML
    private TableColumn<Flight, String> availableSeatsColumn;

    @FXML
    private TableColumn<Flight, String> availableSeatsColumn1;

    @FXML
    private Button backButton;

    @FXML
    private Button buyButton;

    @FXML
    private AnchorPane buyTicketsPane;

    @FXML
    private TableColumn<Flight, String> dateColumn;

    @FXML
    private TableColumn<Flight, String> dateColumn1;

    @FXML
    private TableColumn<Flight, String> destinationColumn;

    @FXML
    private TableColumn<Flight, String> destinationColumn1;

    @FXML
    private TextField destinationTextField;

    @FXML
    private DatePicker flightDatePicker;

    @FXML
    private TableView<Flight> flightsTableView;

    @FXML
    private TableColumn<Flight, String> hourColumn;

    @FXML
    private TableColumn<Flight, String> hourColumn1;

    @FXML
    private Label loggedInUsernameLabel;

    @FXML
    private Button logoutButton;

    @FXML
    private AnchorPane paneFlights;

    @FXML
    private Button searchButton;

    @FXML
    private TextField touristNameTextField;


    ObservableList<Flight> flightObservableList = FXCollections.observableArrayList();
    ObservableList<Flight> allFlightObservableList = FXCollections.observableArrayList();

    @Override
    public void ticketBought(Ticket ticket) {
        Platform.runLater(() -> {
            try {
                var date = flightDatePicker.getValue();
                if (date!=null)
                    initLists(destinationTextField.getText(), date.format(Constants.DATE_FORMATTER));
                else
                    initLists(destinationTextField.getText(), "");
            } catch (Exception e) {
                e.printStackTrace();
            }
        });
    }

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        flightsTableView.setItems(flightObservableList);
        destinationColumn.setCellValueFactory(new PropertyValueFactory<>("destination"));
        dateColumn.setCellValueFactory(new PropertyValueFactory<>("date"));
        hourColumn.setCellValueFactory(new PropertyValueFactory<>("hour"));
        flightsTableView.getSelectionModel().selectedItemProperty().addListener(o -> onSelectedFlightChanged());
        buyTicketsPane.setVisible(false);
        allFlightsTableView.setItems(allFlightObservableList);
        destinationColumn1.setCellValueFactory(new PropertyValueFactory<>("destination"));
        dateColumn1.setCellValueFactory(new PropertyValueFactory<>("date"));
        hourColumn1.setCellValueFactory(new PropertyValueFactory<>("hour"));

        //destinationTextField.textProperty().addListener(o -> onSearchButtonClicked());


        availableSeatsColumn.setCellValueFactory(new PropertyValueFactory<>("availableSeats"));
        availableSeatsColumn1.setCellValueFactory(new PropertyValueFactory<>("availableSeats"));

    }

    @FXML
    private void initialize() {
        flightsTableView.setItems(flightObservableList);
        destinationColumn.setCellValueFactory(new PropertyValueFactory<>("destination"));
        dateColumn.setCellValueFactory(new PropertyValueFactory<>("date"));
        hourColumn.setCellValueFactory(new PropertyValueFactory<>("hour"));
        flightsTableView.getSelectionModel().selectedItemProperty().addListener(o -> onSelectedFlightChanged());
        buyTicketsPane.setVisible(false);
        allFlightsTableView.setItems(allFlightObservableList);
        destinationColumn1.setCellValueFactory(new PropertyValueFactory<>("destination"));
        dateColumn1.setCellValueFactory(new PropertyValueFactory<>("date"));
        hourColumn1.setCellValueFactory(new PropertyValueFactory<>("hour"));

        destinationTextField.textProperty().addListener(o -> onSearchButtonClicked());


    }

    private void onSelectedFlightChanged() {
        Flight selected_flight = flightsTableView.getSelectionModel().getSelectedItem();
        if (selected_flight != null) {
            buyTicketsPane.setVisible(true);
            paneFlights.setVisible(false);
        } else {
            buyTicketsPane.setVisible(false);
            paneFlights.setVisible(true);
        }
    }

    private IService service;

    private Stage loginStage;

    public void setStage(Stage stage) {
        this.loginStage = stage;
    }

    @FXML
    public void onLogoutButtonClicked() {
        logout();
        Stage currentStage = (Stage) logoutButton.getScene().getWindow();
        currentStage.close();
    }

    private Employee loggedUser;

    public void setService(IService service, Employee employee) {
        this.service = service;
        this.loggedUser = employee;
        loggedInUsernameLabel.setText("Logged in as: " + loggedUser.getUsername());
        try {
            allFlightObservableList.setAll((List<Flight>) service.getAllFlights());
        } catch (Exception e) {
            e.printStackTrace();
        }

    }

    @FXML
    public void onSearchButtonClicked() {
        String destination = destinationTextField.getText();
        String date = "";
        try {
            date = flightDatePicker.getValue().format(Constants.DATE_FORMATTER);
        } catch (Exception e) {
            logger.error(e);
        }
        initLists(destination, date);

    }

    @FXML
    public void onBackButtonClicked() {
        paneFlights.setVisible(true);
        buyTicketsPane.setVisible(false);
    }

    @FXML
    public void onBuyButtonClicked() {
        Flight selected_flight = flightsTableView.getSelectionModel().getSelectedItem();
        String touristName = touristNameTextField.getText();
        String address = addressTextField.getText();
        try {
            service.buyTicket(selected_flight.getId(), touristName, address);
        } catch (Exception e) {
            e.printStackTrace();
        }
        flightsTableView.getSelectionModel().clearSelection();
    }

    private void initLists(String destination, String date) {
        try {
            flightObservableList.setAll((List<Flight>) service.getFlights(destination, date));
        } catch (Exception e) {
            e.printStackTrace();
        }
        try {
            allFlightObservableList.setAll((List<Flight>) service.getAllFlights());
        } catch (Exception e) {
            e.printStackTrace();
        }


    }

    public void logout() {
        try {
            service.logout(loggedUser, this);
            loginStage.show();
        } catch (Exception e) {
            System.out.println("Logout error " + e);
        }
    }


}
