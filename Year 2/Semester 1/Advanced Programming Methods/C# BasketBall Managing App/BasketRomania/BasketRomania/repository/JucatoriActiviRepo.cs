using BasketRomania.domain;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BasketRomania.repository
{
    internal class JucatoriActiviRepo<ID> : AbstractRepository<ID,JucatorActiv<ID>>
    {
        public JucatoriActiviRepo(string filePath) : base(filePath) {
            base.loadData(filePath);
        }

        public override JucatorActiv<ID> extractEntity(string[] values)
        {
            ID id = (ID)Convert.ChangeType(values[0], typeof(ID));
            ID idJucator = (ID)Convert.ChangeType(values[1], typeof(ID));
            ID idMeci = (ID)Convert.ChangeType(values[2], typeof(ID));
            int puncte = Convert.ToInt32(values[3]);
            JucatorActiv<ID> jucatorActiv = new JucatorActiv<ID>(id, idJucator, idMeci, puncte);
            jucatorActiv.Tip = values[4];
            return jucatorActiv;
        }

        
    }
}
