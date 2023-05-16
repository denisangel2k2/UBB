package airline.persistence;


import airline.model.Entity;

public interface IRepository<E extends Entity<Integer>>{
    Iterable<E> getAll();
    E findById(int id);
    void add(E entity);
}
