import socket
import hashlib
from Crypto.Cipher import DES
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

#take the message from the inbox and dec it and print the original message
def printmsg():
    global inbox,mode
    if len(inbox) != 0:
        msg = inbox.pop()
        print("recived msg is :",msg)
        if len(msg)<33:
            print("erorr msg is too short")
            return
        dec_msg = process(msg[:-33],mode)
        print("original text:", dec_msg)
        mac = msg[-32:].decode("cp437")
        print("recived mac:", mac)
        mymac=hmac(dec_msg, hkey)
        if mac == mymac:
            print("correct mac")
        else:
            print("Wrong MAC")

#if there are data put it into the inbox file
def rec():
    global mysocket,buff_size
    try:
        data = mysocket.recv(buff_size)
        if data:
            inbox.reverse()
            inbox.append(data)
            inbox.reverse()
    except:
        print("erorr in recive")

#close the connection
def close_conn():
    global mysocket
    mysocket.shutdown(socket.SHUT_RDWR)
    mysocket.close()


#decryption using ECB
def dec_ecb(txt,key,Bsize):
    mydec = DES.new(key, DES.MODE_ECB)
    i,final = 0,""
    while i < len(txt):
        block = txt[i:i + Bsize]
        i = i + Bsize
        final += (mydec.decrypt(block)).decode('cp437')
    return final

#decryption using CBC
def dec_cbc(txt,key,iv,Bsize):
    mydec = DES.new(key, DES.MODE_ECB)
    i, final = 0, ""
    while i < len(txt):
        block = txt[i:i + Bsize]
        i = i + Bsize
        temp = mydec.decrypt(block)
        temp = bytes(j ^ iv for j, iv in zip(temp, iv))
        final += temp.decode('cp437')
        iv = block
    return final

#decryption using CFB
def dec_cfb(txt,key,iv,Bsize):
    mydec = DES.new(key, DES.MODE_ECB)
    i, final = 0, ""
    while i < len(txt):
        block = txt[i:i + 1]
        i = i + 1
        temp = mydec.encrypt(iv)
        temp = bytes(j ^ k for j, k in zip(temp[:1], block))
        final += temp.decode('cp437')
        iv = iv[1:] + block
    return final

#decryption using CTR
def dec_ctr(txt,key,ctr,Bsize):
    mydec = DES.new(key, DES.MODE_ECB)
    i, final = 0, ""
    while i < len(txt):
        block = txt[i:i + Bsize]
        i = i + Bsize
        temp = mydec.encrypt(ctr)
        temp = bytes(j ^ k for j, k in zip(block, temp))
        final += temp.decode('cp437')
        ctr = (str(int(ctr.decode('cp437')) + 1).zfill(Bsize)).encode('cp437')
    return final

#main function that decide which mode to use
def process(txt,mode):
    global key,Bsize
    iv = "IGKLMNOP".encode("utf8")
    ctr = "00000001".encode("utf8")
    if mode == "ECB":
        return dec_ecb(txt,key,Bsize)
    elif mode == "CBC":
        return dec_cbc(txt,key,iv,Bsize)
    elif mode == "CFB":
        return dec_cfb(txt,key,iv,Bsize)
    elif mode == "CTR":
        return dec_ctr(txt,key,ctr,Bsize)
    else:
        print("invalid mode input return empty string")
        return ""


#config
key = "ABCDEFGH".encode("utf8")
iv = "IGKLMNOP".encode("utf8")
ctr = "00000008".encode("utf8")
Bsize = 8
hkey = "AAAAAAAA"

#trying to connect to the server
print("trying to connect")
inbox = []
port=5100
buff_size = 512
server="127.0.0.1"
mysocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = ('localhost', port)
mysocket.connect((server, port))
print("connection is success")

#send message to the server telling him that u r alive
data = ("Hello").encode("utf8")
mysocket.sendall(data)

#wait for config message
while(True):
    time.sleep(1)
    print("waiting for config msg")
    rec()
    if len(inbox) != 0:
        msg = inbox.pop()
        msg= msg.decode("cp437")
        print("recived msg is :", msg)
        res=msg.split()
        mode,key,hkey,Bsize=res[0],res[1],res[2],res[3]
        try:
            Bsize=int(Bsize)
        except:
            Bsize=8
        break
print("Key is:",key,"mode is",mode,"hkey is:",hkey,"and block size is :",Bsize)
key=key.encode("utf8")

#wait for the origianl message to decode
inbox=[]
finish=time.time()
while(True):
    time.sleep(1)
    print("waiting for new msg")
    rec()
    if (len(inbox) != 0):
        start = time.time()
        printmsg()
        end = time.time()
        total = end - start
        print("total time for only processes ",total)
    if(time.time()-finish>20):
        break


#close the connection and end the program
print("bye bye")
close_conn()



