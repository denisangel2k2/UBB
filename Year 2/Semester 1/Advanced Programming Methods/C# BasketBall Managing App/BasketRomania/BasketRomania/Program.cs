
using BasketRomania.domain;
using BasketRomania.repository;
using BasketRomania.service;
using BasketRomania.ui;
using System;

class Application
{
    public static void Main(String[] args)
    {
        string filepathJucatori = "C:\\Users\\Denis\\Documents\\GitHub\\UBB\\Year 2\\Advanced Programming Methods\\C# BasketBall Managing App\\BasketRomania\\BasketRomania\\data\\jucatori.csv";
        string filepathJucatoriActivi = "C:\\Users\\Denis\\Documents\\GitHub\\UBB\\Year 2\\Advanced Programming Methods\\C# BasketBall Managing App\\BasketRomania\\BasketRomania\\data\\jucatoriActivi.csv";
        string filepathMeci = "C:\\Users\\Denis\\Documents\\GitHub\\UBB\\Year 2\\Advanced Programming Methods\\C# BasketBall Managing App\\BasketRomania\\BasketRomania\\data\\meciuri.csv";
        string filepathEchipe = "C:\\Users\\Denis\\Documents\\GitHub\\UBB\\Year 2\\Advanced Programming Methods\\C# BasketBall Managing App\\BasketRomania\\BasketRomania\\data\\echipe.csv";
        
        AbstractRepository<int, Echipa<int>> echipaRepo = new EchipeRepo<int>(filepathEchipe);
        AbstractRepository<int, Jucator<int>> jucatorRepo = new JucatoriRepo<int>(filepathJucatori,(EchipeRepo<int>)echipaRepo);
        AbstractRepository<int,Meci<int>> meciRepo = new MeciRepo<int>(filepathMeci, (EchipeRepo<int>)echipaRepo);
        AbstractRepository<int,JucatorActiv<int>> jucatorActivRepo = new JucatoriActiviRepo<int>(filepathJucatoriActivi);
        Service<int> service = new Service<int>((MeciRepo<int>)meciRepo, (JucatoriRepo<int>)jucatorRepo, (EchipeRepo<int>)echipaRepo, (JucatoriActiviRepo<int>)jucatorActivRepo);
        UI<int> ui = new UI<int>(service);

        service.getJucatoriPentruEchipa("Chicago Bulls");
        service.getJucatoriActiviPentruEchipaLaMeci("Chicago Bulls", 1);
        service.getScorPentruMeci(1);
        service.getMeciuriBetweenDates("31.12.2022", "04.01.2023");


    }
}