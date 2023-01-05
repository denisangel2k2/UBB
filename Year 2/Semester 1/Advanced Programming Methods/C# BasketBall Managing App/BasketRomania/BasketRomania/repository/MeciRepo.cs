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
        private EchipeRepo<ID> echipeRepo;
        public MeciRepo(string filePath, EchipeRepo<ID> echipeRepo) : base(filePath) {
            this.echipeRepo = echipeRepo;
            base.loadData(filePath);
        }

        public override Meci<ID> extractEntity(string[] values)
        {
            ID id = (ID)Convert.ChangeType(values[0], typeof(ID));
            Echipa<ID> echipa1 = echipeRepo.findByName(values[1]);
            Echipa<ID> echipa2 = echipeRepo.findByName(values[2]);
            Meci<ID> meci = new Meci<ID>(id, echipa1, echipa2, DateTime.Parse(values[3]));
            return meci;
        }
    }
}
