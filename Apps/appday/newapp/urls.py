from django.urls import include, path
from rest_framework.authtoken import views
from newapp.views import SeasonView,MatchView

urlpatterns = [
    path('season/<int:id>',SeasonView.as_view(),name="season"),
    path('seasons',SeasonView.as_view(),name="seasons"),
    path('match/<int:mid>',MatchView.as_view(),name="match")
]