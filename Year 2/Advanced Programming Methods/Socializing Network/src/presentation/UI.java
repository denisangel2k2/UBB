package presentation;

import domain.User;
import exceptions.NetworkException;
import exceptions.RepoException;
import service.Service;

import java.io.Console;
import java.util.Scanner;
import java.util.Vector;

public class UI {
    private Service service;
    private Scanner in = new Scanner(System.in);

    public UI(Service service) {
        this.service = service;
        showMenu();
    }

    public void run() {

        while (true) {
            System.out.println(">>>");
            String input = in.nextLine();
            if (input.equals("6")) showMenu();
            else if (input.equals("99")) System.exit(0);
            else if (input.equals("1")) add();
            else if (input.equals("2")) remove();
            else if (input.equals("3")) addFriendship();
            else if (input.equals("4")) removeFriendship();
            else if (input.equals("5")) showUsers();
            else if (input.equals("7")) numberOfCommunities();
            else if (input.equals("8")) mostSociableCommunity();
        }
    }

    private void showMenu() {
        System.out.println("1 - Add a user to the system");
        System.out.println("2 - Remove a user to the system");
        System.out.println("3 - Add a friendship to the system");
        System.out.println("4 - Remove a friendship from the system");
        System.out.println("5 - Show all users");
        System.out.println("6 - Show menu");
        System.out.println("7 - Number of communities");
        System.out.println("8 - Most sociable community");
        System.out.println("99 - Exit");


    }
    private void addFriendship(){
        showUsers();
        System.out.println("Select two users you want to have a friendship between by using their ids: ");
        System.out.println("ID 1: ");
        String id1String=in.nextLine();
        System.out.println("ID 2: ");
        String id2String=in.nextLine();

        try{
            int id1=Integer.parseInt(id1String);
            int id2=Integer.parseInt(id2String);
            service.addFriendship(id1,id2);
            System.out.println("Added friendship!");

        }
        catch (NumberFormatException nex){
            System.out.println("ID invalid!");
        }
        catch (NetworkException ex){
            System.out.println(ex.getMessage());
        }
        catch (RepoException ex){
            System.out.println(ex.getMessage());
        }
    }
    private void removeFriendship(){
        System.out.println("Select two users you want to remove a friendship between by using their ids: ");
        System.out.println("ID 1: ");
        String id1String=in.nextLine();
        System.out.println("ID 2: ");
        String id2String=in.nextLine();
        try{
            int id1=Integer.parseInt(id1String);
            int id2=Integer.parseInt(id2String);
            service.removeFriendship(id1,id2);
            System.out.println("Removed friendship!");

        }
        catch (NumberFormatException nex){
            System.out.println("ID invalid!");
        }
        catch (NetworkException ex){
            System.out.println(ex.getMessage());
        }
        catch (RepoException ex){
            System.out.println(ex.getMessage());
        }

    }
    private void numberOfCommunities(){
        System.out.println("There are "+Integer.toString(service.numberOfCommunities()) + " communities!");
    }
    private void mostSociableCommunity(){
        var community=service.mostSociableCommunity();
        System.out.println("Most sociable community is made of the following users:");
        for (User user : community)
            System.out.println(user.printPatternString());

    }
    private void showUsers() {
        for (User user : service.getAll())
            System.out.println(user.printPatternString());

    }
    private void remove(){
        showUsers();
        System.out.print("Input the ID of the user you want to remove: ");
        String idString = in.nextLine();

        try {
            int id=Integer.parseInt(idString);
            service.remove(id);
            System.out.println("Successfully removed!");
        }
        catch(NumberFormatException nex){
            System.out.println("ID invalid!");
        }
        catch (Exception ex){
            System.out.println(ex.getMessage());
        }
    }
    private void add() {
        System.out.print("First Name: ");
        String firstName = in.nextLine();
        System.out.print("Last Name: ");
        String lastName = in.nextLine();
        System.out.print("Email Name: ");
        String email = in.nextLine();

        try {
            service.add(firstName, lastName, email);
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
    }
}
