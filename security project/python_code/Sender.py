import socket
import hashlib
from Crypto.Cipher import DES
#from Crypto.Util.Padding import pad, unpad##
import time


#Message Authentication Code (MAC) generation algorithm
def hmac(txt, key):
	txt = txt.strip()
	block_size = 64
	i=block_size-len(key)
	if i <0:
		key = hashlib.sha1(key.encode()).hexdigest()
	elif i>0:
		while i>0:
			key += "A"
			i= i-1
	key = key.encode("utf8")
	key1,key2 = "",""
	for i in key:
		key1 = key1+(chr(i ^ 0xff))
		key2 = key2+(chr(i ^ 0x11))
	return hashlib.md5(key1.encode()+hashlib.md5(key2.encode()+txt.encode()).hexdigest().encode()).hexdigest()

#to end the connection between the 2 files
def close_conn():
	conn.shutdown(socket.SHUT_RDWR)
	conn.close()

#if the msg size can't divide into equal blocks we use this function to add empty string at the end
#until all blockes have the same size
def padding(txt, Bsize):
	i=len(txt) % Bsize
	if i != 0 :
		i = Bsize - i
		while i > 0:
			i , txt = i - 1 , txt + ' '
	return txt

#used for check for invalid input
def check(txt):
	for i in txt:
		if i==" ":
			return True
	return False

#encryption using ECB
def enc_ecb(txt,key,Bsize):
	txt = txt.encode("utf8")
	myenc = DES.new(key, DES.MODE_ECB)
	i, final = 0, ""
	while i < len(txt):
		block = txt[i:i + Bsize]
		i = i + Bsize
		final += (myenc.encrypt(block)).decode('cp437')
	return final

#encryption using CBC
def enc_cbc(txt,key,iv,Bsize):
	myenc = DES.new(key, DES.MODE_ECB)
	i, final = 0, ""
	while i < len(txt):
		block = txt[i:i + Bsize]
		i = i + Bsize
		temp = bytes(j ^ iv for j, iv in zip(block.encode('cp437'), iv))
		iv = myenc.encrypt(temp)
		final += iv.decode('cp437')
	return final

#encryption using CFB
def enc_cfb(txt,key,iv,Bsize):
	myenc = DES.new(key, DES.MODE_ECB)
	i, final = 0, ""
	while i < len(txt):
		block = txt[i:i + 1]
		i = i + 1
		temp = myenc.encrypt(iv)
		temp = bytes(j ^ k for j, k in zip(temp[:1], block.encode('cp437')))
		final += temp.decode('cp437')
		iv = iv[1:] + temp
	return final

#encryption using CTR
def enc_ctr(txt,key,ctr,Bsize):
	myenc = DES.new(key, DES.MODE_ECB)
	i, final = 0, ""
	while i < len(txt):
		block = txt[i:i + Bsize]
		i = i + Bsize
		temp = myenc.encrypt(ctr)
		temp = bytes(j ^ k for j, k in zip(block.encode('cp437'), temp))
		final += temp.decode('cp437')
		ctr = (str(int(ctr.decode('cp437')) + 1).zfill(Bsize)).encode('cp437')
	return final

#main function that decide which mode to use
def process(txt,mode):
	global key,Bsize
	txt = padding(txt, Bsize)
	iv = "IGKLMNOP".encode("utf8")
	ctr = "00000001".encode("utf8")
	if mode == "ECB":
		return enc_ecb(txt,key,Bsize)
	elif mode == "CBC":
		return enc_cbc(txt,key,iv,Bsize)
	elif mode == "CFB":
		return enc_cfb(txt,key,iv,Bsize)
	elif mode == "CTR":
		return enc_ctr(txt,key,ctr,Bsize)
	else:
		print("invalid mode input return empty string")
		return ""



#take input from the user
print("enter the msg")
msg=input()
print("for the next inputs add space will make it invalid inputs")
print("enter DES config only one of (ECB,CBC,CFB or CTR) , make sure that all letter are capital")
x =str(input())
mode = "ECB"
if x == "CBC":
	mode = "CBC"
elif x == "CFB":
	mode = "CFB"
elif x == "CTR":
	mode = "CTR"
elif x!="ECB":
	print("* Invalid input.. I choose ECB for u no need to thx me XD")
print("ur message is:",msg," and ur mode is: ", mode)

hkey = "AAAAAAAA"
key = "ABCDEFGH".encode("utf8")
iv = "IGKLMNOP".encode("utf8")
ctr = "00000008".encode("utf8")
Bsize = 8

print("enter the key for DES")
key=str(input())
if len(key) != 8 or check(key):
	key = "ABCDEFGH"
key=key.encode("utf8")
print("enter the hmac key ")
hkey=str(input())
if len(hkey)==0 or check(hkey) :
	hkey = "AAAAAAAA"
print("enter the Block size ")
Bsize=input()
try:
	Bsize = int(Bsize)
	if Bsize<0 or Bsize%8!=0:
		Bsize=8
except:
	Bsize = 8
print("Key is:",key,"mode is",mode,"hkey is:",hkey,"and block size is :",Bsize)

#start server
print("trying to connect with reciver")
inbox = []
port=5100
buff_size = 512
server="127.0.0.1"
mysocket = socket.socket()
mysocket.bind(('', port))
mysocket.listen(5)
conn, client_address = mysocket.accept()
print("connection is completed")

#wait until Receiver is alive (he will send "hello" when he is)
while(True):
	data = conn.recv(buff_size)
	if data:
		inbox.reverse()
		inbox.append(data)
		inbox.reverse()
		break

#now receiver is alive send to him the config message
temp = inbox.pop()
conn.sendall((mode+" "+key.decode("utf8")+" "+hkey+" "+str(Bsize)+" ").encode("cp437"))
time.sleep(3)


#send the original message
start=time.time()
buff=buff_size-10
num=int(len(msg)/buff)+1
msgs=[]
for i in range(0,num):
	msgs.append(msg[i:i+buff])

for i in msgs:
	final = process(i,mode)
	mac = hmac(i, hkey)
	print("sent: ",final, "mac:", mac)
	conn.sendall((final+" "+mac).encode("cp437"))

end= time.time()
total=end-start
print("total time for only processes (without connection and input time)",total)


time.sleep(5)

#end the program
close_conn()

print("bye bye")


