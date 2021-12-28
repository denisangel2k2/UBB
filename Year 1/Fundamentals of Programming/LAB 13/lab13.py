
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

def ok(k,st):

	for i in range(k):
		if st[i]==st[k]:
			return False

	if k==0:
		return True
	elif st[k-1]>st[k] or common_digit(st[k-1],st[k])==False:
		return False
	return True

def afis(st,k):
	for i in range (0,k):
		print (st[i],end=" ")
	print()

def back(k, v, st):
	for el in v:
		st[k]=el
		#print (st)
		if ok(k, st):
			if k<len(v)-1:
				if k>1:
					afis(st,k)
				back(k+1,v,st)


def main():
	v=[]

	n=int(input("Introduceti un numar: "))
	for i in range(n):
		x=int(input())
		v.append(x)

	s=[0]*len(v)
	back(0,v,s)



main()
