from pymongo import MongoClient
from time import time

import pyodbc
conn = pyodbc.connect('Driver={SQL Server};'
                      'Server=DESKTOP-2IAGPNL;'
                      'Database=ADB;'
                      'Trusted_Connection=yes;')


old_time = time()

cursor = conn.cursor()
cursor.execute('Select * from ADB.dbo.Member M where EXISTS ( select * from ADB.dbo.Travel T where M.MemberID=T.MEID and (T.Feedback>0 or EXISTS( select * from ADB.dbo.Trip Tr where T.TRID=Tr.TripID and Tr.Cost > 1500)));')
num=0
for row in cursor:
    num+=1
print(num)
now = time()
print("Time elapsed for Q1 = sec", now - old_time)



old_time = time()

cursor = conn.cursor()
cursor.execute('Select * from ADB.dbo.Member M where EXISTS ( select * from ADB.dbo.Participate P where M.MemberID=P.MEID and EXISTS( select * from ADB.dbo.Team T where P.TEID=T.TeamID and exists( select * from ADB.dbo.Compete C where C.TEID =T.TeamID and (C.Points>500 and (C.Standing<8000 or T.CoachID<100000)))));')
num=0
for row in cursor:
    num+=1
print(num)
now = time()
print("Time elapsed for Q2 = sec", now - old_time)




old_time = time()

cursor = conn.cursor()
cursor.execute('Select * from ADB.dbo.Employee E where EXISTS( select * from ADB.dbo.Trip T where E.EmployeeID=T.SupervisorID and EXISTS( select * from ADB.dbo.Travel Tr where T.TripID=Tr.TRID and (Tr.Feedback > 0 or E.Salary>500)));')
num=0
for row in cursor:
    num+=1
print(num)
now = time()
print("Time elapsed for Q3 = sec", now - old_time)


