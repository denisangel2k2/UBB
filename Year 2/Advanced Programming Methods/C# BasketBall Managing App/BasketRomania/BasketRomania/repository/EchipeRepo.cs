using BasketRomania.domain;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BasketRomania.repository
{
    internal class EchipeRepo<ID> : AbstractRepository<ID, Echipa<ID>>
    {
        public EchipeRepo(string filePath) : base(filePath) { }
        public override void loadData(string filePath)
        {
            throw new NotImplementedException();
        }
    }
}
