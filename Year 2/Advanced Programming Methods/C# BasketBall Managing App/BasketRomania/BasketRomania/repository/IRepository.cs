using BasketRomania.domain;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BasketRomania.repository
{
    internal interface IRepository<ID, E> where E : Entity<ID>
    {
        IEnumerable<E> GetAll();
    }
}
