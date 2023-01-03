using BasketRomania.domain;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BasketRomania.repository
{
    internal class JucatoriRepo<ID> : AbstractRepository<ID,Jucator<ID>>
    {
        private EchipeRepo<ID> echipeRepo;
        public JucatoriRepo(string filePath, EchipeRepo<ID> echipeRepo) : base(filePath) { 
            this.echipeRepo = echipeRepo;
            base.loadData(filePath);
        }

        public override Jucator<ID> extractEntity(string[] values)
        {
            ID id = (ID)Convert.ChangeType(values[0], typeof(ID));
            Echipa<ID> echipa = echipeRepo.findByName(values[3]);
            Jucator<ID> jucator=new Jucator<ID>(id, values[1], values[2],echipa);
            return jucator;
        }
    }
}
