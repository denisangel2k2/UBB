
using BasketRomania.domain;
using BasketRomania.repository;
using BasketRomania.service;
using BasketRomania.ui;
using System;

class Application
{
    public static void Main(String[] args)
    {
        string filepathJucatori = "filepathJucatori";
        string filepathJucatoriActivi = "filepathJucatoriActivi";
        string filepathMeci = "filepathMeci";
        string filepathEchipe = "filepathEchipe";
        AbstractRepository<int,Jucator<int>> jucatorRepo = new JucatoriRepo<int>(filepathJucatori);
        AbstractRepository<int,Meci<int>> meciRepo = new MeciRepo<int>(filepathMeci);
        AbstractRepository<int,Echipa<int>> echipaRepo = new EchipeRepo<int>(filepathEchipe);
        AbstractRepository<int,JucatorActiv<int>> jucatorActivRepo = new JucatoriActiviRepo<int>(filepathJucatoriActivi);
        Service<int> service = new Service<int>((MeciRepo<int>)meciRepo, (JucatoriRepo<int>)jucatorRepo, (EchipeRepo<int>)echipaRepo, (JucatoriActiviRepo<int>)jucatorActivRepo);
        UI<int> ui = new UI<int>(service);


    }
}