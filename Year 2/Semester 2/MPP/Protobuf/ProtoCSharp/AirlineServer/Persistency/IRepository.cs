using Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Persistency
{
    public interface IRepository<E> where E : Entity<int>
    {
        List<E> GetAll();
        E findById(int id);
        void add(E entity);

    }
}
