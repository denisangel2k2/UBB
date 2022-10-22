import socket

HOST="127.0.0.1"
PORT=1111


with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
	s.connect((HOST,PORT))
	string=input("Introduceti string-ul: ").encode();
	s.sendall(string);
	c=input("Introduceti un carcater: ").encode();
	s.send(c);

	lgpoz=s.recv(2);
	poz=s.recv(1024);

	cnt=0
	l=[]
	for e in poz:
		if cnt==1 or e>0:
			l.append(e)
		cnt+=1

	print(l)


