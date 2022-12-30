using BasketRomania.repository;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BasketRomania.service
{
    internal class Service<ID>
    {
        private MeciRepo<ID> meciRepo;
        private JucatoriRepo<ID> jucatoriRepo;
        private EchipeRepo<ID> echipeRepo;
        private JucatoriActiviRepo<ID> jucatoriActiviRepo;

        public Service(MeciRepo<ID> meciRepo, JucatoriRepo<ID> jucatoriRepo, EchipeRepo<ID> echipeRepo, JucatoriActiviRepo<ID> jucatoriActiviRepo)
        {
            this.meciRepo = meciRepo;
            this.jucatoriRepo = jucatoriRepo;
            this.echipeRepo = echipeRepo;
            this.jucatoriActiviRepo = jucatoriActiviRepo;
        }
        public ArrayList testFunction()
        {
            ArrayList filepaths = new ArrayList();
            filepaths.Add(meciRepo.testFunction());
            filepaths.Add(jucatoriRepo.testFunction());
            filepaths.Add(echipeRepo.testFunction());
            filepaths.Add(jucatoriActiviRepo.testFunction());

            return filepaths;
        }
    }
}
