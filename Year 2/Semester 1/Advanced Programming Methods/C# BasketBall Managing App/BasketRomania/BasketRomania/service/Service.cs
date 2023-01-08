using BasketRomania.domain;
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


        //cerinta 1
        public List<Jucator<ID>> getJucatoriPentruEchipa(string nume_echipa)
        {
            List<Jucator<ID>> jucatori = (List<Jucator<ID>>)jucatoriRepo.GetAll();
            List<Jucator<ID>> jucatoriPentruEchipa = new List<Jucator<ID>>();
            jucatoriPentruEchipa = jucatori.FindAll(x => x.Team.Nume.Equals(nume_echipa));
            return jucatoriPentruEchipa;

        }

        //cerinta 2

        public List<JucatorActiv<ID>> getJucatoriActiviPentruEchipaLaMeci(string nume_echipa, ID id_meci)
        {

            List<JucatorActiv<ID>> jucatoriActivi = (List<JucatorActiv<ID>>)jucatoriActiviRepo.GetAll();
            List<JucatorActiv<ID>>jucatoriPtEchipaLaMeci = new List<JucatorActiv<ID>>();

            Meci<ID> meci=meciRepo.findByID(id_meci);

            foreach(var jucator in jucatoriActivi)
            {
                if (jucator.IdMeci.Equals(id_meci) && jucatoriRepo.findByID(jucator.IdJucator).Team.Nume.Equals(nume_echipa))
                    jucatoriPtEchipaLaMeci.Add(jucator);
            }

            /*
            jucatoriPtEchipaLaMeci = jucatoriActivi.FindAll(
                jucator => jucator.IdMeci.Equals(id_meci) &&
                jucatoriRepo.findByID(jucator.IdJucator).Team.Nume.Equals(nume_echipa)
            );
            */

            return jucatoriPtEchipaLaMeci;

        }

        //cerinta 3

        public List<Meci<ID>> getMeciuriBetweenDates(string date1S, string date2S)
        {
            DateTime date1=DateTime.Parse(date1S);
            DateTime date2=DateTime.Parse(date2S);
            List<Meci<ID>> meciuri = (List<Meci<ID>>)meciRepo.GetAll();
            List<Meci<ID>> meciuriInPerioada = new List<Meci<ID>>();

            meciuriInPerioada=meciuri.FindAll(meci => date1.CompareTo(meci.Time)<=0 && date2.CompareTo(meci.Time)>=0);

            return meciuriInPerioada;

        }

        //cerinta 4
        public string getScorPentruMeci(ID idMeci)
        {
            Meci<ID> meci = meciRepo.findByID(idMeci);
            List<JucatorActiv<ID>> jucatoriActivi = (List<JucatorActiv<ID>>)jucatoriActiviRepo.GetAll();
            List<JucatorActiv<ID>> jucatoriInMeci=new List<JucatorActiv<ID>>();
            jucatoriInMeci = jucatoriActivi.FindAll(jucator => jucator.IdMeci.Equals(idMeci));

            Dictionary<string, int> scor = new Dictionary<string, int>();


            scor.Add(meci.Echipa1.Nume, 0);
            scor.Add(meci.Echipa2.Nume, 0);


            foreach(JucatorActiv<ID> jucator in jucatoriInMeci) {
                string numeEchipa = jucatoriRepo.findByID(jucator.IdJucator).Team.Nume;
                    scor[numeEchipa]+=jucator.NrPuncteInscrise;
                
            }

            string scor_string = scor.Keys.ToArray()[0] + "-" + scor.Keys.ToArray()[1] + " | ";
            foreach (string key in scor.Keys.ToArray())
            {
                scor_string+= scor[key].ToString()+" ";
            }
            scor_string+= "";
            //Console.WriteLine(scor_string);
            return scor_string;
        }

        public List<Echipa<ID>> getEchipe()
        {
            return (List<Echipa<ID>>)echipeRepo.GetAll();
        }
        public List<JucatorActiv<ID>> getJucatoriActivi()
        {
            return (List<JucatorActiv<ID>>)jucatoriActiviRepo.GetAll();
        }
        public List<Meci<ID>> getMeciuri()
        {
            return (List<Meci<ID>>)meciRepo.GetAll();
        }
        public List<Jucator<ID>> getJucatori()
        {
            return (List<Jucator<ID>>)jucatoriRepo.GetAll();
        }

    }
}
