import pymongo
import datetime
from pymongo import MongoClient
from time import time
myclient =  MongoClient()
mydb = myclient["ADB"]


old_time = time()

mycol = mydb["dbo.Travel"]
TrlID =[]
myq = {"Feedback":{"$gt":0}}
for post in mycol.find(myq,{"TRID":1,"_id":0}) :
    TrlID.append(post.get('TRID'))



mycol=mydb["dbo.Trip"]
EmpID=[]
myq = {"TripID":{"$in": TrlID }}
for post in mycol.find(myq,{"SupervisorID":1,"_id":0}):
    EmpID.append(post.get('SupervisorID'))

mycol=mydb["dbo.Employee"]
res = []
myq={"$or":[{"EmployeeID": {"$in":EmpID }},{"Salary":{"$gt":500}}]}
for post in mycol.find(myq):
    res.append(post)

print(len(res))

now = time()
print("Time elapsed = sec", now - old_time)




