package repository;

import domain.Entity;
import exceptions.RepoException;
import utils.Constants;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import java.util.List;
import java.util.Optional;
import java.util.Vector;




public abstract class AbstractRepo<E extends Entity<Integer>> implements Repository<E>{
    private Vector<E> entities;
    private String filepath;


    public AbstractRepo(String _filepath) {
        entities=new Vector<>();
        filepath=_filepath;

    }
    protected abstract E extractEntity(String line);


    @Override
    public void loadData(){
        entities.clear();
        Path path=Paths.get(filepath);
        try{
            List<String> lines=Files.readAllLines(path);
            for (String line : lines)
            {
                E entity=extractEntity(line);
                entities.add(entity);
            }
        }
        catch (IOException ex){
            ex.printStackTrace();
        }
    }
    @Override
    public void storeData(){
        Path path=Paths.get(filepath);
        try{
            StringBuilder info=new StringBuilder();
            for (E entity : entities)
                info.append(entity.fileCsvPatternString());

            Files.writeString(path,info.toString());

        }
        catch (IOException ex){
            ex.printStackTrace();
        }

    }
    @Override
    public int size(){
        return entities.size();
    }
    @Override
    public void add(E obj) throws RepoException{
        loadData();
        Optional<E> optionalE = entities.stream().filter(entity ->entity.equals(obj)).findFirst();
        if (optionalE.isEmpty()) {
            entities.add(obj);
            storeData();
        }
        else throw new RepoException(Constants.REPO_ALREADY_EXISTS);
    }

    private E find(int id){
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
            entities.remove(entity);
            storeData();
            return entity;
        }
        else throw new RepoException(Constants.REPO_REMOVE_ENTITY);
    }

    @Override
    public E remove(E entity) throws Exception{


        Optional<E> optionalE=entities.stream().filter(_entity->_entity.equals(entity)).findFirst();
        if (!optionalE.isPresent())
            throw new RepoException(Constants.REPO_REMOVE_ENTITY);

        entities.remove(optionalE.get());


        storeData();
        return optionalE.get();

    }

    @Override
    public E findElement(int id) throws RepoException {
        E entity=find(id);
        if (entity==null)
            throw new RepoException(Constants.REPO_NO_ELEMENT_FOUND);
        return entity;
    }

    @Override
    public Vector<E> getAll() {
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


}
