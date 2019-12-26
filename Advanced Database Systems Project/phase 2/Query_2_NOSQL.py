import pymongo
from time import time
from pymongo import MongoClient
myclient =  MongoClient()
mydb = myclient["ADB"]


old_time = time()
mycol = mydb["dbo.Compete"]
TmID1=[]
myq={"Points":{"$gt":500},"Standing":{"$lt":8000}}
for post in mycol.find(myq,{"TEID":1,"_id":0}) :
    TmID1.append(post.get('TEID'))

TmID2=[]
myq={"Points":{"$gt":500}}
for post in mycol.find(myq,{"TEID":1,"_id":0}) :
    TmID2.append(post.get('TEID'))

mycol=mydb["dbo.Team"]
TmID=[]
myq = {"TeamID": {"$in":TmID2} }
for post in mycol.find(myq,{"TeamID":1,"_id":0}):
    TmID.append(post.get('TeamID'))

mycol=mydb["dbo.Participate"]
MeID=[]
myq={"TEID":{"$in": TmID}}
for post in mycol.find(myq,{"MEID":1,"_id":0}):
    MeID.append(post.get("MEID"))

print(len(MeID))
mycol=mydb["dbo.Member"]
res=[]
myq={"MemberID":{"$in": MeID[0:200000] }}
for post in mycol.find(myq):
    res.append(post)
myq={"MemberID":{"$in": MeID[200000:500000] }}
for post in mycol.find(myq):
    res.append(post)
myq={"MemberID":{"$in": MeID[500000:len(MeID)] }}
for post in mycol.find(myq):
    res.append(post)

print(len(res))

now = time()
print("Time elapsed = sec", now - old_time)

