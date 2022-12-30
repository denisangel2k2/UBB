using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BasketRomania.domain
{
    internal class Entity<ID>
    {

        private ID id;
        public ID Id
        {
            get { return id; }
            set { id = value; }
        }
        public Entity(ID givenId) {
            id = givenId;
        }
    }
   
}
