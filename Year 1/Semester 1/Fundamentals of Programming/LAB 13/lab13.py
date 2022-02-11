
def common_digit(a,b):
    if a==0 and b==0:
        return True
    else:
        if a==0:
            a, b= b, a
        while a!=0:
            n=b

            if a%10==n%10:
                return True

            while n!=0:
                if a%10==n%10:
                    return True
                n//=10
            a//=10

        return False

def valid(l):
    for i in range(len(l)-1):
        if common_digit(l[i], l[i+1])==False:
            return False
    
    if l!=sorted(l):
        return False

    '''if len(l)<2:
        for i in range(len(l)-1):
            if l[i]==l[len(l)-1]:
                return False'''
    
    
    for i in range(1,len(l)):
        if l[i-1]>l[i]:
            return False
        
    return True
    
def back_r(l,st,last, ind_last):
    
    if len(l)>2:
        print(l)
    l.append(-1)
    for i in range(last,len(st)):
        l[-1]=st[i]
        if valid(l)==True:
            if len(l)>1:
                if  i-ind_last==1: #l[len(l)-2]==st[i-1] and
                    back_r(l,st,last+1,i)
            else:
                back_r(l,st,last+1,i)
            
    l.pop()


    
def back_i(a):
    all_lists=[]
    for i in range(len(a)+1):
        for j in range(i,len(a)+1):
            if valid(a[i:j]):
                if len(a[i:j])>2:
                    all_lists.append(a[i:j])
    return all_lists
            
'''
def main1():
    n=int(input("n="))
    v=[]
    for i in range(n):
        x=int(input())
        v.append(x)
        
    cmd=int(input("1=Recursiv / 2=Iterativ: "))
    
    if cmd==1:

        back_r([], v, -1)
    elif cmd==2:
       l=back_i(v)
       for el in l:
           print(el)'''

def main():
    
    
    while(True):
        v=[]
        valide=True
        numere=input("\nIntroduceti numerele dorite: ")
        parts=numere.split(" ")
        for part in parts:
            try:
                x=int(part)
                v.append(x)
            except Exception:
                print("Nu ati introdus date valide!")
                valide=False
                break
        
        if valide:
            cmd=input("Cum doriti sa rezolvati problema: 1-Iterativ\t2-Recursiv\t3-Iesire: ")
            if cmd=="1":
                l=back_i(v)
                for el in l:
                    print (el)
                    
            elif cmd=="2":
                back_r([],v,0,-1)
                
            elif cmd=="3":
                return
        
        
        

main()
    
