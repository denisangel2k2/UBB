using BasketRomania.domain;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BasketRomania.repository
{
    internal class MeciRepo<ID> : AbstractRepository<ID,Meci<ID>>
    {
        public MeciRepo(string filePath) : base(filePath) { }
        public override void loadData(string filePath)
        {
            throw new NotImplementedException();
        }
    }
}
