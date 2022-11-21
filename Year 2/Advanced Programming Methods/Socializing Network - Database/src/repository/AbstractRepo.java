package repository;

import domain.Entity;
import exceptions.RepoException;
import utils.Constants;

import java.sql.*;
import java.util.LinkedList;
import java.util.List;
import java.util.Optional;
import java.util.Vector;




public abstract class AbstractRepo<E extends Entity<Integer>> implements Repository<E>{
    private List<E> entities;
    protected String url;
    protected String userName;
    protected String password;


    public AbstractRepo(String url, String userName, String password) {
        entities=new LinkedList<>();
        this.url = url;
        this.userName = userName;
        this.password = password;
    }

    protected abstract E extractEntity(String line);
    protected abstract List<E> extractEntity(ResultSet set) throws SQLException;

    protected abstract PreparedStatement ps_getAll(Connection connection) throws SQLException;
    @Override
    public void loadData(){
        entities.clear();
        try{
            Connection connection= DriverManager.getConnection(url,userName,password);
            PreparedStatement ps=ps_getAll(connection);
            ResultSet resultSet=ps.executeQuery();

            List<E> list=extractEntity(resultSet);
            list.forEach(entity->entities.add(entity));
        }
        catch (SQLException ex){
            ex.printStackTrace();
        }
    }

    /**
     * @param obj
     * @throws Exception
     */
    @Override
    public void update(E obj) throws RepoException {
        loadData();
        try {
            Connection connection=DriverManager.getConnection(url,userName,password);
            E entity=findElement(obj.getId());
            updateEntity(obj,connection);
            entity.set(obj);


        }
        catch (SQLException ex){
            throw new RepoException(Constants.REPO_DATABASE_ERROR);
        }
    }

    @Override
    public void storeData(){}
    protected abstract void storeEntity(E entity, Connection connection) throws SQLException;
    protected abstract void deleteEntity(E entity, Connection connection) throws SQLException;
    protected abstract void updateEntity(E entity, Connection connection) throws SQLException;

    @Override
    public void add(E obj) throws RepoException{
        loadData();
        Optional<E> optionalE = entities.stream().filter(entity ->entity.equals(obj)).findFirst();
        if (optionalE.isEmpty()) {
            try{
                Connection connection=DriverManager.getConnection(url,userName,password);
                storeEntity(obj,connection);
                entities.add(obj);
            }
            catch (SQLException ex){
                ex.getStackTrace();
                throw new RepoException(Constants.REPO_DATABASE_ERROR);
            }
        }
        else throw new RepoException(Constants.REPO_ALREADY_EXISTS);
    }

    private E find(int id){

        //loadData();
        Optional<E> optionalEntities=entities.stream()
                .filter(entity -> entity.getId()==id)
                .findFirst();
        if (optionalEntities.isPresent())
            return optionalEntities.get();
        else return null;
    }


    @Override
    public E remove(int id) throws Exception {
        loadData();
        E entity=find(id);
        if (entity!=null){
            try {
                Connection connection=DriverManager.getConnection(url,userName,password);
                deleteEntity(entity,connection);
                entities.remove(entity);

            }
            catch (SQLException ex){
                ex.printStackTrace();
                throw new RepoException(Constants.REPO_DATABASE_ERROR);
            }
            return entity;
        }
        else throw new RepoException(Constants.REPO_REMOVE_ENTITY);
    }

    @Override
    public E remove(E entity) throws Exception{

        loadData();
        Optional<E> optionalE=entities.stream().filter(_entity->_entity.equals(entity)).findFirst();
        if (!optionalE.isPresent())
            throw new RepoException(Constants.REPO_REMOVE_ENTITY);

        try {
            Connection connection=DriverManager.getConnection(url,userName,password);
            deleteEntity(optionalE.get(), connection);
            entities.remove(optionalE.get());
        }
        catch (SQLException ex){
            ex.printStackTrace();
            throw new RepoException(Constants.REPO_DATABASE_ERROR);
        }

        return optionalE.get();

    }

    @Override
    public E findElement(int id) throws RepoException {
        loadData();
        E entity=find(id);
        if (entity==null)
            throw new RepoException(Constants.REPO_NO_ELEMENT_FOUND);
        return entity;
    }

    @Override
    public List<E> getAll() {
        return entities;
    }

    @Override
    public int getLastID() {

        int ID = -1;
        for (Entity entity : entities)
            ID = Math.max(ID, (Integer)entity.getId());
        if (ID == -1) return 1;
        else return ID;
    }

    /**
     * @return
     */
    @Override
    public int size() {
        return entities.size();
    }
}
