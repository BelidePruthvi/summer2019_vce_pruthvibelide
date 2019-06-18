from django.http import HttpResponse
from django.views import View
from newapp.models import *
from django.shortcuts import render
from django.contrib.auth.mixins import LoginRequiredMixin
from django.core.paginator import Paginator
from django.db.models import Sum,Count

class SeasonView(View):
    def get(self,request,*args,**kwargs):
        if kwargs:
            match=Match.objects.all().filter(season=kwargs['id'])
            seasons = Match.objects.distinct().values('season').order_by('season')
            paginator = Paginator(match, 8)
            page = request.GET.get('page')
            matches = paginator.get_page(page)

            return render(request, "seasons.html", {'matches': matches,'seasons':seasons, "season": kwargs['id']})

        match = Match.objects.all().filter(season=2019)
        paginator = Paginator(match, 8)
        page = request.GET.get('page')
        matches = paginator.get_page(page)
        seasons = Match.objects.distinct().values('season').order_by('season')
        return render(request, "seasons.html", {'matches': matches, 'seasons': seasons, "season": 2019})

class MatchView(View):
    def get(self,request,*args,**kwargs):

        i1bo1=Deliveries.objects.filter(match_id=kwargs['mid'],inning=1).exclude(player_dismissed=None).values('bowler').annotate(total=Count('bowler')).order_by('-total')[:3]
        i1ba1 = Deliveries.objects.filter(match_id=kwargs['mid'], inning=1).values(
            'batsman').annotate(total=Sum('batsman_runs')).values('batsman','total').order_by('-total')[:3]
        i1bo2 = Deliveries.objects.filter(match_id=kwargs['mid'], inning=2).exclude(player_dismissed=None).values(
            'bowler').annotate(total=Count('bowler')).order_by('-total')[:3]
        i1ba2 = Deliveries.objects.filter(match_id=kwargs['mid'], inning=2).values(
            'batsman').annotate(total=Sum('batsman_runs')).values('batsman', 'total').order_by('-total')[:3]

        match=Match.objects.all().filter(id=kwargs['mid'])
        print(match)
        temp1=Deliveries.objects.all().filter(match_id=kwargs['mid'],inning=1).aggregate(score=Sum('total_runs'),wickets=Count('player_dismissed'))
        temp2=Deliveries.objects.all().filter(match_id=kwargs['mid'],inning=2).aggregate(score=Sum('total_runs'),wickets=Count('player_dismissed'))
        deliveries1=Deliveries.objects.all().filter(match_id=kwargs['mid'],inning=1)#.aggregate(score=Sum('total_runs'),wickets=Count('player_dismissed'))
        deliveries2=Deliveries.objects.all().filter(match_id=kwargs['mid'],inning=2)#.aggregate(score=Sum('total_runs'),wickets=Count('player_dismissed'))
        return render(request, "deliveries.html", {'deliveries1': deliveries1,'deliveries2': deliveries2,'matches':match,
                      'temp1':temp1,'temp2':temp2,
                        'i1ba1':i1ba1,
                        'i1ba2': i1ba2,
                        'i1bo1': i1bo1,
                        'i1bo2':i1bo2
                        }
                      )

