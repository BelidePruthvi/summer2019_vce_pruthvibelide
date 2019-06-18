import os
import django
import openpyxl as xl
os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'appday.settings')
django.setup()
from newapp.models import *
from datetime import datetime

def storedata():
    workbook=xl.load_workbook(filename="matches.xlsx")
    worksheet=workbook['matches']
    flag=0
    for row in worksheet.rows:
        if flag==0:
            flag=1
            continue
        match=[cell.value for cell in row]
        c=Match(match_id=match[0],season=match[1],city=match[2],date=match[3],team1=match[4],team2=match[5],
                  toss_winner=match[6],toss_decision=match[7],result=match[8],dl_applied=match[9],
                  winner=match[10],win_by_runs=match[11],win_by_wickets=match[12],player_of_match=match[13],
                  venue=match[14],umpire1=match[15],umpire2=match[16],umpire3=match[17]
                  );
        c.save()

def storedata1():
        workbook = xl.load_workbook(filename="deliveries.xlsx")
        worksheet = workbook.active
        print("hello")
        flag = 0
        for row in worksheet.rows:

            if flag == 0:
                flag = 1
                continue
            deliveries = [cell.value for cell in row]
            c = Deliveries(inning=deliveries[1], batting_team=deliveries[2], bowling_team=deliveries[3],
                           over=deliveries[4], ball=deliveries[5], batsman=deliveries[6], non_striker=deliveries[7],
                           bowler=deliveries[8], is_super_over=deliveries[9], wide_runs=deliveries[10],
                           bye_runs=deliveries[11], legbye_runs=deliveries[12], noball_runs=deliveries[13],
                           penalty_runs=deliveries[14], batsman_runs=deliveries[15], extra_runs=deliveries[16],
                           total_runs=deliveries[17], player_dismissed=deliveries[18], dismissal_kind=deliveries[19],
                           fielder=deliveries[20], match=Match.objects.get(match_id=deliveries[0]));
            c.save()

#storedata()
storedata1()
