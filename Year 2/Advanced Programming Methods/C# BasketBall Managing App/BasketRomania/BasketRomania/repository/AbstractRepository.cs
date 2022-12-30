using BasketRomania.domain;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BasketRomania.repository
{
    internal abstract class AbstractRepository<ID, E> : IRepository<ID, E> where E : Entity<ID>
    {
        private string filePath;
        public AbstractRepository(string filePath) { this.filePath = filePath; }

        public IEnumerable<E> GetAll()
        {
            throw new NotImplementedException();
        }
        public abstract void loadData(string filePath);

        public string testFunction() { return filePath; }

    }
}
