'''
Created on Dec 8, 2021

@author: Denis
'''
from infrastructure.repos import RepoPictura
from business.services import ServicePictura
from presentation.ui import Consola
from tests.tests import *

def main():
    
    repoPictura=RepoPictura("picturi.txt")
    srvPictura=ServicePictura(repoPictura)
    ui=Consola(srvPictura)
    ui.run()
    print("DA")
    
if __name__ == '__main__':
    #unittest.main(exit=False)
    main()