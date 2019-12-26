import pymongo
import datetime
from pymongo import MongoClient
from time import time
myclient =  MongoClient()
mydb = myclient["ADB"]


old_time = time()

mycol = mydb["dbo.Trip"]
TrpID=[]
myq={"Cost": {"$gt":1500}}
for post in mycol.find(myq,{ "TripID": 1,"_id": 0}) :
    TrpID.append(post.get('TripID'))

mycol=mydb["dbo.Travel"]
MeID=[]
myq={"$or":[{"TRID":{"$in": TrpID}},{"Feedback":{"$gt":0}}]}
for post in mycol.find(myq,{ "MEID": 1,"_id": 0}):
    MeID.append(post.get('MEID'))

mycol=mydb["dbo.Member"]
res=[]
myq={"MemberID":{"$in": MeID}}
for post in mycol.find(myq):
    res.append(post)
print(len(res))

now = time()
print("Time elapsed = sec", now - old_time)
