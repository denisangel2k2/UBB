package com.socialnetwork.app.controllers;

import com.socialnetwork.app.domain.Friendship;
import com.socialnetwork.app.domain.User;
import com.socialnetwork.app.domain.UserDTOFriend;
import com.socialnetwork.app.service.AppService;
import com.socialnetwork.app.utils.Observer.Observer;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.AnchorPane;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class UserMainInterfaceController implements Observer {

    private ObservableList<User> usersList = FXCollections.observableArrayList();
    private ObservableList<UserDTOFriend> friendList = FXCollections.observableArrayList();

    private ObservableList<User> friendRequestsList = FXCollections.observableArrayList();
    private User loggedUser = null;
    @FXML
    public AnchorPane friendRequestsPane;
    @FXML
    public Button acceptFriendButton;
    @FXML
    public Button rejectFriendButton;

    @FXML
    public Button removeFriendButton;

    @FXML
    public Button addFriendshipButton;
    @FXML
    public TextField searchUserTextField;

    @FXML
    public Label connectedUserLabel;
    @FXML
    public Label emailUserLabel;
    @FXML
    public TableView<UserDTOFriend> friendsTableView;
    @FXML
    public ListView<User> friendRequestsListView;
    @FXML
    public TableView<User> usersTable;
    @FXML
    public TableColumn<UserDTOFriend, String> friendNameColumn;
    @FXML
    public TableColumn<UserDTOFriend, String> friendsSinceColumn;
    @FXML
    public TableColumn<User, String> firstNameColumn;
    @FXML
    public TableColumn<User, String> lastNameColumn;
    @FXML
    public TableColumn<User, String> emailColumn;

    AppService service;

    public void setService(AppService service) {

        this.service = service;
        this.service.addObserver(this);
        this.loggedUser = this.service.getAllUsers().get(0);

        connectedUserLabel.setText(loggedUser.getFirstName() + " " + loggedUser.getLastName());
        emailUserLabel.setText(loggedUser.getEmail());
        initLists();
    }

    private void initLists() {
        HashMap<User, String> friendsOfUser = service.getFriends(loggedUser.getId());

        List<UserDTOFriend> friendsTemp = new ArrayList<>();

        for (User user : friendsOfUser.keySet()) {
            UserDTOFriend friend = new UserDTOFriend(user, friendsOfUser.get(user));
            friendsTemp.add(friend);
        }
        List<User> friendReqTemp = new ArrayList<>();
        List<User> friendReqOfUsers = service.getFriendRequests(loggedUser.getId());
        for (User user : friendReqOfUsers) {
            friendReqTemp.add(user);
        }
        friendList.setAll(friendsTemp);
        friendRequestsList.setAll(friendReqTemp);

        List<User> allUsers = service.getAllUsers();
        List<User> allUsersTempList = new ArrayList<>();
        allUsersTempList = allUsers.stream()
                .filter(user -> user.getId() != loggedUser.getId())
                .collect(Collectors.toList());

        usersList.setAll(allUsersTempList);

    }

    @FXML
    public void onAcceptButton() {

        try {
            int id = friendRequestsListView.getSelectionModel().getSelectedItem().getId();
            service.addFriendship(loggedUser.getId(), id);
        } catch (Exception ex) {
            Alert alert = new Alert(Alert.AlertType.ERROR, ex.getMessage(), ButtonType.OK);
        }
    }

    @FXML
    public void onSearchUserTextField() {

    }

    @FXML
    public void initialize() {
        friendNameColumn.setCellValueFactory(new PropertyValueFactory<UserDTOFriend, String>("name_user"));
        friendsSinceColumn.setCellValueFactory(new PropertyValueFactory<UserDTOFriend, String>("friendsSince"));


        firstNameColumn.setCellValueFactory(new PropertyValueFactory<User, String>("firstName"));
        lastNameColumn.setCellValueFactory(new PropertyValueFactory<User, String>("lastName"));
        emailColumn.setCellValueFactory(new PropertyValueFactory<User, String>("email"));
        usersTable.setItems(usersList);

        friendRequestsListView.setItems(friendRequestsList);
        friendsTableView.setItems(friendList);


    }


    @Override
    public void update() {
        initLists();
    }

}
