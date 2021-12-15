from presentation.ui import UI
from business.services import serviceParticipare, servicePersoane, serviceEvents
from validators.validate import validatorPersoane, validatorEvents
from infrastructure.repos import FileRepoParticipare, FileRepoEvents, repoParticipare, repoPersoane, repoEvents, FileRepoPersoane
from tests.Teste import *

def main():

    
    
        
    #t=Teste()sss
    #t.run()
    repPers=FileRepoPersoane("repoPersoane.txt")
    repEv=FileRepoEvents("repoEvent.txt")
    repPart=FileRepoParticipare("repoParticipare.txt") 
    valP=validatorPersoane()
    valE=validatorEvents()
    servP=servicePersoane(repPers,valP)
    servE=serviceEvents(repEv,valE)
    servPart=serviceParticipare(repPers,repEv,repPart,valE,valP)

    consola=UI(servP,servE,servPart)
    consola.run()
    
if __name__ == '__main__':
        #unittest.main(exit=False, failfast=True)
        main()




