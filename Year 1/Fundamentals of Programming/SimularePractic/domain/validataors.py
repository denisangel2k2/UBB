from errors.erori import ValidError
class validatorJucator(object):
    def validateJucator(self, jucator):
        '''
        Functia valideaza un jucator
        @param jucator: jucator object
        @return: - 
        '''
        err=""
        if jucator.get_nume()=="":
            err+="Nume invalid!\n"
        
        if jucator.get_prenume()=="":
            err+="Prenume invalid!\n"
            
        if jucator.get_post()!="Pivot" and jucator.get_post()!="Fundas" and jucator.get_post()!="Extrema":
            err+="Post invalid!\n"
        if jucator.get_inaltime()<0:
            err+="Inaltime invalida!\n"
            
        if len(err)>0:
            raise ValidError(err)
        


