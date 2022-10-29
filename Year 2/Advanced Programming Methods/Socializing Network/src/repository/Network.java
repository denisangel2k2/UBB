package repository;

import domain.User;
import exceptions.NetworkException;
import utils.Constants;

import java.util.*;
import java.util.concurrent.atomic.AtomicInteger;

public class Network {
    private Map<Integer, List<Integer>> network = new HashMap();

    private void addUserToNetwork(User user) {
        network.put(user.getId(), new LinkedList<Integer>());
    }

    private boolean isThereFriendship(User u1, User u2){
        boolean sw = false;
        for (int identificator : network.get(u1.getId()))
            if (identificator == u2.getId())
                sw = true;

        return sw;

    }

    public void removeFriendship(User u1, User u2) throws NetworkException{
        if (network.containsKey(u1.getId()) && network.containsKey(u2.getId())) {
            if (isThereFriendship(u1, u2)) {
                var list=network.get(u1.getId());
                list.removeIf(integer -> integer==u2.getId());
                list=network.get(u2.getId());
                list.removeIf(integer -> integer==u1.getId());

            }
            else throw new NetworkException(Constants.NETWORK_NO_FRIENDSHIP);
        }

    }

    public void addFriendship(User u1, User u2) throws NetworkException {


        if (!network.containsKey(u1.getId()))
            addUserToNetwork(u1);

        if (!network.containsKey(u2.getId()))
            addUserToNetwork(u2);

        if (isThereFriendship(u1, u2))
            throw new NetworkException(Constants.NETWORK_EXISTS_FRIENDSHIP);

        network.get(u1.getId()).add(u2.getId());
        network.get(u2.getId()).add(u1.getId());
    }

    public List<Integer> mostSociableCommunity() {
        AtomicInteger maxLevel = new AtomicInteger(0);
        var community_indexes = getCommunities();
        int[] visited = new int[maxNode() + 1];
        Arrays.fill(visited, 0);
        int highestLevel = 0;
        int indexOfSociableCom = 0;
        for (int communityIndex : community_indexes.keySet()) {
            maxLevel.set(0);
            int node = community_indexes.get(communityIndex).get(0);
            longest_road(node, visited, 0, maxLevel);

            if (highestLevel < maxLevel.get()) {
                highestLevel = maxLevel.get();
                indexOfSociableCom = communityIndex;
            }
        }

        return community_indexes.get(indexOfSociableCom);
    }

    public int getNumberOfCommunities() {
        int community_number = 0;
        var indexes=getCommunityIndexes();
        for (int number : indexes){
            if (Arrays.stream(indexes).filter(value -> value==number).count()>1)
                community_number = Math.max(community_number, number);
        }
        return community_number;

    }

    private void longest_road(int node, int[] visited, int level, AtomicInteger maxLevel) {
        visited[node] = 1;
        maxLevel.set(Math.max(level, maxLevel.get()));
        for (int neighbor : network.get(node))
            if (visited[neighbor] == 0)
                longest_road(neighbor, visited, level + 1, maxLevel);

    }

    private void dfs_util(int node, int[] visited, int number) {
        visited[node] = number;
        for (int neighbor : network.get(node))
            if (visited[neighbor] == 0)
                dfs_util(neighbor, visited, number);
    }

    private int maxNode(){
        int size=1;
        for (int key : network.keySet())
            size=Math.max(size,key);
        return size;
    }
    private int[] getCommunityIndexes() {



        int visited[] = new int[maxNode()+1];
        Arrays.fill(visited, 0);
        int community_number = 0;
        for (int user : network.keySet())
            if (visited[user] == 0) {
                community_number++;
                dfs_util(user, visited, community_number);
            }
        return visited;
    }

    public HashMap<Integer, List<Integer>> getCommunities() {

        int[] comm_indexes = getCommunityIndexes();

        HashMap<Integer, List<Integer>> communities = new HashMap<>();
        for (int userId = 1; userId < comm_indexes.length; userId++) {
            if (comm_indexes[userId]!=0) {
                if (!communities.containsKey(comm_indexes[userId]))
                    communities.put(comm_indexes[userId], new LinkedList<Integer>());
                communities.get(comm_indexes[userId]).add(userId);
            }
        }
        return communities;

    }


}
