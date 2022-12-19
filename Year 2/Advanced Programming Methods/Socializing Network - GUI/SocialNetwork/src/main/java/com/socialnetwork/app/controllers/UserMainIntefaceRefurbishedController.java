package com.socialnetwork.app.controllers;

import com.socialnetwork.app.Main;
import com.socialnetwork.app.domain.Message;
import com.socialnetwork.app.domain.MessageDTO;
import com.socialnetwork.app.domain.User;
import com.socialnetwork.app.domain.UserDTOFriend;
import com.socialnetwork.app.exceptions.RepoException;
import com.socialnetwork.app.service.AppService;
import com.socialnetwork.app.utils.Observer.Observer;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.stream.Collectors;

public class UserMainIntefaceRefurbishedController implements Observer {

    private ObservableList<User> usersList = FXCollections.observableArrayList();
    private ObservableList<UserDTOFriend> friendList = FXCollections.observableArrayList();
    private ObservableList<MessageDTO> messagesList = FXCollections.observableArrayList();

    private ObservableList<User> friendRequestsList = FXCollections.observableArrayList();
    private User loggedUser = null;
    @FXML
    private ImageView acceptFriendButton;

    @FXML
    private Label connectedUserLabel;

    @FXML
    private Button deleteAccountButton;

    @FXML
    private TableColumn<User, String> emailColumn;


    @FXML
    private TableColumn<UserDTOFriend, String> friendNameColumn;
    @FXML
    private TableColumn<UserDTOFriend, String> friendsSinceColumn;
    @FXML
    private Label emailUserLabel;

    @FXML
    private TableColumn<User, String> firstNameColumn;

    @FXML
    private VBox friendsPane;

    @FXML
    private TableView<UserDTOFriend> friendsTableView;
    @FXML
    private ListView<User> friendRequestsListView;

    @FXML
    private TableColumn<User, String> lastNameColumn;

    @FXML
    private VBox messagesListPane;

    @FXML
    private ImageView profileImageView;

    @FXML
    private ImageView rejectFriendButton;

    @FXML
    private Button removeFriendButton;

    @FXML
    private VBox searchPane;

    @FXML
    private TextField searchUserTextField;

    @FXML
    private VBox settingsPane;

    @FXML
    private TableView<User> usersTable;

    @FXML
    private ImageView settingsPaneButton;

    @FXML
    private ImageView usersPaneButton;

    @FXML
    private ImageView logoutButton;

    @FXML
    private ImageView messagesListPaneButton;

    @FXML
    private ImageView friendsPaneButton;

    @FXML
    private TableColumn<MessageDTO, String> messageToUserColumn;

    @FXML
    private TableColumn<MessageDTO, String> messageFromUserColumn;

    @FXML
    private TableView<MessageDTO> chatTable;

    @FXML
    private TextField messageTextField;

    @FXML
    private Button sendMessageButton;

    @FXML
    private ListView<UserDTOFriend> usersMessageList;

    @FXML
    private VBox chatPane;

    @FXML
    private Button refreshButton;

    private AppService service;


    @FXML
    public void onLogoutButtonAction() {
        FXMLLoader loader = new FXMLLoader(Main.class.getResource("LoginInterfaceView.fxml"));
        Scene scene;
        try {
            scene = new Scene(loader.load(), 286, 400);
        } catch (Exception ex) {
            ex.printStackTrace();
            return;
        }
        LoginInterfaceController controller = loader.getController();
        controller.setService(service);
        Stage currentStage = (Stage) deleteAccountButton.getScene().getWindow();

        Stage newStage = new Stage();
        newStage.setScene(scene);
        newStage.setResizable(false);
        newStage.setTitle("HI6");
        currentStage.close();
        newStage.show();
    }

    @FXML
    public void onRemoveAccountAction() {
        try {
            service.remove(loggedUser.getId());

            FXMLLoader loader = new FXMLLoader(Main.class.getResource("LoginInterfaceView.fxml"));
            Scene scene;
            try {
                scene = new Scene(loader.load(), 286, 400);
            } catch (Exception ex) {
                ex.printStackTrace();
                return;
            }
            LoginInterfaceController controller = loader.getController();
            controller.setService(service);
            Stage currentStage = (Stage) deleteAccountButton.getScene().getWindow();

            Stage newStage = new Stage();
            newStage.setScene(scene);
            newStage.setResizable(false);
            newStage.setTitle("HI6");
            currentStage.close();
            newStage.show();
        } catch (Exception ex) {
            ex.printStackTrace();
            Alert alert = new Alert(Alert.AlertType.ERROR, "No action finished!", ButtonType.OK);
        }
    }

    public void setService(AppService service, User user) {


        settingsPane.setVisible(true);
        this.service = service;
        this.service.addObserver(this);
        this.loggedUser = user;

        connectedUserLabel.setText(loggedUser.getFirstName() + " " + loggedUser.getLastName());
        emailUserLabel.setText(loggedUser.getEmail());
        profileImageView.setImage(new Image("https://i.imgur.com/DnozCSK.png"));
        initLists();
    }

    private void initLists() {
        HashMap<User, String> friendsOfUser = service.getFriends(loggedUser.getId());

        List<UserDTOFriend> friendsTemp = new ArrayList<>();


        List<User> friendReqTemp = new ArrayList<>();
        List<User> friendReqOfUsers = service.getFriendRequests(loggedUser.getId());
        for (User user : friendReqOfUsers) {
            friendReqTemp.add(user);
        }

        for (User user : friendsOfUser.keySet()) {
            UserDTOFriend friend = new UserDTOFriend(user, friendsOfUser.get(user));
            if (!friendReqTemp.contains(user))
                friendsTemp.add(friend);
        }
        friendList.setAll(friendsTemp);
        friendRequestsList.setAll(friendReqTemp);

        List<User> allUsers = service.getAllUsers();
        List<User> allUsersTempList = allUsers.stream()
                .filter(user -> user.getId() != loggedUser.getId())
                .collect(Collectors.toList());

        usersList.setAll(allUsersTempList);


    }

    @FXML
    public void onAcceptButton() {

        try {
            int id = friendRequestsListView.getSelectionModel().getSelectedItem().getId();
            service.addFriendship(loggedUser.getId(), id);
        } catch (NullPointerException npe) {
            Alert alert = new Alert(Alert.AlertType.WARNING, "No user selected!", ButtonType.OK);
            alert.show();
        } catch (Exception ex) {
            Alert alert = new Alert(Alert.AlertType.ERROR, ex.getMessage(), ButtonType.OK);
            alert.show();
        }
    }


    @FXML
    public void onRejectFriendrequestButton() {
        try {
            int userID = friendRequestsListView.getSelectionModel().getSelectedItem().getId();
            service.removeFriendship(loggedUser.getId(), userID);
        } catch (NullPointerException npe) {
            Alert alert = new Alert(Alert.AlertType.WARNING, "No user selected!", ButtonType.OK);
            alert.show();
        } catch (Exception ex) {
            Alert alert = new Alert(Alert.AlertType.ERROR, ex.getMessage(), ButtonType.OK);
            alert.show();
        }
    }

    @FXML
    public void onAddFriendButton() {
        try {
            User userToAskFriendship = usersTable.getSelectionModel().getSelectedItem();
            service.addFriendship(loggedUser.getId(), userToAskFriendship.getId());
            Alert alert = new Alert(Alert.AlertType.INFORMATION, "Sent friendrequest", ButtonType.OK);
            alert.show();

        } catch (NullPointerException npe) {
            Alert alert = new Alert(Alert.AlertType.WARNING, "No user selected!", ButtonType.OK);
            alert.show();
        } catch (Exception ex) {
            Alert alert = new Alert(Alert.AlertType.ERROR, ex.getMessage(), ButtonType.OK);
            alert.show();
        }

    }


    @FXML
    public void onRemoveFriendButton() {

        try {
            int friendID = friendsTableView.getSelectionModel().getSelectedItem().getUID();
            service.removeFriendship(friendID, loggedUser.getId());
        } catch (NullPointerException npe) {
            Alert alert = new Alert(Alert.AlertType.WARNING, "No friend selected!", ButtonType.OK);
            alert.show();
        } catch (Exception ex) {
            ex.printStackTrace();
            Alert alert = new Alert(Alert.AlertType.ERROR, ex.getMessage(), ButtonType.OK);
            alert.show();
        }
    }

    @FXML
    public void onSearchUserTextField() {
        List<User> users = service.getAllUsers();
        List<User> usersTemp = new ArrayList<>();
        for (User user : users) {
            String name = user.getFirstName() + " " + user.getLastName();
            if (name.startsWith(searchUserTextField.getText()) && user.getId() != loggedUser.getId())
                usersTemp.add(user);
        }
        usersList.setAll(usersTemp);
        usersTable.setItems(usersList);
    }


    @FXML
    public void initialize() {
        friendNameColumn.setCellValueFactory(new PropertyValueFactory<UserDTOFriend, String>("name_user"));
        friendsSinceColumn.setCellValueFactory(new PropertyValueFactory<UserDTOFriend, String>("friendsSince"));

        messageToUserColumn.setCellValueFactory(new PropertyValueFactory<MessageDTO, String>("toMessage"));
        messageFromUserColumn.setCellValueFactory(new PropertyValueFactory<MessageDTO, String>("fromMessage"));


        firstNameColumn.setCellValueFactory(new PropertyValueFactory<User, String>("firstName"));
        lastNameColumn.setCellValueFactory(new PropertyValueFactory<User, String>("lastName"));
        emailColumn.setCellValueFactory(new PropertyValueFactory<User, String>("email"));
        usersTable.setItems(usersList);

        friendRequestsListView.setItems(friendRequestsList);
        friendsTableView.setItems(friendList);

        usersMessageList.setItems(friendList);
        chatTable.setItems(messagesList);

        searchUserTextField.textProperty().addListener(o -> onSearchUserTextField());


    }


    @FXML
    public void onUserFromUserMessageListClick() {
        //make visibile pane
        chatPane.setVisible(true);
        int fromUserID = usersMessageList.getSelectionModel().getSelectedItem().getUID();

        User fromUser = service.findUserById(fromUserID);
        List<Message> messageList = service.getMessagesBetweenUsers(loggedUser.getId(), fromUserID);


        List<MessageDTO> messages = new ArrayList<>();
        for (Message message : messageList) {
            MessageDTO messageDTO;
            if (message.getSender().getId() == loggedUser.getId()) {
                messageDTO = new MessageDTO("", message.getMessage());
            } else {
                messageDTO = new MessageDTO(message.getMessage(), "");
            }
            messages.add(messageDTO);
        }

        messagesList.setAll(messages);


    }

    @FXML
    public void onSendMessageButton(){
        String messageText = messageTextField.getText();
        try{
            int id_receipentUser = usersMessageList.getSelectionModel().getSelectedItem().getUID();
            service.addMessage(loggedUser.getId(),id_receipentUser,messageText);


        }
        catch (RepoException ex){
            Alert alert=new Alert(Alert.AlertType.ERROR, ex.getMessage(),ButtonType.OK);
            alert.show();
        }
    }

    @Override
    public void update() {
        initLists();

    }

    @FXML
    private void onFriendsButton() {
        settingsPane.setVisible(false);
        chatPane.setVisible(false);
        friendsPane.setVisible(true);
        messagesListPane.setVisible(false);
        searchPane.setVisible(false);
    }

    @FXML
    private void onMessagesButton() {
        settingsPane.setVisible(false);
        chatPane.setVisible(false);
        friendsPane.setVisible(false);
        messagesListPane.setVisible(true);
        searchPane.setVisible(false);
    }

    @FXML
    private void onSearchButton() {
        settingsPane.setVisible(false);
        chatPane.setVisible(false);
        friendsPane.setVisible(false);
        messagesListPane.setVisible(false);
        searchPane.setVisible(true);
    }

    @FXML
    private void onSettingsButton() {
        settingsPane.setVisible(true);
        chatPane.setVisible(false);
        friendsPane.setVisible(false);
        messagesListPane.setVisible(false);
        searchPane.setVisible(false);
    }

}
